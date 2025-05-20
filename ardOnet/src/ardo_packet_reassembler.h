/**
 * @file ardo_packet_reassembler.h
 * @brief Application-level UDP packet fragmentation and reassembly
 * 
 * This file implements a robust solution for UDP packet fragmentation and reassembly
 * since the ESP32 (and many embedded platforms) do not support IP fragmentation at
 * the network layer by default.
 * 
 * Key features:
 * - Supports multiple in-flight fragmented packets simultaneously
 * - Uses bitmap tracking to efficiently manage out-of-order fragment arrival
 * - Includes CRC-based packet identification
 * - Handles packet boundaries and corruption detection
 * - Automatic LRU (least recently used) buffer management
 * 
 * Main components:
 * - PacketReassembler: Core reassembly logic for a single packet
 * - PacketReassemblerManager: Manages multiple reassemblers
 * - FragmentReceiver: Handles incoming fragments
 * - FragmentSender: Fragments outgoing packets
 * 
 * Usage example:
 *   FragmentReceiver<4, 8> receiver; // Support 4 packets in flight, max 8 fragments each
 *   FragmentSender<8> sender;        // Support packets requiring up to 8 fragments
 *   
 *   // When sending data:
 *   sender.send(data, length, [](const uint8_t* data, uint32_t length) {
 *     udp.send(data, length);
 *   });
 *   
 *   // When receiving data:
 *   receiver.receive(remoteIp, remotePort, data, length, 
 *     [](const uint8_t* data, uint32_t length) {
 *       // Process the reassembled packet
 *     });
 */

#ifndef ARDO_PACKET_REASSEMBLER__H
#define ARDO_PACKET_REASSEMBLER__H


#include <cstdint>
#include <cstring>
#include <array>
#include <functional>

namespace ardo {

struct HeaderContainer {
  std::uint8_t header[4];

  bool operator==(const HeaderContainer& rhs) const {
    return 0 == std::memcmp(header, rhs.header, sizeof(header));
  }

  bool operator!=(const HeaderContainer& rhs) const {
    return !(*this == rhs);
  }
};

struct FragmentHeaderContainer {
  const HeaderContainer header_container{ {
      uint8_t('\x0f'), uint8_t('r'), uint8_t('\xaa'), uint8_t('G') } };

  bool operator==(const FragmentHeaderContainer& rhs) const {
    return header_container == rhs.header_container;
  }

  bool operator!=(const FragmentHeaderContainer& rhs) const {
    return !(*this == rhs);
  }
};


/// Context for defragmentation of a single packet.
template <std::uint32_t w_MaxFragmentCount, std::uint32_t w_FragmentSize = 256>
class PacketReassembler {
public:
  using BitmapType = std::uint32_t;

  constexpr static std::uint32_t MAX_FRAGMENT_COUNT = w_MaxFragmentCount;
  constexpr static std::uint32_t FRAGMENT_SIZE = w_FragmentSize;
  constexpr static std::uint32_t MAX_PACKET_SIZE = MAX_FRAGMENT_COUNT * FRAGMENT_SIZE;
  constexpr static std::uint32_t LIMIT_MAX_FRAGMENT_COUNT = 8 * sizeof(BitmapType);

  static_assert(
    MAX_FRAGMENT_COUNT <= LIMIT_MAX_FRAGMENT_COUNT,
    "Can't handle so many fragments.");

  /// A packet ID provided by the fragmenter.
  struct StreamSequenceId {
    std::uint8_t stream_sequence[8];

    bool operator==(const StreamSequenceId& rhs) const {
      return 0 == ::memcmp(
        stream_sequence, rhs.stream_sequence, sizeof(stream_sequence));
    }
  };

  /// Fragment packet layout.
  struct Fragment {
    FragmentHeaderContainer fragment_header; // Should contain '#FRG'.
    StreamSequenceId stream_sequence_id;
    std::uint8_t fragment_index;      // The index of this fragment.
    std::uint8_t fragment_max_index;  // The index of the last fragment;
    std::uint8_t payload[FRAGMENT_SIZE];
  };

  static std::uint32_t min_frag_size() {
    return offsetof(Fragment, payload);
  }

  enum ReassemblerState {
    CLEAR = 0,
    PARTIAL = 1,
    COMPLETE = 2
  };

  /// Overall fragmented packet sequence state.
  struct PacketSequencer {
    std::uint32_t packet_sequence_gen;
  };

  /// Processing state across reassemblers.
  struct ConsumeStatus {
    PacketReassembler* most_eligible_node{};
  };

