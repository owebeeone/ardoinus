// ArdOinus specific header for AVR at94k MCU.
// This file will not be regenerated (unlike ardo_supplemental_at94k.h)
// so manual changes to this file will survive regeneration of architecture
// specific definitions.

#ifndef ardo_supplemental_at94k_defs__h
#define ardo_supplemental_at94k_defs__h

#include "ardo_supplemental_at94k.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_at94k {

// Add only at94k specific resources here.
// Resources in this namespace will appear in the ardo::sys::avr::mcu
// namespace when compiled for the at94k architecture.
// Any code added here should be independent of compiler provided resources
// so as to enable compiling of this code in any environment for the 
// purpose of cross platform testing.


}  // arch_at94k
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_at94k_defs__h
