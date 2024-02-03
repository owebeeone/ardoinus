/**
 * Hardware timer abstraction.
 */
#ifndef ARDO_TIMERS__H
#define ARDO_TIMERS__H

#include "ardo_sys_defs.h"

#include "setl_templ_utils.h"

#include "setlx_cstdint.h"
#include "setlx_tuple.h"

namespace ardo {
namespace timers {

/**
 * Timer parameters.
 * 
 * A TimerConfig is a tuple of parameters where each parameter is a subclass of
 * the Parameter template designating its "ParameterClass".
 * 
 * No all parameters are used by all MCUs. The MCU will define its set of 
 * available parameters and the all other parameters in the TimerConfig will be
 * ignored. This allows for extensible timer configurations that can be used
 * across multiple MCUs allowing for a single (non conditionally compiled) source
 * code to work for multiple MCUs architectures.
 * 
 */

/**
 * Timer parameters.
 */
enum class ParameterClass {
    frequency,
    frequency_variable,
    resolution,
    avr_fast,
    avr_pwm_pin,        // Pin number for timer PWM output.
    avr_phase_correct,
    avr_top_count_mode,
};

/**
 * Timer parameter base class.
 */
template <ParameterClass w_parameter_class>
struct Parameter {
    static constexpr ParameterClass parameter_class = w_parameter_class;
};

/**
 * List of parameter classes. Also generates a tuple of the base parameter types
 * associated with each parameter class.
 */
template <ParameterClass...P>
struct ParameterClasses {
    using ParameterTuple = setl::ValueTuple<ParameterClass, P...>;

    using BaseTypes = std::tuple<Parameter<P>...>;
};

/** Timer parameters. */
template <typename...T>
struct TimerConfig {
    using Parameters = std::tuple<T...>;
};

/** Specify standard timer paramerters. */

template <
    ParameterClass parameter_class,
    std::uint32_t w_frequency_hz, 
    std::uint32_t w_frequency_divider_hz = 1, 
    typename w_frequency_type = float>
struct FrequencyBase : Parameter<parameter_class> {
    using frequency_type = w_frequency_type;
    static constexpr std::uint32_t frequency_hz = w_frequency_hz;
    static constexpr std::uint32_t frequency_divider_hz = w_frequency_divider_hz;
    static constexpr bool is_variable = false;
};

/** Specify a timer frequency. */
template <std::uint32_t w_frequency_hz, 
    std::uint32_t w_frequency_divider_hz = 1, 
    typename w_frequency_type = float>
struct Frequency : FrequencyBase<
    ParameterClass::frequency, w_frequency_hz, w_frequency_divider_hz, w_frequency_type> {};


/** Specify a variable frequency timer with an API to change frequency. */
template <std::uint32_t w_frequency_hz, 
    std::uint32_t w_frequency_divider_hz = 1, 
    typename w_frequency_type = float>
struct VariableFrequency : FrequencyBase<
    ParameterClass::frequency_variable, w_frequency_hz, w_frequency_divider_hz, w_frequency_type> {};


/** Timer resolution specifier */
template <std::uint32_t w_resolution>
struct Resolution : Parameter<ParameterClass::resolution> {
    static constexpr ParameterClass parameter_class = ParameterClass::resolution;
    static constexpr std::uint32_t resolution = w_resolution;
};

// template <std::uint32_t w_frequency_hz, 
//     std::uint32_t w_frequency_divider_hz, 
//     typename w_frequency_type>
// static constexpr frequency_type = Frequency<w_frequency_hz, w_frequency_divider_hz, w_frequency_type>::frequency = frequency_hz / frequency_divider_hz;

template <std::uint32_t pin_number>
struct PwmPin : Parameter<ParameterClass::avr_pwm_pin> {
    static constexpr ParameterClass parameter_class = ParameterClass::avr_pwm_pin;
    static constexpr std::uint32_t number = pin_number;
};

namespace avr {
/** Specify AVR timer paramerters. */

/** AVR phase correct mode. */
struct PhaseCorrectMode : Parameter<ParameterClass::avr_phase_correct> {};

/** AVR fast mode. */
struct FastMode : Parameter<ParameterClass::avr_fast> {};

/** AVR top count mode. The resolution for an AVR timer is determined by the top count
 * value. The top count can be a built-in value, the ICR register (on timers with an ICR)
 * or the OCRA register. Using the OCRA register will limit the number of PWM outputs to 1
 * so using the ICR register or a built-in value top count is recommended if more than 1
 * PWM output is required.
 */
enum class TopCountMode {
    ocra,
    icr,
    built_in
};

template <TopCountMode w_mode>
struct TopCount : Parameter<ParameterClass::avr_top_count_mode> {
    static constexpr TopCountMode mode = w_mode;
};

// List of parameter classes allowed for AVR timers.
using AllowedAVRParameters = ParameterClasses<
    ParameterClass::avr_pwm_pin,
    ParameterClass::frequency,
    ParameterClass::frequency_variable,
    ParameterClass::resolution,
    ParameterClass::avr_fast,
    ParameterClass::avr_phase_correct,
    ParameterClass::avr_top_count_mode>;

}  // namespace avr



template <template <ParameterClass pc> typename Base, ParameterClass...P>
struct ToTupleFromParameterClasses {
    using type = std::tuple<Base<P>...>;
};

template <typename w_AllowedParameters, typename w_TimerConfig>
struct TimerConfigFilter {
    using AllowedParameters = w_AllowedParameters;
    using InputConfig = w_TimerConfig;

    using Config = setl::tuple_select_by_base_t<
        typename InputConfig::Parameters,
        typename AllowedParameters::BaseTypes>;

};

// Test that TimerConfigFilter filters only to the available parameter types.
static_assert(
    std::is_same_v<
        TimerConfigFilter<
            ParameterClasses<ParameterClass::avr_pwm_pin, ParameterClass::frequency>,
            TimerConfig<
                Frequency<1000>,
                avr::PhaseCorrectMode,
                avr::TopCount<avr::TopCountMode::icr>>>::Config,
        std::tuple<Frequency<1000>>>,
        "TimerConfigFilter failed to filter out invalid parameters.");

namespace nfp {
// Not part of the public API.

template <typename...w_Configs>
struct SelectionResolver {
    using configs = std::tuple<w_Configs...>;

    template <typename...w_SelectedConfigs>
    using Select = SelectionResolver;

    template <typename w_Config>
    using Resolve = w_Config;
};

template <typename w_SystemTimers, typename...w_Configs>
struct BaseTimerSelector {
    using SystemTimers = w_SystemTimers;
    using configs = std::tuple<w_Configs...>;

    template <typename...w_SelectedConfigs>
    using Select = typename nfp::SelectionResolver<w_Configs...>::
        template Select<w_SelectedConfigs...>;
};

using DefaultAvailableTimers = ardo::sys::AvailableTimers<
    ardo::sys::DefaultSignature,
    ardo::sys::TimerAvailabilityMode::safe_to_use>;

}  // namespace nfp

/**
 * Defines a timer selector.
 */
template <typename...w_Configs>
using TimerSelector = nfp::BaseTimerSelector<nfp::DefaultAvailableTimers, w_Configs...>;

}  // namespace timers
}  // namespace ardo

#endif  // ARDO_TIMERS__H
