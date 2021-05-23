// PaketReassembler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ardo_packet_reassembler.h"

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <random>
#include <iterator>
#include <algorithm>
#include <set>


void print_out(std::ostream& outs) {
  // Called by templat print_out<T...>
  outs << ".";
}

template <typename T, typename...P>
void print_out(std::ostream& outs, const T& value, P...ps) {
  outs << value;
  if (sizeof...(P)) {
    outs << ' ';
  }
  print_out(outs, ps...);
}

template <typename...P>
std::string print_to_str(P...ps) {
  std::ostringstream souts;
  print_out(souts, ps...);
  return souts.str();
}

class TestException : public std::string {
public:
  template <typename...T>
  TestException(T...v) : std::string(print_to_str(v...)) {}
};

template <typename FillType, std::uint16_t SIZE, FillType FILL= FillType(SIZE)>
struct TestPayload {
  ardo::HeaderContainer header{ {65u, 66u, 67u, 68u} };

  std::uint8_t payload[sizeof(FillType) * SIZE];

  TestPayload() {
    FillType* data{ reinterpret_cast<FillType*>(payload) };
    for (int i = 0; i < SIZE; ++i) {
      data[i] = FillType(FILL + i);
    }
  }

  bool operator==(const TestPayload& rhs) const {
    return header == rhs.header 
      && 0 == std::memcmp(payload, rhs.payload, sizeof(payload));
  }

  bool operator!=(const TestPayload& rhs) const {
    return !(*this == rhs);
  }
};

template <typename FillType, std::uint16_t...SIZES>
struct TestPayloadSelector;

template <typename FillType>
struct TestPayloadSelector<FillType> {

  /// Returns a pointer to the data given the reverse index.
  static const std::uint8_t* rdata(std::uint16_t rindex) {
    return nullptr;
  }

  static const std::uint8_t* data(std::uint16_t index) {
    return nullptr;
  }

  /// Returns the length of the test payload with reverse index rindex.
  static std::uint16_t rlength(std::uint16_t rindex) {
    return 0;
  }

  /// Returns the length of the test payload with reverse index rindex.
  static std::uint16_t length(std::uint16_t index) {
    return 0;
  }

  /// Finds the reverse index of a payload matching the given data.
  static std::int32_t rfind(const std::uint8_t* data, std::uint16_t length) {
    return -1;
  }

  /// Finds the index of a payload matching the given data.
  static std::int32_t find(const std::uint8_t* data, std::uint16_t length) {
    return -1;
  }
};


template <typename FillType, std::uint16_t w_Size, std::uint16_t...SIZES>
struct TestPayloadSelector<FillType, w_Size, SIZES...> {
  constexpr static std::uint16_t COUNT = 1 + sizeof...(SIZES);
  constexpr static std::uint16_t SIZE = w_Size;

  using Payload = TestPayload<FillType, SIZE>;

 public:

   /// Returns a pointer to the data given the reverse index.
  static const std::uint8_t* rdata(std::uint16_t rindex) {
    if (sizeof...(SIZES) == rindex) {
      return reinterpret_cast<const std::uint8_t*>(get());
    }
    return TestPayloadSelector<FillType, SIZES...>::rdata(rindex);
  }

  static const std::uint8_t* data(std::uint16_t index) {
    if (sizeof...(SIZES) < index) {
      return nullptr;
    }
    return rdata(sizeof...(SIZES) - index);
  }

  /// Returns the length of the test payload with reverse index rindex.
  static std::uint16_t rlength(std::uint16_t rindex) {
    if (sizeof...(SIZES) == rindex) {
      return sizeof(Payload);
    }
    return TestPayloadSelector<FillType, SIZES...>::rlength(rindex);
  }

  /// Returns the length of the test payload with reverse index rindex.
  static std::uint16_t length(std::uint16_t index) {
    if (sizeof...(SIZES) < index) {
      return 0;
    }

    return rlength(sizeof...(SIZES) - index);
  }

  /// Finds the reverse index of a payload matching the given data.
  static std::int32_t rfind(const std::uint8_t* data, std::uint32_t length) {
    if (sizeof(Payload) == length
        && *reinterpret_cast<const Payload*>(data) == *get()) {
      return sizeof...(SIZES);
    }
    return TestPayloadSelector<FillType, SIZES...>::rfind(data, length);
  }

  /// Finds the index of a payload matching the given data.
  static std::int32_t find(const std::uint8_t* data, std::uint32_t length) {
    auto rindex = rfind(data, length);
    if (rindex == -1) {
      return -1;
    }
    return sizeof...(SIZES) - rindex;
  }

  std::uint16_t count_payloads() {
    return sizeof...(SIZES);
  }

private:
  static const Payload* get() {
    static Payload payload;
    return &payload;
  }

};

