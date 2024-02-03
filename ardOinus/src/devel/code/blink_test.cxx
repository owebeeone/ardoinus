
#include "ardOinus.h"

#include "ardo_time_poller.h"  // A time poller class.

#include "setlx_type_traits.h"  // ArdOinus partial implementation of C++ type_traits

using SerialA = ardo::SerialIO<115200>;

template <typename Seq, typename w_LedPin>
class BlinkModule : public ardo::ModuleBase<ardo::Parameters<w_LedPin>> {
public:
  using LedPin = w_LedPin;

  static BlinkModule instance;

  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    if (timeSequence.poll()) {
      switch (timeSequence.state() & 1) {
      case 0: {
        SerialA::println("now: ", ardo::CoreIF::nowMillis().get());
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

  ardo::CyclicTimeSequencePoller<Seq> timeSequence;
};

template <typename Seq, typename Params>
BlinkModule<Seq, Params> BlinkModule<Seq, Params>::instance;

using Blinker2 = BlinkModule<ardo::Sequence<1000, 500>, ardo::OutputPin<2>>;
using Blinker3 = BlinkModule<ardo::Sequence<750, 400>, ardo::OutputPin<3>>;
using SerialM = ardo::ModuleBase<ardo::Parameters<SerialA>>;

// Define the main app with 2 blinker modules.
using mainApp = ardo::Application<SerialM, Blinker2, Blinker3>;


void fsetup() {
  mainApp::runSetup();
}

void floop() {
  mainApp::runLoop();
  SerialA::println(1, 2, 3);
}
