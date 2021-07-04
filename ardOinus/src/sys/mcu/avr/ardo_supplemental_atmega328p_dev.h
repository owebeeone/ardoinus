// ArdOinus specific header for AVR atmega328p MCU.
// This file will not be regenerated (unlike ardo_supplemental_atmega328p.h)
// so manual changes to this file will survive regeneration of architecture
// specific definitions.

#ifndef ardo_supplemental_atmega328p_defs__h
#define ardo_supplemental_atmega328p_defs__h

#include "setl_cat_tuples.h"
#include "setl_int_scaler.h"
#include "setl_system.h"
#include "setlx_cstdint.h"
#include "ardo_supplemental_atmega328p.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_atmega328p {

/**
 * RootDependencies et al. Allows for a graph of resource dependencies
 * to determine what resources conflict if attempting to use them together.
 * The depencency graph must be acyclic (DAG). A resource that depends on
 * itself or nothing else is a root resource.
 */
namespace nfp {
// The nfp namespace is not part of the supported interface.
template <typename...T>
struct RootDependencyFinder;

template <typename T, typename w_Deps>
struct RootDependencyOfHelper;

template <typename T>
struct RootDependencyOfHelper<T, std::tuple<T>> {
  using result = std::tuple<T>;
};

template <typename T>
struct RootDependencyOfHelper<T, std::tuple<>> {
  using result = std::tuple<T>;
};

template <typename T, typename...D>
struct RootDependencyOfHelper<T, std::tuple<D...>> {
  using result = typename RootDependencyFinder<D...>::root_deps;
};

template <typename T>
struct RootDependencyOf {
  using result = typename RootDependencyOfHelper<
    T, typename T::dependencies>::result;
};

template <>
struct RootDependencyFinder<> {
  using root_deps = std::tuple<>;
};

template <typename T, typename...Ts>
struct RootDependencyFinder<T, Ts...> {
  using t_deps = typename RootDependencyOf<T>::result;
  using ts_deps = typename RootDependencyFinder<Ts...>::root_deps;
  using root_deps = typename setl::cat_tuples<t_deps, ts_deps>::type;
};

template <typename T>
struct RootDependencyHelper;

template <typename...P>
struct RootDependencyHelper<std::tuple<P...>> {
  using root_deps = typename RootDependencyFinder<P...>::root_deps;
};
} // namespace nfp

/**
 * Defines a resouce dependency.
 * T is a resource type.
 * P is a tuple of all resources T depends on.
 * 
 * For example: The SPI resource depends on the MISO, MOSI, SCK, SS
 * resources. Hence Dependency<SPI, std::tuple<MISO, MOSI, SCK, SS>> 
 * defines such a relationship. All the dependent resources must also
 * be derived from Dependency.
 */
template <typename T, typename P=std::tuple<T>>
struct Dependency;

template <typename T, typename...Ps>
struct Dependency<T, std::tuple<Ps...>> {
  using self = T;
  using dependencies = std::tuple<Ps...>;
};

/**
 * Tuple of root dependencies of a resource.
 */
template <typename T>
using RootDependencies = typename nfp::RootDependencyHelper<
  typename T::dependencies>::root_deps;


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
  findDividerMultiple(EnumT value) {
  return TccrEnumTraits<EnumT>::FreqMapping::findDividerMultiple(value);
}

/**
 * Returns the "top count" for the timer with the given clock divider setting.
 * If an invalid clock_divider is given the unit clock divider is assumed.
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

static_assert(
  getClockTimerTop(EnumCS1::no_clk, 1, 16000000, true) == 8000000ul,
  "getClockTimerTop computation failed for invalid divider.");

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

// Defines the 16 bits for the ICR1 register. 
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
using TC1 = Timer16<
  RegisterTCCR1AB, RegisterIRC1, w_setup_frequency, w_phase_correct_mode, w_base_frequency>;

/**
 * Defines GPIO ports.
 */
// Defines bits for ports. e.g.
// using BitsPORTB7 = setl::BitsRW<setl::SemanticType<setl::hash("PORTB7"), bool>, ccPORTB7>;
#define MakePortBit(TYPE, LETTER, N) \
using Bits ## TYPE ## LETTER ## N = setl::BitsRW<setl::SemanticType<setl::hash(#TYPE #LETTER #N), bool>, cc ## ## TYPE ## LETTER ## N>