// From 
// https://github.com/lemire/Code-used-on-Daniel-Lemire-s-blog/blob/master/2018/01/08/interleave.c
static inline std::uint32_t deinterleave_lowuint32(std::uint64_t word) {
  word &= 0x5555555555555555ull;
  word = (word ^ (word >> 1)) & 0x3333333333333333ull;
  word = (word ^ (word >> 2)) & 0x0f0f0f0f0f0f0f0full;
  word = (word ^ (word >> 4)) & 0x00ff00ff00ff00ffull;
  word = (word ^ (word >> 8)) & 0x0000ffff0000ffffull;
  word = (word ^ (word >> 16)) & 0x00000000ffffffffull;
  return (std::uint32_t)word;
}

using PacketType = std::vector< std::uint8_t>;

struct HostPacket {


  const std::uint8_t* data() const {
    return &(packet_data[0]);
  }

  const std::uint16_t length() const {
    auto result{ packet_data.size() };
    if (result > std::numeric_limits<std::uint16_t>::max()) {
      throw TestException(
        "Length too large: ", result, 
        "max is", std::numeric_limits<std::uint16_t>::max());
    }
    return std::uint16_t(result);
  }

  ip_addr_t remoteIp;
  std::uint16_t remotePort;
  
  PacketType packet_data;
};

using HostPacketList = std::list<HostPacket>;
using HostPacketVector = std::vector<HostPacket>;

template <
  std::uint32_t w_InFlightPacketCount,
  std::uint32_t w_MaxFragmentCount,
  std::uint32_t w_FragmentSize,
  std::uint16_t HOST_COUNT,
  typename FillType,
  std::uint16_t...SIZES>
struct TestSendTRecvFragmentsBase {

  using Receiver = ardo::FragmentReceiver<
    w_InFlightPacketCount, w_MaxFragmentCount, w_FragmentSize>;
  using Sender = ardo::FragmentSender<w_MaxFragmentCount, w_FragmentSize>;
  using ReceiverFunc = typename Receiver::ReceiverFunc;
  using SenderFunc = typename Sender::SenderFunc;

  using TestPayloads = TestPayloadSelector<FillType, SIZES...>;

  using TestRecieverFunc = std::function<void(const ip_addr_t& remoteIp,
    std::uint16_t remotePort,
    const uint8_t* data,
    std::uint32_t length)>;

  struct Senders {
    static std::uint64_t gen_host_port() {
      static std::uint64_t generator = 0xfa;
      return ++generator;
    }

    static ip_addr_t gen_host() {
      return deinterleave_lowuint32(gen_host_port());
    }

    static std::uint16_t gen_port() {
      static std::uint16_t port;
      return deinterleave_lowuint32(gen_host_port() >> 1);
    }

    void send(
      const std::uint8_t* sdata, 
      std::uint16_t slength,
      const ReceiverFunc& func) const {
      sender.send(sdata, slength, [&func, this](
        const uint8_t* data, std::uint32_t length) {
          func(remoteIp, remotePort, sdata, slength);
        });
    }

    void send(
      const std::uint8_t* sdata,
      std::uint16_t slength,
      Receiver& reciver,
      const TestRecieverFunc& func) const {
      sender.send(sdata, slength, [&reciver, &func, this](
        const uint8_t* data, std::uint32_t length) {
          func(remoteIp, remotePort, sdata, slength);
        });
    }

    HostPacketList send(
      const std::uint8_t* sdata,
      std::uint16_t slength) const {
      HostPacketList packets;
      sender.send(sdata, slength, [&packets, this](
        const uint8_t* data, std::uint32_t length) {
          packets.push_back({ remoteIp, remotePort, {data, data + length} });
        });

      return packets;
    }

    template <typename Container>
    void send_to(
      const std::uint8_t* sdata,
      std::uint16_t slength,
      Container& container) const {
      sender.send(sdata, slength, [&container, this](
        const uint8_t* data, std::uint32_t length) {
          container.push_back({ remoteIp, remotePort, {data, data + length} });
        });
    }

    ip_addr_t remoteIp{ gen_host() };
    std::uint16_t remotePort{ gen_port() };
    mutable Sender sender;
  };

  const Senders& get_sender(std::uint16_t host_index) const {
    if (host_index >= HOST_COUNT) {
      throw TestException("Requested host too large requested:", host_index,
        "max:", HOST_COUNT - 1);
    }
    return senders[host_index];
  }

  HostPacketList send_payload(std::uint16_t payload_index, std::uint16_t host_index) {
    return get_sender(host_index).send(
      TestPayloads::data(payload_index), TestPayloads::length(payload_index));
  }

  template <typename Container>
  std::list<PacketType> recieve(const Container& packets) {
    std::list<PacketType> recieved_packets;

    for (const auto& host_packet : packets) {
      receiver.receive(
        host_packet.remoteIp,
        host_packet.remotePort,
        host_packet.data(),
        host_packet.length(),
        [&recieved_packets](const uint8_t* data, std::uint32_t length) {
          recieved_packets.push_back({data, data + length});
        });
    }
    return recieved_packets;
  }

  Receiver receiver;
  Senders senders[HOST_COUNT];
};


