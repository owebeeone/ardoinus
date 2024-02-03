
#include "ardOinus.h"  // The main ArdOinus module framework API.

class MyModule : public ardo::ModuleBase<> {
public:
  // Override these functions as needed.
  // static void runSetup() {}
  // static void runLoop() {}
};

// Define the main application class. This will combine 
// multiple modules.
using mainApp = ardo::Application<MyModule>;

void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}