#define MakePort8(TYPE, RTYPE, LETTER) \
MakePortBit(TYPE, LETTER, 7); \
MakePortBit(TYPE, LETTER, 6); \
MakePortBit(TYPE, LETTER, 5); \
MakePortBit(TYPE, LETTER, 4); \
MakePortBit(TYPE, LETTER, 3); \
MakePortBit(TYPE, LETTER, 2); \
MakePortBit(TYPE, LETTER, 1); \
MakePortBit(TYPE, LETTER, 0); \
 \
using Fields ## TYPE ## LETTER = setl::BitFields< \
  Bits ## TYPE ## LETTER ## 7, \
  Bits ## TYPE ## LETTER ## 6, \
  Bits ## TYPE ## LETTER ## 5, \
  Bits ## TYPE ## LETTER ## 4, \
  Bits ## TYPE ## LETTER ## 3, \
  Bits ## TYPE ## LETTER ## 2, \
  Bits ## TYPE ## LETTER ## 1, \
  Bits ## TYPE ## LETTER ## 0>; \
 \
using Register ## TYPE ## LETTER = Register<Fields ## TYPE ## LETTER, rr ## RTYPE ## LETTER>; \
// end MakePort8

#define MakePortRegisters8(LETTER) \
MakePort8(PORT, PORT, LETTER) \
MakePort8(DD, DDR, LETTER) \
MakePort8(PIN, PIN, LETTER) \
// End MakePortRegisters

// PORT/DDR/PIN C7 does not exist for atmega328p, defining here to simplify.
constexpr unsigned ccPORTC7 = 7;
constexpr unsigned ccDDC7 = 7;
constexpr unsigned ccPINC7 = 7;

MakePortRegisters8(B)
MakePortRegisters8(C)
MakePortRegisters8(D)

#undef MakePortRegisters8
#undef MakePort8
#undef MakePortBit

/**
 * Collects all the bits and registers for a single GPIO port.
 */
template <
  typename w_PortBit,
  typename w_PinBit,
  typename w_DdBit,
  typename w_PortReg,
  typename w_PinReg,
  typename w_DdReg>
struct GpioPortDefinition {
  using PortBit = w_PortBit;
  using PinBit = w_PinBit;
  using DdBit = w_DdBit;
  using PortReg = w_PortReg;
  using PinReg = w_PinReg;
  using DdReg = w_DdReg;
};

/**
 * Appliers provides a template class that may be used to perform a number
 * bitfield operations.
 */
template <typename...w_Appliers>
struct Appliers;

template <typename w_BitField, typename w_BitField::type w_value, typename w_Register>
struct Applier {
  template <typename...w_Appliers>
  friend struct Appliers;

private:
  static void apply() {
    w_Register::ReadModifyWrite(w_BitField{w_value});
  }
};

template <>
struct Appliers<> {
  template <typename...v_Appliers>
  friend struct Appliers;

  using types = std::tuple<>;
  static void apply() {
  }
};

template <typename w_Applier, typename...w_Appliers>
struct Appliers<w_Applier, w_Appliers...> {
  template <typename...v_Appliers>
  friend struct Appliers;
  friend struct ApplierRunner;

  using types = std::tuple<w_Applier, w_Appliers...>;

 private:
  static void apply() {
    w_Applier::apply();
    Appliers<w_Appliers...>::apply();
  }
};

/**
 * Provides "apply" frunctions that execute the given bit Appliers. One of the
 * functions performs a synchronization (memory barrier) as may be needed on some
 * microcontrollers.
 */
struct ApplierRunner {
 protected:
  /// Applies the given "Appliers" and performs a sync barrier.
  template <typename w_Appliers>
  static void applySync() {
    setl::System::MemoryBarrier barrier;
    w_Appliers::apply();
  }

  /// Applies the given "Appliers".
  template <typename w_Appliers>
  static void applyNoSync() {
    w_Appliers::apply();
  }
};

