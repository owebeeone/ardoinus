// ArdOinus specific header for AVR atmega328p MCU.
// This file will not be regenerated (unlike ardo_supplemental_atmega328p.h)
// so manual changes to this file will survive regeneration of architecture
// specific definitions.

#ifndef ardo_supplemental_atmega328p_defs__h
#define ardo_supplemental_atmega328p_defs__h

#include "setl_int_scaler.h"
#include "setlx_cstdint.h"
#include "ardo_supplemental_atmega328p.h"

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

/**
 * Traits for TCCR register CS1 enum values. Specialized as needed.
 */
template <typename w_EnumClass> 
struct TccrEnumTraits;

using setl::NA;

template <typename w_BitfieldType,
  typename w_Register,
  template <typename T, ptrdiff_t u_addrx> typename RegisterType = ::ardo::sys::avr::IoAccessor>
using Register = setl::IoRegister<w_BitfieldType, w_Register, RegisterType>;

template <typename w_EnumT, w_EnumT w_cs1_value, std::uint32_t w_divider>
struct DividerMapping {
  using EnumT = w_EnumT;
  static constexpr EnumT cs1_value = w_cs1_value;
  static constexpr std::uint32_t divider = w_divider;
};

template <typename...Ts>
struct DividerMappings;

template <typename T>
struct DividerMappings<T> {

  using EnumT = typename T::EnumT;
  static constexpr EnumT start_range = TccrEnumTraits<EnumT>::start_range;
  static constexpr EnumT null_value = TccrEnumTraits<EnumT>::null_value;

  /**
   * Returns the divider associated with cs1_value. If not found, returns NA.
   */
  static constexpr std::uint32_t findDividerMultiple(EnumT cs1_value) {
    return cs1_value == T::cs1_value ? T::divider : NA;
  }

  /**
   * Returns the EnumCS1 associated with the largest divider less than
   * the divider provided. Returns EnumCS1::no_clk if there is no divider
   * smaller than the divider provided.
   */
  static constexpr EnumT findLargestLessThanOrEq(std::uint32_t divider) {
    return divider <= T::divider ? T::cs1_value : null_value;
  }

};

template <typename T, typename...Ts>
struct DividerMappings<T, Ts...> {

  using EnumT = typename T::EnumT;
  static constexpr EnumT start_range = TccrEnumTraits<EnumT>::start_range;
  static constexpr EnumT null_value = TccrEnumTraits<EnumT>::null_value;
  /**
   * Returns the divider associated with cs1_value. If not found, returns NA.
   */
  static constexpr std::uint32_t findDividerMultiple(EnumT cs1_value) {
    return cs1_value <= T::cs1_value 
        ? T::divider 
        : DividerMappings<Ts...>::findDividerMultiple(cs1_value);
  }

  /**
   * Returns the EnumCS1 associated with the largest divider less than
   * the divider provided. Returns EnumCS1::no_clk if there is no divider
   * smaller than the divider provided.
   */
  static constexpr EnumT findLargestLessThanOrEq(std::uint32_t divider) {
    return divider <= T::divider
        ? T::cs1_value
        : DividerMappings<Ts...>::findLargestLessThanOrEq(divider);
  }
};

/**
 * Finds the mapping associated with cs1_value. Will have a compile error if not found.
 */
//template <EnumCS1 cs1_value, typename...Ts>
//struct DividerMappingsFindCs1;
//
//template <EnumCS1 cs1_value, std::uint32_t w_divider, typename...Ts>
//struct DividerMappingsFindCs1<
//  cs1_value, DividerMappings<DividerMapping<cs1_value, w_divider>, Ts...>> {
//  using Mapping = DividerMapping<cs1_value, w_divider>;
//};
//
//template <EnumCS1 cs1_value, EnumCS1 cs1_value_w, std::uint32_t w_divider, typename...Ts>
//struct DividerMappingsFindCs1<
//  cs1_value, DividerMappings<DividerMapping<cs1_value_w, w_divider>, Ts...>> {
//  using Mapping = typename DividerMappingsFindCs1<Ts...>::Mapping;
//};


/**
 * Computes the clock multiple and divider setting for TCCCR*B registers. The divider 
 * will only apply to the internal clock source.
 *
 * @params
 * minimum_frequency : The minimum frequency setting desired.
 * timer_clock_frequency : The clock frequency of the timer/counter. usually CPU clock.
 * resolution_bits_of_top_comparator : The bit width of the "top" value comparator.
 * phase_correct_mode : If true, the clock frequency is divided by 2.
 */

template <typename T>
constexpr std::uint32_t getClockDividerMultiple(
  T minimum_frequency,
  std::uint32_t timer_clock_frequency,
  std::uint8_t resolution_bits_of_top_comparator,
  bool phase_correct_mode) {
  return timer_clock_frequency
      / ((phase_correct_mode ? 2ul : 1ul)
         * minimum_frequency
         * setl::mersenne(resolution_bits_of_top_comparator));
}

