// ArdOinus specific header for AVR atmega64 MCU.
// This file will not be regenerated (unlike ardo_supplemental_atmega64.h)
// so manual changes to this file will survive regeneration of architecture
// specific definitions.

#ifndef ardo_supplemental_atmega64_defs__h
#define ardo_supplemental_atmega64_defs__h

#include "ardo_supplemental_atmega64.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_atmega64 {

// Add only atmega64 specific resources here.
// Resources in this namespace will appear in the ardo::sys::avr::mcu
// namespace when compiled for the atmega64 architecture.
// Any code added here should be independent of compiler provided resources
// so as to enable compiling of this code in any environment for the 
// purpose of cross platform testing.


}  // arch_atmega64
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega64_defs__h
