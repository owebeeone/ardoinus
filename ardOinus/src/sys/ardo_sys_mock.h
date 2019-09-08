
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

void pinMode(unsigned pin, std::uint8_t mode);
void digitalWrite(unsigned pin, std::uint8_t mode);
int digitalRead(unsigned pin);
unsigned millis();
unsigned micros();

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

EEPROMType EEPROM;


namespace ardo_system {
using ardo::GPIOResource;

#define ARDO_HAS_SERIAL0 1
  using Serial0Resources0 = setl::TypeArgs<GPIOResource<100>, GPIOResource<101>>;

#define ARDO_HAS_SERIAL1 1
  using Serial1Resources1 = setl::TypeArgs<GPIOResource<102>, GPIOResource<103>>;

#define ARDO_HAS_SERIAL2 1
  using Serial2Resources2 = setl::TypeArgs<GPIOResource<104>, GPIOResource<105>>;

} // namespace ardo_system

#endif SYS__ARDO_SYS_MOCK___H