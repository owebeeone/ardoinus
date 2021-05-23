
// Example using the embedded ArdOinus framework that shows how to:
// 1. Define an ardo::ModuleInstanceBase that runs setup and loop on a
//    singleton instance.
// 2. Use GPIO digital write pins.
// 3. Have multiple modules running in one "Application".
// 4. Use a cyclic sequence poller. (ardo::CyclicTimeSequencePoller)

#include "ardOinus.h"  // The main ArdOinus module framework API.

#include "ardo_time_poller.h"  // Time polling helpers.


// A basic blinking module that will follow the given ardo::Sequence
// specification for periods between transitions.
//
// Using ModuleInstanceBase as the base class will cause an instance
// of the module to be created and the instanceLoop() and instanceSetup()
// functions called.
template <typename Seq, typename LedPin>
class BlinkModule : 
    public ardo::ModuleInstanceBase<
	BlinkModule<Seq, LedPin>, 
	ardo::Parameters<LedPin>> {
public:

  void instanceLoop() {
    if (timeSequence.poll()) {
      LedPin::set(timeSequence.state() & 1);
    }
  }

  ardo::CyclicTimeSequencePoller<Seq> timeSequence;
};

#if !defined(LED_BUILTIN) // Some 
#define LED_BUILTIN 2
#endif

// Here we "specialize" the BlinkModule template by defining all the parameters.
using BlinkerA = BlinkModule<
  ardo::Sequence<750, 400, 650, 300, 550, 200, 450, 100, 350, 50, 1000, 50>, 
  ardo::OutputPin<LED_BUILTIN>>;

// A second blinker module running on a different pin.
using BlinkerB = BlinkModule<
  ardo::Sequence<1000, 500>,
  ardo::OutputPin<7>>;

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