/**
 * Interface for GPIO ports.
 * Provides configuration support either by function or configuration
 * types. i.e the following are equivalent, however ppPB7::ConfigureInputPullup
 * may be used as a template configuration parameter:
 *   ppPB7::configure<ppPB7::ConfigureInputPullup>();
 *   ppPB7::configure(false, true);  // Can be used dynamically.
 */
template <
  typename w_GpioPort,
  typename w_GpioPortDefinition>
struct GpioPort : 
    Dependency<w_GpioPort, std::tuple<w_GpioPort>>,
    ApplierRunner, 
    w_GpioPortDefinition {
  using DerivedPort = w_GpioPort;
  using GpioPortDefinition = w_GpioPortDefinition;
  using PortBit = typename GpioPortDefinition::PortBit;
  using PinBit = typename GpioPortDefinition::PinBit;
  using DdBit = typename GpioPortDefinition::DdBit;
  using PortReg = typename GpioPortDefinition::PortReg;
  using PinReg = typename GpioPortDefinition::PinReg;
  using DdReg = typename GpioPortDefinition::DdReg;

  template <bool is_output, bool with_pullup>
  using Configure = Appliers<
    Applier<DdBit, is_output, DdReg>, Applier<PortBit, with_pullup, PortReg>>;

  template <bool is_output, bool with_pullup>
  using ConfigureLevelFirst = Appliers<
    Applier<PortBit, with_pullup, PortReg>, Applier<DdBit, is_output, DdReg>> ;

  // Table 13-1 of the ATMEGA328P datasheet defines these bits.
  // These assume the ccPUD bit rrMCUCR is 0 (false).
  using ConfigureInput = Configure<false, false>;
  using ConfigureInputPullup = Configure<false, true>;
  using ConfigureOutputFalse = Configure<true, false>;
  using ConfigureOutputTrue = Configure<true, true>;

 public:
  /// configure the GPIO based on the Configure<out, pullup> template type.
  template <typename w_Configuration>
  static void configure() {
    // ApplierRunner performs state synchronization.
    ApplierRunner::applySync<w_Configuration>();
  }

  static void configure(bool is_output, bool with_pullup) {
    // Synchronization block.
    { // AVR needs gpio pin register configurations changes to have a 
      // synchronizing clock cycle.
      setl::System::MemoryBarrier barrier;
      DdReg::ReadModifyWrite(DdBit{ is_output });
      PortReg::ReadModifyWrite(PortBit{ with_pullup });
    }
  }

  /// Sets the level of the output bit (true = HIGH, false = LOW).
  static void set(bool out) {
    PortReg::ReadModifyWrite(PortBit{ out });
  }

  /// Gets the current value of the GPIO pin.
  static bool get() {
    PinBit pin = PinReg::Read();
    return pin.value;
  }
};

#define MakeGpioPort(L, N) \
struct ppP ## L ## N : GpioPort<ppP ## L ## N, GpioPortDefinition< \
  BitsPORT ## L ## N, BitsPIN ## L ## N, BitsDD ## L ## N, \
  RegisterPORT ## L, RegisterPIN ## L, RegisterDD ## L>> \
{}; \
// End MakeGpioPort

MakeGpioPort(B, 0)
MakeGpioPort(B, 1)
MakeGpioPort(B, 2)
MakeGpioPort(B, 3)
MakeGpioPort(B, 4)
MakeGpioPort(B, 5)
MakeGpioPort(B, 6)
MakeGpioPort(B, 7)
MakeGpioPort(C, 0)
MakeGpioPort(C, 1)
MakeGpioPort(C, 2)
MakeGpioPort(C, 3)
MakeGpioPort(C, 4)
MakeGpioPort(C, 5)
MakeGpioPort(C, 6)
MakeGpioPort(D, 0)
MakeGpioPort(D, 1)
MakeGpioPort(D, 2)
MakeGpioPort(D, 3)
MakeGpioPort(D, 4)
MakeGpioPort(D, 5)
MakeGpioPort(D, 6)
MakeGpioPort(D, 7)
#undef MakeGpioPort

/**
 * An input only GPIO port. Use when the GPIO should never change mode.
 */
template <typename w_Gpio, bool with_pullup>
struct InputGpioPort {
  using Gpio = w_Gpio;
  using Configuration = typename Gpio::template Configure<false, with_pullup>;

