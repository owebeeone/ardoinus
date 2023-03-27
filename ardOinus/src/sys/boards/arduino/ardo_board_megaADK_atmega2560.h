// ArdOinus specific header for board megaADK_atmega2560 using the atmega2560 MCU.

#ifndef ardo_board_megaADK_atmega2560__h
#define ardo_board_megaADK_atmega2560__h

#include "setl_device_map.h"
#include "setlx_type_traits.h"
#include "setlx_tuple.h"

// Include the MCU specific definitions.
#include "ardo_supplemental_atmega2560_dev.h"

namespace ardo {
namespace sys {
namespace boards {
namespace arduino {
namespace board_megaADK_atmega2560 {
    
namespace board_mcu = ardo::sys::avr::arch_atmega2560;

struct BoardDefinition {
  static constexpr std::uint32_t CPU_FREQUENCY_HZ = 16000000L;

  using DevicePinMapping = setl::DeviceMappings<
    std::tuple<
        setl::PortMapping<board_mcu::ppPE0, 0>,
        setl::PortMapping<board_mcu::ppPE1, 1>,
        setl::PortMapping<board_mcu::ppPE4, 2>,
        setl::PortMapping<board_mcu::ppPE5, 3>,
        setl::PortMapping<board_mcu::ppPG5, 4>,
        setl::PortMapping<board_mcu::ppPE3, 5>,
        setl::PortMapping<board_mcu::ppPH3, 6>,
        setl::PortMapping<board_mcu::ppPH4, 7>,
        setl::PortMapping<board_mcu::ppPH5, 8>,
        setl::PortMapping<board_mcu::ppPH6, 9>,
        setl::PortMapping<board_mcu::ppPB4, 10>,
        setl::PortMapping<board_mcu::ppPB5, 11>,
        setl::PortMapping<board_mcu::ppPB6, 12>,
        setl::PortMapping<board_mcu::ppPB7, 13>,
        setl::PortMapping<board_mcu::ppPJ1, 14>,
        setl::PortMapping<board_mcu::ppPJ0, 15>,
        setl::PortMapping<board_mcu::ppPH1, 16>,
        setl::PortMapping<board_mcu::ppPH0, 17>,
        setl::PortMapping<board_mcu::ppPD3, 18>,
        setl::PortMapping<board_mcu::ppPD2, 19>,
        setl::PortMapping<board_mcu::ppPD1, 20>,
        setl::PortMapping<board_mcu::ppPD0, 21>,
        setl::PortMapping<board_mcu::ppPA0, 22>,
        setl::PortMapping<board_mcu::ppPA1, 23>,
        setl::PortMapping<board_mcu::ppPA2, 24>,
        setl::PortMapping<board_mcu::ppPA3, 25>,
        setl::PortMapping<board_mcu::ppPA4, 26>,
        setl::PortMapping<board_mcu::ppPA5, 27>,
        setl::PortMapping<board_mcu::ppPA6, 28>,
        setl::PortMapping<board_mcu::ppPA7, 29>,
        setl::PortMapping<board_mcu::ppPC7, 30>,
        setl::PortMapping<board_mcu::ppPC6, 31>,
        setl::PortMapping<board_mcu::ppPC5, 32>,
        setl::PortMapping<board_mcu::ppPC4, 33>,
        setl::PortMapping<board_mcu::ppPC3, 34>,
        setl::PortMapping<board_mcu::ppPC2, 35>,
        setl::PortMapping<board_mcu::ppPC1, 36>,
        setl::PortMapping<board_mcu::ppPC0, 37>,
        setl::PortMapping<board_mcu::ppPD7, 38>,
        setl::PortMapping<board_mcu::ppPG2, 39>,
        setl::PortMapping<board_mcu::ppPG1, 40>,
        setl::PortMapping<board_mcu::ppPG0, 41>,
        setl::PortMapping<board_mcu::ppPL7, 42>,
        setl::PortMapping<board_mcu::ppPL6, 43>,
        setl::PortMapping<board_mcu::ppPL5, 44>,
        setl::PortMapping<board_mcu::ppPL4, 45>,
        setl::PortMapping<board_mcu::ppPL3, 46>,
        setl::PortMapping<board_mcu::ppPL2, 47>,
        setl::PortMapping<board_mcu::ppPL1, 48>,
        setl::PortMapping<board_mcu::ppPL0, 49>,
        setl::PortMapping<board_mcu::ppPB3, 50>,
        setl::PortMapping<board_mcu::ppPB2, 51>,
        setl::PortMapping<board_mcu::ppPB1, 52>,
        setl::PortMapping<board_mcu::ppPB0, 53>,
        setl::PortMapping<board_mcu::ppPF0, 54>,
        setl::PortMapping<board_mcu::ppPF1, 55>,
        setl::PortMapping<board_mcu::ppPF2, 56>,
        setl::PortMapping<board_mcu::ppPF3, 57>,
        setl::PortMapping<board_mcu::ppPF4, 58>,
        setl::PortMapping<board_mcu::ppPF5, 59>,
        setl::PortMapping<board_mcu::ppPF6, 60>,
        setl::PortMapping<board_mcu::ppPF7, 61>,
        setl::PortMapping<board_mcu::ppPK0, 62>,
        setl::PortMapping<board_mcu::ppPK1, 63>,
        setl::PortMapping<board_mcu::ppPK2, 64>,
        setl::PortMapping<board_mcu::ppPK3, 65>,
        setl::PortMapping<board_mcu::ppPK4, 66>,
        setl::PortMapping<board_mcu::ppPK5, 67>,
        setl::PortMapping<board_mcu::ppPK6, 68>,
        setl::PortMapping<board_mcu::ppPK7, 69>
    >
  >;
};  // Board



} // board_megaADK_atmega2560
} // arduino
} // boards
} // sys
} // ardo

#endif  // ardo_board_megaADK_atmega2560__h
