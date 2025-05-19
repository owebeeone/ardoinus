
#include "circular_buffer.h"
#include "assert_that.h"

#include "setl_test_framework.h"

#include "ardo_singleton.h"

namespace singleton_test {

template <typename Seq, typename Params>
class BlinkModule : 
    public ardo::Singleton<BlinkModule<Seq, Params>>, public ardo::ModuleBase<Params> {
public:
  using LedPin = typename Params::template Param<0>;

  static void runLoop() {
    BlinkModule::instance.instanceLoop();
  }

  void instanceLoop() {
    if (timeSequence.poll()) {
      LedPin::set(timeSequence.state() & 1);
    }
  }

  ardo::CyclicTimeSequencePoller<Seq> timeSequence;
};

#if !defined(LED_BUILTIN)
#define LED_BUILTIN 1
#endif

using Blinker2 = BlinkModule<ardo::Sequence<1000, 100, 100, 100, 100>, ardo::Parameters<ardo::OutputPin<LED_BUILTIN>>>;
using Blinker3 = BlinkModule<ardo::Sequence<750, 400>, ardo::Parameters<ardo::OutputPin<3>>>;

// Define the main app with 2 blinker modules.
using mainApp = ardo::Application<Blinker2, Blinker3>;

void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}

class Test_DO_NOT_USE : setl_test::SetlTest {

  bool run() override {

  }
};

} // namespace singleton_test

namespace moduleinstance_test {

template <typename Seq, typename Params>
class BlinkModule :
  public ardo::ModuleInstanceBase<BlinkModule<Seq, Params>, Params> {
public:
  using LedPin = typename Params::template Param<0>;

  void instanceLoop() {
    if (timeSequence.poll()) {
      LedPin::set(timeSequence.state() & 1);
    }
  }

  ardo::CyclicTimeSequencePoller<Seq> timeSequence;
};

#if !defined(LED_BUILTIN)
#define LED_BUILTIN 1
#endif

using Blinker2 = BlinkModule<ardo::Sequence<1000, 100, 100, 100, 100>, ardo::Parameters<ardo::OutputPin<LED_BUILTIN>>>;
using Blinker3 = BlinkModule<ardo::Sequence<750, 400>, ardo::Parameters<ardo::OutputPin<3>>>;

// Define the main app with 2 blinker modules.
using mainApp = ardo::Application<Blinker2, Blinker3>;

void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}

class Test_DO_NOT_USE : setl_test::SetlTest {

  bool run() override {
  }
};

} // namespace moduleinstance_test


