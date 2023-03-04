// ArdOinus specific header for AVR atmega328p MCU.
// This file will not be regenerated (unlike ardo_supplemental_atmega328p.h)
// so manual changes to this file will survive regeneration of architecture
// specific definitions.

#ifndef ardo_supplemental_atmega328p_defs__h
#define ardo_supplemental_atmega328p_defs__h

#include "setl_optional.h"
#include "setl_tuple_helpers.h"
#include "setl_int_scaler.h"
#include "setl_system.h"
#include "setlx_cstdint.h"
#include "setlx_type_traits.h"
#include "ardo_supplemental_atmega328p.h"

namespace ardo {
namespace sys {
namespace avr {

/**
 * The types of resources provided.
 */
enum class ResourceType : unsigned {
  none,
  digital_gpio,
  analog_in,
  analog_comparator_in,
  analog_comparator,
  pulse_width_modulation,
  counter_input,
  counter_capture,
  spi_bus,
  i2c_bus,
  uart_w,
  uart_r,
  uart_rw,
  uart_external_clock,
  interrupt_input,
  timed_event,
  clock_out,
  reset_input,
  xtal
};

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
  using root_deps = typename setl::tuple_concat<t_deps, ts_deps>::type;
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
template <typename T, ResourceType w_resource_type, typename P=std::tuple<T>>
struct Dependency;

template <typename T, ResourceType w_resource_type, typename...Ps>
struct Dependency<T, w_resource_type, std::tuple<Ps...>> {
  using Resource = T;
  static constexpr ResourceType resource_type = w_resource_type;
  using dependencies = std::tuple<Ps...>;
};

/**
 * Tuple of root dependencies of a resource.
 */
template <typename T>
using RootDependencies = typename nfp::RootDependencyHelper<
  typename T::dependencies>::root_deps;

namespace nfp {

template <typename T, ResourceType w_resource_type, typename w_resources>
struct ResourceFinderHelper {};

template <typename T, ResourceType w_resource_type>
struct ResourceFinderHelper<T, w_resource_type, std::tuple<>> {
  using Resource = void;
};

template <typename T, ResourceType w_resource_type, typename R, typename...Rs>
struct ResourceFinderHelper<T, w_resource_type, std::tuple<R, Rs...>> {
  using Rest = ResourceFinderHelper<T, w_resource_type, std::tuple<Rs...>>;

  using Resource = typename std::conditional_t<
      R::resource_type == w_resource_type
      && setl::has_type_v<T, typename R::dependencies>, R, Rest>::Resource;
};

}  // namespace nfp

template <typename...w_Resources>
struct ResourceFinder {
  using Resources = std::tuple<w_Resources...>;

