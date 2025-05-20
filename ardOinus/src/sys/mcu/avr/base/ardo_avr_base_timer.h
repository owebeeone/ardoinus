

#ifndef ARDO_AVR_BASE_TIMER__H
#define ARDO_AVR_BASE_TIMER__H

#include "ardo_avr_base_register.h"

#include "sys/mcu/avr/ardo_supplemental_atmega328p.h" // remove

namespace ardo {
namespace sys {
namespace avr {
namespace base {

using namespace ::ardo::sys::avr::arch_atmega328p;


/**
 * Traits for TCCR register CS1 enum values. Specialized as needed.
 */
template <typename w_EnumClass> 
struct TccrEnumTraits;

using setl::NA;

/**
 * Provides divider constants for Clock Selector enums.
 */
template <typename w_EnumT, w_EnumT w_cs_value, std::uint32_t w_divider>
struct DividerMapping {
  using EnumT = w_EnumT;
  static constexpr EnumT cs_value = w_cs_value;
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
   * Returns the divider associated with cs_value. If not found, returns NA.
   */
  static constexpr std::uint32_t findDividerMultiple(EnumT cs_value) {
    return cs_value == T::cs_value ? T::divider : NA;
  }

  /**
   * Returns the EnumCS1 associated with the largest divider less than
   * the divider provided. Returns EnumCS1::no_clk if there is no divider
   * smaller than the divider provided.
   */
  static constexpr EnumT findLargestLessThanOrEq(std::uint32_t divider) {
    return divider <= T::divider ? T::cs_value : null_value;
  }
};

template <typename T, typename...Ts>
struct DividerMappings<T, Ts...> {
  using EnumT = typename T::EnumT;
  static constexpr EnumT start_range = TccrEnumTraits<EnumT>::start_range;
  static constexpr EnumT null_value = TccrEnumTraits<EnumT>::null_value;
  /**
   * Returns the divider associated with cs_value. If not found, returns NA.
   */
  static constexpr std::uint32_t findDividerMultiple(EnumT cs_value) {
    return cs_value <= T::cs_value 
        ? T::divider 
        : DividerMappings<Ts...>::findDividerMultiple(cs_value);
  }

  /**
   * Returns the EnumCS1 associated with the largest divider less than
   * the divider provided. Returns EnumCS1::no_clk if there is no divider
   * smaller than the divider provided.
   */
  static constexpr EnumT findLargestLessThanOrEq(std::uint32_t divider) {
    return divider <= T::divider
        ? T::cs_value
        : DividerMappings<Ts...>::findLargestLessThanOrEq(divider);
  }
};


/**
 * Indicates the type of waveform generator mode being used.
 */
enum class TimerMode : unsigned {
  normal,
  ctc,
  pwm
};

/**
 * Indicates the type of PWM mode being used.
 */
enum class TimerPwmMode : unsigned {
  none,
  fast,
  phase_correct,
  phase_freq_correct
};

constexpr bool TimerPwmModePhaseCorrect(TimerPwmMode timer_pwm_mode) {
  return timer_pwm_mode == TimerPwmMode::phase_correct
    || timer_pwm_mode == TimerPwmMode::phase_freq_correct;
}

/**
 * The timer top count used.
 */
enum class TimerTop : unsigned {
  none,
  built_in,
  ocra,
  icr
};

/**
 * Provides enum metadata for Waveform Generator Mode enums.
 */
template <typename w_EnumT,
          w_EnumT w_wgm_value,
          TimerMode w_timer_mode,
          TimerPwmMode w_timer_pwm_mode,
          TimerTop w_timer_top,
          std::uint32_t w_built_in_top=NA>
struct WaveformGeneratorMode {
  using EnumT = w_EnumT;
  static constexpr EnumT wgm_value = w_wgm_value;
  static constexpr TimerMode timer_mode = w_timer_mode;
  static constexpr TimerPwmMode timer_pwm_mode = w_timer_pwm_mode;
  static constexpr TimerTop timer_top = w_timer_top;
  static constexpr std::uint32_t built_in_top = w_built_in_top;
};

/**
 * Provides enum metadata for Waveform Generator Mode parameters.
 */
enum class WaveformGeneratorModeParam : unsigned {
  wgm_value,
  timer_mode,
  timer_pwm_mode,
  timer_top,
  built_in_top
};

/**
 * Provides getter templates for WaveformGeneratorMode enum metadata.
 */
struct WaveformGeneratorModeGetters {
  template <
          WaveformGeneratorModeParam w_param,
          typename T>
  struct Getter {};

  /** Getter for the WGMx value for the mode provided. */
  template <
        typename w_EnumT,
        w_EnumT w_wgm_value,
        TimerMode w_timer_mode,
        TimerPwmMode w_timer_pwm_mode,
        TimerTop w_timer_top,
        std::uint32_t w_built_in_divider>
  struct Getter<
    WaveformGeneratorModeParam::wgm_value,
    WaveformGeneratorMode<w_EnumT, w_wgm_value, w_timer_mode, w_timer_pwm_mode, w_timer_top, w_built_in_divider>> {
    static constexpr w_EnumT value = w_wgm_value;
  };

  /** Getter for the timer mode for the mode provided. */  
  template <
        typename w_EnumT,
        w_EnumT w_wgm_value,
        TimerMode w_timer_mode,
        TimerPwmMode w_timer_pwm_mode,
        TimerTop w_timer_top,
        std::uint32_t w_built_in_divider>
  struct Getter<
    WaveformGeneratorModeParam::timer_mode,
    WaveformGeneratorMode<w_EnumT, w_wgm_value, w_timer_mode, w_timer_pwm_mode, w_timer_top, w_built_in_divider>> {
    static constexpr TimerMode value = w_timer_mode;
  };
  
  /** Getter for the timer PWM mode for the mode provided. */
  template <
        typename w_EnumT,
        w_EnumT w_wgm_value,
        TimerMode w_timer_mode,
        TimerPwmMode w_timer_pwm_mode,
        TimerTop w_timer_top,
        std::uint32_t w_built_in_divider>
  struct Getter<
    WaveformGeneratorModeParam::timer_pwm_mode,
    WaveformGeneratorMode<w_EnumT, w_wgm_value, w_timer_mode, w_timer_pwm_mode, w_timer_top, w_built_in_divider>> {
    static constexpr TimerPwmMode value = w_timer_pwm_mode;
  };

  /** Getter for the timer top for the mode provided. */      
  template <
        typename w_EnumT,
        w_EnumT w_wgm_value,
        TimerMode w_timer_mode,
        TimerPwmMode w_timer_pwm_mode,
        TimerTop w_timer_top,
        std::uint32_t w_built_in_divider>
  struct Getter<
    WaveformGeneratorModeParam::timer_top,
    WaveformGeneratorMode<w_EnumT, w_wgm_value, w_timer_mode, w_timer_pwm_mode, w_timer_top, w_built_in_divider>> {
    static constexpr TimerTop value = w_timer_top;
  };

  /** Getter for the timer top for the mode provided. */
  template <
    typename w_EnumT,
    w_EnumT w_wgm_value,
    TimerMode w_timer_mode,
    TimerPwmMode w_timer_pwm_mode,
    TimerTop w_timer_top,
    std::uint32_t w_built_in_divider>
  struct Getter<
    WaveformGeneratorModeParam::built_in_top,
    WaveformGeneratorMode<w_EnumT, w_wgm_value, w_timer_mode, w_timer_pwm_mode, w_timer_top, w_built_in_divider>> {
    static constexpr std::uint32_t value = w_built_in_divider;
  };
};

template <
      WaveformGeneratorModeParam w_param,
      typename T>
constexpr auto WaveformGeneratorModeGet = WaveformGeneratorModeGetters::Getter<w_param, T>::value;

/**
 * Getter for WaveformGeneratorMode metadata.
 */
// template <
//       WaveformGeneratorModeParam w_param,
//       typename w_EnumT,
//       w_EnumT w_wgm_value,
//       TimerMode w_timer_mode,
//       TimerPwmMode w_timer_pwm_mode,
//       TimerTop w_timer_top,
//       std::uint32_t w_built_in_divider>
// constexpr auto WaveformGeneratorModeGet =
//     WaveformGeneratorModeGetters::Getter<
//       w_param, 
//       WaveformGeneratorMode<w_EnumT, w_wgm_value, w_timer_mode, w_timer_pwm_mode, w_timer_top, w_built_in_divider>
//     >::value;

/**
 * Waveform generator modes container. Provides searh facilities to select
 * the most appropriate waveform generator modes.
 */
template <typename...Ts>
struct WaveformGeneratorModes;

template <typename T>
struct WaveformGeneratorModesFinder;

template <>
struct WaveformGeneratorModesFinder<std::tuple<>> {
  template <std::uint32_t w_built_in_divider>
  using type = void;
};

template <typename T, typename...Ts>
struct WaveformGeneratorModesFinder<std::tuple<T, Ts...>> {
  using Rest = WaveformGeneratorModesFinder<std::tuple<Ts...>>;
  template <std::uint32_t w_built_in_top>
  using type = std::conditional_t<
      T::built_in_top == w_built_in_top, T, 
      typename Rest::template type<w_built_in_top>>;
};

// Specialization for the empty list. 
template <>
struct WaveformGeneratorModes<> {
  template <TimerMode timer_mode, TimerPwmMode timer_pwm_mode, TimerTop timer_top>
  static constexpr bool found = false;

  template <TimerMode timer_mode, TimerPwmMode timer_pwm_mode, TimerTop timer_top>
  using type = std::tuple<>;
  
