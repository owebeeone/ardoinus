
// Example using the embedded ArdOinus framework for putting together
// multiple blink modules.

#include "ardOinus.h"  // The main ArdOinus module framework API.

#include "ardo_time_poller.h"  // A time poller class.

// Use the arduino Serial port.
using SerialA = ardo::SerialIO<115200>;

// A timer module to execute in a timed sequence.
template <typename Seq>
class TimeModule : public ardo::ModuleBase<ardo::Parameters<>> {
public:

  static TimeModule instance;  // Define an instance here.

  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    if (timeSequence.poll()) {
      switch (timeSequence.state() & 1) {
        case 0: {
          SerialA::println("now: ", ardo::CoreIF::nowMillis().get());
          break;
        }
      }
    }
  }

  ardo::CyclicTimeSequencePoller<Seq> timeSequence;  // State variable.
};

// C++ requires the instantiation of the static instance outside the class.
template <typename Seq>
TimeModule<Seq> TimeModule<Seq>::instance;


using TimeModuleA = TimeModule<ardo::Sequence<1000, 500>>;
using SerialM = ardo::ModuleBase<ardo::Parameters<SerialA>>;

// Define the main app with the serial module and a timer module.
using mainApp = ardo::Application<SerialM, TimeModuleA>;

void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}
