/**
 * Decoder/encoder for PWE (Pulse Width Encoded) serial data. 
 * Data is encoded using a alternate a short pulse followed by a long
 * pulse or a long pulse followed by a short pulse. The sum of the 
 * pulses should be the same. A 1 is distinguished from a 0 based
 * on the sequence short-long or long-short.
 */
#ifndef PWE_SERIAL___H
#define PWE_SERIAL___H

#include "type_for_size.h"
#include "setl_time.h"

#include "setlx_cstdint.h"
#include "setlx_array.h"
#include "setlx_cassert.h"

namespace setl {

// Data type used for period.
using xpwe_type = std::uint32_t;
const TimeUnit PWE_UNIT = TimeUnit::MICROS;

/**
 * Holder for bit data.
 */
template <std::uint16_t w_size_bits>
class PweBitCollector {
  static_assert(w_size_bits > 0, "Cannot have 0 bits");

public:
  static const std::uint16_t size_bits = w_size_bits;
  using value_type = typename setl::TypeForMaxBits<size_bits>::selected::type_unsigned;

  /**
   * Returns the current value and resets the value.
   */
  void readValue(value_type& result) {
    result = working_value;
    working_value = value_type{};
  }

  void saveBit(bool bit_value, std::uint32_t bit_address) {
    assert(bit_address < size_bits);
    if (bit_value) {
      auto bit = value_type(1u) << bit_address;
      working_value |= bit;
    }
  }

  void writeValue(const value_type& new_value) {
    working_value = new_value;
  }

  bool getBit(std::uint32_t bit_address) const {
    assert(bit_address < size_bits);
    auto bit = value_type(1u) << bit_address;
    return working_value & bit;
  }

private:
  value_type working_value = 0;
};

/**
 * Array version.
 */
template <typename T, std::uint16_t w_size_bits>
class PweBitCollectorArray {
  static_assert(w_size_bits > 0, "Cannot have 0 bits");
  static_assert(w_size_bits < ((1u << 16u) - 2u), "Cannot have more 65534 bits");

public:
  using value_type = std::array<T, (w_size_bits + 8 * sizeof(T) - 1) / sizeof(T)>;
  static const std::uint16_t size_bits = w_size_bits;
  
  void readValue(value_type& result) {
    result = working_value;
    working_value = T{};
  }

  void saveBit(bool bit_value, std::uint32_t bit_address) {
    assert(bit_address < size_bits);
    if (bit_value) {
      auto index = bit_address / sizeof(T);
      auto bit = T(1) << bit_address % sizeof(T);
      working_value[index] |= bit;
    }
  }

  void writeValue(const value_type& new_value) {
    working_value = new_value;
  }

  bool getBit(std::uint32_t bit_address) const {
    assert(bit_address < size_bits);
    auto index = bit_address / sizeof(T);
    auto bit = T(1) << bit_address % sizeof(T);
    return working_value[index] & bit;
  }

private:
  value_type working_value{};
};

/**
 * Parameters that describe the waveform.
 */
template <typename w_type, TimeUnit units = PWE_UNIT>
struct PweWaveformParams {
  using PeriodType = Period<w_type, units>;
  PeriodType settle_period;
  PeriodType stop_period;
  PeriodType bit_on_period;
  PeriodType bit_off_period;
  PeriodType bit_half_period;
  PeriodType bit_min_period;
  PeriodType bit_max_period;
};

/**
 * Template to create statically initialized plain old data PweWaveformParams 
 * with 1:3 on/off ratio for the bit signal.
 */
// This should optimize to statically initialized data in the rdata segement.
template <
  typename w_type,
  w_type settle_period,
  w_type stop_period,
  w_type bit_period,
  TimeUnit units = PWE_UNIT>
const PweWaveformParams<w_type, units> PweWaveformParams1to3 = {
  period<units>(settle_period),
  period<units>(stop_period),
  period<units>(w_type(bit_period * 0.25)),
  period<units>(w_type(bit_period * 0.75)),
  period<units>(w_type(bit_period / 2)),
  period<units>(w_type(bit_period * 0.8)),
  period<units>(w_type(bit_period * 1.2)) };

/**
 * Decodes a sequence of timed on/off signals and provides a decoded value.
 */
template <
  typename CollectorType,     /// The assembler of bit into data.
  bool inverted = false,      /// The sense of the signal.
  bool long_on_is_1 = false,  /// Long on period is a 1 (0 if false).
  typename w_type = xpwe_type,/// The time value type.
  TimeUnit units = PWE_UNIT>  /// Units used.
class PweDecoder {
private:
  enum class State : char {
    NO_SAMPLES,
    SETTLE,
    ON,
    OFF,
    STOP
  };

public:

  using PeriodType = Period<w_type, units>;
  using TimeType = Time<w_type, units>;
  static const std::uint16_t size_bits = CollectorType::size_bits;
  using value_type = typename CollectorType::value_type;