template <typename EnumT, typename T>
constexpr EnumT getClockDivider(
  T minimum_frequency,
  std::uint32_t timer_clock_frequency,
  std::uint8_t resolution_bits_of_top_comparator,
  bool phase_correct_mode) {
  using Traits = TccrEnumTraits<EnumT>;
  using FreqMapping = typename Traits::FreqMapping;
  return FreqMapping::findLargestLessThanOrEq(
    getClockDividerMultiple(
      minimum_frequency, 
      timer_clock_frequency, 
      resolution_bits_of_top_comparator, 
      phase_correct_mode));
}

/**
 * Returns the multiple for a divider setting.
 */
template <typename EnumT>
constexpr decltype(
    TccrEnumTraits<EnumT>::FreqMapping::findDividerMultiple(TccrEnumTraits<EnumT>::start_range))
  findDividerMultiple(EnumT cs1_value) {
  return TccrEnumTraits<EnumT>::FreqMapping::findDividerMultiple(cs1_value);
}

/**
 * Returns the "top count" for the timer with the given clock divider setting.
 * If an invalid clock_divider is given, 
 */
template <typename EnumT, typename T>
constexpr std::uint32_t getClockTimerTop(
  EnumT clock_divider,
  T selected_frequency,
  std::uint32_t timer_clock_frequency,
  bool phase_correct_mode) {
  using Traits = TccrEnumTraits<EnumT>;
  using FreqMapping = typename Traits::FreqMapping;
  return timer_clock_frequency
    / ((phase_correct_mode ? 2ul : 1ul)
      * selected_frequency
      * FreqMapping::findDividerMultiple(clock_divider));
}

/**
 * Define register TCCR1B CS1n definitions.
 */
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

/**
 * Mapping of EnumCS1 to divider value.
 */
// Note: must be in ascending divider order.
using Cs1DividerMapping = DividerMappings<
  DividerMapping<EnumCS1, EnumCS1::clk1, 1>,
  DividerMapping<EnumCS1, EnumCS1::clk8, 8>,
  DividerMapping<EnumCS1, EnumCS1::clk64, 64>,
  DividerMapping<EnumCS1, EnumCS1::clk256, 256>,
  DividerMapping<EnumCS1, EnumCS1::clk1024, 1024>
>;

/**
 * Traits for the EnumCS1 used by getClockDivider to discover
 * the clock divider for a specific frequency.
 */
template <>
struct TccrEnumTraits<EnumCS1> {
  using EnumT = EnumCS1;
  using FreqMapping = Cs1DividerMapping;
  static constexpr EnumT null_value = EnumT::no_clk;
  static constexpr EnumT start_range = EnumT::clk1;
  static constexpr EnumT end_range = EnumT::clk1024;
};

static_assert(
  getClockDivider<EnumCS1>(100000, 16000000, 16, false) == EnumCS1::clk1,
  "Clockdivider computation failed or 100kHz and 16 bit comparator.");

static_assert(
  getClockDivider<EnumCS1>(2, 16000000, 16, true) == EnumCS1::clk64,
  "Clockdivider computation failed or 2Hz and 16 bit comparator in phase correct mode.");

static_assert(
  getClockDivider<EnumCS1>(2, 16000000, 16, false) == EnumCS1::clk256,
  "Clockdivider computation failed or 2Hz and 16 bit comparator.");

static_assert(
  getClockDivider<EnumCS1>(0.5, 16000000, 16, false) == EnumCS1::clk1024,
  "Clockdivider computation failed or 0.5Hz and 16 bit comparator.");

static_assert(
  getClockTimerTop(EnumCS1::clk1, 100000, 16000000, true) == 80ul,
  "getClockTimerTop computation failed or 100kHz and clk1 clock divider on phase correct mode.");

static_assert(
  getClockTimerTop(EnumCS1::clk1024, 0.5, 16000000, true) == 15625ul,
  "getClockTimerTop computation failed or 0.5kHz and clk1024 clock divider on phase correct mode.");

/**
 * Controls for output compare register modes.
 */
enum class EnumCOM1 : unsigned char {
  disconnect = 0b00,
  toggle = 0b01,
  clear = 0b10,
  set = 0b11
};

/**
 * Bit field definitions for the COM1A and COM1B fields.
 */
using BitsCOM1A = setl::BitsRW<EnumCOM1, ccCOM1A1, ccCOM1A0>;
using BitsCOM1B = setl::BitsRW<EnumCOM1, ccCOM1B1, ccCOM1B0>;

/**
 * Defines for operating modes of the timer/counter.
 */
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

/**
 * Mapping of EnumWGM1 to constants for top values.
 */
 // Note: must be in ascending divider order.
