
#ifndef ARDOINUS___H
#error "This must be included by ardOinus.h"
#endif // ARDOINUS___H

#ifdef ARDOINUS___H_DONE
#error "This must only be included by ardOinus.h"
#endif

namespace ardo_system {

// Defines for Arduino Nano
#if defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO)

#define ARDO_HAS_SERIAL0
using Serial0Resources = setl::TypeArgs<ExternalPin<0>, ExternalPin<1>>;

#elif defined(ARDUINO_attiny)

// No serial resources.

#elif defined(ARDUINO_ESP32_DEV)

#define ARDO_HAS_SERIAL0
using Serial0Resources = setl::TypeArgs<ExternalPin<1>, ExternalPin<3>>;

#define ARDO_HAS_SERIAL1
using Serial1Resources = setl::TypeArgs<ExternalPin<9>, ExternalPin<10>>;

#define ARDO_HAS_SERIAL2
using Serial2Resources = setl::TypeArgs<ExternalPin<17>, ExternalPin<16>>;

#elif defined(ARDO_DEV_MOCK_SERIAL)

#define ARDO_HAS_SERIAL0
using Serial0Resources = setl::TypeArgs<ExternalPin<100>, ExternalPin<101>>;

#define ARDO_HAS_SERIAL1
using Serial1Resources = setl::TypeArgs<ExternalPin<102>, ExternalPin<103>>;

#define ARDO_HAS_SERIAL2
using Serial2Resources = setl::TypeArgs<ExternalPin<104>, ExternalPin<105>>;

#else

#pragma message ( "Processor type is not defined. Serial interface disabled." )


#endif // ARDUINO_AVR_NANO

} // namespace