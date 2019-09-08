
#ifndef SYS__ARDO_SYS_MOCK___H
#define SYS__ARDO_SYS_MOCK___H

#include "ardo_resources.h"
#include "setl_templ_utils.h"

#define ARDO_USE_ARDUINO_COREIF
namespace ardo_system {
using ardo::GPIOResource;

#define ARDO_HAS_SERIAL0 1
  using Serial0Resources0 = setl::TypeArgs<GPIOResource<1>, GPIOResource<3>>;

#define ARDO_HAS_SERIAL1 1
  using Serial1Resources1 = setl::TypeArgs<GPIOResource<9>, GPIOResource<10>>;

#define ARDO_HAS_SERIAL2 1
  using Serial2Resources2 = setl::TypeArgs<GPIOResource<17>, GPIOResource<16>>;
}  // namespace ardo_system

#endif