  PweDecoder(const PweWaveformParams<w_type, units>& params)
    : params(params)
  {}

  // Signal has been deemed changed at a specific time.
  void signalChanged(const TimeType& time, bool in_level) {
    bool level = in_level != inverted;

    switch (state) {
      case State::NO_SAMPLES: {
        transition(State::STOP, time);
        break;
      }     
      case State::STOP: {
        // We need the level to stay off for a minimum time.
        if ((time - time_state_entered) < params.stop_period) {
          if (level) {
            // Ignore data being sent until after a full stop period has passed.
            time_state_entered = time;  // transition to self.
          }
          break;
        }
        transition(State::SETTLE, time);

        // fall though to settle because basically it's that state after top period.
      }

      case State::SETTLE: {
        if (level) {
          // start of first bit.
          transition(State::ON, time);
          if (bit_number != 0) {
            overrun = true;
            bit_number = 0;
          }
        }
        break;
      }

      case State::ON: {
        auto period = time - time_state_entered;
        if (!level) {
          auto is_long = period >= params.bit_half_period;
          if (long_on_is_1 != is_long) {
            collector.saveBit(true, bit_number);
          }
          bit_number++;
          if (bit_number < size_bits) {
            state = State::OFF;
          } else {
            transition(State::STOP, time);
          }
        }
        break;
      }

      case State::OFF: {
        auto period = time - time_state_entered;

        // Period for the bit has to be within margin.
         if (period > params.bit_max_period) {
          transition(State::STOP, time);
          signal_error = true;
        } else if (level) {
          if (period < params.bit_min_period) {
            transition(State::STOP, time);
            signal_error = true;
          } else if (bit_number >= size_bits) {
            transition(State::STOP, time);
          } else {
            transition(State::ON, time);
          }
        }
        break;
      }
    }
  }

  bool pollDataReady() {
    return bit_number == size_bits && (state == State::STOP || state == State::SETTLE);
  }

  /// Returns nomonal minimum period of time that data could possibly be ready by.
  PeriodType nextPollWaitTime(const TimeType& now) const {
    switch (state) {
      case State::SETTLE: {
        if (bit_number == size_bits) {
          return PeriodType(0);
        }
        return bitsDecodePeriod();
      }
      case State::STOP: {
        auto period = now - time_state_entered;
        auto result = bitsDecodePeriod() + params.stop_period;
        if (period < params.stop_period) {
          return result -= period;
        }
        return result;
      }
      case State::ON:
      case State::OFF: {
        auto bit_count = size_bits - bit_number;
        return bit_count * (params.bit_half_period + params.bit_on_period);
      }
      default:
      case State::NO_SAMPLES: {
        return bitsDecodePeriod() + params.stop_period;
      }
    }
  }

  /** The nominal time required to decode the bits. */
  PeriodType bitsDecodePeriod() const {
    return size_bits * (params.bit_off_period + params.bit_on_period);
  }

  /** Returns true if a value is available and places the result in the given parameter. */
  bool readValue(value_type& result) {
    if (bit_number < size_bits) {
      return false;
    }
    collector.readValue(result);
    bit_number = 0;
    return true;
  }

  bool hasSignalError() {
    return signal_error;
  }

  void clearSignalError() {
    signal_error = false;
  }

  bool isOverrun() {
    return overrun;
  }

  void clearOverrun() {
    overrun = false;
  }

  /** Resets all state. */
  void reset() {
    state = State::NO_SAMPLES;
    time_state_entered = TimeType();
    bit_number = 0;
    clearOverrun();
    clearSignalError();
  }

  std::uint16_t get_bit_number() {
    return bit_number;
  }

private:

  void transition(State nextState, const TimeType& time) {
    state = nextState;
    time_state_entered = time;
  }

  // The encoder parameters used for this.
  const PweWaveformParams<w_type, units>& params;

  State state = State::NO_SAMPLES;
  std::uint16_t bit_number = 0;
  bool overrun = false;
  bool signal_error = false;
  CollectorType collector;
  TimeType time_state_entered;
};

template <
  typename CollectorType,     /// The assembler of bit into data.
  bool inverted = false,      /// The sense of the signal.
  bool long_on_is_1 = false,  /// Long on period is a 1 (0 if false).
  typename w_type = xpwe_type,/// The time value type.
  TimeUnit units = PWE_UNIT>  /// Units used.
class PweEncoder {
private:
  enum class State : char {
    NO_DATA,
    HAVE_DATA,
    BIT_ON_FIRST,
    BIT_ON_SECOND,
    BIT_OFF_FIRST,
    BIT_OFF_SECOND,
    STOP
  };
public:

