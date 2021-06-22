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

#ifdef _MSC_VER 

#define __AVR
#define __AVR_ATmega328P__ 1
#define __AVR_DEVICE_NAME__ atmega328p
#define AVR_MOCK_IOREGISTERS 1

#endif // _MSC_VER


#ifdef __AVR

#include "ardo_mcu_avr.h"

#endif

// Defines for Arduino Nano
#if defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO)

#include "sys/ardo_sys_atmega328.h"


#elif defined(ARDUINO_attiny)

#define ARDO_USE_ARDUINO_COREIF 1

// No serial port on ATtiny.

#elif defined(ARDUINO_ESP32_DEV)

#include "sys/ardo_sys_esp32.h"

#elif defined(ARDO_USE_MOCK_ARDUINO) || !defined(INPUT_PULLUP)

#include "sys/ardo_sys_mock.h"

#else

// If there is evidence of Arduino beig included then go ahead an use Arduino.
#if defined(INPUT_PULLUP)
#define ARDO_USE_ARDUINO_COREIF
#endif

#pragma message ( "Processor type is not defined. Serial interface disabled." )

#endif // ARDUINO_AVR_NANO

// Include the system specific include file.
#if defined(ARDO_SYS_INCLUDE)
#include ARDO_SYS_INCLUDE
#endif

// ardo::CoreIF should use the ardo:: namespace.
namespace ardo {

// If system uses Arduino API, then ARDO_USE_ARDUINO_COREIF is defined.
// This will define the generic arduino core interface.
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

template <typename ST>
struct CoreIF::NowTimeEvaluator::NowTime<setl::Time<ST, setl::TimeUnit::MILLIS>> {
  static setl::Time<ST, setl::TimeUnit::MILLIS> get() {
    return CoreIF::nowMillis();
  }
};


template <typename ST>
struct CoreIF::NowTimeEvaluator::NowTime<setl::Time<ST, setl::TimeUnit::MICROS>> {
  static setl::Time<ST, setl::TimeUnit::MICROS> get() {
    return CoreIF::nowMicros();
  }
};


/**
 * Arduino serial port support.
 */

// Serial support. Set ARDO_HAS_SERIAL{0,1,2} to 1 get Serial support.
#define ARDO_HAS_ANY_SERIAL (ARDO_HAS_SERIAL0 || ARDO_HAS_SERIAL1 || ARDO_HAS_SERIAL2)

#if ARDO_HAS_ANY_SERIAL
template <unsigned PortN>
class SerialIf {
public:
  static decltype(Serial)& get();
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

  inline static void println () {
    SerialIfType::get().println();
  }

  /**
   * Prints a variable list of arguments.
   */
  template <typename T, typename... Ts>
  inline static void print(const T& arg, Ts... args) {
    SerialIfType::get().print(arg);
    print(args...);
  }

  template <typename T>
  inline static void println(const T& arg) {
    SerialIfType::get().println(arg);
  }

  /**
   * Prints a variable list of arguments and prints a newline after 
   * the last argument is printed.
   */
  template <typename T, typename... Ts>
  inline static void println(const T& arg, Ts... args) {
    SerialIfType::get().print(arg);
    println(args...);
  }
};
#endif


// Serial support. Define ARDO_HAS_SERIAL0 as 1 to get Serial support.
#ifdef ARDO_HAS_SERIAL0
template <>
class SerialIf<0> {
public:
  using Resource = ardo_system::Serial0Resources0;

  inline static decltype(Serial)& get() {
    return Serial;
  }
};
#endif

// Serial1 support. Define ARDO_HAS_SERIAL1 as 1 to get Serial1 support.
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

  inline static decltype(Serial2)& get() {
    return Serial2;
  }
};
#endif


#if ARDO_USE_ARDUINO_HARDWARE_PWM
namespace nfp {
template <typename w_OutputPin, typename w_PwmParams>
class HardwarePwmIF {
public:
  using PinType = w_OutputPin;
  using value_type = std::uint8_t;

  inline static void runSetup() {
    // ardo::OutputPin setup is sufficient here.
  }

  inline static void runLoop() {}

  inline static void set_pwm(value_type value) {
    ::analogWrite(PinType::PIN, value);
  }
};

} // namespace nfp

#endif // ARDO_USE_ARDUINO_HARDWARE_PWM


#endif // ARDO_USE_ARDUINO_COREIF

} // namespace ardo