  template <WaveformGeneratorModeParam w_param, typename EnumT, typename Result>
  static constexpr void getParamFor(EnumT wgm_value, Result& result) {
    // Result is not modified, it is already initialized as empty.
  }
};

template <typename T, typename...Ts>
struct WaveformGeneratorModes<T, Ts...> {
  using Rest = WaveformGeneratorModes<Ts...>;
  using Mode = T;
 private:
   template <TimerMode timer_mode, TimerPwmMode timer_pwm_mode, TimerTop timer_top>
   struct Helper {
     static constexpr bool this_selected =
       Mode::timer_mode == timer_mode
       && Mode::timer_pwm_mode == timer_pwm_mode
       && Mode::timer_top == timer_top;
     using type = std::conditional_t<this_selected, std::tuple<Mode>, std::tuple<>>;
   };
 public:

  template <TimerMode timer_mode, TimerPwmMode timer_pwm_mode, TimerTop timer_top>
  using type = setl::tuple_concat_t<
    typename Helper<timer_mode, timer_pwm_mode, timer_top>::type,
    typename Rest::template type<timer_mode, timer_pwm_mode, timer_top>>;


  template <TimerMode timer_mode, 
            TimerPwmMode timer_pwm_mode,
            std::uint32_t w_built_in_divider>
  using built_in_type = typename WaveformGeneratorModesFinder<
    typename WaveformGeneratorModes::
        template type<timer_mode, timer_pwm_mode, TimerTop::built_in>>::
    template type<w_built_in_divider>;

  template <WaveformGeneratorModeParam w_param, typename EnumT, typename Result>
  static constexpr void getParamFor(EnumT wgm_value, Result& result) {
    if (wgm_value == Mode::wgm_value) {
      result = WaveformGeneratorModeGetters::Getter<w_param, Mode>::value;
    } else {
      Rest::template getParamFor<w_param>(wgm_value, result);
    }
  }
  
  template <WaveformGeneratorModeParam w_param>
  using ParamType = std::remove_cv_t<decltype(
      WaveformGeneratorModeGetters::Getter<w_param, Mode>::value)>;
  
  template <WaveformGeneratorModeParam w_param>
  using ParamReturnType = setl::Optional<ParamType<w_param>>;

