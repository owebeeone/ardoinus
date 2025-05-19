
#include "ardOinus.h"

namespace ardo {
namespace sys {
namespace avr {
namespace base {

#ifdef AVR_MOCK_IOREGISTERS

unsigned char mcu_io_memory[mcu_io_memory_size];
unsigned char* const mcu_io_memory_ptr{ mcu_io_memory };

#endif

}  // nanespace base
}  // namespace avr
}  // namespace sys
}  // namespace ardo
