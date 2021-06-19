// ArdOinus specific header for AVR m3000 MCU.
// This file will not be regenerated (unlike ardo_supplemental_m3000.h)
// so manual changes to this file will survive regeneration of architecture
// specific definitions.

#ifndef ardo_supplemental_m3000_defs__h
#define ardo_supplemental_m3000_defs__h

#include "ardo_supplemental_m3000.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_m3000 {

// Add only m3000 specific resources here.
// Resources in this namespace will appear in the ardo::sys::avr::mcu
// namespace when compiled for the m3000 architecture.
// Any code added here should be independent of compiler provided resources
// so as to enable compiling of this code in any environment for the 
// purpose of cross platform testing.


}  // arch_m3000
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_m3000_defs__h
