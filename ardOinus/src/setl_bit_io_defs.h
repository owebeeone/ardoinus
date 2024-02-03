/**
 * bit field io/memory mapped register define.
 */

#ifndef ARDO_AVR_BIT_IO_DEFS___H
#define ARDO_AVR_BIT_IO_DEFS___H

#include "setlx_cstdint.h"

namespace ardo {
namespace sys {
namespace avr {
namespace nfp {

/**
 * Defines an IO location for a mapped location.
 */
template <typename T, ptrdiff_t w_addr>
struct MemRegisterDef {
  static constexpr ptrdiff_t addr = w_addr;
  using type = T;
};

template <typename T, ptrdiff_t w_addr, ptrdiff_t w_offset>
struct IoRegisterDef {
  static constexpr ptrdiff_t offset = w_offset;
  static constexpr ptrdiff_t addr = w_addr + offset;
  using type = T;
};

}  // namespace nfp
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ARDO_AVR_BIT_IO_DEFS___H