  // Find the resouce related to the root resources.
  template <typename T, ResourceType w_resource_type>
  using Resource = typename nfp::ResourceFinderHelper<
      T, w_resource_type, Resources>::Resource;
};


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
    / (R{phase_correct_mode ? 2ul : 1ul}
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
    Dependency<w_GpioPort, ResourceType::digital_gpio, std::tuple<w_GpioPort>>,
    setl::ApplierRunner,
    w_GpioPortDefinition {
  using DerivedPort = w_GpioPort;
  using GpioPortDefinition = w_GpioPortDefinition;
  using PortBit = typename GpioPortDefinition::PortBit;
  using PinBit = typename GpioPortDefinition::PinBit;
  using DdBit = typename GpioPortDefinition::DdBit;
  using PortReg = typename GpioPortDefinition::PortReg;
  using PinReg = typename GpioPortDefinition::PinReg;
  using DdReg = typename GpioPortDefinition::DdReg;

  template <bool with_pullup>
  using ConfigureAsInput = setl::Appliers<
    setl::Applier<DdBit, false, DdReg>, setl::Applier<PortBit, with_pullup, PortReg>>;

  template <bool level>
  using ConfigureOutput = setl::Appliers<
    setl::Applier<PortBit, level, PortReg>, setl::Applier<DdBit, true, DdReg>>;

 public:
  // Table 13-1 of the ATMEGA328P datasheet defines these bits.
  // These assume the ccPUD bit rrMCUCR is 0 (false).
  using ConfigureInput = ConfigureAsInput<false>;
  using ConfigureInputPullup = ConfigureAsInput<true>;
  using ConfigureOutputFalse = ConfigureOutput<false>;
  using ConfigureOutputTrue = ConfigureOutput<true>;
  using ConfigureOutputOnly = setl::Appliers<setl::Applier<DdBit, true, DdReg>>;

  /// configure the GPIO based on the Configure<out, pullup> template type.
  template <typename w_Configuration>
  static void configure() {
    // ApplierRunner performs state synchronization.
    ApplierRunner::applySync<w_Configuration>();
  }

  static void configure_input() {
    configure<ConfigureInput>();
  }

  static void configure_input_pullup() {
    configure<ConfigureInputPullup>();
  }

  static void configure_output() {
    configure<ConfigureOutputOnly>();
  }

  static void configure_output_true() {
    configure<ConfigureOutputTrue>();
  }
  static void configure_output_false() {
    configure<ConfigureOutputFalse>();
  }

  static void configure(bool is_output, bool with_pullup_or_outval) {
    // Synchronization block.
    { // AVR needs gpio pin register configurations changes to have a 
      // synchronizing clock cycle.
      setl::System::MemoryBarrier barrier;
      DdReg::ReadModifyWrite(DdBit{ is_output });
      PortReg::ReadModifyWrite(PortBit{ with_pullup_or_outval });
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
  using Configuration = typename Gpio::template ConfigureAsInput<with_pullup>;

  static void configure() {
    Gpio::template configure<Configuration>();
  }

  // Gets the current value of the GPIO pin.
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
  using Configuration = typename Gpio::template ConfigureOutput<default_value>;

  static void configure() {
    Gpio::template configure<Configuration>();
  }

  // Sets the level of the output bit (true = HIGH, false = LOW).
  static void set(bool out) {
    return Gpio::set(out);
  }

  // Gets the current value of the GPIO pin.
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
  using ConfigurationHigh = typename Gpio::template ConfigureAsInput<with_pullup>;
  using ConfigurationOutLow = typename Gpio::template ConfigureOutput<false>;

  static void configure() {
    return Gpio::template configure<ConfigurationHigh>();
  }

  // Sets the level of the output bit (true = HIGH, false = LOW).
  static void set(bool out) {
    if (out) {
      Gpio::template configure<ConfigurationHigh>();
    } else {
      Gpio::template configure<ConfigurationOutLow>();
    }
  }

  // Gets the current value of the GPIO pin.
  static bool get() {
    return Gpio::get();
  }
};

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

template <typename w_OCR, 
          typename w_OCIE, 
          typename w_OCF, 
          typename w_COM, 
          typename w_COM8>
struct OutputCompare {
  using OCR = w_OCR;
  using OCIE = w_OCIE;
  using OCF = w_OCF;
  using COM = w_COM;
  using COM8 = w_COM8;
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
  using OCR = typename w_TimerDef::OutputCompareA::OCR;
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
  using OutputCompareA = typename w_TimerDef::OutputCompareA;
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
 *  w_OutputCompareA: An OutputCompare type containing properties for OCRA functions.
 *  w_OutputCompareB: An OutputCompare type containing properties for OCRB functions.
 *  w_TimerCapture: A TimerCapture type containing properties for ICR functions.
 *  w_RegistersTuple: A RegisterSelector wil all the registers used by the timer.
 *  w_GpioA: The GPIO pin used for OCRA.
 *  w_GpioB: The GPIO pin used for OCRB.
 */
template <
  typename w_BitsWGM_16,
  typename w_BitsCS,
  typename w_BitsFOCA,
  typename w_BitsFOCB,
  typename w_BitsTCNT,
  typename w_OutputCompareA,
  typename w_OutputCompareB,
  typename w_TimerCapture,
  typename w_RegistersTuple,
  typename w_GpioA,
  typename w_GpioB,
  typename w_TimerTopTuple = setl::ValueTuple<TimerTop, TimerTop::built_in, TimerTop::ocra>
>
struct TimerDefinition
{
  using BitsWGM_16 = w_BitsWGM_16;
  using BitsCS = w_BitsCS;
  using BitsFOCA = w_BitsFOCA;
  using BitsFOCB = w_BitsFOCB;
  using BitsTCNT = w_BitsTCNT;
  using OutputCompareA = w_OutputCompareA;
  using OutputCompareB = w_OutputCompareB;
  using TimerCaptureType = w_TimerCapture;
  using Registers = setl::RegisterSelector<w_RegistersTuple>;
  using GpioA = w_GpioA;
  using GpioB = w_GpioB;
  using TimerTopTuple = setl::ValueTupleCat<
      w_TimerTopTuple, typename TimerCaptureType::TopCountProvided>;
  using TypeWgmEnum = typename BitsWGM_16::type;

  template <TimerTop w_timer_top>
  using TimerDefTopGetter = TopGetter<TimerDefinition, w_timer_top>;

  template <TimerTop w_timer_top>
  using TimerDefTopRegister = typename TopRegisterFinder<TimerDefinition, w_timer_top>::type;

  /** Returns the timer top value for the given timer top enum. */
  static setl::Optional<std::uint32_t> get_timer_top(TimerTop timer_top) {
    return setl::ValueTupleGetter<TimerTop, TimerTopTuple, TimerDefTopGetter>::get(timer_top);
  }

  /** Returns the timer top value for the given timer top enum. */
  static setl::Optional<std::uint32_t> get_timer_top(TimerTop timer_top, TypeWgmEnum wgmEnum) {
    return setl::ValueTupleGetter<TimerTop, TimerTopTuple, TimerDefTopGetter>::get(timer_top, wgmEnum);
  }
};

using Timer0Def = TimerDefinition<
  BitsWGM0_210,
  BitsCS01_16,
  BitsFOC0A,
  BitsFOC0B,
  BitsTCNT0,
  OutputCompare<BitsOCR0A, BitsOCIE0A, BitsOCF0A, BitsCOM0A, BitsCOM0A8>,
  OutputCompare<BitsOCR0B, BitsOCIE0B, BitsOCF0B, BitsCOM0B, BitsCOM0B8>,
  TimerCapture<void, void, void>,
  std::tuple<
    RegisterTCCR0AB,
    RegisterTCCR0A,
    RegisterTCNT0, 
    RegisterOCR0A,
    RegisterOCR0B, 
    RegisterTIMSK0, 
    RegisterTIFR0>,
  ppPD6, // OC0A
  ppPD5  // OC0B
>;

using Timer1Def = TimerDefinition<
  BitsWGM1_3210,
  BitsCS11_16,
  BitsFOC1A,
  BitsFOC1B,
  BitsTCNT1,
  OutputCompare<BitsOCR1A, BitsOCIE1A, BitsOCF1A, BitsCOM1A, BitsCOM1A8>,
  OutputCompare<BitsOCR1B, BitsOCIE1B, BitsOCF1B, BitsCOM1B, BitsCOM1B8>,
  TimerCapture<BitsICR1, BitsICNC1_16, BitsICES1_16>,
  std::tuple<
    RegisterTCCR1A,
    RegisterTCCR1AB,
    RegisterTCCR1C,  // Timer1 has FOC1A/B in this register.
    RegisterIRC1,
    RegisterTCNT1,
    RegisterOCR1A,
    RegisterOCR1B,
    RegisterTIMSK1,
    RegisterTIFR1>,
  ppPB1,  // OC1A
  ppPB2   // OC1B
>;

using Timer2Def = TimerDefinition<
  BitsWGM2_210,
  BitsCS21_16,
  BitsFOC2A,
  BitsFOC2B,
  BitsTCNT2,
  OutputCompare<BitsOCR2A, BitsOCIE2A, BitsOCF2A, BitsCOM2A, BitsCOM2A8>,
  OutputCompare<BitsOCR2B, BitsOCIE2B, BitsOCF2B, BitsCOM2B, BitsCOM2B8>,
  TimerCapture<void, void, void>,
  std::tuple<
    RegisterTCCR2AB, 
    RegisterTCCR2A,
    RegisterTCNT2,
    RegisterOCR2A, 
    RegisterOCR2B, 
    RegisterTIMSK2, 
    RegisterTIFR2>,
  ppPB3,  // OC2A
  ppPD3   // OC2B
>;


// template <
//   typename w_TimerDef,
//   std::uint32_t w_setup_frequency,
//   bool w_phase_correct_mode,
//   std::uint32_t w_base_frequency  // Usually CPU clock frequency.
// >
// struct Timer16 {
//   using TimerDef = w_TimerDef;
//   using Registers = typename TimerDef::Registers;
//   using BitsWGM_16 = typename TimerDef::BitsWGM_16;
//   using EnumWGM = typename BitsWGM_16::type;
//   using BitsCS = typename TimerDef::BitsCS;
//   using BitsTCNT = typename TimerDef::BitsTCNT;
//   using EnumCS = typename BitsCS::type;
//   static constexpr std::uint32_t setup_frequency = w_setup_frequency;
//   static constexpr std::uint32_t base_frequency = w_base_frequency;
//   static constexpr bool phase_correct_mode = w_phase_correct_mode;
//   static constexpr std::uint32_t top_resolution = sizeof(typename BitsTCNT::type) * 8;
//   static constexpr EnumCS cs_value = getClockDivider<EnumCS>(
//     setup_frequency, base_frequency, top_resolution, phase_correct_mode);
//   static constexpr auto top_count = getClockTimerTop(
//     cs_value, setup_frequency, base_frequency, phase_correct_mode);

//   static_assert(cs_value != TccrEnumTraits<EnumCS>::null_value,
//        "Impossible frequency settings for timer.");
//   static_assert(top_count >= 2u, "Frequency too high. Invalid settings for timer.");

//   /**
//    *
//    */
//   static void setFastPwm() {
//     Registers::ReadModifyWrite(BitsCS{ cs_value }, BitsWGM_16{ EnumWGM::fast_pwm_icr });
//     Registers::ReadModifyWrite(BitsICR1{ top_count });
//   }
// };

template <typename T>
struct PickSingleItem;

// Picks a single tuple item.
template <typename T>
struct PickSingleItem<std::tuple<T>> {
  using type = T;
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
    if (!timer_mode_optional.has_value()) {
      return -1;
    }

    auto l_top_count = p_top_count.has_value() 
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
    const auto top_count = Config::setFrequency(frequency);
    
    Registers::ReadModifyWrite(TopCountBits{top_count});
    return top_count;
  }
  
  /**
   * Get the current frequency of the timer.
   */
  template <typename T>
  static T getFrequency() {
    return Config::template getFrequency<T>();
  }
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
  using Config = TimerPwmBuiltinTopConfigutation<
    w_TimerDef, w_setup_frequency, w_base_frequency, w_timer_pwm_mode, w_bits_resolution>;
  using Registers = typename Config::Registers;

  /**
   * Setup the timer for these settings.
   */
  static void setupTimer() {
    Config::TimerSetupApplier::template apply<Registers>();
  }

  template <typename w_GpioPin>
  static void setupGpio() {

  }


  void pwmWrite(std::uint16_t) {

  }

};

enum class OcrEnum : std::uint8_t {
  OcrA,
  OcrB
};


template <typename w_TimerDef>
struct Timer {

  using TimerDef = w_TimerDef;

  /**
   * The OutputCompare type for the given w_ocr value.
   */
  template <OcrEnum w_ocr>
  using OcrType = std::conditional_t<
    w_ocr == OcrEnum::OcrA,
    typename TimerDef::OutputCompareA,
    typename TimerDef::OutputCompareB>;

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

};

struct Timer0 : Timer<Timer0Def> {
  using PwmFrequencyAccurate = FrequencyAccurate<
    20000, 16000000, TimerMode::pwm, TimerPwmMode::fast, TimerTop::built_in>;

};

struct Timer1 : Timer<Timer1Def> {

  using PwmFrequencyAccurate = FrequencyAccurate<
    11000, 16000000, TimerMode::pwm, TimerPwmMode::fast, TimerTop::icr>;

  using BuiltInTopConf = BuiltInTop<
    50000, 16000000, TimerMode::pwm, TimerPwmMode::fast, 8>;

  static std::uint32_t xx() {

    using TT = WgmEnumTraits<BitsWGM1_3210::type>::Modes;
    using TT1 = Wgm1TopCountMapping;

    auto qq = Timer1Def::TimerDefTopGetter<TimerTop::ocra>::get();

    auto zz = WgmEnumTraits<EnumWGM1>::Modes::getParamFor<WaveformGeneratorModeParam::built_in_top>
      (EnumWGM1::fast_pwm_10bit).get();


    setl::Optional<EnumWGM1> ww;

    setl::Optional<TimerTop> dd = 
    WgmEnumTraits<EnumWGM1>::Modes::
      template getParamFor<WaveformGeneratorModeParam::timer_top>(
        EnumWGM1::fast_pwm_10bit);

    auto tt = Timer1Def::get_timer_top(dd.get(), EnumWGM1::fast_pwm_10bit);

    auto c = WgmEnumTraits<EnumWGM1>::Modes::
      template getParamFor<WaveformGeneratorModeParam::timer_top>(
        EnumWGM1::pwm_phase_correct_9bit).get();

    auto vv = Timer1Def::get_timer_top(TimerTop::built_in, EnumWGM1::pwm_phase_correct_9bit).get();

    vv = Timer1Def::TimerDefTopGetter<TimerTop::built_in>::get(EnumWGM1::pwm_phase_correct_9bit);

    using TimerTopTuple = Timer1Def::TimerTopTuple;

    vv = setl::ValueTupleGetter<TimerTop, TimerTopTuple, Timer1Def::TimerDefTopGetter>
          ::get(TimerTop::built_in, EnumWGM1::pwm_phase_correct_9bit).get();

    return vv;
  }  
};

struct Timer2 : Timer<Timer2Def> {
  using PwmFrequencyAccurate = FrequencyAccurate<
    20000, 16000000, TimerMode::pwm, TimerPwmMode::fast, TimerTop::ocra>;

  using BuiltInTopConf = BuiltInTop<
    11000, 16000000, TimerMode::pwm, TimerPwmMode::fast, 8>;
};

// template <typename w_OCR, typename w_Gpio, typename w_Timer, OcrEnum w_ocr>
// struct OCRPin : Dependency<w_OCR, ResourceType::pulse_width_modulation, std::tuple<w_Gpio>> {
//   using TimerType = w_Timer;
//   using Gpio = w_Gpio;
//   static constexpr OcrEnum ocr = w_ocr;
//   using OutputCompareType = typename TimerType:: template OcrType<ocr>;

// };



// template <typename w_ComBits, typename w_RegisterTccnA>
// struct TimerCompareDefinition {
//   using ComBits = w_ComBits;
//   using RegisterTccnA = w_RegisterTccnA;

// };

// template <typename w_Self, typename w_Gpio, typename w_Defn>
// struct TimerCompare {
//   using Self = w_Self;
//   using Gpio = w_Gpio;
//   using Definition = w_Defn;
//   using ComBits = typename Definition::ComBits;
//   using RegisterTccnA = typename Definition::RegisterTccnA;

// };

using AvailableTimers = std::tuple<Timer0, Timer1, Timer2>;

struct ppADC6 : Dependency<ppADC6, ResourceType::analog_in, std::tuple<ppADC6>> {
  static constexpr bool Package32pinOnly = true;
};

struct ppADC7 : Dependency<ppADC7, ResourceType::analog_in, std::tuple<ppADC7>> {
  static constexpr bool Package32pinOnly = true;
};

struct ppT0 : Dependency<ppT0, ResourceType::counter_input, std::tuple<ppPD4>> {
};

struct ppT1 : Dependency<ppT1, ResourceType::counter_input, std::tuple<ppPD5>> {
};

struct ppXCK : Dependency<ppXCK, ResourceType::uart_external_clock, std::tuple<ppPD4>> {
};

struct ppADC0 : Dependency<ppADC0, ResourceType::analog_in, std::tuple<ppPC0>> {
};

struct ppADC1 : Dependency<ppADC1, ResourceType::analog_in, std::tuple<ppPC1>> {
};

struct ppADC2 : Dependency<ppADC2, ResourceType::analog_in, std::tuple<ppPC2>> {
};

struct ppADC3 : Dependency<ppADC3, ResourceType::analog_in, std::tuple<ppPC3>> {
};

struct ppADC4 : Dependency<ppADC4, ResourceType::analog_in, std::tuple<ppPC4>> {
};

struct ppADC5 : Dependency<ppADC5, ResourceType::analog_in, std::tuple<ppPC5>> {
};

struct ppCLKO : Dependency<ppCLKO, ResourceType::clock_out, std::tuple<ppPB0>> {
};

struct ppICP1 : Dependency<ppICP1, ResourceType::counter_capture, std::tuple<ppPB0>> {
};

struct ppINT0 : Dependency<ppINT0, ResourceType::interrupt_input, std::tuple<ppPD2>> {
};

struct ppINT1 : Dependency<ppINT1, ResourceType::interrupt_input, std::tuple<ppPD3>> {
};

struct ppOC0A : Dependency<ppOC0A, ResourceType::pulse_width_modulation, std::tuple<ppPD6>> {
};

struct ppOC0B : Dependency<ppOC0B, ResourceType::pulse_width_modulation, std::tuple<ppPD5>> {
};

struct ppOC1A : Dependency<ppOC1A, ResourceType::pulse_width_modulation, std::tuple<ppPB1>> {
};

struct ppOC1B : Dependency<ppOC1B, ResourceType::pulse_width_modulation, std::tuple<ppPB2>> {
};

struct ppOC2A : Dependency<ppOC2A, ResourceType::pulse_width_modulation, std::tuple<ppPB3>> {
};

struct ppOC2B : Dependency<ppOC2B, ResourceType::pulse_width_modulation, std::tuple<ppPD3>> {
};

struct ppRESET : Dependency<ppRESET, ResourceType::reset_input, std::tuple<ppPC6>> {
};

struct ppTOSC1 : Dependency<ppTOSC1, ResourceType::counter_input, std::tuple<ppPB6>> {
};

struct ppTOSC2 : Dependency<ppTOSC2, ResourceType::counter_input, std::tuple<ppPB7>> {
};

struct ppPCINT0 : Dependency<ppPCINT0, ResourceType::interrupt_input, std::tuple<ppPB0>> {
};

struct ppPCINT1 : Dependency<ppPCINT1, ResourceType::interrupt_input, std::tuple<ppPB1>> {
};

struct ppPCINT2 : Dependency<ppPCINT2, ResourceType::interrupt_input, std::tuple<ppPB2>> {
};

struct ppPCINT3 : Dependency<ppPCINT3, ResourceType::interrupt_input, std::tuple<ppPB3>> {
};

struct ppPCINT4 : Dependency<ppPCINT4, ResourceType::interrupt_input, std::tuple<ppPB4>> {
};

struct ppPCINT5 : Dependency<ppPCINT5, ResourceType::interrupt_input, std::tuple<ppPB5>> {
};

struct ppPCINT6 : Dependency<ppPCINT6, ResourceType::interrupt_input, std::tuple<ppPB6>> {
};

struct ppPCINT7 : Dependency<ppPCINT7, ResourceType::interrupt_input, std::tuple<ppPB7>> {
};

struct ppPCINT8 : Dependency<ppPCINT8, ResourceType::interrupt_input, std::tuple<ppPC0>> {
};

struct ppPCINT9 : Dependency<ppPCINT9, ResourceType::interrupt_input, std::tuple<ppPC1>> {
};

struct ppPCINT10 : Dependency<ppPCINT10, ResourceType::interrupt_input, std::tuple<ppPC2>> {
};

struct ppPCINT11 : Dependency<ppPCINT11, ResourceType::interrupt_input, std::tuple<ppPC3>> {
};

struct ppPCINT12 : Dependency<ppPCINT12, ResourceType::interrupt_input, std::tuple<ppPC4>> {
};

struct ppPCINT13 : Dependency<ppPCINT13, ResourceType::interrupt_input, std::tuple<ppPC5>> {
};

struct ppPCINT14 : Dependency<ppPCINT14, ResourceType::interrupt_input, std::tuple<ppPC6>> {
};

struct ppPCINT16 : Dependency<ppPCINT16, ResourceType::interrupt_input, std::tuple<ppPD0>> {
};

struct ppPCINT17 : Dependency<ppPCINT17, ResourceType::interrupt_input, std::tuple<ppPD1>> {
};

struct ppPCINT18 : Dependency<ppPCINT18, ResourceType::interrupt_input, std::tuple<ppPD2>> {
};

struct ppPCINT19 : Dependency<ppPCINT19, ResourceType::interrupt_input, std::tuple<ppPD3>> {
};

struct ppPCINT20 : Dependency<ppPCINT20, ResourceType::interrupt_input, std::tuple<ppPD4>> {
};

struct ppPCINT21 : Dependency<ppPCINT21, ResourceType::interrupt_input, std::tuple<ppPD5>> {
};

struct ppPCINT22 : Dependency<ppPCINT22, ResourceType::interrupt_input, std::tuple<ppPD6>> {
};

struct ppPCINT23 : Dependency<ppPCINT23, ResourceType::interrupt_input, std::tuple<ppPD7>> {
};

struct ppAIN0 : Dependency<ppAIN0, ResourceType::analog_comparator_in, std::tuple<ppPD6>> {
};

struct ppAIN1 : Dependency<ppAIN1, ResourceType::analog_comparator_in, std::tuple<ppPD7>> {
};

struct ppAIN : Dependency<ppAIN, ResourceType::analog_comparator, std::tuple<ppAIN0, ppAIN1>> {
};

struct ppSCL : Dependency<ppSCL, ResourceType::none, std::tuple<ppPC5>> {
};

struct ppSDA : Dependency<ppSDA, ResourceType::none, std::tuple<ppPC4>> {
};

struct ppI2C0 : Dependency<ppI2C0, ResourceType::i2c_bus, std::tuple<ppSCL, ppSDA>> {
};

struct ppSS : Dependency<ppSS, ResourceType::none, std::tuple<ppPB2>> {
};

struct ppSCK : Dependency<ppSCK, ResourceType::none, std::tuple<ppPB5>> {
};

struct ppMISO : Dependency<ppMISO, ResourceType::none, std::tuple<ppPB4>> {
};

struct ppMOSI : Dependency<ppMOSI, ResourceType::none, std::tuple<ppPB3>> {
};

struct ppSPI0 : Dependency<ppSPI0, ResourceType::spi_bus, std::tuple<ppMISO, ppMOSI, ppSCK, ppSS>> {
};

struct ppRXD : Dependency<ppRXD, ResourceType::uart_r, std::tuple<ppPD0>> {
};

struct ppTXD : Dependency<ppTXD, ResourceType::uart_w, std::tuple<ppPD1>> {
};

struct ppUSART0 : Dependency<ppUSART0, ResourceType::uart_rw, std::tuple<ppRXD, ppTXD>> {
};

struct ppXTAL1 : Dependency<ppXTAL1, ResourceType::none, std::tuple<ppPB6>> {
};

struct ppXTAL2 : Dependency<ppXTAL2, ResourceType::none, std::tuple<ppPB7>> {
};

struct ppXTAL : Dependency<ppXTAL, ResourceType::xtal, std::tuple<ppXTAL1, ppXTAL2>> {
};

static_assert(
  std::is_same<
    RootDependencies<ppUSART0>,
    std::tuple<ppPD0, ppPD1>>::value,
  "Failed to find correct root dependencies for USART0.");

// Used for traversing resource graph to find dependencies.
using McuResources = ResourceFinder<
  ppPB0,
  ppPB1,
  ppPB2,
  ppPB3,
  ppPB4,
  ppPB5,
  ppPB6,
  ppPB7,
  ppPC0,
  ppPC1,
  ppPC2,
  ppPC3,
  ppPC4,
  ppPC5,
  ppPC6,
  ppPD0,
  ppPD1,
  ppPD2,
  ppPD3,
  ppPD4,
  ppPD5,
  ppPD6,
  ppPD7,
  ppADC6,
  ppADC7,
  ppT0,
  ppT1,
  ppXCK,
  ppADC0,
  ppADC1,
  ppADC2,
  ppADC3,
  ppADC4,
  ppADC5,
  ppCLKO,
  ppICP1,
  ppINT0,
  ppINT1,
  ppOC0A,
  ppOC0B,
  ppOC1A,
  ppOC1B,
  ppOC2A,
  ppOC2B,
  ppRESET,
  ppTOSC1,
  ppTOSC2,
  ppPCINT0,
  ppPCINT1,
  ppPCINT2,
  ppPCINT3,
  ppPCINT4,
  ppPCINT5,
  ppPCINT6,
  ppPCINT7,
  ppPCINT8,
  ppPCINT9,
  ppPCINT10,
  ppPCINT11,
  ppPCINT12,
  ppPCINT13,
  ppPCINT14,
  ppPCINT16,
  ppPCINT17,
  ppPCINT18,
  ppPCINT19,
  ppPCINT20,
  ppPCINT21,
  ppPCINT22,
  ppPCINT23,
  ppAIN0,
  ppAIN1,
  ppAIN,
  ppSCL,
  ppSDA,
  ppI2C0,
  ppSS,
  ppSCK,
  ppMISO,
  ppMOSI,
  ppSPI0,
  ppRXD,
  ppTXD,
  ppUSART0,
  ppXTAL1,
  ppXTAL2,
  ppXTAL
>;

constexpr bool xx = setl::has_type_v<ppPD3, ppOC2B::dependencies>;

using x = McuResources::Resource<ppPB1, ResourceType::pulse_width_modulation>;

static_assert(true, "");

/**
 * Maps an arduino pin no to a port type.
 */
template <typename P, std::uint16_t w_pin_no>
struct ArduinoPortMap {
  using PinType = P;
  static constexpr std::uint16_t pin_no = w_pin_no;
};

/**
 * Holds a collection of pin mapings.
 */
template <typename w_DigitalMap>
struct ArduinoDeviceMapping {
  using DigitalMap = w_DigitalMap;  // A tuple of all the ArduinoPortMaps
};

// "digital" pin map for Arduino Nano (with 32 pin package).
using ArduinoNanoPinmap = ArduinoDeviceMapping<
  std::tuple<
    ArduinoPortMap<ppPD0, 0>,
    ArduinoPortMap<ppPD1, 1>,
    ArduinoPortMap<ppPD2, 2>,
    ArduinoPortMap<ppPD3, 3>,
    ArduinoPortMap<ppPD4, 4>,
    ArduinoPortMap<ppPD5, 5>,
    ArduinoPortMap<ppPD6, 6>,
    ArduinoPortMap<ppPD7, 7>,
    ArduinoPortMap<ppPB0, 8>,
    ArduinoPortMap<ppPB1, 9>,
    ArduinoPortMap<ppPB2, 10>,
    ArduinoPortMap<ppPB3, 11>,
    ArduinoPortMap<ppPB4, 12>,
    ArduinoPortMap<ppPB5, 13>,
    ArduinoPortMap<ppPC0, 14>,
    ArduinoPortMap<ppPC1, 15>,
    ArduinoPortMap<ppPC2, 16>,
    ArduinoPortMap<ppPC3, 17>,
    ArduinoPortMap<ppPC4, 18>,
    ArduinoPortMap<ppPC5, 19>,
    ArduinoPortMap<ppADC6, 20>,
    ArduinoPortMap<ppADC7, 21>>
>;

// "digital" pin map for Arduino Uno (with 28 pin package).
using ArduinoUnoPinmap = ArduinoDeviceMapping <
  std::tuple <
    ArduinoPortMap<ppPD0, 0>,
    ArduinoPortMap<ppPD1, 1>,
    ArduinoPortMap<ppPD2, 2>,
    ArduinoPortMap<ppPD3, 3>,
    ArduinoPortMap<ppPD4, 4>,
    ArduinoPortMap<ppPD5, 5>,
    ArduinoPortMap<ppPD6, 6>,
    ArduinoPortMap<ppPD7, 7>,
    ArduinoPortMap<ppPB0, 8>,
    ArduinoPortMap<ppPB1, 9>,
    ArduinoPortMap<ppPB2, 10>,
    ArduinoPortMap<ppPB3, 11>,
    ArduinoPortMap<ppPB4, 12>,
    ArduinoPortMap<ppPB5, 13>,
    ArduinoPortMap<ppPC0, 14>,
    ArduinoPortMap<ppPC1, 15>,
    ArduinoPortMap<ppPC2, 16>,
    ArduinoPortMap<ppPC3, 17>,
    ArduinoPortMap<ppPC4, 18>,
    ArduinoPortMap<ppPC5, 19>>
>;

}  // arch_atmega328p
}  // namespace avr


// These specializations must be defined in the namespace ardo::sys.

/**
 * Defines the available timers for the atmega328p.
 */
template <>
struct AvailableTimers<
    avr::arch_atmega328p::Signature,
    TimerAvailabilityMode::all_available> {
  using Timers = std::tuple<
      avr::arch_atmega328p::Timer0, 
      avr::arch_atmega328p::Timer1, 
      avr::arch_atmega328p::Timer2>;
};

template <>
struct AvailableTimers<
    avr::arch_atmega328p::Signature,
    TimerAvailabilityMode::safe_to_use> {
  using Timers = std::tuple<
      avr::arch_atmega328p::Timer1, 
      avr::arch_atmega328p::Timer2>;
};

template <>
struct IOMapping<avr::arch_atmega328p::Signature, BoardType::arduino_uno> {
  using Mapping = avr::arch_atmega328p::ArduinoUnoPinmap;
};

template <>
struct IOMapping<avr::arch_atmega328p::Signature, BoardType::arduino_nano> {
  using Mapping = avr::arch_atmega328p::ArduinoNanoPinmap;
};

}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega328p_defs__h
