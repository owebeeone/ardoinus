// Note: This must only be included through ardOinus.h.

// System specific attributes here.

#ifndef ARDOINUS___H
#error "This must only be included by ardOinus.h"
#endif // ARDOINUS___H

#ifdef ARDOINUS___H_DONE
#error "This must only be included by ardOinus.h"
#endif

namespace ardo_system {

// Defines for Arduino Nano
#if defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO)

#define ARDO_HAS_SERIAL0
using Serial0Resources = setl::TypeArgs<GPIOResource<0>, GPIOResource<1>>;

#elif defined(ARDUINO_attiny)

// No serial resources.

#elif defined(ARDUINO_ESP32_DEV)

#define ARDO_HAS_SERIAL0
using Serial0Resources = setl::TypeArgs<GPIOResource<1>, GPIOResource<3>>;

#define ARDO_HAS_SERIAL1
using Serial1Resources = setl::TypeArgs<GPIOResource<9>, GPIOResource<10>>;

#define ARDO_HAS_SERIAL2
using Serial2Resources = setl::TypeArgs<GPIOResource<17>, GPIOResource<16>>;

#elif defined(ARDO_DEV_MOCK_SERIAL)

#define ARDO_HAS_SERIAL0
using Serial0Resources = setl::TypeArgs<GPIOResource<100>, GPIOResource<101>>;

#define ARDO_HAS_SERIAL1
using Serial1Resources = setl::TypeArgs<GPIOResource<102>, GPIOResource<103>>;

#define ARDO_HAS_SERIAL2
using Serial2Resources = setl::TypeArgs<GPIOResource<104>, GPIOResource<105>>;

#else

#pragma message ( "Processor type is not defined. Serial interface disabled." )

#endif // ARDUINO_AVR_NANO

} // namespace