  using PeriodType = Period<w_type, units>;
  using TimeType = Time<w_type, units>;
  static const std::uint16_t size_bits = CollectorType::size_bits;
  using value_type = typename CollectorType::value_type;
  enum {
    on_level = true != inverted,
    off_level = true == inverted,
  };

  // The result of a poll.
  struct PollResult {
    std::uint8_t current_output;  // The output needed.
    std::uint8_t no_data;  // indicates that no future poll needed until next send.
    TimeType time_next_poll; 
  };

  PweEncoder(const PweWaveformParams<w_type, units>& params)
    : params(params)
  {}

  /** Sets the data to send */
  bool send(const value_type& value) {

    // If we're using the last data then no, we can't send this new data now.
    if ((state != State::NO_DATA) 
      && ((state != State::STOP) || (bit_number == 0))) {
      return false;
    }

    collector.writeValue(value);
    bit_number = 0;
    if (state == State::NO_DATA) {
      state = State::HAVE_DATA;
    }
    return true;
  }


  /** The time on the next poll event. */
  PollResult poll(const TimeType& time) {
    switch (state) {
      default:
      case State::NO_DATA: {
        return PollResult{ off_level, true, TimeType{ 0 } };
      }
      case State::HAVE_DATA: {
        transitionBit(time);
        return PollResult{ on_level, false, next_transition_time };
      }
      case State::BIT_ON_FIRST: {
        if (hasPassedMidBitPoint(time)) {
          state = State::BIT_ON_SECOND;
          next_transition_time += statePeriod(State::BIT_ON_SECOND);
          return PollResult{ off_level, false, next_transition_time };
        }
        return PollResult{ on_level, false, next_transition_time };
      }
      case State::BIT_OFF_FIRST: {
        if (hasPassedMidBitPoint(time)) {
          state = State::BIT_OFF_SECOND;
          next_transition_time += statePeriod(State::BIT_OFF_SECOND);
          return PollResult{ off_level, false, next_transition_time };
        }
        return PollResult{ on_level, false, next_transition_time };
      }
      case State::BIT_OFF_SECOND:
      case State::BIT_ON_SECOND: {
        if (hasPassedMidBitPoint(time)) {
          if (bit_number < size_bits) {
            transitionBit(next_transition_time);
            return PollResult{ on_level, false, next_transition_time };
          } else {
            state = State::STOP;
            next_transition_time += statePeriod(State::STOP);
            return PollResult{ off_level, false, next_transition_time };
          }
        }
        return PollResult{ off_level, false, next_transition_time };
      }
      case State::STOP: {
        if (hasPassedMidBitPoint(time)) {
          if (bit_number > 0) {
            state = State::NO_DATA;
            return PollResult{ off_level, true, TimeType(0) };
          } else {
            transitionBit(time);
            return PollResult{ on_level, false, next_transition_time };
          }
        }
        return PollResult{ off_level, false, next_transition_time };
      }
    }
  }

  /** Resets all state. */
  void reset() {
    state = State::NO_DATA;
    next_transition_time = TimeType();
    bit_number = 0;
  }

private:
  PeriodType statePeriod(State for_state) {
    switch (for_state) {
      default:
      case State::NO_DATA: {
        return PeriodType{ 0 };
      }
      case State::HAVE_DATA: {
        return PeriodType{ 0 };
      }
      case State::BIT_ON_FIRST: {
        return long_on_is_1 == false ? params.bit_on_period : params.bit_off_period;
      }
      case State::BIT_ON_SECOND: {
        return long_on_is_1 == false ? params.bit_off_period : params.bit_on_period;
      }
      case State::BIT_OFF_FIRST: {
        return long_on_is_1 == false ? params.bit_off_period : params.bit_on_period;
      }
      case State::BIT_OFF_SECOND: {
        return long_on_is_1 == false ? params.bit_on_period : params.bit_off_period;
      }
      case State::STOP: {
        return params.stop_period + params.settle_period;
      }
    }
  }

  void transitionBit(const TimeType& time) {
    auto bit_is_long = collector.getBit(bit_number) == long_on_is_1;
    if (bit_is_long) {
      state = State::BIT_ON_FIRST;
      next_transition_time = time + params.bit_on_period;
    } else {
      next_transition_time = time + params.bit_off_period;
      state = State::BIT_OFF_FIRST;
    }
    ++bit_number;
  }

  bool hasPassedMidBitPoint(const TimeType& time) {
    const auto mid_value = PeriodType(~(w_type(1) << (sizeof(w_type) * 8 - 1)));
    return (time - next_transition_time) < mid_value;
  }

  State state = State::NO_DATA;
  TimeType next_transition_time;
  std::uint16_t bit_number = 0;

  CollectorType collector;

  // The encoder parameters used for this.
  const PweWaveformParams<w_type, units>& params;
};

} // namespace pwm_serial

#endif  // PWE_SERIAL___H