using Wgm1TopCountMapping = DividerMappings<
  DividerMapping<EnumWGM1, EnumWGM1::normal, setl::mersenne(16)>,
  DividerMapping<EnumWGM1, EnumWGM1::pwm_phase_correct_8bit, setl::mersenne(8)>,
  DividerMapping<EnumWGM1, EnumWGM1::pwm_phase_correct_9bit, setl::mersenne(9)>,
  DividerMapping<EnumWGM1, EnumWGM1::pwm_phase_correct_10bit, setl::mersenne(10)>,
  DividerMapping<EnumWGM1, EnumWGM1::fast_pwm_8bit, setl::mersenne(8)>,
  DividerMapping<EnumWGM1, EnumWGM1::fast_pwm_9bit, setl::mersenne(9)>,
  DividerMapping<EnumWGM1, EnumWGM1::fast_pwm_10bit, setl::mersenne(10)>
>;

using BitsWGM1_10 = setl::BitsRW<EnumWGM1, NA, NA, ccWGM11, ccWGM10>;
using BitsWGM1_32 = setl::BitsRW<EnumWGM1, ccWGM13, ccWGM12, NA, NA>;
// Define bitfields when treating TCCR1A and TCCR1B as a 16 bit value.
using BitsWGM1_3210 = setl::BitsRW<EnumWGM1, ccWGM13 + 8, ccWGM12 + 8, ccWGM11, ccWGM10>;

using BitsCS11 = setl::BitsRW<EnumCS1, ccCS12, ccCS11, ccCS10>;
// Define bitfields when treating TCCR1A and TCCR1B as a 16 bit value.
using BitsCS11_16 = setl::BitsRW<EnumCS1, ccCS12 + 8, ccCS11 + 8, ccCS10 + 8>;

using BitsICNC1 = setl::BitsRW<bool, ccICNC1>;
using BitsICES1 = setl::BitsRW<bool, ccICES1>;
// Define bitfields when treating TCCR1A and TCCR1B as a 16 bit value.
using BitsICNC1_16 = setl::BitsRW<bool, ccICNC1 + 8>;
using BitsICES1_16 = setl::BitsRW<bool, ccICES1 + 8>;

using FieldsTCCR1A = setl::BitFields<BitsCOM1A, BitsCOM1B, BitsWGM1_10>;
using FieldsTCCR1AB = setl::BitFields<
  BitsCOM1A, BitsCOM1B, BitsWGM1_3210, BitsCS11_16, BitsICNC1_16, BitsICES1_16>;

// Add a TCCR1AB 16 bit register.
using rrTCCR1AB = MemRegisterDef<std::uint16_t, 0x80>;
using RegisterTCCR1AB = Register<FieldsTCCR1AB, rrTCCR1AB>;


using FieldsTCCR1B = setl::BitFields<BitsWGM1_32, BitsCS11, BitsICES1, BitsICNC1>;
using RegisterTCCR1B = Register<FieldsTCCR1B, rrTCCR1B>;

using BitsICR1 = setl::BitsRW<setl::SemanticType<setl::hash("ICR1"), std::uint16_t>,
  ccICR1H7 + 8,
  ccICR1H6 + 8,
  ccICR1H5 + 8,
  ccICR1H4 + 8,
  ccICR1H3 + 8,
  ccICR1H2 + 8,
  ccICR1H1 + 8,
  ccICR1H0 + 8,
  ccICR1L7,
  ccICR1L6,
  ccICR1L5,
  ccICR1L4,
  ccICR1L3,
  ccICR1L2,
  ccICR1L1,
  ccICR1L0
>;

using FieldsICR1 = setl::BitFields<BitsICR1>;
using RegisterIRC1 = Register<FieldsICR1, rrICR1>;

template <
  typename w_RegisterTCCRAB,
  typename w_RegisterIRC,
  std::uint32_t w_setup_frequency,
  bool w_phase_correct_mode,
  std::uint32_t w_base_frequency  // Usually CPU clock frequency.
>
struct Timer16 {
  using TccrAB = w_RegisterTCCRAB;
  using Tirc = w_RegisterIRC;
  static constexpr std::uint32_t setup_frequency = w_setup_frequency;
  static constexpr std::uint32_t base_frequency = w_base_frequency;
  static constexpr bool phase_correct_mode = w_phase_correct_mode;
  static constexpr EnumCS1 cs1_value = getClockDivider<EnumCS1>(
    setup_frequency, base_frequency, 16, phase_correct_mode);
  static constexpr auto top_count = getClockTimerTop(
    cs1_value, setup_frequency, base_frequency, phase_correct_mode);

  static_assert(cs1_value != EnumCS1::no_clk, "Impossible frequency settings for timer.");
  static_assert(top_count >= 2u, "Impossible frequency settings for timer.");

  /**
   *
   */
  static void setFastPwm() {
    TccrAB::ReadModifyWrite(BitsCS11_16{ cs1_value }, BitsWGM1_3210{ EnumWGM1::fast_pwm_icr1 });
    Tirc::Write(BitsICR1{ top_count });
  }
};

template <
  std::uint32_t w_setup_frequency,
  bool w_phase_correct_mode,
  std::uint32_t w_base_frequency  // Usually CPU clock frequency.
>
using TC1 = Timer16<RegisterTCCR1AB, RegisterIRC1, w_setup_frequency, w_phase_correct_mode, w_base_frequency>;


}  // arch_atmega328p
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega328p_defs__h
