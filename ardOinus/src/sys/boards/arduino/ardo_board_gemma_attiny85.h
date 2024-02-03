// ArdOinus specific header for board gemma_attiny85 using the attiny85 MCU.

#ifndef ardo_board_gemma_attiny85__h
#define ardo_board_gemma_attiny85__h

#include "setl_device_map.h"
#include "setlx_type_traits.h"
#include "setlx_tuple.h"

// Include the MCU specific definitions.
#include "sys/mcu/avr/ardo_supplemental_attiny85_dev.h"

namespace ardo {
namespace sys {
namespace boards {
namespace arduino {
namespace board_gemma_attiny85 {
    
namespace board_mcu = ardo::sys::avr::arch_attiny85;

struct BoardDefinition {
  static constexpr std::uint32_t CPU_FREQUENCY_HZ = 8000000L;

  using DevicePinMapping = setl::DeviceMappings<
    std::tuple<
        setl::PortMapping<board_mcu::ppPB0, 0>,
        setl::PortMapping<board_mcu::ppPB1, 1>,
        setl::PortMapping<board_mcu::ppPB2, 2>,
        setl::PortMapping<board_mcu::ppPB3, 3>,
        setl::PortMapping<board_mcu::ppPB4, 4>,
        setl::PortMapping<board_mcu::ppPB5, 5>,
        setl::PortMapping<board_mcu::ppPB5, 6>,
        setl::PortMapping<board_mcu::ppPB2, 7>,
        setl::PortMapping<board_mcu::ppPB4, 8>,
        setl::PortMapping<board_mcu::ppPB3, 9>
    >
  >;
};  // Board



} // board_gemma_attiny85
} // arduino
} // boards
} // sys
} // ardo

#endif  // ardo_board_gemma_attiny85__h