  ReassemblerState state = CLEAR;
  IPAddress remoteIp;
  StreamSequenceId stream_sequence_id;
  std::uint16_t current_length;
  std::uint16_t remotePort;
  std::uint32_t packet_sequence;
  BitmapType outstanding_bitmap;
  std::uint32_t fragment_max_index;
  std::uint8_t payload[MAX_PACKET_SIZE];

  /// Take over this reassembler with a new fragment.
  void start_new_packet(
    IPAddress remoteIp,
    std::uint16_t remotePort,
    std::uint8_t fragment_max_index
  ) {
    state = PARTIAL;
    this->remoteIp = remoteIp;
    this->remotePort = remotePort;
    this->fragment_max_index = fragment_max_index;

    // Need to set mask bits that need cleaing.
    auto shift_count = fragment_max_index + 1;
    auto is_at_limit = LIMIT_MAX_FRAGMENT_COUNT == shift_count;
    this->outstanding_bitmap = is_at_limit ? ~0u : (1 << shift_count) - 1;
  }

  /// Unsets the outstanding bit and returns true if the bitmap transitions to zero
  /// which indicates the packet is complete.
  bool unset_outstanding_bit(std::uint8_t bit) {
    // The bitmap is already finished. Don't do it twice.
    if (outstanding_bitmap == 0) {
      return false;
    }

    outstanding_bitmap &= ~(1 << bit);
    if (outstanding_bitmap == 0) {
      state = COMPLETE;
      return true;
    }
    state = PARTIAL;
    return false;
  }

  /// Applies a new fragment to this reassembler and returns true if the 
  /// packet transitions to complete.
  bool apply_fragment(
    const Fragment*& fragment,
    const PacketSequencer& packet_sequencer,
    const std::uint16_t length) {

    packet_sequence = packet_sequencer.packet_sequence_gen;
    auto offset = FRAGMENT_SIZE * fragment->fragment_index;
    auto fragment_payload_len = length - min_frag_size();
    std::memcpy(payload + offset, fragment->payload, fragment_payload_len);
    
    if (fragment->fragment_max_index == fragment->fragment_index) {
      current_length = offset + fragment_payload_len;
    }

    return unset_outstanding_bit(fragment->fragment_index);
  }

  /// Force consume this fragment. If a previous packet was being reassembled
  /// is it discarded.
  /// Returns true if the packet is fully reassembled (a single fragment packet).
  bool consume(
    const PacketSequencer& packet_sequencer,
    const IPAddress& remoteIp,
    std::uint16_t remotePort,
    const std::uint8_t* data,
    const std::uint16_t length) {

    const Fragment* fragment = reinterpret_cast<const Fragment*>(data);
    start_new_packet(remoteIp, remotePort, fragment->fragment_max_index);
    this->stream_sequence_id = fragment->stream_sequence_id;

    return apply_fragment(fragment, packet_sequencer, length);
  }

  enum MaybeConsumeResult {
    NOT_CONSUMED,
    NOT_CONSUMED_POSSIBLE_REPEAT,
    CONSUMED_INCOMPLETE,
    CONSUMED_AND_COMPLETE
  };

  /// Return true if the packet was used.
  MaybeConsumeResult maybe_consume(
    ConsumeStatus& status,
    const PacketSequencer& packet_sequencer,
    const IPAddress& remoteIp,
    std::uint16_t remotePort,
    const std::uint8_t* data,
    const std::uint16_t length) {

    if (state == CLEAR) {
      pick_most_eligible(status, packet_sequencer);
      return NOT_CONSUMED;
    }

    const Fragment* fragment = reinterpret_cast<const Fragment*>(data);

    if (packet_matches(remoteIp, remotePort, fragment->stream_sequence_id)) {
      if (state == COMPLETE) { // Not resending same data.
        return NOT_CONSUMED_POSSIBLE_REPEAT;
      }
      auto result = apply_fragment(fragment, packet_sequencer, length);
      return result ? CONSUMED_AND_COMPLETE : CONSUMED_INCOMPLETE;
    }

    pick_most_eligible(status, packet_sequencer);
    return NOT_CONSUMED;
  }

  // Returns true if the packet has the same source and sequence.
  bool packet_matches(
    const IPAddress& remoteIp,
    std::uint16_t remotePort,
    const StreamSequenceId& stream_sequence_id) const {
    return remoteIp == this->remoteIp
      && remotePort == this->remotePort
      && stream_sequence_id == this->stream_sequence_id;
  }

  bool contains_undelivered_data() {
    return state == PARTIAL;
  }

