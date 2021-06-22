// ArdOinus specific header for AVR atmega328p MCU.
// This file will not be regenerated (unlike ardo_supplemental_atmega328p.h)
// so manual changes to this file will survive regeneration of architecture
// specific definitions.

#ifndef ardo_supplemental_atmega328p_defs__h
#define ardo_supplemental_atmega328p_defs__h

#include "ardo_supplemental_atmega328p.h"

#include "setlx_cstdint.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_atmega328p {

// Add only atmega328p specific resources here.
// Resources in this namespace will appear in the ardo::sys::avr::mcu
// namespace when compiled for the atmega328p architecture.
// Any code added here should be independent of compiler provided resources
// so as to enable compiling of this code in any environment for the 
// purpose of cross platform testing.


using setl::NA;

template <typename w_BitfieldType,
  typename w_Register,
  template <typename T, ptrdiff_t u_addrx> typename RegisterType = RegisterSelector<debug_mode>::IoAccessor>
using Register = setl::IoRegister<w_BitfieldType, w_Register, RegisterType>;


enum class EnumCOM1 : unsigned char {
  disconnect = 0b00,
  toggle = 0b01,
  clear = 0b10,
  set = 0b11
};

using BitsCOM1A = setl::BitsRW<EnumCOM1, COM1A1, COM1A0>;
using BitsCOM1B = setl::BitsRW<EnumCOM1, COM1B1, COM1B0>;

enum class EnumWGM1 : unsigned char {
  normal = 0b0000,
  pwm_phase_correct_8bit = 0b0001,
  pwm_phase_correct_9bit = 0b0010,
  pwm_phase_correct_10bit = 0b0011,
  ctc_ocr1a = 0b0100,
  fast_pwm_8bit = 0b0101,
  fast_pwm_9bit = 0b0110,
  fast_pwm_10bit = 0b0111,
  pwm_phase_freq_correct_icr1 = 0b1000,
  pwm_phase_freq_correct_ocr1a = 0b1001,
  pwm_phase_correct_icr1 = 0b1010,
  pwm_phase_correct_ocr1a = 0b1011,
  ctc_icr1 = 0b1100,
  reserved_d = 0b1101,
  fast_pwm_icr1 = 0b1110,
  fast_pwm_ocr1a = 0b1111,
};

using BitsWGM1_10 = setl::BitsRW<EnumWGM1, NA, NA, WGM11, WGM10>;
using BitsWGM1_32 = setl::BitsRW<EnumWGM1, WGM13, WGM12, NA, NA>;

using FieldsTCCR1A = setl::BitFields<BitsCOM1A, BitsCOM1B, BitsWGM1_10>;
enum class EnumCS1 : unsigned char {
  no_clk = 0b000,
  clk1 = 0b001,
  clk8 = 0b010,
  clk64 = 0b011,
  clk256 = 0b100,
  clk1024 = 0b101,
  ext_clk_falling = 0b110,
  ext_clk_rising = 0b111,
};

using BitsCS11 = setl::BitsRW<EnumCS1, CS12, CS11, CS10>;

using BitsICNC1 = setl::BitsRW<bool, ICNC1>;
using BitsICES1 = setl::BitsRW<bool, ICES1>;

using FieldsTCCR1B = setl::Format<std::uint8_t, BitsWGM1_32, BitsCS11, BitsICES1, BitsICNC1>;
using RegisterTCCR1B = Register<FieldsTCCR1B, rrTCCR1B>;

}  // arch_atmega328p
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega328p_defs__h
