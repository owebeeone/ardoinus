
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


    static void loop() {
      BlinkModule::instance.instanceLoop();
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

    ardo::CyclicTimeSequencePoller<Seq> timeSequence;
  };

  using setl_test::assertThat;

  using Blinker2 = BlinkModule<ardo::Sequence<1000, 500>, ardo::Parameters<ardo::OutputPin<2>>>;
  using Blinker3 = BlinkModule<ardo::Sequence<750, 400>, ardo::Parameters<ardo::OutputPin<3>>>;

  // Define the main app with 2 blinker modules.
  using mainApp = ardo::Application<Blinker2, Blinker3>;

  void setup() {
    mainApp::runSetup();
  }

  void loop() {
    mainApp::runLoop();
  }

  class Test_DO_BOT_USE : setl_test::SetlTest {

    bool run() override {

    }
  };
}