  /**
   * Returns the value of the parameter w_param for the mode associated with wgm_value.
   * This will work at run time.
   */
  template <WaveformGeneratorModeParam w_param, typename EnumT>
  static constexpr ParamReturnType<w_param> getParamFor(EnumT wgm_value) {
    ParamReturnType<w_param> result;
    getParamFor<w_param>(wgm_value, result);
    return result;
  }

};

/**
 * Finds the mapping associated with cs_value. Will have a compile error if not found.
 */
// template <EnumCS1 cs_value, typename...Ts>
// struct DividerMappingsFindCs1;

// template <EnumCS1 cs_value, std::uint32_t w_divider, typename...Ts>
// struct DividerMappingsFindCs1<
//  cs_value, DividerMappings<DividerMapping<cs_value, w_divider>, Ts...>> {
//  using Mapping = DividerMapping<cs_value, w_divider>;
// };

// template <EnumCS1 cs_value, EnumCS1 cs_value_w, std::uint32_t w_divider, typename...Ts>
// struct DividerMappingsFindCs1<
//  cs_value, DividerMappings<DividerMapping<cs_value_w, w_divider>, Ts...>> {
//  using Mapping = typename DividerMappingsFindCs1<Ts...>::Mapping;
// };


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
 * Computes the clock frequency for the timers given the 
 * top count, clock divider, and timer clock frequency including
 * the phase correct mode.
 * 
 * The return type can be a floating point type since sub 1Hz frequencies
 * are possible. Specify the return type with the R template parameter
 * or pass a top_count as a floating point type to allow for sub 1Hz 
 * frequencies. 
 */
template <typename R, typename EnumT, typename T>
constexpr R getTimerFrequency(
  T top_count,
  EnumT clock_divider_enum,
  std::uint32_t timer_clock_frequency,
  bool phase_correct_mode) {
    
  using Traits = TccrEnumTraits<EnumT>;
  using FreqMapping = typename Traits::FreqMapping;
  return timer_clock_frequency
    / ((phase_correct_mode ? R{2} : R{1})
      * top_count
      * FreqMapping::findDividerMultiple(clock_divider_enum));
}

/**
 * Returns the multiple for a divider setting.
 */
template <typename EnumT>
constexpr std::remove_cv_t<decltype(
    TccrEnumTraits<EnumT>::FreqMapping::findDividerMultiple(TccrEnumTraits<EnumT>::start_range))>
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
 * Define register TCCR0B/TCCR1B CS1n definitions.
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

// Timer counter 0 uses the same bit definitions.
using EnumCS0 = EnumCS1;

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
 * Traits for EnumCS1 used by getClockDivider to discover
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


/**
 * Define register TCCR2B CS2n definitions.
 */
enum class EnumCS2 : unsigned char {
  no_clk = 0b000,
  clk1 = 0b001,
  clk8 = 0b010,
  clk32 = 0b011,
  clk64 = 0b100,
  clk128 = 0b101,
  clk256 = 0b110,
  clk1024 = 0b111
};

/**
 * Mapping of EnumCS2 to divider value.
 */
 // Note: must be in ascending divider order.
using Cs2DividerMapping = DividerMappings<
  DividerMapping<EnumCS2, EnumCS2::clk1, 1>,
  DividerMapping<EnumCS2, EnumCS2::clk8, 8>,
  DividerMapping<EnumCS2, EnumCS2::clk32, 32>,
  DividerMapping<EnumCS2, EnumCS2::clk64, 64>,
  DividerMapping<EnumCS2, EnumCS2::clk128, 128>,
  DividerMapping<EnumCS2, EnumCS2::clk256, 256>,
  DividerMapping<EnumCS2, EnumCS2::clk1024, 1024>
>;

/**
 * Traits for EnumCS2 used by getClockDivider to discover
 * the clock divider for a specific frequency.
 */
template <>
struct TccrEnumTraits<EnumCS2> {
  using EnumT = EnumCS2;
  using FreqMapping = Cs2DividerMapping;
  static constexpr EnumT null_value = EnumT::no_clk;
  static constexpr EnumT start_range = EnumT::clk1;
  static constexpr EnumT end_range = EnumT::clk1024;
};

static_assert(
  getClockDivider<EnumCS1>(100000, 16000000, 16, false) == EnumCS1::clk1,
  "Clockdivider computation failed or 100kHz and 16 bit comparator.");

static_assert(
  getClockDivider<EnumCS2>(100000, 16000000, 16, false) == EnumCS2::clk1,
  "Clockdivider computation failed or 100kHz and 16 bit comparator.");

static_assert(
  getClockDivider<EnumCS1>(2, 16000000, 16, true) == EnumCS1::clk64,
  "Clockdivider computation failed or 2Hz and 16 bit comparator in phase correct mode.");

static_assert(
  getClockDivider<EnumCS1>(2, 16000000, 16, false) == EnumCS1::clk256,
  "Clockdivider computation failed or 2Hz and 16 bit comparator.");

static_assert(
  getClockDivider<EnumCS2>(2, 16000000, 16, false) == EnumCS2::clk128,
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

static_assert(
  getTimerFrequency<std::uint32_t>(80ul, EnumCS1::clk1, 16000000, true) == 100000ul,
  "getTimerFrequency computation failed for divider.");

static_assert(
  getTimerFrequency<float>(15625, EnumCS1::clk1024, 16000000, true) == 0.5f,
  "getTimerFrequency computation failed for divider.");

/**
 * Controls for timer output compare register modes.
 */
enum class EnumCOMn : unsigned char {
  disconnect = 0b00,
  toggle = 0b01, // Reserved for Fast PWM mode on COM2A
  clear = 0b10,
  set = 0b11
};

/**
 * Bit field definitions for the COMnA and COMnB fields.
 */
using BitsCOM0A = setl::BitsRW<
  setl::SemanticType<setl::hash("COM0A"), EnumCOMn>, ccCOM0A1, ccCOM0A0>;
using BitsCOM0B = setl::BitsRW<
  setl::SemanticType<setl::hash("COM0B"), EnumCOMn>, ccCOM0B1, ccCOM0B0>;
using BitsCOM1A = setl::BitsRW<
  setl::SemanticType<setl::hash("COM1A"), EnumCOMn>, ccCOM1A1, ccCOM1A0>;
using BitsCOM1B = setl::BitsRW<
  setl::SemanticType<setl::hash("COM1B"), EnumCOMn>, ccCOM1B1, ccCOM1B0>;
using BitsCOM2A = setl::BitsRW<
  setl::SemanticType<setl::hash("COM2A"), EnumCOMn>, ccCOM2A1, ccCOM2A0>;
using BitsCOM2B = setl::BitsRW<
  setl::SemanticType<setl::hash("COM2B"), EnumCOMn>, ccCOM2B1, ccCOM2B0>;

/**
 * Bit field defintions for distinguishing access to the COMn bits from
 * 8 bit register defintions.
 */
using BitsCOM0A8 = setl::BitsRW<
  setl::SemanticType<setl::hash("COM0A8"), EnumCOMn>, ccCOM0A1, ccCOM0A0>;
using BitsCOM0B8 = setl::BitsRW<
  setl::SemanticType<setl::hash("COM0B8"), EnumCOMn>, ccCOM0B1, ccCOM0B0>;
using BitsCOM1A8 = setl::BitsRW<
  setl::SemanticType<setl::hash("COM1A8"), EnumCOMn>, ccCOM1A1, ccCOM1A0>;
using BitsCOM1B8 = setl::BitsRW<
  setl::SemanticType<setl::hash("COM1B8"), EnumCOMn>, ccCOM1B1, ccCOM1B0>;
using BitsCOM2A8 = setl::BitsRW<
  setl::SemanticType<setl::hash("COM2A8"), EnumCOMn>, ccCOM2A1, ccCOM2A0>;
using BitsCOM2B8 = setl::BitsRW<
  setl::SemanticType<setl::hash("COM2B8"), EnumCOMn>, ccCOM2B1, ccCOM2B0>;

/**
 * Defines for operating modes of timer/counter 0.
 */
enum class EnumWGM0 : unsigned char {
  normal = 0b000,
  pwm_phase_correct_8bit = 0b001,
  ctc_ocra = 0b010,
  fast_pwm_8bit = 0b011,
  reserved_8 = 0b100,
  pwm_phase_correct_ocra = 0b101,
  reserved_6 = 0b110,
  fast_pwm_ocra = 0b111,
};

// Timer/counter 2 uses the same WGM bits as timer/counter 0.
using EnumWGM2 = EnumWGM0;

template <typename WgmEnum>
struct WgmEnumTraits;

/**
 * Mapping of EnumWGM0 to properties.
 */
using Wgm0TopCountMapping = WaveformGeneratorModes<
  WaveformGeneratorMode<
    EnumWGM0, EnumWGM0::normal, TimerMode::normal, TimerPwmMode::none, 
    TimerTop::built_in, setl::mersenne(8)>,
  WaveformGeneratorMode<
    EnumWGM0, EnumWGM0::pwm_phase_correct_8bit, TimerMode::pwm, TimerPwmMode::phase_correct, 
    TimerTop::built_in, setl::mersenne(8)>,
  WaveformGeneratorMode<
    EnumWGM0, EnumWGM0::ctc_ocra, TimerMode::ctc, TimerPwmMode::none,
    TimerTop::ocra>,
  WaveformGeneratorMode<
    EnumWGM0, EnumWGM0::fast_pwm_8bit, TimerMode::pwm, TimerPwmMode::fast, 
    TimerTop::built_in, setl::mersenne(8)>,
  WaveformGeneratorMode<
    EnumWGM0, EnumWGM0::pwm_phase_correct_ocra, TimerMode::pwm, TimerPwmMode::phase_correct,
    TimerTop::ocra>,
  WaveformGeneratorMode<
    EnumWGM0, EnumWGM0::fast_pwm_ocra, TimerMode::pwm, TimerPwmMode::fast, TimerTop::ocra>
>;

template <>
struct WgmEnumTraits<EnumWGM0> {
  using Modes = Wgm0TopCountMapping;
};


/**
 * Defines for operating modes of timer/counter 1.
 */
enum class EnumWGM1 : unsigned char {
  normal = 0b0000,
  pwm_phase_correct_8bit = 0b0001,
  pwm_phase_correct_9bit = 0b0010,
  pwm_phase_correct_10bit = 0b0011,
  ctc_ocra = 0b0100,
  fast_pwm_8bit = 0b0101,
  fast_pwm_9bit = 0b0110,
  fast_pwm_10bit = 0b0111,
  pwm_phase_freq_correct_icr = 0b1000,
  pwm_phase_freq_correct_ocra = 0b1001,
  pwm_phase_correct_icr = 0b1010,
  pwm_phase_correct_ocra = 0b1011,
  ctc_icr = 0b1100,
  reserved_d = 0b1101,
  fast_pwm_icr = 0b1110,
  fast_pwm_ocra = 0b1111,
};

/**
 * Mapping of EnumWGM1 to properties.
 */
using Wgm1TopCountMapping = WaveformGeneratorModes<
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::normal, TimerMode::normal, TimerPwmMode::none, 
    TimerTop::built_in, setl::mersenne(16)>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::pwm_phase_correct_8bit, TimerMode::pwm, TimerPwmMode::phase_correct, 
    TimerTop::built_in, setl::mersenne(8)>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::pwm_phase_correct_9bit, TimerMode::pwm, TimerPwmMode::phase_correct, 
    TimerTop::built_in, setl::mersenne(9)>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::pwm_phase_correct_10bit, TimerMode::pwm, TimerPwmMode::phase_correct, 
    TimerTop::built_in, setl::mersenne(10)>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::ctc_ocra, TimerMode::ctc, TimerPwmMode::none, TimerTop::ocra>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::ctc_icr, TimerMode::ctc, TimerPwmMode::none, TimerTop::icr>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::fast_pwm_8bit, TimerMode::pwm, TimerPwmMode::fast,
    TimerTop::built_in, setl::mersenne(8)>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::fast_pwm_9bit, TimerMode::pwm, TimerPwmMode::fast,
    TimerTop::built_in, setl::mersenne(9)>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::fast_pwm_10bit, TimerMode::pwm, TimerPwmMode::fast,
    TimerTop::built_in, setl::mersenne(10)>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::pwm_phase_freq_correct_icr, TimerMode::pwm, TimerPwmMode::phase_freq_correct,
    TimerTop::icr>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::pwm_phase_freq_correct_ocra, TimerMode::pwm, TimerPwmMode::phase_freq_correct,
    TimerTop::ocra>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::pwm_phase_correct_icr, TimerMode::pwm, TimerPwmMode::phase_correct,
    TimerTop::icr>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::pwm_phase_correct_ocra, TimerMode::pwm, TimerPwmMode::phase_correct,
    TimerTop::ocra>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::fast_pwm_icr, TimerMode::pwm, TimerPwmMode::fast, TimerTop::icr>,
  WaveformGeneratorMode<
    EnumWGM1, EnumWGM1::fast_pwm_ocra, TimerMode::pwm, TimerPwmMode::fast, TimerTop::ocra>
>;

// Check that built_in_type works.
static_assert(Wgm1TopCountMapping::built_in_type<
  TimerMode::pwm, TimerPwmMode::fast, setl::mersenne(10)>::wgm_value == EnumWGM1::fast_pwm_10bit,
  "Should evaluate to EnumWGM1::fast_pwm_10bit");

// Check that getter works.
static_assert(
  WaveformGeneratorModeGet<
    WaveformGeneratorModeParam::wgm_value,
    WaveformGeneratorMode<
      EnumWGM1, EnumWGM1::fast_pwm_icr, TimerMode::pwm, TimerPwmMode::fast, 
      TimerTop::icr>
    > == EnumWGM1::fast_pwm_icr, "Should evaluate to EnumWGM1::fast_pwm_icr");

static_assert(
  WaveformGeneratorModeGet<
    WaveformGeneratorModeParam::timer_mode,
    WaveformGeneratorMode<
      EnumWGM1, EnumWGM1::fast_pwm_icr, TimerMode::pwm, TimerPwmMode::fast, 
      TimerTop::icr>
    > == TimerMode::pwm, "Should evaluate to TimerMode::pwm");

static_assert(
  WaveformGeneratorModeGet<
    WaveformGeneratorModeParam::timer_pwm_mode,
    WaveformGeneratorMode<
      EnumWGM1, EnumWGM1::fast_pwm_icr, TimerMode::pwm, TimerPwmMode::fast, 
      TimerTop::icr>
    > == TimerPwmMode::fast, "Should evaluate to TimerPwmMode::fast");

static_assert(
  WaveformGeneratorModeGet<
    WaveformGeneratorModeParam::timer_top,
    WaveformGeneratorMode<
      EnumWGM1, EnumWGM1::fast_pwm_icr, TimerMode::pwm, TimerPwmMode::fast, 
      TimerTop::icr>
    > == TimerTop::icr, "Should evaluate to TimerTop::icr");

static_assert(
  WaveformGeneratorModeGet<
    WaveformGeneratorModeParam::built_in_top,
    WaveformGeneratorMode<
      EnumWGM1, EnumWGM1::fast_pwm_10bit, TimerMode::pwm, TimerPwmMode::fast,
      TimerTop::built_in, setl::mersenne(10)>
    > == setl::mersenne(10), "Should evaluate to setl::mersenne(10)");


template <>
struct WgmEnumTraits<EnumWGM1> {
  using Modes = Wgm1TopCountMapping;
};

// Define registers for timer/counter 0
using BitsWGM0_10 = setl::BitsRW<EnumWGM0, NA, ccWGM01, ccWGM00>;
using BitsWGM0_2 = setl::BitsRW<EnumWGM0, ccWGM02, NA, NA>;
// Define bitfields when treating TCCR0A + TCCR0B as a 16 bit value.
using BitsWGM0_210 = setl::BitsRW<EnumWGM0, ccWGM02 + 8, ccWGM01, ccWGM00>;

using BitsCS01 = setl::BitsRW<EnumCS0, ccCS02, ccCS01, ccCS00>;
// Define bitfields when treating TCCR0A + TCCR0B as a 16 bit value.
using BitsCS01_16 = setl::BitsRW<EnumCS0, ccCS02 + 8, ccCS01 + 8, ccCS00 + 8>;

// Define force output compare bits for timer/counter 0.
using BitsFOC0A = setl::BitsRW<setl::SemanticType<setl::hash("FOC0A"), bool>, ccFOC0A>;
using BitsFOC0B = setl::BitsRW<setl::SemanticType<setl::hash("FOC0B"), bool>, ccFOC0B>;
// Define 16 bit register modes for these bits.
using BitsFOC0A_16 = setl::BitsRW<setl::SemanticType<setl::hash("FOC0A"), bool>, ccFOC0A + 8>;
using BitsFOC0B_16 = setl::BitsRW<setl::SemanticType<setl::hash("FOC0B"), bool>, ccFOC0B + 8>;

// Define register TCCR0A.
using FieldsTCCR0A = setl::BitFields<BitsCOM0A8, BitsCOM0B8, BitsWGM0_10>;
using RegisterTCCR0A = Register<FieldsTCCR0A, rrTCCR0A>;

// Define register TCCR0B.
using FieldsTCCR0B = setl::BitFields<BitsFOC0A, BitsFOC0B, BitsWGM0_2, BitsCS01>;
using RegisterTCCR0B = Register<FieldsTCCR0B, rrTCCR0B>;

// Define register TCCR0AB.
using FieldsTCCR0AB = setl::BitFields<
  BitsCOM0A, BitsCOM0B, 
  BitsWGM0_210, 
  BitsFOC0A_16, BitsFOC0B_16, 
  BitsCS01_16>;
using rrTCCR0AB = rrTCCR0A::ForType<std::uint16_t>;
using RegisterTCCR0AB = Register<FieldsTCCR0AB, rrTCCR0AB>;

using BitsTCNT0 = setl::BitsRW<setl::SemanticType<setl::hash("TCNT0"), std::uint8_t>,
  ccTCNT0_7,
  ccTCNT0_6,
  ccTCNT0_5,
  ccTCNT0_4,
  ccTCNT0_3,
  ccTCNT0_2,
  ccTCNT0_1,
  ccTCNT0_0
>;
using FieldsTCNT0 = setl::BitFields<BitsTCNT0>;
using RegisterTCNT0 = Register<FieldsTCNT0, rrTCNT0>;

using BitsOCR0A = setl::BitsRW<setl::SemanticType<setl::hash("OCR0A"), std::uint8_t>,
  ccOCR0A_7,
  ccOCR0A_6,
  ccOCR0A_5,
  ccOCR0A_4,
  ccOCR0A_3,
  ccOCR0A_2,
  ccOCR0A_1,
  ccOCR0A_0
>;
using FieldsOCR0A = setl::BitFields<BitsOCR0A>;
using RegisterOCR0A = Register<FieldsOCR0A, rrOCR0A>;

using BitsOCR0B = setl::BitsRW<setl::SemanticType<setl::hash("OCR0B"), std::uint8_t>,
  ccOCR0B_7,
  ccOCR0B_6,
  ccOCR0B_5,
  ccOCR0B_4,
  ccOCR0B_3,
  ccOCR0B_2,
  ccOCR0B_1,
  ccOCR0B_0
>;
using FieldsOCR0B = setl::BitFields<BitsOCR0B>;
using RegisterOCR0B = Register<FieldsOCR0B, rrOCR0B>;

// Timer/Counter0 Interrupt Mask Register.
using BitsOCIE0B = setl::BitsRW<setl::SemanticType<setl::hash("OCIE0B"), bool>, ccOCIE0B>;
using BitsOCIE0A = setl::BitsRW<setl::SemanticType<setl::hash("OCIE0A"), bool>, ccOCIE0A>;
using BitsTOIE0 = setl::BitsRW<setl::SemanticType<setl::hash("TOIE0"), bool>, ccTOIE0>;
using FieldsTIMSK0 = setl::BitFields<BitsOCIE0B, BitsOCIE0A, BitsTOIE0>;
using RegisterTIMSK0 = Register<FieldsTIMSK0, rrTIMSK0>;

// Timer/Counter0 Interrupt Flag Register.
using BitsOCF0B = setl::BitsRW<setl::SemanticType<setl::hash("OCF0B"), bool>, ccOCF0B>;
using BitsOCF0A = setl::BitsRW<setl::SemanticType<setl::hash("OCF0A"), bool>, ccOCF0A>;
using BitsTOV0 = setl::BitsRW<setl::SemanticType<setl::hash("TOV0"), bool>, ccTOV0>;
using FieldsTIFR0 = setl::BitFields<BitsOCF0B, BitsOCF0A, BitsTOV0>;
using RegisterTIFR0 = Register<FieldsTIFR0, rrTIFR0>;

// Define registers for timer/counter 2
using BitsWGM2_10 = setl::BitsRW<EnumWGM2, NA, ccWGM21, ccWGM20>;
using BitsWGM2_2 = setl::BitsRW<EnumWGM2, ccWGM22, NA, NA>;
// Define bitfields when treating TCCR2A + TCCR2B as a 16 bit value.
using BitsWGM2_210 = setl::BitsRW<EnumWGM2, ccWGM22 + 8, ccWGM21, ccWGM20>;

using BitsCS21 = setl::BitsRW<EnumCS2, ccCS22, ccCS21, ccCS20>;
// Define bitfields when treating TCCR2A + TCCR2B as a 16 bit value.
using BitsCS21_16 = setl::BitsRW<EnumCS2, ccCS22 + 8, ccCS21 + 8, ccCS20 + 8>;

// Define force output compare bits for timer/counter 2.
using BitsFOC2A = setl::BitsRW<setl::SemanticType<setl::hash("FOC2A"), bool>, ccFOC2A>;
using BitsFOC2B = setl::BitsRW<setl::SemanticType<setl::hash("FOC2B"), bool>, ccFOC2B>;
// Define 16 bit register modes for these bits.
using BitsFOC2A_16 = setl::BitsRW<setl::SemanticType<setl::hash("FOC2A"), bool>, ccFOC2A + 8>;
using BitsFOC2B_16 = setl::BitsRW<setl::SemanticType<setl::hash("FOC2B"), bool>, ccFOC2B + 8>;

// Define register TCCR2A.
using FieldsTCCR2A = setl::BitFields<BitsCOM2A8, BitsCOM2B8, BitsWGM2_10>;
using RegisterTCCR2A = Register<FieldsTCCR2A, rrTCCR2A>;

// Define register TCCR0B.
using FieldsTCCR2B = setl::BitFields<BitsFOC2A, BitsFOC2B, BitsWGM2_2, BitsCS21>;
using RegisterTCCR2B = Register<FieldsTCCR2B, rrTCCR2B>;

// Define register TCCR0AB.
using FieldsTCCR2AB = setl::BitFields<
  BitsCOM2A, BitsCOM2B, 
  BitsWGM2_210, 
  BitsFOC2A_16, BitsFOC2B_16, 
  BitsCS21_16>;
using rrTCCR2AB = rrTCCR2A::ForType<std::uint16_t>;
using RegisterTCCR2AB = Register<FieldsTCCR2AB, rrTCCR2AB>;

using BitsTCNT2 = setl::BitsRW<setl::SemanticType<setl::hash("TCNT2"), std::uint8_t>,
  ccTCNT2_7,
  ccTCNT2_6,
  ccTCNT2_5,
  ccTCNT2_4,
  ccTCNT2_3,
  ccTCNT2_2,
  ccTCNT2_1,
  ccTCNT2_0
>;
using FieldsTCNT2 = setl::BitFields<BitsTCNT2>;
using RegisterTCNT2 = Register<FieldsTCNT2, rrTCNT2>;

using BitsOCR2A = setl::BitsRW<setl::SemanticType<setl::hash("OCR2A"), std::uint8_t>,
  ccOCR2_7,
  ccOCR2_6,
  ccOCR2_5,
  ccOCR2_4,
  ccOCR2_3,
  ccOCR2_2,
  ccOCR2_1,
  ccOCR2_0
>;
using FieldsOCR2A = setl::BitFields<BitsOCR2A>;
using RegisterOCR2A = Register<FieldsOCR2A, rrOCR2A>;

using BitsOCR2B = setl::BitsRW<setl::SemanticType<setl::hash("OCR2B"), std::uint8_t>,
  ccOCR2_7,
  ccOCR2_6,
  ccOCR2_5,
  ccOCR2_4,
  ccOCR2_3,
  ccOCR2_2,
  ccOCR2_1,
  ccOCR2_0
>;
using FieldsOCR2B = setl::BitFields<BitsOCR2B>;
using RegisterOCR2B = Register<FieldsOCR2B, rrOCR2B>;

// Timer/Counter2 Interrupt Mask Register.
using BitsOCIE2B = setl::BitsRW<setl::SemanticType<setl::hash("OCIE2B"), bool>, ccOCIE2B>;
using BitsOCIE2A = setl::BitsRW<setl::SemanticType<setl::hash("OCIE2A"), bool>, ccOCIE2A>;
using BitsTOIE2 = setl::BitsRW<setl::SemanticType<setl::hash("TOIE2"), bool>, ccTOIE2>;
using FieldsTIMSK2 = setl::BitFields<BitsOCIE2B, BitsOCIE2A, BitsTOIE2>;
using RegisterTIMSK2 = Register<FieldsTIMSK2, rrTIMSK2>;

// Timer/Counter2 Interrupt Flag Register.
using BitsOCF2B = setl::BitsRW<setl::SemanticType<setl::hash("OCF2B"), bool>, ccOCF2B>;
using BitsOCF2A = setl::BitsRW<setl::SemanticType<setl::hash("OCF2A"), bool>, ccOCF2A>;
using BitsTOV2 = setl::BitsRW<setl::SemanticType<setl::hash("TOV2"), bool>, ccTOV2>;
using FieldsTIFR2 = setl::BitFields<BitsOCF2B, BitsOCF2A, BitsTOV2>;
using RegisterTIFR2 = Register<FieldsTIFR2, rrTIFR2>;

// Asynchronous Status Register for timer 2.
using BitsEXCLK = setl::BitsRW<setl::SemanticType<setl::hash("EXCLK"), bool>, ccEXCLK>;
using BitsAS2 = setl::BitsRW<setl::SemanticType<setl::hash("AS2"), bool>, ccAS2>;
using BitsTCN2UB = setl::BitsRO<setl::SemanticType<setl::hash("TCN2UB"), bool>, ccTCN2UB>;
using BitsOCR2AUB = setl::BitsRO<setl::SemanticType<setl::hash("OCR2BUA"), bool>, ccOCR2AUB>;
using BitsOCR2BUB = setl::BitsRO<setl::SemanticType<setl::hash("OCR2BUB"), bool>, ccOCR2BUB>;
using BitsTCR2AUB = setl::BitsRO<setl::SemanticType<setl::hash("TCR2AUB"), bool>, ccTCR2AUB>;
using BitsTCR2BUB = setl::BitsRO<setl::SemanticType<setl::hash("TCR2BUB"), bool>, ccTCR2BUB>;
using FieldsASSR = setl::BitFields<
    BitsEXCLK, BitsAS2, BitsOCR2AUB, BitsOCR2BUB, BitsTCR2AUB, BitsTCR2BUB>;
using RegisterASSR = Register<FieldsASSR, rrASSR>;

// General Timer/Counter Control Register for timers 0 & 1.
using BitsTSM = setl::BitsRW<setl::SemanticType<setl::hash("TSM"), bool>, ccTSM>;
using BitsPSRASY = setl::BitsRW<setl::SemanticType<setl::hash("PSRASY"), bool>, ccPSRASY>;
using BitsPSRSYNC = setl::BitsRW<setl::SemanticType<setl::hash("PSRSYNC"), bool>, ccPSRSYNC>;
using FieldsGTCCR = setl::BitFields<BitsTSM, BitsPSRASY, BitsPSRSYNC>;
using RegisterGTCCR = Register<FieldsGTCCR, rrGTCCR>;

// Define registers for timer/counter 1
using BitsWGM1_10 = setl::BitsRW<EnumWGM1, NA, NA, ccWGM11, ccWGM10>;
using BitsWGM1_32 = setl::BitsRW<EnumWGM1, ccWGM13, ccWGM12, NA, NA>;
// Define bitfields when treating TCCR1A + TCCR1B as a 16 bit value.
using BitsWGM1_3210 = setl::BitsRW<EnumWGM1, ccWGM13 + 8, ccWGM12 + 8, ccWGM11, ccWGM10>;

using BitsCS11 = setl::BitsRW<EnumCS1, ccCS12, ccCS11, ccCS10>;
// Define bitfields when treating TCCR1A and TCCR1B as a 16 bit value.
using BitsCS11_16 = setl::BitsRW<EnumCS1, ccCS12 + 8, ccCS11 + 8, ccCS10 + 8>;

using BitsICNC1 = setl::BitsRW<bool, ccICNC1>;
using BitsICES1 = setl::BitsRW<bool, ccICES1>;
// Define bitfields when treating TCCR1A and TCCR1B as a 16 bit value.
using BitsICNC1_16 = setl::BitsRW<bool, ccICNC1 + 8>;
using BitsICES1_16 = setl::BitsRW<bool, ccICES1 + 8>;

using FieldsTCCR1A = setl::BitFields<BitsCOM1A8, BitsCOM1B8, BitsWGM1_10>;
using RegisterTCCR1A = Register<FieldsTCCR1A, rrTCCR1A>;

using FieldsTCCR1AB = setl::BitFields<
  BitsCOM1A, BitsCOM1B, BitsWGM1_3210, BitsCS11_16, BitsICNC1_16, BitsICES1_16>;

using FieldsTCCR1B = setl::BitFields<BitsWGM1_32, BitsCS11, BitsICES1, BitsICNC1>;
using RegisterTCCR1B = Register<FieldsTCCR1B, rrTCCR1B>;

// Add a TCCR1AB 16 bit register using TCCR1A's address.
using rrTCCR1AB = rrTCCR1A::ForType<std::uint16_t>;
using RegisterTCCR1AB = Register<FieldsTCCR1AB, rrTCCR1AB>;

// Forced output compare bit definitions for timer/counter 1.
using BitsFOC1A = setl::BitsRW<setl::SemanticType<setl::hash("FOC1A"), bool>, ccFOC1A>;
using BitsFOC1B = setl::BitsRW<setl::SemanticType<setl::hash("FOC1B"), bool>, ccFOC1B>;
using FieldsTCCR1C = setl::BitFields<BitsFOC1A, BitsFOC1B>;
using RegisterTCCR1C = Register<FieldsTCCR1C, rrTCCR1C>;


// Timer/Counter1 Interrupt Mask Register.
using BitsOCIE1B = setl::BitsRW<setl::SemanticType<setl::hash("OCIE1B"), bool>, ccOCIE1B>;
using BitsOCIE1A = setl::BitsRW<setl::SemanticType<setl::hash("OCIE1A"), bool>, ccOCIE1A>;
using BitsTOIE1 = setl::BitsRW<setl::SemanticType<setl::hash("TOIE1"), bool>, ccTOIE1>;
using FieldsTIMSK1 = setl::BitFields<BitsOCIE1B, BitsOCIE1A, BitsTOIE1>;
using RegisterTIMSK1 = Register<FieldsTIMSK1, rrTIMSK1>;

// Timer/Counter1 Interrupt Flag Register.
using BitsOCF1B = setl::BitsRW<setl::SemanticType<setl::hash("OCF1B"), bool>, ccOCF1B>;
using BitsOCF1A = setl::BitsRW<setl::SemanticType<setl::hash("OCF1A"), bool>, ccOCF1A>;
using BitsTOV1 = setl::BitsRW<setl::SemanticType<setl::hash("TOV1"), bool>, ccTOV1>;
using FieldsTIFR1 = setl::BitFields<BitsOCF1B, BitsOCF1A, BitsTOV1>;
using RegisterTIFR1 = Register<FieldsTIFR1, rrTIFR1>;

using BitsTCNT1 = setl::BitsRW<setl::SemanticType<setl::hash("TCNT1"), std::uint16_t>,
  ccTCNT1H7 + 8,
  ccTCNT1H6 + 8,
  ccTCNT1H5 + 8,
  ccTCNT1H4 + 8,
  ccTCNT1H3 + 8,
  ccTCNT1H2 + 8,
  ccTCNT1H1 + 8,
  ccTCNT1H0 + 8,
  ccTCNT1L7,
  ccTCNT1L6,
  ccTCNT1L5,
  ccTCNT1L4,
  ccTCNT1L3,
  ccTCNT1L2,
  ccTCNT1L1,
  ccTCNT1L0
  >;
using FieldsTCNT1 = setl::BitFields<BitsTCNT1>;
using RegisterTCNT1 = Register<FieldsTCNT1, rrTCNT1>;

using BitsOCR1A = setl::BitsRW<setl::SemanticType<setl::hash("OCR1A"), std::uint16_t>,
  ccOCR1AH7 + 8,
  ccOCR1AH6 + 8,
  ccOCR1AH5 + 8,
  ccOCR1AH4 + 8,
  ccOCR1AH3 + 8,
  ccOCR1AH2 + 8,
  ccOCR1AH1 + 8,
  ccOCR1AH0 + 8,
  ccOCR1AL7,
  ccOCR1AL6,
  ccOCR1AL5,
  ccOCR1AL4,
  ccOCR1AL3,
  ccOCR1AL2,
  ccOCR1AL1,
  ccOCR1AL0
>;
using FieldsOCR1A = setl::BitFields<BitsOCR1A>;
using RegisterOCR1A = Register<FieldsOCR1A, rrOCR1A>;

using BitsOCR1B = setl::BitsRW<setl::SemanticType<setl::hash("OCR1B"), std::uint16_t>,
  ccOCR1BH7 + 8,
  ccOCR1BH6 + 8,
  ccOCR1BH5 + 8,
  ccOCR1BH4 + 8,
  ccOCR1BH3 + 8,
  ccOCR1BH2 + 8,
  ccOCR1BH1 + 8,
  ccOCR1BH0 + 8,
  ccOCR1BL7,
  ccOCR1BL6,
  ccOCR1BL5,
  ccOCR1BL4,
  ccOCR1BL3,
  ccOCR1BL2,
  ccOCR1BL1,
  ccOCR1BL0
>;
using FieldsOCR1B = setl::BitFields<BitsOCR1B>;
using RegisterOCR1B = Register<FieldsOCR1B, rrOCR1B>;

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

// Timers

template <typename B>
struct TimerInputNoiseCanceller {
  using Activate = setl::ApplierValues<setl::ApplierValue<B, true>>;
  using Deactivate = setl::ApplierValues<setl::ApplierValue<B, false>>;
  static constexpr bool has_noise_canceller = true;
};

template <>
struct TimerInputNoiseCanceller<void> {
  using Activate = setl::ApplierValues<>;
  using Deactivate = setl::ApplierValues<>;
  static constexpr bool has_noise_canceller = false;
};

/**
 * Configuration information for timer capture. The ICR register is used to
 * capture the timer value when an input capture event occurs or sets the top
 * value for the timer. The noise canceler is used to filter out noise on the
 * input capture pin. The edge selection is used to select the edge of the input
 * capture pin that will trigger the capture event.
 * 
 * The ICR register is only available on some timers.
 */
template <typename w_BitsICR, typename w_BitsICNC, typename w_BitsEdge>
struct TimerCapture {
  static constexpr bool has_capture_register = true;
  using CaptureBits = w_BitsICR;
  using NoiseCanceler = w_BitsICNC;
  using Rising = setl::ApplierValues<setl::ApplierValue<w_BitsEdge, true>>;
  using Falling = setl::ApplierValues<setl::ApplierValue<w_BitsEdge, false>>;
  using NoiseCanceller = TimerInputNoiseCanceller<NoiseCanceler>;
  using TopCountProvided = setl::ValueTuple<TimerTop, TimerTop::icr>;
  static constexpr bool has_input_capture = true;
  static constexpr bool has_edge_selection = true;
};

template <>
struct TimerCapture<void, void, void> {
  static constexpr bool has_capture_register = false;
  using CaptureBits = void;
  using Rising = setl::ApplierValues<>;
  using Falling = setl::ApplierValues<>;
  using NoiseCanceller = TimerInputNoiseCanceller<void>;
  using TopCountProvided = setl::ValueTuple<TimerTop>;  // Empty tuple.
  static constexpr bool has_input_capture = false;
  static constexpr bool has_edge_selection = false;
};

enum class OcrEnum : std::uint8_t {
  OcrA = 0,
  OcrB = 1
};

template <typename w_OCR, 
          typename w_OCIE, 
          typename w_OCF, 
          typename w_COM, 
          typename w_COM8,
          typename w_GpioDef>
struct OutputCompare {
  using OCR = w_OCR;
  using OCIE = w_OCIE;
  using OCF = w_OCF;
  using COM = w_COM;
  using COM8 = w_COM8;
  using GpioDef = w_GpioDef;
};

/**
 * Specializations for providing the configured timer top value dynamically.
 */

template <typename w_TimerDef, TimerTop timertop>
struct TopGetter;

/** Specialization for fetching from the ICR register. */
template <typename w_TimerDef>
struct TopGetter<w_TimerDef, TimerTop::icr> {
  using TypeWgmEnum = typename w_TimerDef::TypeWgmEnum;
  using Registers = typename w_TimerDef::Registers;
  using TimerCaptureType = typename w_TimerDef::TimerCaptureType;
  using BitsICR = typename TimerCaptureType::CaptureBits;
  using ICRType = typename BitsICR::type;

  static ICRType get() {
    return Registers::template Read<BitsICR>();
  }

  static ICRType get(TypeWgmEnum...) {
    return Registers::template Read<BitsICR>();
  }
};

/** Specialization for fetching from the OCRA register. */
template <typename w_TimerDef>
struct TopGetter<w_TimerDef, TimerTop::ocra> {
  using TypeWgmEnum = typename w_TimerDef::TypeWgmEnum;
  using Registers = typename w_TimerDef::Registers;
  using OCR = typename w_TimerDef::template OcrType<OcrEnum::OcrA>::OCR;
  using OCRAType = typename OCR::type;

  static OCRAType get() {
    return Registers::template Read<OCR>();
  }

  static OCRAType get(TypeWgmEnum) {
    return Registers::template Read<OCR>();
  }
};

/** Specialization for returning the hard wired timer-top. */
template <typename w_TimerDef>
struct TopGetter<w_TimerDef, TimerTop::built_in> {
  using TypeWgmEnum = typename w_TimerDef::TypeWgmEnum;
  using Registers = typename w_TimerDef::Registers;
  using BitsWGM_16 = typename w_TimerDef::BitsWGM_16;
  using BitsWGM_16_type = typename BitsWGM_16::type;

  static std::uint32_t get() {
    return WgmEnumTraits<BitsWGM_16_type>::Modes::
      template getParamFor<WaveformGeneratorModeParam::built_in_top>(
        Registers::template Read<BitsWGM_16>()).get();
  }

  static std::uint32_t get(TypeWgmEnum wgm) {
    return WgmEnumTraits<BitsWGM_16_type>::Modes::
      template getParamFor<WaveformGeneratorModeParam::built_in_top>(wgm).get();
  }
};

/**
 * Provides the register used to set the top value for the timer.
 */
template <typename w_TimerDef, TimerTop w_timer_top>
struct TopRegisterFinder;

template <typename w_TimerDef>
struct TopRegisterFinder<w_TimerDef, TimerTop::icr> {
  using TimerCaptureType = typename w_TimerDef::TimerCaptureType;
  using BitsICR = typename TimerCaptureType::CaptureBits;
  using type = BitsICR;
};

template <typename w_TimerDef>
struct TopRegisterFinder<w_TimerDef, TimerTop::ocra> {
  using OutputCompareA = typename w_TimerDef::template OcrType<OcrEnum::OcrA>;
  using type = typename OutputCompareA::OCR;
};



/**
 * Defines all the resources for a single AVR timer. This can be used for both
 * 8-bit and 16-bit timers.
 * @Params:
 *  w_BitsWGM_16: The WGM bits in the TCCRnA and TCCRnB registers.
 *  w_BitsCS: The CS bits in the TCCRnB register.
 *  w_BitsFOCA: The FOCnA bit in the TCCRnA register.
 *  w_BitsFOCB: The FOCnB bit in the TCCRnA register.
 *  w_BitsTCNT: The TCNTn register.
 *  w_OutputCompareTuple: A tuple of OutputCompare type containing properties for OCRA functions.
 *  w_TimerCapture: A TimerCapture type containing properties for ICR functions.
 *  w_RegistersTuple: A RegisterSelector wil all the registers used by the timer.
 */
template <
  typename w_BitsWGM_16,
  typename w_BitsCS,
  typename w_BitsFOCA,
  typename w_BitsFOCB,
  typename w_BitsTCNT,
  typename w_OutputCompareTuple,
  typename w_TimerCapture,
  typename w_RegistersTuple,
  typename w_TimerTopTuple = setl::ValueTuple<TimerTop, TimerTop::built_in, TimerTop::ocra>
>
struct TimerDefinition
{
  using BitsWGM_16 = w_BitsWGM_16;
  using BitsCS = w_BitsCS;
  using BitsFOCA = w_BitsFOCA;
  using BitsFOCB = w_BitsFOCB;
  using BitsTCNT = w_BitsTCNT;
  using OutputCompareTuple = w_OutputCompareTuple;
  using TimerCaptureType = w_TimerCapture;
  using Registers = setl::RegisterSelector<w_RegistersTuple>;
  using TimerTopTuple = setl::ValueTupleCat<
      w_TimerTopTuple, typename TimerCaptureType::TopCountProvided>;
  using TypeWgmEnum = typename BitsWGM_16::type;

  template <TimerTop w_timer_top>
  using TimerDefTopGetter = TopGetter<TimerDefinition, w_timer_top>;

  template <TimerTop w_timer_top>
  using TimerDefTopRegister = typename TopRegisterFinder<TimerDefinition, w_timer_top>::type;

  /**
   * The OutputCompare type for the given w_ocr value.
   */
  template <OcrEnum w_ocr>
  using OcrType = std::tuple_element_t<static_cast<std::size_t>(w_ocr), OutputCompareTuple>;


  /** Returns the timer top value for the given timer top enum. */
  static setl::Optional<std::uint32_t> get_timer_top(TimerTop timer_top) {
    return setl::ValueTupleGetter<TimerTop, TimerTopTuple, TimerDefTopGetter>::get(timer_top);
  }

  /** Returns the timer top value for the given timer top enum. */
  static setl::Optional<std::uint32_t> get_timer_top(TimerTop timer_top, TypeWgmEnum wgmEnum) {
    return setl::ValueTupleGetter<TimerTop, TimerTopTuple, TimerDefTopGetter>::get(timer_top, wgmEnum);
  }
};

/**
 * Grabs a type from a single item tuple.
 */
template <typename T>
struct PickSingleItem;

// Picks a single tuple item.
template <typename T>
struct PickSingleItem<std::tuple<T>> {
  using type = T;
};


template <typename w_TimerOutputPinSettings, typename w_TimerConfig>
struct TimerOutputPin {
  using TimerOutputPinSettings = w_TimerOutputPinSettings;
  using TimerConfig = w_TimerConfig;
  using TimerDef = typename TimerConfig::TimerDef;
  using OutputCompare = typename TimerDef::template OcrType<TimerOutputPinSettings::ocrEnum>;
    

  using COMn = EnumCOMn;
  using OCR = typename OutputCompare::OCR;

  using GpioPin = typename OutputCompare::GpioDef;

  constexpr static auto COM_MODE = TimerOutputPinSettings::invert_output
      ? COMn::clear
      : COMn::set;

  static void setupGpio() {
    GpioPin::configure_output();
  }

  static void setupTimerOutputMode() {
    TimerDef::Registers::ReadModifyWrite(typename OutputCompare::COM8{ COM_MODE });
  }

  static void setupGpioOutputMode() {
    TimerDef::Registers::ReadModifyWrite(typename OutputCompare::COM8{ EnumCOMn::disconnect });
  }

  static void pwmWriteAbsoluteValue(typename OCR::type value) {
    TimerDef::Registers::ReadModifyWrite(OCR{ value });
  }

  template <typename T>
  static void pwmWritef(float value, T top_count) {  // 0.0 to 1.0
    OCR ocr_bits{ value * top_count };
    if (value > 0.0f && value < 1.0f) {
      setupTimerOutputMode();
      TimerDef::Registers::ReadModifyWrite(ocr_bits);
    } else {
      setupGpioOutputMode();
      GpioPin::set((value > 0.0f) == TimerOutputPinSettings::invert_output);
    }
  }

  /**
   * Write a PWM value to the timer compare register.
   * Forces the output to true or false if the value is outside the range.
   */
  template <typename T, typename U>
  static void pwmWrite(T value, U top_count) {
    if (value > 0 && value < top_count) {
      setupTimerOutputMode();
      TimerDef::Registers::ReadModifyWrite(OCR{static_cast<typename OCR::type>(value)});
    } else {
      setupGpioOutputMode();
      GpioPin::set((value > 0) == TimerOutputPinSettings::invert_output);
    }
  }

  /**
   * Adjust the PWM value to the timer compare register for a top count
   * change to maintain a similar duty cycle.
   */
  template <typename T>
  static void pwmAdjust(T prev_top_count, T new_top_count) {
    if (prev_top_count == new_top_count) {
      // No change.
      return;
    }

    typename OutputCompare::COM8 com_value;
    TimerDef::Registers::Read(com_value);
    if (com_value == EnumCOMn::disconnect) {
      // Not in PWM mode, so nothing to do.
      return;
    }

    OCR ocr_bits{};
    TimerDef::Registers::Read(ocr_bits);

    float scale = new_top_count * 1.0f / prev_top_count;
    auto new_ocr_value = ocr_bits.value * scale;
    pwmWrite(new_ocr_value, new_top_count);
  }

  /**
   * Initial setup of the timer output pin.
   */
  template <typename T>
  static void setup(T initial_value, T top_count) {
    setupGpio();
    pwmWrite(initial_value, top_count);
  }

};

/**
 * Configure the timer using accurate frequency mode. This uses a programmable
 * top value (as opposed to a built in top value of 0xff, 0x1ff or 0x3ff). 
 * On 16 bit timers, the "ICR" (Input Capture Register) may be used as a top value
 * comparator otherwise all the timers will also allow the "OCRA" (Output Compare
 * Register) which clashes with one of the PWM (A) outputs reducing to one PWM
 * output for the timer using the OCRB register.
 * 
 * The timers are selected so that the most accurate setup_frequency is provided
 * however for vey high frequencies, fewer bits of resolution are provided hence
 * reducing both the frequency accuracy and the PWM resolution.
 */
template <
  typename w_TimerDef,
  std::uint32_t w_setup_frequency,
  std::uint32_t w_base_frequency,  // Usually CPU clock frequency.
  TimerPwmMode w_timer_pwm_mode,
  TimerTop w_timer_top
>
struct TimerPwmConfigutation {
  using TimerDef = w_TimerDef;
  using Registers = typename TimerDef::Registers;
  using BitsWGM_16 = typename TimerDef::BitsWGM_16;
  using EnumWGM = typename BitsWGM_16::type;
  using BitsCS = typename TimerDef::BitsCS;
  using BitsTCNT = typename TimerDef::BitsTCNT;
  using EnumCS = typename BitsCS::type;
  static constexpr TimerMode timer_mode = TimerMode::pwm;
  static constexpr TimerPwmMode timer_pwm_mode = w_timer_pwm_mode;
  static constexpr TimerTop timer_top = w_timer_top;
  using Modes = typename WgmEnumTraits<EnumWGM>::Modes::
      template type<timer_mode, timer_pwm_mode, timer_top>;
  static_assert(!std::is_same_v<std::tuple<>, Modes>,
    "Requested timer_mode and timer_top modes for waveform generator not found.");
  using Mode = typename PickSingleItem<Modes>::type;  // There must be only a single mode.

  static constexpr std::uint32_t setup_frequency = w_setup_frequency;
  static constexpr std::uint32_t base_frequency = w_base_frequency;
  static constexpr bool phase_correct_mode = TimerPwmModePhaseCorrect(w_timer_pwm_mode);
  static constexpr std::uint32_t top_resolution = sizeof(typename BitsTCNT::type) * 8;
  static constexpr EnumCS cs_value = getClockDivider<EnumCS>(
    setup_frequency, base_frequency, top_resolution, phase_correct_mode);
  static constexpr auto top_count = getClockTimerTop(
    cs_value, setup_frequency, base_frequency, phase_correct_mode);

  static_assert(cs_value != TccrEnumTraits<EnumCS>::null_value,
    "Impossible frequency settings for timer.");
  static_assert(top_count >= 2u, "Frequency too high. Invalid settings for timer.");

  using TimerSetupApplier = setl::ApplierValues<
    setl::ApplierValue<BitsCS, cs_value>,
    setl::ApplierValue<BitsWGM_16, Mode::wgm_value>>;

  /**
   * Set the base frequency for the timer dynamically. Returns the top_count
   * (maximum value) for the compare registers.
   */
  template <typename T>
  static std::uint32_t setFrequency(T frequency) {
    EnumCS cs_value = getClockDivider<EnumCS>(
        frequency, base_frequency, top_resolution, phase_correct_mode);
    auto top_count = getClockTimerTop(
        cs_value, frequency, base_frequency, phase_correct_mode);

    Registers::ReadModifyWrite(
      BitsCS{cs_value}, 
      BitsWGM_16{Mode::wgm_value});
    return top_count;
  }

  /**
   * Get the current frequency of the timer.
   * If no parameters are provided, the current timer settings are used to
   * compute the frequency.
   */
  template <typename T>
  static T getFrequency(
      setl::Optional<std::uint32_t> p_top_count = {}, 
      std::uint32_t p_base_frequency = base_frequency) {
    BitsCS cs_value_bits;
    BitsWGM_16 wgm_value_bits;
    Registers::Read(cs_value_bits, wgm_value_bits);
    auto timer_mode_optional = WgmEnumTraits<EnumWGM>::Modes::
        template getParamFor<WaveformGeneratorModeParam::timer_pwm_mode>(
            wgm_value_bits.value);
    if (!timer_mode_optional.is_present()) {
      return -1;
    }

    auto l_top_count = p_top_count.is_present() 
        ? p_top_count.get() 
        : TimerDef::get_timer_top(WgmEnumTraits<EnumWGM>::Modes::
          template getParamFor<WaveformGeneratorModeParam::timer_top>(
            wgm_value_bits.value).get()).get();
    auto is_phase_correct_mode = TimerPwmModePhaseCorrect(timer_mode_optional.get());
    return getTimerFrequency<T>(
      l_top_count, cs_value_bits.value, p_base_frequency, is_phase_correct_mode);
  }
};

/**
 * Configure the timer using a built-in top counter value. 8 bit timers are limited
 * to one top value (0xff) while the 16 bit timers have 3 top values (0xff, 0x1ff and
 * 0x3ff or 8, 9 and 10 bits of resolution.
 * 
 * The selected running frequencu will be less than or equal to the provided 
 * "max_frequency" but greater than.
 */
template <
  typename w_TimerDef,
  std::uint32_t w_max_frequency,
  std::uint32_t w_base_frequency,  // Usually CPU clock frequency.
  TimerPwmMode w_timer_pwm_mode,
  std::uint32_t w_bits_resolution  // Number of bits for the top value.
>
struct TimerPwmBuiltinTopConfigutation {
  using TimerDef = w_TimerDef;
  using Registers = typename TimerDef::Registers;
  using BitsWGM_16 = typename TimerDef::BitsWGM_16;
  using EnumWGM = typename BitsWGM_16::type;
  using BitsCS = typename TimerDef::BitsCS;
  using BitsTCNT = typename TimerDef::BitsTCNT;
  using EnumCS = typename BitsCS::type;

  using TopCountType = typename TimerDef::template OcrType<OcrEnum::OcrA>::OCR::type;

  static constexpr std::uint32_t setup_frequency = w_max_frequency;
  static constexpr std::uint32_t base_frequency = w_base_frequency;
  static constexpr TimerPwmMode timer_pwm_mode = w_timer_pwm_mode;
  static constexpr bool phase_correct_mode = TimerPwmModePhaseCorrect(w_timer_pwm_mode);
  static constexpr std::uint32_t top_resolution = w_bits_resolution;
  static constexpr EnumCS cs_value = getClockDivider<EnumCS>(
    setup_frequency, base_frequency, top_resolution, phase_correct_mode);
  static constexpr std::uint32_t actual_divider = w_base_frequency;
  static constexpr auto top_count = setl::mersenne(top_resolution);
  // Find the WGM bits for these settings.
  static constexpr EnumWGM wgm_value = WgmEnumTraits<EnumWGM>::Modes::
      template built_in_type<TimerMode::pwm, timer_pwm_mode, top_count>::wgm_value;

  // Timer setup for "built in" top setting.
  using TimerSetupApplier = setl::ApplierValues<
    setl::ApplierValue<BitsCS, cs_value>,
    setl::ApplierValue<BitsWGM_16, wgm_value>>;


  using PwmEnableA = setl::ApplierValues<
    setl::ApplierValue<BitsWGM_16, wgm_value>>;

  /**
 * Set the base frequency for the timer dynamically. Returns the top_count
 * (maximum value) for the compare registers.
 */
  template <typename T>
  static std::uint32_t setFrequency(T frequency) {
    EnumCS cs_value = getClockDivider<EnumCS>(
      frequency, base_frequency, top_resolution, phase_correct_mode);

    Registers::ReadModifyWrite(
      BitsCS{ cs_value },
      BitsWGM_16{ wgm_value });

    return top_count;
  }

  /**
   * Get the current frequency of the timer.
   * If no parameters are provided, the current timer settings are used to
   * compute the frequency.
   */
  template <typename T>
  static T getFrequency(
    setl::Optional<std::uint32_t> p_top_count = {},
    std::uint32_t p_base_frequency = base_frequency) {
    BitsCS cs_value_bits;
    BitsWGM_16 wgm_value_bits;
    Registers::Read(cs_value_bits, wgm_value_bits);
    auto timer_mode_optional = WgmEnumTraits<EnumWGM>::Modes::
      template getParamFor<WaveformGeneratorModeParam::timer_pwm_mode>(
        wgm_value_bits.value);
    if (!timer_mode_optional.is_present()) {
      return -1;
    }

    auto l_top_count = p_top_count.is_present()
      ? p_top_count.get()
      : TimerDef::get_timer_top(WgmEnumTraits<EnumWGM>::Modes::
        template getParamFor<WaveformGeneratorModeParam::timer_top>(
          wgm_value_bits.value).get()).get();
    auto is_phase_correct_mode = TimerPwmModePhaseCorrect(timer_mode_optional.get());
    return getTimerFrequency<T>(
      l_top_count, cs_value_bits.value, p_base_frequency, is_phase_correct_mode);
  }

};

template <
  TimerMode w_timer_mode,
  TimerPwmMode w_timer_pwm_mode,
  TimerTop w_timer_top>
struct TimerSettings {
  static constexpr TimerMode timer_mode = w_timer_mode;
  static constexpr TimerPwmMode timer_pwm_mode = w_timer_pwm_mode;
  static constexpr TimerTop timer_top = w_timer_top;
};

template <
  typename w_TimerDef,
  std::uint32_t w_setup_frequency,
  std::uint32_t w_base_frequency,  // Usually CPU clock frequency.
  typename w_TimerSettings
>
struct TimerConfiguration;

/**
 * Constant frequency using ICR top register.
 */
template <
  typename w_TimerDef,
  std::uint32_t w_setup_frequency,
  std::uint32_t w_base_frequency,  // Usually CPU clock frequency.
  TimerPwmMode w_timer_pwm_mode,
  TimerTop w_timer_top
>
struct TimerConfiguration<
    w_TimerDef, 
    w_setup_frequency, 
    w_base_frequency, 
    TimerSettings<
        TimerMode::pwm,
        w_timer_pwm_mode, 
        w_timer_top>> {

  using TimerDef = w_TimerDef;
  using TopCountBits = typename TimerDef::template TimerDefTopRegister<w_timer_top>;
  using TopCountType = typename TopCountBits::type;

  using Config = TimerPwmConfigutation<
    w_TimerDef, w_setup_frequency, w_base_frequency, w_timer_pwm_mode, w_timer_top>;
  using Registers = typename Config::Registers;

  using TopApplier = setl::ApplierValues<
      setl::ApplierValue<TopCountBits, Config::top_count>>;

  /**
   * Setup the timer for these settings.
   */
  static void setupTimer() {
    Config::TimerSetupApplier::template apply<Registers>();
    TopApplier::template apply<Registers>();
  }

  template <typename T>
  static std::uint32_t setFrequency(T frequency) {
    const typename TopCountBits::type top_count = Config::setFrequency(frequency);
    
    Registers::ReadModifyWrite(TopCountBits{top_count});
    return top_count;
  }

  /**
   * Get the current top count.
   */
  static typename TopCountBits::type get_top_count() {
    TopCountBits top_count_bits;
    Registers::Read(top_count_bits);
    return top_count_bits.value;
  }
  
  /**
   * Get the current frequency of the timer.
   */
  template <typename T>
  static T getFrequency() {
    return Config::template getFrequency<T>();
  }

  template <typename w_TimerOutputPinSettings>
  using OutputPin = TimerOutputPin<w_TimerOutputPinSettings, TimerConfiguration>;

};

/**
 * Timer settings for built in top values.
 * The 8 bit timers have only an 8 bit (0xff) top value but
 * the 16 bt timers have 8, 9 and 10 bit built in top values.
 */


template <
  TimerMode w_timer_mode,
  TimerPwmMode w_timer_pwm_mode,
  std::uint8_t w_bits_resolution=8u
>
struct TimerBuiltInSettings {
  static constexpr TimerMode timer_mode = w_timer_mode;
  static constexpr TimerPwmMode timer_pwm_mode = w_timer_pwm_mode;
  static constexpr TimerTop timer_top = TimerTop::built_in;
  static constexpr std::uint8_t bits_resolution = w_bits_resolution;
};

template <
  typename w_TimerDef,
  std::uint32_t w_setup_frequency,
  std::uint32_t w_base_frequency,  // Usually CPU clock frequency.
  TimerPwmMode w_timer_pwm_mode,
  std::uint8_t w_bits_resolution
>
struct TimerConfiguration<
  w_TimerDef,
  w_setup_frequency,
  w_base_frequency,
  TimerBuiltInSettings<
    TimerMode::pwm,
    w_timer_pwm_mode,
    w_bits_resolution>> {

  using TimerDef = w_TimerDef;

  using Config = TimerPwmBuiltinTopConfigutation<
    w_TimerDef, w_setup_frequency, w_base_frequency, w_timer_pwm_mode, w_bits_resolution>;
  using Registers = typename Config::Registers;
  using TopCountType = typename Config::TopCountType;

  /**
   * Setup the timer for these settings.
   */
  static void setupTimer() {
    Config::TimerSetupApplier::template apply<Registers>();
  }


  template <typename T>
  static std::uint32_t setFrequency(T frequency) {
    const auto top_count = Config::setFrequency(frequency);

    // Top count it determined by w_bits_resolution and is set by the WGM bits.
    return top_count;
  }

  /**
   * Get the current frequency of the timer.
   */
  template <typename T>
  static T getFrequency() {
    return Config::template getFrequency<T>();
  }

  /**
   * Get the current top count.
   */
  static TopCountType get_top_count() {
    return Config::top_count;
  }

  /**
   * A PWM timer pin configuration.
   */
  template <typename w_TimerOutputPinSettings>
  using OutputPin = TimerOutputPin<w_TimerOutputPinSettings, TimerConfiguration>;

};


/**
 * Timer settings for output GPIO pins.
 */
template <
  OcrEnum w_ocrEnum,
  bool w_invert_output>
struct TimerOutputPinSettings {
  static constexpr OcrEnum ocrEnum = w_ocrEnum;
  static constexpr bool invert_output = w_invert_output;
};

template <OcrEnum w_ocrEnum>
struct TimerOutputPinSettingsSelector {
  template <typename Settings>
  struct Predicate {
    static constexpr bool value = w_ocrEnum == Settings::ocrEnum;
  };
};


/**
 * A PWM timer configuration containing pin settings.
 * This contains a complete configuration for a timer including the output
 * PWM pins.
 */
template <typename w_Config, typename...w_PinSettings>
struct TimerPwmPinConfiguration {
  using Config = w_Config;

  using TopCountType = typename Config::TopCountType;
  using PinSettings = std::tuple<w_PinSettings...>;
  template <typename w_PinSetting>
  using OutputPin = typename Config::template OutputPin<w_PinSetting>;

  template <int w_pin>
  using PwmPinByArgN = OutputPin<std::tuple_element_t<w_pin, PinSettings>>;

  template <OcrEnum w_ocrEnum>
  using PwmPinByOcrReg = OutputPin<setl::tuple_find_t<
      TimerOutputPinSettingsSelector<w_ocrEnum>::template Predicate, PinSettings>>;

 private:
  // Function for setting up a pin.
  template <typename w_PinSetting>
  struct SetupPin {
    using ThisPin = OutputPin<w_PinSetting>;

    static void run(TopCountType set_count, TopCountType top_count) {
      ThisPin::setup(set_count, top_count);
    }
  };

  // Function for adjusting for a new timer top.
  template <typename w_PinSetting>
  struct AdjustPin {
    using ThisPin = OutputPin<w_PinSetting>;

    static void run(TopCountType prev_top_count, TopCountType new_top_count) {
      ThisPin::pwmAdjust(prev_top_count, new_top_count);
    }
  };

 public:
  /**
    * Setup the timer for these settings.
    */
  static void setup() {
    Config::setupTimer();

    // Configure PWM pins.
    auto top_count = Config::get_top_count();
    setl::tuple_for_each<SetupPin, PinSettings>::runall(top_count / 2, top_count);
  }

  /**
    * Set the frequency of the timer.
    */
  template <typename T>
  static std::uint32_t setFrequency(T frequency) {
    if (sizeof...(w_PinSettings) > 0) {
      auto prev_top_count = Config::get_top_count();
      auto new_top_count = Config::setFrequency(frequency);
      setl::tuple_for_each<AdjustPin, PinSettings>::runall(prev_top_count, new_top_count);
      return new_top_count;
    }
    return Config::setFrequency(frequency);
  }

  /**
    * Get the current frequency of the timer.
    */
  template <typename T>
  static T getFrequency() {
    return Config::template getFrequency<T>();
  }

  /**
    * Get the current top count.
    */
  static typename Config::TopCountType get_top_count() {
    return Config::get_top_count();
  }

  /**
    * Write a PWM value to the given pin.
    */
  template <typename w_PinSetting>
  static void pwmWrite(w_PinSetting, std::uint16_t value) {
    Config::pwmWrite(value);
  }

};


template <typename w_TimerDef>
struct Timer {

  using TimerDef = w_TimerDef;

  /**
   * The OutputCompare type for the given w_ocr value.
   */
  template <OcrEnum w_ocr>
  using OcrType = typename TimerDef::template OcrType<w_ocr>;

  /**
   * Settings for accurate static frequency timer.
   */
  template <
    std::uint32_t w_setup_frequency,
    std::uint32_t w_base_frequency,  // Usually CPU clock frequency.
    TimerMode w_timer_mode,
    TimerPwmMode w_timer_pwm_mode,
    TimerTop w_timer_top
  >
  using FrequencyAccurate = TimerConfiguration<
      TimerDef, 
      w_setup_frequency, 
      w_base_frequency,
      TimerSettings<w_timer_mode, w_timer_pwm_mode, w_timer_top>>;

  /**
   * Settings for approximate frequency using built in top values.
   */
  template <
    std::uint32_t w_setup_frequency,
    std::uint32_t w_base_frequency,  // Usually CPU clock frequency.
    TimerMode w_timer_mode,
    TimerPwmMode w_timer_pwm_mode,
    std::uint8_t w_bits_resolution
  >
  using BuiltInTop = TimerConfiguration<
    TimerDef,
    w_setup_frequency,
    w_base_frequency,
    TimerBuiltInSettings<w_timer_mode, w_timer_pwm_mode, w_bits_resolution>>;


  static std::uint32_t getTopCount() {
    typename TimerDef::BitsCS cs_value_bits;
    typename TimerDef::BitsWGM_16 wgm_value_bits;
    TimerDef::Registers::Read(cs_value_bits, wgm_value_bits);
    using EnumWGM = typename TimerDef::BitsWGM_16::type;
    auto top_count = TimerDef::get_timer_top(
      WgmEnumTraits<EnumWGM>::Modes::
          template getParamFor<WaveformGeneratorModeParam::timer_top>(
            wgm_value_bits.value).get()).get();
    return top_count;
  }
  
  /**
   * A PWM timer configuration containing pin settings.
   * This contains a complete configuration for a timer including the output
   * PWM pins.
   */
  template <typename w_Config, typename...w_PinSettings>
  using PwmPinConfiguration = TimerPwmPinConfiguration<w_Config, w_PinSettings...>;
};


} // namespace base
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ARDO_AVR_BASE_TIMER__H