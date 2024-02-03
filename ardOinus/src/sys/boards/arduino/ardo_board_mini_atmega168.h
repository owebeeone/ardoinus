// ArdOinus specific header for board mini_atmega168 using the atmega168 MCU.

#ifndef ardo_board_mini_atmega168__h
#define ardo_board_mini_atmega168__h

#include "setl_device_map.h"
#include "setlx_type_traits.h"
#include "setlx_tuple.h"

// Include the MCU specific definitions.
#include "sys/mcu/avr/ardo_supplemental_atmega168_dev.h"

namespace ardo {
namespace sys {
namespace boards {
namespace arduino {
namespace board_mini_atmega168 {
    
namespace board_mcu = ardo::sys::avr::arch_atmega168;

struct BoardDefinition {
  static constexpr std::uint32_t CPU_FREQUENCY_HZ = 16000000L;

  using DevicePinMapping = setl::DeviceMappings<
    std::tuple<
        setl::PortMapping<board_mcu::ppPD0, 0>,
        setl::PortMapping<board_mcu::ppPD1, 1>,
        setl::PortMapping<board_mcu::ppPD2, 2>,
        setl::PortMapping<board_mcu::ppPD3, 3>,
        setl::PortMapping<board_mcu::ppPD4, 4>,
        setl::PortMapping<board_mcu::ppPD5, 5>,
        setl::PortMapping<board_mcu::ppPD6, 6>,
        setl::PortMapping<board_mcu::ppPD7, 7>,
        setl::PortMapping<board_mcu::ppPB0, 8>,
        setl::PortMapping<board_mcu::ppPB1, 9>,
        setl::PortMapping<board_mcu::ppPB2, 10>,
        setl::PortMapping<board_mcu::ppPB3, 11>,
        setl::PortMapping<board_mcu::ppPB4, 12>,
        setl::PortMapping<board_mcu::ppPB5, 13>,
        setl::PortMapping<board_mcu::ppPC0, 14>,
        setl::PortMapping<board_mcu::ppPC1, 15>,
        setl::PortMapping<board_mcu::ppPC2, 16>,
        setl::PortMapping<board_mcu::ppPC3, 17>,
        setl::PortMapping<board_mcu::ppPC4, 18>,
        setl::PortMapping<board_mcu::ppPC5, 19>
    >
  >;
};  // Board



} // board_mini_atmega168
} // arduino
} // boards
} // sys
} // ardo

#endif  // ardo_board_mini_atmega168__h