  static void configure() {
    Gpio::template configure<Configuration>();
  }

  /// Gets the current value of the GPIO pin.
  static bool get() {
    return Gpio::get();
  }
};

/**
 * An output only GPIO port. Use when the GPIO should never change mode.
 */
template <typename w_Gpio, bool default_value = false>
struct OutputGpioPort {
  using Gpio = w_Gpio;
  using Configuration = typename Gpio::template Configure<true, default_value>;

  static void configure() {
    Gpio::template configure<Configuration>();
  }

  /// Sets the level of the output bit (true = HIGH, false = LOW).
  static void set(bool out) {
    return Gpio::set(out);
  }

  /// Gets the current value of the GPIO pin.
  static bool get() {
    return Gpio::get();
  }
};

/**
 * A biderectional GPIO port. Use when emulating an "open drain"/ 
 * "open collector" input, output type protocols.
 */
template <typename w_Gpio, bool with_pullup = true>
struct BidirectionalGpioPort {
  using Gpio = w_Gpio;
  using ConfigurationHigh = typename Gpio::template Configure<false, with_pullup>;
  using ConfigurationOutLow = typename Gpio::template ConfigureLevelFirst<true, false>;

  static void configure() {
    return Gpio::template configure<ConfigurationHigh>();
  }

  /// Sets the level of the output bit (true = HIGH, false = LOW).
  static void set(bool out) {
    if (out) {
      Gpio::template configure<ConfigurationHigh>();
    } else {
      Gpio::template configure<ConfigurationOutLow>();
    }
  }

  /// Gets the current value of the GPIO pin.
  static bool get() {
    return Gpio::get();
  }
};

struct ppADC6 : Dependency<ppADC6, std::tuple<ppADC6>> {
};

struct ppADC7 : Dependency<ppADC7, std::tuple<ppADC7>> {
};

struct ppT0 : Dependency<ppT0, std::tuple<ppPD4>> {
};

struct ppT1 : Dependency<ppT1, std::tuple<ppPD5>> {
};

struct ppXCK : Dependency<ppXCK, std::tuple<ppPD4>> {
};

struct ppADC0 : Dependency<ppADC0, std::tuple<ppPC0>> {
};

struct ppADC1 : Dependency<ppADC1, std::tuple<ppPC1>> {
};

struct ppADC2 : Dependency<ppADC2, std::tuple<ppPC2>> {
};

struct ppADC3 : Dependency<ppADC3, std::tuple<ppPC3>> {
};

struct ppADC4 : Dependency<ppADC4, std::tuple<ppPC4>> {
};

struct ppADC5 : Dependency<ppADC5, std::tuple<ppPC5>> {
};

struct ppCLKO : Dependency<ppCLKO, std::tuple<ppPB0>> {
};

struct ppICP1 : Dependency<ppICP1, std::tuple<ppPB0>> {
};

struct ppINT0 : Dependency<ppINT0, std::tuple<ppPD2>> {
};

struct ppINT1 : Dependency<ppINT1, std::tuple<ppPD3>> {
};

struct ppOC0A : Dependency<ppOC0A, std::tuple<ppPD6>> {
};

struct ppOC0B : Dependency<ppOC0B, std::tuple<ppPD5>> {
};

struct ppOC1A : Dependency<ppOC1A, std::tuple<ppPB1>> {
};

struct ppOC1B : Dependency<ppOC1B, std::tuple<ppPB2>> {
};

struct ppOC2A : Dependency<ppOC2A, std::tuple<ppPB3>> {
};

struct ppOC2B : Dependency<ppOC2B, std::tuple<ppPD3>> {
};

struct ppRESET : Dependency<ppRESET, std::tuple<ppPC6>> {
};

struct ppTOSC1 : Dependency<ppTOSC1, std::tuple<ppPB6>> {
};

struct ppTOSC2 : Dependency<ppTOSC2, std::tuple<ppPB7>> {
};

struct ppPCINT0 : Dependency<ppPCINT0, std::tuple<ppPB0>> {
};

struct ppPCINT1 : Dependency<ppPCINT1, std::tuple<ppPB1>> {
};

