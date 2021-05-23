
#ifndef SYS__ARDO_SYS_MOCK___H
#define SYS__ARDO_SYS_MOCK___H

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

void pinMode(int pin, std::uint8_t mode);
void digitalWrite(int pin, std::uint8_t mode);
int digitalRead(int pin);
unsigned long millis();
unsigned long micros();
void analogWrite(int pin, int value);

#define ARDO_DEV_MOCK_SERIAL


class SerialType {
public:
  void begin(unsigned long) {}
  template <typename T>
  void print(const T&) {}
  template <typename T>
  void println(const T&) {}
  void print(const char*) {}
  void println(const char*) {}
  void println() {}

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

/**
 * ArdOinus needs this basic set of parameters, some of which are
 * utilized by some architectures and not others. The goal is to enable
 * source code compatability across different architectures.
 */
template <std::int8_t w_bits, std::int32_t w_frequency, std::int8_t w_channel>
class HwPwmParameters {
public:
  static constexpr std::int8_t bits = w_bits;
  static constexpr std::int32_t frequency = w_frequency;
  static constexpr std::int8_t channel = w_channel;
  using value_type = std::uint16_t;
};

using DefaultHwPwmParameters = HwPwmParameters<8, -1, 0>;

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