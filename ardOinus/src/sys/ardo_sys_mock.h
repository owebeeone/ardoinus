
#ifndef SYS__ARDO_SYS_MOCK___H
#define SYS__ARDO_SYS_MOCK___H

#include <iostream>
#include <iomanip>
#include <cstring>
#include "setlx_array.h"
#include "ardo_resources.h"
#include "setl_templ_utils.h"

#define ARDO_USE_ARDUINO_COREIF  // Enable Arudino ardo::CoreIF veneer.

// For IDEs (like visual studio), this mocks the arduino.h API amnd helps
// make the IDE less noisy.

#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define LOW 0
#define HIGH 1
#define LED_BUILTIN 1

#ifdef BIN  // Remove prior BIN defined (Yuck!)
#undef BIN
#endif
#define BIN 2
#define OCT 8
#define DEC 10
#define HEX 16

inline void pinMode(int pin, std::uint8_t mode) {}
inline void digitalWrite(int pin, std::uint8_t mode) {}
inline int digitalRead(int pin) { return 0; }
inline unsigned long millis() { return 0; }
inline unsigned long micros() { return 0; }
inline void analogWrite(int pin, int value) {}

#define ARDO_DEV_MOCK_SERIAL


template <typename T, bool is_float=std::is_floating_point<T>::value>
struct PrintBinary {
  static void print(const T& v) {
    std::cout << std::setbase(10) << v;
  }
};


template <typename T>
struct PrintBinary<T, false> {
  static void print(const T& v) {

    if (v) {
      std::array<char, sizeof(v) * 8 + 2> bytes;
      T outval{ v };
      T bit{ 1 };
      auto iter{ bytes.end() - 1 };
      *iter-- = '\0';
      while (outval && bit && iter != bytes.begin()) {
        *iter = outval & bit ? '1' : '0';
        iter--;
        outval &= ~bit;
        bit <<= 1;
      }

      std::cout << &*(iter + 1);
    } else {
      std::cout << "0";
    }

    std::cout << " - 0x" << std::setbase(16) << v;
  }
};


template <typename T>
void write_modified(const T& v, int mod) {
  switch (mod) {
  case BIN:
    PrintBinary<T>::print(v);
    break;
  case OCT:
    std::cout << std::setbase(8) << v;
    break;
  default:
  case DEC:
    std::cout << std::setbase(10) << v;
    break;
  case HEX:
    std::cout << std::setbase(16) << v;
    break;
  }
}


class SerialType {
public:
  void begin(unsigned long) {}
  template <typename T>
  void print(const T& v) {
    write_modified(v, DEC);
  }
  template <typename T>
  void print(const T& v, int mod) {
    write_modified(v, mod);
  }
  template <typename T>
  void println(const T& v) {
    write_modified(v, DEC);
    println();
  }
  template <typename T>
  void println(const T& v, int mod) {
    write_modified(v, mod);
    println();
  }
  void print(const char* s) {
    std::cout << s;
  }
  void print(const char* s, int mod) {
    std::cout << s;
  }
  void println(const char* s) {
    std::cout << s << std::endl;
  }
  void println(const char* s, int mod) {
    std::cout << s << std::endl;
  }
  void println() {
    std::cout << std::endl;
  }

  // TODO need many more.

};

extern SerialType Serial;
extern SerialType Serial1;
extern SerialType Serial2;

struct EEPROMType
{
  void update(int address, unsigned char value) {
    values[address] = value;
  }

  unsigned char read(int address) {
    return values[address];
  }

  unsigned char values[4096];
};

extern EEPROMType EEPROM;


namespace ardo_system {
using ardo::GPIOResource;

#define ARDO_HAS_SERIAL0 1
using Serial0Resources0 = setl::TypeArgs<GPIOResource<100>, GPIOResource<101>>;

#define ARDO_HAS_SERIAL1 1
using Serial1Resources1 = setl::TypeArgs<GPIOResource<102>, GPIOResource<103>>;

#define ARDO_HAS_SERIAL2 1
using Serial2Resources2 = setl::TypeArgs<GPIOResource<104>, GPIOResource<105>>;

#define ARDO_USE_ARDUINO_HARDWARE_PWM 1

///**
// * ArdOinus needs this basic set of parameters, some of which are
// * utilized by some architectures and not others. The goal is to enable
// * source code compatability across different architectures.
// */
//template <std::int8_t w_bits, std::int32_t w_frequency, std::int8_t w_channel>
//class HwPwmParameters {
//public:
//  static constexpr std::int8_t bits = w_bits;
//  static constexpr std::int32_t frequency = w_frequency;
//  static constexpr std::int8_t channel = w_channel;
//  using value_type = std::uint16_t;
//};
//
//using DefaultHwPwmParameters = HwPwmParameters<8, -1, 0>;

/**
 * Define the resources for GPIO pins for the given set of parameters. The
 * resources declared here are added to the resources associated with the
 * ardo::OutputPin.
 */
template <typename w_Pin, typename w_Parameters>
class HardwarePwmResources {
public:
  using Pin = w_Pin;
  using Parameters = w_Parameters;

  // Claim additional resources here (like timers).
  using Claims = ardo::ResourceClaim<>;

  using value_type = typename Parameters::value_type;

  // Use 9 bits in the mock.
  constexpr static std::uint8_t timer_bits = 9;

  static void setPwm(value_type value) {
    ::analogWrite(Pin::PIN, value);
  }
};

} // namespace ardo_system

#endif SYS__ARDO_SYS_MOCK___H