  /// Decides if this or the currently most eligible node is more appropriate for reaping.
  /// If the packed has no undelivered data, then it is selected unless the currently 
  /// "most eligible node" also has no undelivered data. Otherwise, the least recently 
  /// used reassembler is used.
  void pick_most_eligible(ConsumeStatus& status, const PacketSequencer& packet_sequencer) {
    if (status.most_eligible_node) {
      if (!status.most_eligible_node->contains_undelivered_data()) {
        // The currently selected assembler already is ready for re-use.
        return;
      }
      if (!contains_undelivered_data()) {
        // This assembler contains nothing.
        status.most_eligible_node = this;
        return;
      }
      if (status.most_eligible_node->packet_sequence > packet_sequence) {
        status.most_eligible_node = this;
      }
    } else {
      // By default this is more eligible than null.
      status.most_eligible_node = this;
    }
  }

};

template <
    std::uint32_t w_InFlightPacketCount,
    std::uint32_t w_MaxFragmentCount,
    std::uint32_t w_FragmentSize = 256>
class PacketReassemblerManager {
 public:
  constexpr static std::uint32_t IN_FLIGHT_PACKET_COUNT = w_InFlightPacketCount;
  constexpr static std::uint32_t MAX_FRAGMENT_COUNT = w_MaxFragmentCount;
  constexpr static std::uint32_t FRAGMENT_SIZE = w_FragmentSize;
  constexpr static std::uint32_t MAX_PACKET_SIZE = MAX_FRAGMENT_COUNT * FRAGMENT_SIZE;

  using Reassembler = PacketReassembler<MAX_FRAGMENT_COUNT, FRAGMENT_SIZE>;
  using ConsumeStatus = typename Reassembler::ConsumeStatus;
  using PacketSequencer = typename  Reassembler::PacketSequencer;
  using Fragment = typename  Reassembler::Fragment;

  // A PacketReassembler is returned if the packet is completed.
  Reassembler* consume_fragment_packet(
    const IPAddress& remoteIp,
    std::uint16_t remotePort,
    const std::uint8_t* data,
    const std::uint16_t length) {

    if (length < Reassembler::min_frag_size() || length > MAX_PACKET_SIZE + Reassembler::min_frag_size()) {
      error_malformed_packet++;
      return nullptr;  // Bad fragment.
    }

    auto* const fragment = reinterpret_cast<const Fragment*>(data);

    // Sanitity check on the packet index info.
    if (fragment->fragment_index >= MAX_FRAGMENT_COUNT
      || fragment->fragment_max_index >= MAX_FRAGMENT_COUNT
      || fragment->fragment_index > fragment->fragment_max_index) {
      // Bad data - drop it.
      error_malformed_packet++;
      return nullptr;
    }

    // All except the last packet must be a full packet.
    if (fragment->fragment_max_index != fragment->fragment_index
      && sizeof(Fragment) != length) {
      // Bad data - drop it.
      error_malformed_packet++;
      return nullptr;
    }

    ConsumeStatus status{};
    // Packets with more recent fragments are more important.
    packet_sequencer.packet_sequence_gen++;

    for (auto& packet_reassembler : packet_Reassemblers) {
      auto result = packet_reassembler.maybe_consume(
        status,
        packet_sequencer,
        remoteIp,
        remotePort,
        data,
        length);
      switch (result) {
        default:
        case Reassembler::NOT_CONSUMED: {
          // Try to consume it in the next assembler.
          break;
        }
        case Reassembler::NOT_CONSUMED_POSSIBLE_REPEAT:
        case Reassembler::CONSUMED_INCOMPLETE: {
          return nullptr;
        }
        case Reassembler::CONSUMED_AND_COMPLETE: {
          return &packet_reassembler;
        }
      }
    }

    auto* packet_reassembler = status.most_eligible_node;
    if (packet_reassembler->consume(
      packet_sequencer,
      remoteIp,
      remotePort,
      data,
      length)) {
      // Packet got completed.
      return packet_reassembler;
    }

    // The fragment was consumed but not
    return nullptr;
  }

  std::uint32_t error_malformed_packet{};
  PacketSequencer packet_sequencer{};
  std::array<Reassembler, IN_FLIGHT_PACKET_COUNT> packet_Reassemblers{};
};

template <
  std::uint32_t w_InFlightPacketCount,
  std::uint32_t w_MaxFragmentCount,
  std::uint32_t w_FragmentSize = 256>
  class FragmentReceiver {
  public:
    constexpr static std::uint32_t IN_FLIGHT_PACKET_COUNT = w_InFlightPacketCount;
    constexpr static std::uint32_t MAX_FRAGMENT_COUNT = w_MaxFragmentCount;
    constexpr static std::uint32_t FRAGMENT_SIZE = w_FragmentSize;
    constexpr static std::uint32_t MAX_PACKET_SIZE = MAX_FRAGMENT_COUNT * FRAGMENT_SIZE;

