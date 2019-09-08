// This example is similar in function with the Arduino Arrays example.
//

#include "ardOinus.h"
#include "ardo_time_poller.h" 

// This ardOinus module template takes a sequence and a number of LED pins
// to sequence an arbitrary set of LEDs.
template <typename Seq, typename... w_LedPins>
class BlinkLedsSequenceModule : 
  public ardo::ModuleBase<ardo::Parameters<w_LedPins...>> {
public:
  static_assert(
    Seq::count >= sizeof...(w_LedPins),
    "More pins defined than sequence steps. i.e. Remove unused pins.");

  static_assert(
    sizeof...(w_LedPins) > 1,
    "A single LED is uninteresting. i.e. It will always be on.");

  // PinsSeqencer will turn on just the selected pin.
  // This unpacks the w_LedPins parameter.
  template <unsigned N, typename... T>
  struct PinsSeqencer;

  template <unsigned N>
  struct PinsSeqencer<N> {
    static void doThing(unsigned state) {}
  };

  template <unsigned N, typename T, typename... Ts>
  struct PinsSeqencer<N, T, Ts...> {
    static void doThing(unsigned state) {
      T::set(state == N);
      PinsSeqencer<N + 1u, Ts...>::doThing(state);
    }
  };

  static void runLoop() {
    instance.instanceLoop();
  }
  
  void instanceLoop() {
    if (timeSequence.poll()) {
      PinsSeqencer<0, w_LedPins...>::doThing(select_LED_from_state());
    }
  }

  // Returns back and forth sequence of (like the Arrays example).
  // e.g. 0, 1, 2, 2, 1, 0, 0, 1, 2, ... (for a 3 LED sequence).
  unsigned select_LED_from_state() {
    auto state = timeSequence.state() % (2 * sizeof...(w_LedPins));
    if (state < sizeof...(w_LedPins)) {
      return state;
    }
    return sizeof...(w_LedPins) * 2 - 1 - state;
  }

  // C++17 will allow "inline" declaration and eliminate the outer definintion.
  static BlinkLedsSequenceModule instance;
  ardo::CyclicTimeSequencePoller<Seq> timeSequence;  // State variable.
};

// C++ requires the instantiation of the static instance outside the class.
template <typename Seq, typename... w_LedPins>
BlinkLedsSequenceModule<Seq, w_LedPins...> 
    BlinkLedsSequenceModule<Seq, w_LedPins...>::instance;

// Here we "specialize" the BlinkLedsSequenceModule template by adding
// a sequence generator and using the same 6 pins in the Arduino Arrays example.
using SequenceBlinker = BlinkLedsSequenceModule<
  ardo::Sequence<
    750, 200, 200, 200, 200, 200, 
    1000, 400, 400, 400, 400, 400, 
    50, 100, 100, 100, 100, 50, 
    50, 100, 100, 100, 100, 50>,
  ardo::OutputPin<2>, 
  ardo::OutputPin<7>, 
  ardo::OutputPin<4>, 
  ardo::OutputPin<6>, 
  ardo::OutputPin<5>, 
  ardo::OutputPin<3>>;

// We can now define another sequencer with just 3 LEDs.
using SequenceBlinker2 = BlinkLedsSequenceModule<
  ardo::Sequence<500, 500, 500, 500, 500, 500>,
  ardo::OutputPin<8>, 
  ardo::OutputPin<9>, 
  ardo::OutputPin<10>>;

// Define the main app with SequenceBlinker and SequenceBlinker2 modules
// operating together in one application.
using mainApp = ardo::Application<SequenceBlinker, SequenceBlinker2>;

void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}
