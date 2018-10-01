

#ifndef PWM_SERIAL_COMMS__H
#define PWM_SERIAL_COMMS__H

#include "pwe_serial.h"

#include "ardoino.h"

namespace ardo {

/**
 * A module for receiving PWE data.
 */
template <
  typename P,
  typename CollectorType,     /// The assembler of bit into data.
  typename w_type,
  w_type settle_period,
  w_type stop_period,
  w_type bit_period,
  bool inverted = false,      /// The sense of the signal.
  bool long_on_is_1 = false,  /// Long on period is a 1 (0 if false).
  setl::TimeUnit UNITS = setl::PWE_UNIT>
class PweReceiverModule : public ardo::ModuleBase<ardo::Parameters<P>> {
public:
  using DecoderType = setl::PweDecoder<CollectorType, inverted, long_on_is_1, w_type, UNITS>;
  using Pin = P;
  using value_type = typename DecoderType::value_type;

  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    auto in_level = Pin::get();
    decoder.signalChanged(ardo::CoreIF::now(), in_level);
  }

  bool isDataReady() {
    decoder.pollDataReady();
  }

  bool readValue(value_type& result) {
    return decoder.readValue(result);
  }

  static PweReceiverModule instance;
  DecoderType decoder{
    setl::PweWaveformParams1to3<w_type, settle_period, stop_period, bit_period, UNITS >};
};

template <
  typename P,
  typename CollectorType,
  typename w_type,
  w_type settle_period,
  w_type stop_period,
  w_type bit_period,
  bool inverted,
  bool long_on_is_1,
  setl::TimeUnit UNITS>
PweReceiverModule<
    P,
    CollectorType,
    w_type,
    settle_period,
    stop_period,
    bit_period,
    inverted,
    long_on_is_1,
    UNITS>
  PweReceiverModule<
        P,
        CollectorType,
        w_type,
        settle_period,
        stop_period,
        bit_period,
        inverted,
        long_on_is_1,
        UNITS>::instance;

/**
 * A module for transmitting PWE data.
 */
template <
  typename P,
  typename CollectorType,
  typename w_type,
  w_type settle_period,
  w_type stop_period,
  w_type bit_period,
  bool inverted = false,
  bool long_on_is_1 = false,
  setl::TimeUnit UNITS = setl::PWE_UNIT>
class PweTransmitterModule : public ardo::ModuleBase<ardo::Parameters<P>> {
public:
  using EncoderType = setl::PweEncoder<CollectorType, inverted, long_on_is_1, w_type, UNITS>;
  using Pin = P;
  using value_type = typename EncoderType::value_type;

  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    auto result = encoder.poll(ardo::CoreIF::now());
    Pin::set(result.current_output);
  }

  // Returns false if the data not sent (because the previous data has not
  // been sent yet.
  bool send(const value_type& value) {
    return encoder.send(value);
  }

  static PweTransmitterModule instance;
  EncoderType encoder{
    setl::PweWaveformParams1to3<w_type, settle_period, stop_period, bit_period, UNITS> };
};

template <
  typename P,
  typename CollectorType,
  typename w_type,
  w_type settle_period,
  w_type stop_period,
  w_type bit_period,
  bool inverted,
  bool long_on_is_1,
  setl::TimeUnit UNITS>
PweTransmitterModule<
    P, 
    CollectorType, 
    w_type,
    settle_period,
    stop_period,
    bit_period,
    inverted, 
    long_on_is_1, 
    UNITS>
  PweTransmitterModule<
      P,
      CollectorType,
      w_type,
      settle_period,
      stop_period,
      bit_period,
      inverted,
      long_on_is_1,
      UNITS>::instance;

}


#endif