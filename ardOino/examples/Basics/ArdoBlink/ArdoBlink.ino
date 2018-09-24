// Example using the embedded ArdOino framework for putting together
// multiple blink modules.

#include "ardoino.h"  // The main ArdOino module framework API.

#include "ardo_time_poller.h"  // A time poller class.

#include "setlx_type_traits.h"  // Ardoino partial implementation of C++ type_traits


// Re-usable blink module.
// Module classes are not instantiated by the framework. If an instance
// is required, the module is responsible for creating one.
template <typename Seq, typename Params>
class BlinkModule : public ardo::ModuleBase<Params> {
public:
  using LedPin = typename Params::template Param<0>::param;

  static BlinkModule instance;

  static void loop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    if (timeSequence.poll()) {
      switch (timeSequence.state() & 1) {
        case 0: {
          LedPin::set(true);
          break;
        }
        case 1: {
          LedPin::set(false);
          break;
        }
      }
    }
  }

  ardo::TimeSequencePoller<Seq> timeSequence;
};

template <typename Seq, typename Params>
BlinkModule<Seq, Params> BlinkModule<Seq, Params>::instance;

using Blinker2 = BlinkModule<ardo::Sequence<1000, 500>, ardo::Parameters<ardo::OutputPin<2>>>;
using Blinker3 = BlinkModule<ardo::Sequence<750, 400>, ardo::Parameters<ardo::OutputPin<3>>>;

// Define the main app with 2 blinker modules.
using mainApp = ardo::Application<Blinker2, Blinker3>;


void setup() {
  mainApp::setup();
}

void loop() {
  mainApp::loop();
}