    using ReceiverFunc = std::function<void(const uint8_t* data, std::uint32_t length)>;

    using ReassemblerManager = PacketReassemblerManager<
      IN_FLIGHT_PACKET_COUNT, MAX_FRAGMENT_COUNT, FRAGMENT_SIZE>;
    using Reassembler = typename ReassemblerManager::Reassembler;

    void receive(const IPAddress& remoteIp,
                std::uint16_t remotePort, 
                const uint8_t* data, 
                std::uint32_t length, 
                const ReceiverFunc& receiver) {
      if (length < sizeof(FragmentHeaderContainer)) {
        receiver(data, length);
        return;
      }

      const FragmentHeaderContainer* header = reinterpret_cast<const FragmentHeaderContainer*>(data);

      if (*header != FragmentHeaderContainer{}) {
        // This is not a fragment packet.
        receiver(data, length);
        return;
      }

      auto reassembler = reassembler_manager.consume_fragment_packet(
        remoteIp, remotePort, data, length);

      if (reassembler) {
        receiver(reassembler->payload, reassembler->current_length);
      }
    }

    ReassemblerManager reassembler_manager{};
};


template <
  std::uint32_t w_MaxFragmentCount,
  std::uint32_t w_FragmentSize = 256>
class FragmentSender {
 public:

   constexpr static std::uint32_t MAX_FRAGMENT_COUNT = w_MaxFragmentCount;
   constexpr static std::uint32_t FRAGMENT_SIZE = w_FragmentSize;
   constexpr static std::uint32_t MAX_PACKET_SIZE = MAX_FRAGMENT_COUNT * FRAGMENT_SIZE;

   using SenderFunc = std::function<void(const uint8_t* data, std::uint32_t length)>;
   using Reassembler = PacketReassembler<MAX_FRAGMENT_COUNT, FRAGMENT_SIZE>;
   using Fragment = typename Reassembler::Fragment;
   using StreamSequenceId = typename Reassembler::StreamSequenceId;


   /* CRC-32C (iSCSI) polynomial in reversed bit order. */
   constexpr static std::uint32_t POLY = 0x82f63b78;

   /* CRC-32 (Ethernet, ZIP, etc.) polynomial in reversed bit order. */
   /* #define POLY 0xedb88320 */

   // crc32c lifted from https://stackoverflow.com/questions/27939882/fast-crc-algorithm
   static std::uint32_t crc32c(std::uint32_t crc, const std::uint8_t* data, std::uint32_t length)
   {
     crc = ~crc;
     while (length--) {
       crc ^= *data++;
       for (std::uint8_t k = 0; k < 8; k++)
         crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
     }
     return ~crc;
   }

   /// If fragmentation is required this sends resulting packets to the sender 
   /// function. Returns false if the packet was too large.
   bool send(
     const std::uint8_t* data,
     const std::uint16_t length,
     const SenderFunc& sender) {

     if (length > MAX_PACKET_SIZE) {
       return false;
     }

     if (length <= FRAGMENT_SIZE) {
       sender(data, length);
       return true;
     }

     auto crc = crc32c(0, data, length);
     sequence_number++;
     Fragment fragment;
     fragment.stream_sequence_id = StreamSequenceId{ {
         crc & 0xff,
         (crc >> 8) & 0xff,
         (crc >> 16) & 0xff,
         (crc >> 24) & 0xff,
         sequence_number & 0xff,
         (sequence_number >> 8) & 0xff,
         (sequence_number >> 16) & 0xff,
         (sequence_number >> 24) & 0xff,
       } };

     fragment.fragment_max_index = (length - 1) / FRAGMENT_SIZE;

     for (std::uint32_t i = 0, start = 0, end = FRAGMENT_SIZE; 
         start < length; 
         start = end, end += FRAGMENT_SIZE, ++i) {

       fragment.fragment_index = i;
       auto size = end > length ? length - start : FRAGMENT_SIZE;
       std::memmove(fragment.payload, data + start, size);
       std::uint8_t* frag_data = reinterpret_cast<std::uint8_t*>(&fragment);
       auto frag_length = (fragment.payload + size) - frag_data;
       sender(frag_data, frag_length);
     }
     return true;
   }

   std::uint32_t sequence_number{};
};

}

#endif // ARDO_PACKET_REASSEMBLER__H