

#include "ardOinus.h"

#include "ardo_time_poller.h"

// Resource claim testers.
using su_claim1 = ardo::shared_use_claim<int, 1, long>;
using su_claim2 = ardo::shared_use_claim<int, 1, long>;
using su_claim3 = ardo::shared_use_claim<int, 1, unsigned>;
using su_claim4 = ardo::shared_use_claim<int, 2, unsigned>;
using su_claim5 = ardo::shared_use_claim<short, 1, unsigned>;

static_assert(
  false == ardo::has_conflict<su_claim1, su_claim2>::value,
  "Identical shared_use_claim claims should be OK");

static_assert(
  true == ardo::has_conflict<su_claim1, su_claim3>::value,
  "shared_use_claim with the same id and different params should be in conflict");

static_assert(
  false == ardo::has_conflict<su_claim1, su_claim4>::value,
  "shared_use_claim with different resource types should be OK");

static_assert(
  false == ardo::has_conflict<su_claim1, su_claim5>::value,
  "shared_use_claim with different resource types should be OK");

using r_claim1 = ardo::range_claim<int, 1, 4>;
using r_claim2 = ardo::range_claim<int, 4, 8>;
using r_claim3 = ardo::range_claim<int, 3, 8>;
using r_claim4 = ardo::range_claim<short, 1, 4>;

static_assert(
  true == ardo::has_conflict<r_claim1, r_claim1>::value,
  "range_claims that are idential have conflict");

static_assert(
  false == ardo::has_conflict<r_claim1, r_claim2>::value,
  "range_claims that don't have overlapping ranges are OK");

static_assert(
  true == ardo::has_conflict<r_claim1, r_claim3>::value,
  "range_claims that have overlapping ranges conflict");

static_assert(
  false == ardo::has_conflict<r_claim1, r_claim4>::value,
  "range_claims for different types are OK");

namespace adro_test_do_not_use {
auto& pin1 = ardo::OutputPin<1, ardo::CoreIF::Output>::pin;
auto& pin2 = ardo::OutputPin<2, ardo::CoreIF::OpenDrainLowOutput>::pin;
auto& pin3 = ardo::OutputPin<3, ardo::CoreIF::Output, ardo::OutputPinIF>::pin;
auto& pin4 = ardo::OutputPin<4, ardo::CoreIF::OpenDrainLowOutput, ardo::OutputPinIF>::pin;
using Pin5Type = ardo::DebounceInput<ardo::InputPin<5>, 13, ardo::CoreIF::MillisTime>;
auto& pin5 = Pin5Type::pin;

bool getValue() {
  return pin5.get() || Pin5Type::get();
}


template <typename Seq, typename Params>
class BlinkModule : public ardo::ModuleBase<Params> {
public:
  using LedPin = typename Params::template Param<0>;

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

  ardo::CyclicTimeSequencePoller<Seq> timeSequence;
};

template <typename Seq, typename Params>
BlinkModule<Seq, Params> BlinkModule<Seq, Params>::instance;

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

}
