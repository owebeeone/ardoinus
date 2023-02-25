
#include "ArdoFastLED.h"
#include "ArdoQuadEncoder.h"

// Define the QuadEncoder to use.
using QEncoder = quad::QuadEncoder<
  ardo::DebounceInput<ardo::InputPin<7>>,  // Use Pin 7 and pin 8 and debounce the input.
  ardo::DebounceInput<ardo::InputPin<8>>>;

// Make an ardo::Module from the encoder.
using QModule = quad::QuadEncoderModule<QEncoder>;

// Create an LEDs module.
using Leds = ardo_fastled::LedStrip<10, ardo::ExternalPin<4>, WS2812B, GRB, 10>;

// This module connects together the QEncoder and Leds modules. This is application logic.
struct CombineModule : ardo::ModuleBase<ardo::Parameters<>> {
  // A runSetup() method is allowed as well.
  
  // This is called once per loop.
  static void runLoop() {
    auto pos = QModule::quadEncoder.getCurrentPosition();
    // Limit the encoder to 0-100.
    if (pos < 0) {
      pos = 0;
      QModule::quadEncoder.setCurrentPosition(pos);
    } else if (pos > 100) {
      pos = 100;
      QModule::quadEncoder.setCurrentPosition(pos);
    }

    // Set the values for each LED based on the encoder position.
    for (int i = 0; i < Leds::COUNT; ++i) {
      Leds::set(i, valueFor(i, pos));
    }
  }

  static CRGB valueFor(int led, long pos) {
    return led >= (pos / 10) ? CRGB::Red : CRGB::Blue;
  }
};

// Put all the modules in the "Application".
using App = ardo::Application<QModule, Leds, CombineModule>;

void setup() {
  App::runSetup();
}

void loop() {
  App::runLoop();
}
