
#include "ArdoQuadEncoder.h"

using QEncoder = quad::QuadEncoder<ardo::InputPin<5>, ardo::InputPin<6>>;

using QModule = quad::QuadEncoderModule<QEncoder>;

using App = ardo::Application<QModule>;

int main() {

  App::runSetup();

  App::runLoop();

  QModule::quadEncoder.getCurrentPosition();
}