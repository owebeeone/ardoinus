// Note: This must only be included through ardOinus.h.

// System specific attributes are provded here.
// If using the Arduio API, set macro ARDO_USE_ARDUINO_COREIF to 1.

#ifndef ARDOINUS___H
#error "This must only be included by ardOinus.h"
#endif // ARDOINUS___H

#ifdef ARDOINUS___H_DONE
#error "This must only be included by ardOinus.h"
#endif

#include "setl_time.h"
#include "setl_utils.h"
#include "setl_templ_utils.h"

#include "setlx_cstdint.h"
#include "setlx_type_traits.h"

namespace ardo_system {
// Used by serial resources.
using ardo::GPIOResource;

// Defines for Arduino Nano
#if defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO)

#define ARDO_USE_ARDUINO_COREIF

#define ARDO_HAS_SERIAL0
using Serial0Resources0 = setl::TypeArgs<GPIOResource<0>, GPIOResource<1>>;

#elif defined(ARDUINO_attiny)

#define ARDO_USE_ARDUINO_COREIF 1

// No serial resources.

#elif defined(ARDUINO_ESP32_DEV)

#define ARDO_USE_ARDUINO_COREIF

#define ARDO_HAS_SERIAL0
using Serial0Resources0 = setl::TypeArgs<GPIOResource<1>, GPIOResource<3>>;

#define ARDO_HAS_SERIAL1
using Serial1Resources1 = setl::TypeArgs<GPIOResource<9>, GPIOResource<10>>;

#define ARDO_HAS_SERIAL2
using Serial2Resources2 = setl::TypeArgs<GPIOResource<17>, GPIOResource<16>>;

#elif defined(ARDO_USE_MOCK_ARDUINO) || !defined(INPUT_PULLUP)

#define ARDO_USE_ARDUINO_COREIF

// MOCK arduino interface when we don't have Arduino.h
#if !defined(INPUT_PULLUP)  // This is provided by Arduino.h
}  // namespace ardo_system
#include "mock_arduino.h"
namespace ardo_system {
#endif

#define ARDO_HAS_SERIAL0
using Serial0Resources0 = setl::TypeArgs<GPIOResource<100>, GPIOResource<101>>;

#define ARDO_HAS_SERIAL1
using Serial1Resources1 = setl::TypeArgs<GPIOResource<102>, GPIOResource<103>>;

#define ARDO_HAS_SERIAL2
using Serial2Resources2 = setl::TypeArgs<GPIOResource<104>, GPIOResource<105>>;

#else

// If there is evidence of Arduino beig included then go ahead an use Arduino.
#if defined(INPUT_PULLUP)
#define ARDO_USE_ARDUINO_COREIF
#endif

#pragma message ( "Processor type is not defined. Serial interface disabled." )

#endif // ARDUINO_AVR_NANO

} // namespace ardo_system

// ardo::CoreIF should
namespace ardo {

#ifdef ARDO_USE_ARDUINO_COREIF

/**
 * An implementation of CoreIF veneer over some of the Android API.
 */
class CoreIF {
public:
  enum OutputPinMode : std::uint8_t {
    OpenDrainLowOutput = 0xffu,   // Open collector/drain low output. 
    OpenDrainHighOutput = 0xfeu,  // Open collector/drain high output. 
    Output = OUTPUT,              // Output mode.
  };

  enum InputPinMode : std::uint8_t {
    PullUp = INPUT_PULLUP,    // Input tied through pullup resistor.
    Untied = INPUT,           // Floating high impedance input.
  };

  using MillisTime = setl::Time<decltype(millis()), setl::TimeUnit::MILLIS>;
  using MicrosTime = setl::Time<decltype(micros()), setl::TimeUnit::MICROS>;

  inline static void pinMode(unsigned pin, std::uint8_t mode) {
    ::pinMode(pin, mode);
  }

  inline static void digitalWrite(unsigned pin, std::uint8_t mode) {
    ::digitalWrite(pin, mode);
  }

  inline static bool digitalRead(unsigned pin) {
    return ::digitalRead(pin) != LOW;
  }

  inline static MillisTime nowMillis() {
    return MillisTime(millis());
  }

  inline static MicrosTime nowMicros() {
    return MicrosTime(micros());
  }

private:
  // Cast operator conversion to target time.
  struct NowTimeEvaluator {
    template <typename T>
    struct NowTime;

    template <typename T>
    operator T () const {
      return NowTime<T>::get();
    }
  };

public:
  static NowTimeEvaluator now() {
    return NowTimeEvaluator();
  }
};

template <>
struct CoreIF::NowTimeEvaluator::NowTime<CoreIF::MillisTime> {
  static CoreIF::MillisTime get() {
    return CoreIF::nowMillis();
  }
};

template <>
struct CoreIF::NowTimeEvaluator::NowTime<CoreIF::MicrosTime> {
  static CoreIF::MicrosTime get() {
    return CoreIF::nowMicros();
  }
};

/**
 * Serial port support.
 */

// Serial support. Define ARDO_HAS_SERIAL0 to get Serial support.
#ifdef ARDO_HAS_SERIAL0

template <unsigned PortN>
class SerialIf {
public:
  static decltype(Serial)& get();
};


template <>
class SerialIf<0> {
public:
  using Resource = ardo_system::Serial0Resources0;

  inline static decltype(Serial)& get() {
    return Serial;
  }
};

/**
 * Provides module parameter support for Serial initialization.
 */
template <unsigned long baudRate, unsigned long PortN = 0>
class SerialIO {
public:
  using SerialIfType = SerialIf<PortN>;
  using Claims = typename SerialIfType::Resource
    ::template cat<SerialResource<PortN>>::template eval<ResourceClaim>;

  inline static void runSetup() {
    SerialIfType::get().begin(baudRate);
  }

  inline static void runLoop() {}

  inline static void print() {}

  template <typename T, typename... Ts>
  inline static void print(const T& arg, Ts... args) {
    SerialIfType::get().print(arg);
    print(args...);
  }

  template <typename T>
  inline static void println(const T& arg) {
    SerialIfType::get().println(arg);
  }

  template <typename T, typename... Ts>
  inline static void println(const T& arg, Ts... args) {
    SerialIfType::get().print(arg);
    println(args...);
  }
};
#endif

// Serial1 support. Define ARDO_HAS_SERIAL1 to get Serial1 support.
#ifdef ARDO_HAS_SERIAL1
template <>
class SerialIf<1> {
public:
  using Resource = ardo_system::Serial1Resources1;

  inline static decltype(Serial1)& get() {
    return Serial1;
  }
};
#endif

// Serial2 support. Define ARDO_HAS_SERIAL2 to get Serial2 support.
#ifdef ARDO_HAS_SERIAL2
template <>
class SerialIf<2> {
public:
  using Resource = ardo_system::Serial2Resources2;

  inline static decltype(Serial1)& get() {
    return Serial2;
  }
};
#endif

#endif // ARDO_USE_ARDUINO_COREIF

} // namespace ardo
