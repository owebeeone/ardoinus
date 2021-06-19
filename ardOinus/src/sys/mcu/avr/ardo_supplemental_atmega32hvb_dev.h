// ArdOinus specific header for AVR atmega32hvb MCU.
// This file will not be regenerated (unlike ardo_supplemental_atmega32hvb.h)
// so manual changes to this file will survive regeneration of architecture
// specific definitions.

#ifndef ardo_supplemental_atmega32hvb_defs__h
#define ardo_supplemental_atmega32hvb_defs__h

#include "ardo_supplemental_atmega32hvb.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_atmega32hvb {

// Add only atmega32hvb specific resources here.
// Resources in this namespace will appear in the ardo::sys::avr::mcu
// namespace when compiled for the atmega32hvb architecture.
// Any code added here should be independent of compiler provided resources
// so as to enable compiling of this code in any environment for the 
// purpose of cross platform testing.


}  // arch_atmega32hvb
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega32hvb_defs__h
