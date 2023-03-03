
#ifndef ARDO_MCU_AVR__H
#define ARDO_MCU_AVR__H

#include "setlx_tuple.h"
#include "setl_bit_fields.h"

namespace ardo {
namespace sys {
namespace avr {

template <unsigned mode>
struct RegisterSelector {
  template <typename T, ptrdiff_t w_addrx>
  using IoAccessor = setl::McuRegister<T, w_addrx>;
};

#ifdef AVR_MOCK_IOREGISTERS
// Alloes for mocking the IO registers, useful for unit testing.

constexpr unsigned debug_mode = AVR_MOCK_IOREGISTERS;

constexpr unsigned mcu_io_memory_size = 4096;
extern unsigned char mcu_io_memory[mcu_io_memory_size];
extern unsigned char* const mcu_io_memory_ptr;

template <>
struct RegisterSelector<1> {
  template <typename T, ptrdiff_t w_addrx>
  using IoAccessor = setl::DebugMcuRegister<T, w_addrx, mcu_io_memory_size, mcu_io_memory_ptr>;
};

#else

constexpr unsigned debug_mode = 0;
#endif

template <typename T, ptrdiff_t w_addrx>
using IoAccessor = typename RegisterSelector<debug_mode>::IoAccessor<T, w_addrx>;

}  // namespace avr
}  // namespace sys
}  // namespace ardo


#include "sys/mcu/avr/ardo_sys_avr_mcu_defs.h"

#endif // ARDO_MCU_AVR__H
