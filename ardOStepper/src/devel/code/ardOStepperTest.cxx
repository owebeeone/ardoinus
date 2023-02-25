
#include "ArdoStepper.h"
#include "ArdoQuadEncoder.h"

using QEncoder = quad::QuadEncoder<ardo::InputPin<2>, ardo::InputPin<3>>;

using QModule = quad::QuadEncoderModule<QEncoder>;

// Define the stepper motor controller module.
using SModule = step::StepperModule<
  /* stepPeriod */ 20,
  /* coilOnPeriod */ 50,
  setl::TimeUnit::MILLIS,
  ardo::OutputPin<5>,
  ardo::OutputPin<6>, 
  ardo::OutputPin<7>,
  ardo::OutputPin<8>>;

struct CombineModule : ardo::ModuleBase<ardo::Parameters<>> {

  static void runLoop() {
    auto pos = QModule::quadEncoder.getCurrentPosition();
    SModule::instance.stepper.setTargetPosition(pos);
    SModule::instance.stepper.setTimeScale(1.0);
  }
};


using App = ardo::Application<SModule, QModule, CombineModule>;

void setup() {
  App::runSetup();
}

void loop() {
  App::runLoop();
}

int main() {

  App::runSetup();

  App::runLoop();

  SModule::instance.stepper.setTargetPosition(2);
}