void testStreamSequenceId() {
  using Receiver = ardo::FragmentReceiver<1, 10, 100>;
  using StreamSequenceId = typename Receiver::Reassembler::StreamSequenceId;

  StreamSequenceId a = { {1, 2, 3} };
  StreamSequenceId b = { {4, 5, 6} };
  b = a;
  if (!(b == a)) {
    throw new TestException("Failed copy or compare of StreamSequenceId");
  }

}

std::string print_diff_details(
  const std::uint8_t* data1, std::uint32_t length1,
  const std::uint8_t* data2, std::uint32_t length2) {
  if (length1 != length1) {
    return print_to_str("Lengths are different. length1:", length1, "length2:", length2);
  }

  std::ostringstream souts;
  bool found_difference = false;
  for (std::uint32_t i = 0, max = 10; i < length1; ++i, max--) {
    if (data1[i] != data2[i]) {
      if (!found_difference) {
        found_difference = true;
        souts << "Found differences\n";
      }
      souts << "[" << i << "]= "
        << std::uint32_t(data1[i])
        << " != "
        << std::uint32_t(data2[i])
        << "\n";

      if (!max) {
        souts << "Too many differences\n";
        break;
      }
    }
  }

  if (!found_difference) {
    return "No differences found";
  }
  return souts.str();
}

void testFragmentedSend() {
  using TestType = TestSendTRecvFragmentsBase<1, 20, 20, 1, std::uint8_t, 21, 350, 396>;

  using TestTypePayloads = typename TestType::TestPayloads;

  TestType test_state;

  for (std::int32_t i = 0; i < TestTypePayloads::COUNT; ++i) {
    HostPacketList sent_packets = test_state.get_sender(0).send(
      TestTypePayloads::data(i),
      TestTypePayloads::length(i));

    if (sent_packets.size() < 2) {
      throw TestException(
        "Fragmenting didn't produce enough packets:", sent_packets.size());
    }

    std::list<PacketType> result = test_state.recieve(sent_packets);
    if (result.size() != 1) {
      throw TestException("Expect 1 packet, recieved", result.size());
    }

    auto& packet = result.front();

    if (TestTypePayloads::find(&(packet[0]), std::uint32_t(packet.size())) != i) {
      throw TestException("Packet may be corrupted", print_diff_details(
        &(packet[0]), 
        packet.size(), 
        TestTypePayloads::data(i),
        TestTypePayloads::length(i)));
    }
  }

};


void run_global_tests() {
  testStreamSequenceId();
  testFragmentedSend();
}

template <
  std::uint32_t w_InFlightPacketCount,
  std::uint32_t w_MaxFragmentCount,
  std::uint32_t w_FragmentSize,
  std::uint16_t HOST_COUNT,
  typename FillType,
  std::uint16_t...SIZES>
struct ReorderTest : TestSendTRecvFragmentsBase<
  w_InFlightPacketCount, w_MaxFragmentCount, w_FragmentSize, HOST_COUNT, FillType, SIZES...> {

  using Base = TestSendTRecvFragmentsBase<
    w_InFlightPacketCount, w_MaxFragmentCount, w_FragmentSize, HOST_COUNT, FillType, SIZES...>;

  using Sender = typename Base::Sender;
  using ReceiverFunc = typename Base::ReceiverFunc;
  using SenderFunc = typename Base::SenderFunc;

  using TestPayloads = typename Base::TestPayloads;

  void runtest() {
    HostPacketVector all_sent_packets;

    for (std::int32_t i = 0; i < TestPayloads::COUNT; ++i) {
      auto orig_size = all_sent_packets.size();
      this->get_sender(0).send_to(
        TestPayloads::data(i),
        TestPayloads::length(i),
        all_sent_packets);

      auto added_count = all_sent_packets.size() - orig_size;
      if (added_count <= 1) {
        throw TestException(
          "Fragmenting didn't produce enough packets:", added_count);
      }
    }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(all_sent_packets.begin(), all_sent_packets.end(), generator);

    std::list<PacketType> result = this->recieve(all_sent_packets);
    if (result.size() != TestPayloads::COUNT) {
      throw TestException("Expect", TestPayloads::COUNT, "packet, recieved", result.size());
    }

    std::set<std::int32_t> indexes;
    for (auto& packet : result) {

      auto index = TestPayloads::find(&(packet[0]), std::uint32_t(packet.size()));
      if (index < 0) {
        throw TestException("Packet may be corrupted");
      }

      if (indexes.find(index) != indexes.end()) {
        throw TestException("Duplicated packet, index:", index);
      }
      indexes.insert(index);
    }

    if (indexes.size() != TestPayloads::COUNT) {
      throw TestException("Fewer packets received than sent:", indexes.size());
    }
  }

};

int run_test() {
  try {
    run_global_tests();

    ReorderTest<4, 20, 74, 1, std::uint8_t, 300>{}.runtest();
    ReorderTest<4, 20, 74, 1, std::uint8_t, 301>{}.runtest();
    ReorderTest<4, 20, 74, 1, std::uint8_t, 99, 300, 301>{}.runtest();

    return 0;
  } catch (const TestException& exc) {
    std::cerr << exc;
    return 1;
  }
}

int main()
{
  run_test();
}
