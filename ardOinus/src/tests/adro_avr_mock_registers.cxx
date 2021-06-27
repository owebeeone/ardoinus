
#include "ardo_mcu_avr.h"

namespace ardo {
namespace sys {
namespace avr {

#ifdef AVR_MOCK_IOREGISTERS

unsigned char mcu_io_memory[mcu_io_memory_size];
unsigned char* const mcu_io_memory_ptr{ mcu_io_memory };

#endif

}  // namespace avr
}  // namespace sys
}  // namespace ardo
