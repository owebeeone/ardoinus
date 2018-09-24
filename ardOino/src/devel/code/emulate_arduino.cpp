
#include "ardoino.h"

// Not much of a emulator.  Just allow linking for now.

void pinMode(unsigned pin, std::uint8_t mode) {

}

void digitalWrite(unsigned pin, std::uint8_t mode) {

}

int digitalRead(unsigned pin) {
  return LOW;
}

unsigned millis() {
  return 1;
}

unsigned micros() {
  return 1000;
}