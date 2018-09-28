
#include "ardOStepper.h"
#include "ArdoQuadEncoder.h"

using QEncoder = quad::QuadEncoder<
  ardo::DebounceInput<ardo::InputPin<2>>,
  ardo::DebounceInput<ardo::InputPin<3>>>;

using QModule = quad::QuadEncoderModule<QEncoder>;

// Define the stepper motor controller module.
using SModule = step::StepperModule<
  /* stepPeriod */ 2000,
  /* coilOnPeriod */ 4000,
  setl::TimeUnit::MICROS,
  ardo::OutputPin<5>,
  ardo::OutputPin<6>, 
  ardo::OutputPin<7>,
  ardo::OutputPin<8>>;

struct CombineModule : ardo::ModuleBase<ardo::Parameters<>> {

  static void runSetup() {
    SModule::instance.stepper.setTimeScale(1.0);
  }
  
  static void runLoop() {
    auto pos = QModule::quadEncoder.getCurrentPosition();
    SModule::instance.stepper.setTargetPosition(pos);
  }
};


using App = ardo::Application<SModule, QModule, CombineModule>;

void setup() {
  App::runSetup();
}

void loop() {
  App::runLoop();
}