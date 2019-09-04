
// Example using the embedded ArdOinus framework for putting together
// multiple blink modules.

#include "ardOinus.h"  // The main ArdOinus module framework API.

#include "ardo_time_poller.h"  // A time poller class.


// Re-usable blink module.
// Module classes are not instantiated by the framework. If an instance
// is required, the module is responsible for creating one.
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

  ardo::CyclicTimeSequencePoller<Seq> timeSequence;  // State variable.
};

// C++ requires the instantiation of the static instance outside the class.
template <typename Seq, typename Params>
BlinkModule<Seq, Params> BlinkModule<Seq, Params>::instance;

#if !defined(LED_BUILTIN)
#define LED_BUILTIN 1
#endif

// Here we "specialize" the BlinkModule template by defining all the parameters.
using BlinkerA = BlinkModule<
  ardo::Sequence<750, 400, 650, 300, 550, 200, 450, 100, 350, 50, 250, 50, 50, 1000>, 
  ardo::OutputPin<LED_BUILTIN>>;
  
using BlinkerB = BlinkModule<
  ardo::Sequence<1000, 500>,
  ardo::OutputPin<2>>;

// Define the main app with 2 blinker modules.
using mainApp = ardo::Application<BlinkerB, BlinkerA>;

void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}
