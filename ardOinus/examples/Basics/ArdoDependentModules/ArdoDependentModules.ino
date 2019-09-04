
#include "ardOinus.h"  // The main ArdOinus module framework API.

// Dependent modules are placed in the ardo::Application
// module set and their runSetup and runLoop functions are
// all called once per module per loop or setup function call.

// Any arbitray graph of module dependency is supported, including
// cyclic graphs if you're so inclined.

// A module should be dependent if it is designed to provide service
// to another module. For example, an SPI bus module may be have
// multiple SPI bus client modules. Adding the SPI module class
// to the main application (while supported) would make for a more
// fragile from an on-going maintenance perspective.

// The graph of module dependency below can be descibed in the following
// digraph:
// AnotherModule -> MyModule
// MoreModule -> MyModule
// The final application module set will include the three distinct 
// modules. The order of runLoop and runSetup calls is not defined 
// and could change in future ArdOinus revisions.

class MyModule : public ardo::ModuleBase<> {
public:
  // Override these functions as needed.
  // static void runSetup() {}
  // static void runLoop() {}
};

class AnotherModule : public ardo::ModuleBase<
  ardo::Parameters<>,
  // Dependent modules are added to the application.
  ardo::DependentModules<MyModule>> {
public:
  // Override these functions as needed.
  // static void runSetup() {}
  // static void runLoop() {}
};

class MoreModule : public ardo::ModuleBase<
  ardo::Parameters<>,
  // A module can be dependent in multiple modules.
  ardo::DependentModules<MyModule>>  {
public:
  // Override these functions as needed.
  // static void runSetup() {}
  // static void runLoop() {}
};

// Define the main application class.
// Module classes will be de-duplicated and only one instance
// of the class will be processed in ardo::Application.
// (A side effect of deriving the transitive closure of the
// dependency graph.)
// In the case below MyModule is added once.
using mainApp = ardo::Application<AnotherModule, MoreModule>;

void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}
