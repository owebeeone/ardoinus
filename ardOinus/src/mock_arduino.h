
#ifndef ARDOINUS___H
#error "This must only be included by ardOinus.h"
#endif // ARDOINUS___H

#ifdef ARDOINUS___H_DONE
#error "This must only be included by ardOinus.h"
#endif

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
