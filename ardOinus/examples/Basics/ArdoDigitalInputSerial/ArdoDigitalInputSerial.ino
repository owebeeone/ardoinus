
#include "ardOinus.h"

template <typename w_InputPin, typename w_Serial>
class SerialExample : public ardo::ModuleBase<
  ardo::Parameters<w_InputPin, w_Serial>> {
public:
  using Pin = w_InputPin;
  using Out = w_Serial;

  static void runSetup() {
    instance.last_state = Pin::get();
    Out::println("Started Value = ", instance.last_state);
  }

  static void runLoop() {
    auto next_state = Pin::get();
    if (next_state != instance.last_state) {
      instance.last_state = next_state;
      Out::println("Value = ", next_state);
    }
  }

  static SerialExample instance;
  bool last_state;
};

template <typename w_InputPin, typename w_Serial>
SerialExample<w_InputPin, w_Serial> SerialExample<w_InputPin, w_Serial>::instance;

using SerialExampleModule = SerialExample<
  ardo::InputPin<7, ardo::CoreIF::Untied>,
  ardo::SerialIO<9600>>;

// Define the main application class. This will combine 
// multiple modules.
using mainApp = ardo::Application<SerialExampleModule>;

void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}
