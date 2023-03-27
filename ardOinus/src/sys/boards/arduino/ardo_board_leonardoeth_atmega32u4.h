// ArdOinus specific header for board leonardoeth_atmega32u4 using the atmega32u4 MCU.

#ifndef ardo_board_leonardoeth_atmega32u4__h
#define ardo_board_leonardoeth_atmega32u4__h

#include "setl_device_map.h"
#include "setlx_type_traits.h"
#include "setlx_tuple.h"

// Include the MCU specific definitions.
#include "ardo_supplemental_atmega32u4_dev.h"

namespace ardo {
namespace sys {
namespace boards {
namespace arduino {
namespace board_leonardoeth_atmega32u4 {
    
namespace board_mcu = ardo::sys::avr::arch_atmega32u4;

struct BoardDefinition {
  static constexpr std::uint32_t CPU_FREQUENCY_HZ = 16000000L;

  using DevicePinMapping = setl::DeviceMappings<
    std::tuple<
        setl::PortMapping<board_mcu::ppPD2, 0>,
        setl::PortMapping<board_mcu::ppPD3, 1>,
        setl::PortMapping<board_mcu::ppPD1, 2>,
        setl::PortMapping<board_mcu::ppPD0, 3>,
        setl::PortMapping<board_mcu::ppPD4, 4>,
        setl::PortMapping<board_mcu::ppPC6, 5>,
        setl::PortMapping<board_mcu::ppPD7, 6>,
        setl::PortMapping<board_mcu::ppPE6, 7>,
        setl::PortMapping<board_mcu::ppPB4, 8>,
        setl::PortMapping<board_mcu::ppPB5, 9>,
        setl::PortMapping<board_mcu::ppPB6, 10>,
        setl::PortMapping<board_mcu::ppPB7, 11>,
        setl::PortMapping<board_mcu::ppPD6, 12>,
        setl::PortMapping<board_mcu::ppPC7, 13>,
        setl::PortMapping<board_mcu::ppPB3, 14>,
        setl::PortMapping<board_mcu::ppPB1, 15>,
        setl::PortMapping<board_mcu::ppPB2, 16>,
        setl::PortMapping<board_mcu::ppPB0, 17>,
        setl::PortMapping<board_mcu::ppPF7, 18>,
        setl::PortMapping<board_mcu::ppPF6, 19>,
        setl::PortMapping<board_mcu::ppPF5, 20>,
        setl::PortMapping<board_mcu::ppPF4, 21>,
        setl::PortMapping<board_mcu::ppPF1, 22>,
        setl::PortMapping<board_mcu::ppPF0, 23>,
        setl::PortMapping<board_mcu::ppPD4, 24>,
        setl::PortMapping<board_mcu::ppPD7, 25>,
        setl::PortMapping<board_mcu::ppPB4, 26>,
        setl::PortMapping<board_mcu::ppPB5, 27>,
        setl::PortMapping<board_mcu::ppPB6, 28>,
        setl::PortMapping<board_mcu::ppPD6, 29>,
        setl::PortMapping<board_mcu::ppPD5, 30>
    >
  >;
};  // Board



} // board_leonardoeth_atmega32u4
} // arduino
} // boards
} // sys
} // ardo

#endif  // ardo_board_leonardoeth_atmega32u4__h