struct ppPCINT2 : Dependency<ppPCINT2, std::tuple<ppPB2>> {
};

struct ppPCINT3 : Dependency<ppPCINT3, std::tuple<ppPB3>> {
};

struct ppPCINT4 : Dependency<ppPCINT4, std::tuple<ppPB4>> {
};

struct ppPCINT5 : Dependency<ppPCINT5, std::tuple<ppPB5>> {
};

struct ppPCINT6 : Dependency<ppPCINT6, std::tuple<ppPB6>> {
};

struct ppPCINT7 : Dependency<ppPCINT7, std::tuple<ppPB7>> {
};

struct ppPCINT8 : Dependency<ppPCINT8, std::tuple<ppPC0>> {
};

struct ppPCINT9 : Dependency<ppPCINT9, std::tuple<ppPC1>> {
};

struct ppPCINT10 : Dependency<ppPCINT10, std::tuple<ppPC2>> {
};

struct ppPCINT11 : Dependency<ppPCINT11, std::tuple<ppPC3>> {
};

struct ppPCINT12 : Dependency<ppPCINT12, std::tuple<ppPC4>> {
};

struct ppPCINT13 : Dependency<ppPCINT13, std::tuple<ppPC5>> {
};

struct ppPCINT14 : Dependency<ppPCINT14, std::tuple<ppPC6>> {
};

struct ppPCINT16 : Dependency<ppPCINT16, std::tuple<ppPD0>> {
};

struct ppPCINT17 : Dependency<ppPCINT17, std::tuple<ppPD1>> {
};

struct ppPCINT18 : Dependency<ppPCINT18, std::tuple<ppPD2>> {
};

struct ppPCINT19 : Dependency<ppPCINT19, std::tuple<ppPD3>> {
};

struct ppPCINT20 : Dependency<ppPCINT20, std::tuple<ppPD4>> {
};

struct ppPCINT21 : Dependency<ppPCINT21, std::tuple<ppPD5>> {
};

struct ppPCINT22 : Dependency<ppPCINT22, std::tuple<ppPD6>> {
};

struct ppPCINT23 : Dependency<ppPCINT23, std::tuple<ppPD7>> {
};

struct ppAIN0 : Dependency<ppAIN0, std::tuple<ppPD6>> {
};

struct ppAIN1 : Dependency<ppAIN1, std::tuple<ppPD7>> {
};

struct ppAIN : Dependency<ppAIN, std::tuple<ppAIN0, ppAIN1>> {
};

struct ppSCL : Dependency<ppSCL, std::tuple<ppPC5>> {
};

struct ppSDA : Dependency<ppSDA, std::tuple<ppPC4>> {
};

struct ppI2C0 : Dependency<ppI2C0, std::tuple<ppSCL, ppSDA>> {
};

struct ppSS : Dependency<ppSS, std::tuple<ppPB2>> {
};

struct ppSCK : Dependency<ppSCK, std::tuple<ppPB5>> {
};

struct ppMISO : Dependency<ppMISO, std::tuple<ppPB4>> {
};

struct ppMOSI : Dependency<ppMOSI, std::tuple<ppPB3>> {
};

struct ppSPI0 : Dependency<ppSPI0, std::tuple<ppMISO, ppMOSI, ppSCK, ppSS>> {
};

struct ppRXD : Dependency<ppRXD, std::tuple<ppPD0>> {
};

struct ppTXD : Dependency<ppTXD, std::tuple<ppPD1>> {
};

struct ppUSART0 : Dependency<ppUSART0, std::tuple<ppRXD, ppTXD>> {
};

struct ppXTAL1 : Dependency<ppXTAL1, std::tuple<ppPB6>> {
};

struct ppXTAL2 : Dependency<ppXTAL2, std::tuple<ppPB7>> {
};

struct ppXTAL : Dependency<ppXTAL, std::tuple<ppXTAL1, ppXTAL2>> {
};

static_assert(
  std::is_same<
    RootDependencies<ppUSART0>,
    std::tuple<ppPD0, ppPD1>>::value,
  "Failed to find correct root dependencies for USART0.");

}  // arch_atmega328p
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega328p_defs__h
