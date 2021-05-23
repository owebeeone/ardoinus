
// Example using the embedded ArdOinus framework that shows how to:
// 1. Define an ardo::Module.
// 2. Use GPIO digital write pins.
// 3. Have multiple modules running in one "Application".
// 4. Use a cyclic sequence poller. (ardo::CyclicTimeSequencePoller)

#include "ardOinus.h"  // The main ArdOinus module framework API.

#include "ardo_time_poller.h"  // Time polling helpers.


// A basic blinking module that will follow the given ardo::Sequence
// specification.
//
// Note that module classes are not instantiated by the framework. If an
// instance is required, the module is responsible for creating one.
template <typename Seq, typename w_LedPin>
class BlinkModule : public ardo::ModuleBase<ardo::Parameters<w_LedPin>> {
public:
  using LedPin = w_LedPin;

  static BlinkModule instance;  // Define an instance here.

  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    if (timeSequence.poll()) {
      LedPin::set(timeSequence.state() & 1);
    }
  }

  // By default, the CyclicTimeSequencePoller inteprets the Seq paramete
  // times as milliseconds.
  ardo::CyclicTimeSequencePoller<Seq> timeSequence;  // Polling state data.
};

// C++ requires the instantiation of the static instance outside the class.
// You can use ardo::ModuleInstance or ardo::Singleton from ardo_singleton.h
// to eliminate this boilerplate code.
template <typename Seq, typename Params>
BlinkModule<Seq, Params> BlinkModule<Seq, Params>::instance;

#if !defined(LED_BUILTIN)
#define LED_BUILTIN 1
#endif

// Here we "specialize" the BlinkModule template by defining all the parameters.
using BlinkerA = BlinkModule<
  ardo::Sequence<750, 400, 650, 300, 550, 200, 450, 100, 350, 50, 1000, 50>, 
  ardo::OutputPin<LED_BUILTIN>>;
  
using BlinkerB = BlinkModule<
  ardo::Sequence<1000, 500>,
  ardo::OutputPin<2>>;

// Define the main application with 2 blinker modules.
using mainApp = ardo::Application<BlinkerB, BlinkerA>;

// Provides the Arduino setup and loop functions. Nothing else should go
// into these functions. If there is a need to call a third party library
// just create a module class and add it to the Application or make a 
// dependent module.
void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}
