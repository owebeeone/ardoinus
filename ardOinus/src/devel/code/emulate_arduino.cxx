
#include "ardOinus.h"

// Not much of a emulator.  Just allow linking for now.


void pinMode(int pin, std::uint8_t mode) {

}

void digitalWrite(int pin, std::uint8_t mode) {

}

int digitalRead(int pin) {
  return LOW;
}

unsigned long millis() {
  return 1;
}

unsigned long micros() {
  return 1000;
}


SerialType Serial;
SerialType Serial1;
