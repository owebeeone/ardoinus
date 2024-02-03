// ArdOinus specific header for AVR atmega32a MCU.
// This file will not be regenerated (unlike ardo_supplemental_atmega32a.h)
// so manual changes to this file will survive regeneration of architecture
// specific definitions.

#ifndef ardo_supplemental_atmega32a_defs__h
#define ardo_supplemental_atmega32a_defs__h

#include "ardo_supplemental_atmega32a.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_atmega32a {

// Add only atmega32a specific resources here.
// Resources in this namespace will appear in the ardo::sys::avr::mcu
// namespace when compiled for the atmega32a architecture.
// Any code added here should be independent of compiler provided resources
// so as to enable compiling of this code in any environment for the 
// purpose of cross platform testing.


}  // arch_atmega32a
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega32a_defs__h
