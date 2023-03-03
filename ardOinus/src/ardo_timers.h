/**
 * Hardware timer abstraction.
 */
#ifndef ARDO_TIMERS__H
#define ARDO_TIMERS__H

#include "ardo_sys_defs.h"
#include "setlx_cstdint.h"
#include "setlx_tuple.h"

namespace ardo {
namespace timers {

/** Timer parameters. */
template <typename...T>
struct TimerConfig {
    using Parameters = std::tuple<T...>;
};

/** Specify standard timer paramerters. */
template <std::uint32_t w_frequency_hz, 
    std::uint32_t w_frequency_divider_hz = 1, 
    typename w_frequency_type = float>
struct Frequency {
    using frequency_type = w_frequency_type;
    static constexpr std::uint32_t frequency_hz = w_frequency_hz;
    static constexpr std::uint32_t frequency_divider_hz = w_frequency_divider_hz;
    static constexpr bool is_variable = false;
};

/** Specify a variable frequency timer with an API to change frequency. */
template <std::uint32_t w_frequency_hz, 
    std::uint32_t w_frequency_divider_hz = 1, 
    typename w_frequency_type = float>
struct VariableFrequency : Frequency<w_frequency_hz, w_frequency_divider_hz, w_frequency_type> {
    static constexpr bool is_variable = true;
};

/** Timer resolution specifier */
template <std::uint32_t w_resolution>
struct Resolution {
    static constexpr std::uint32_t resolution = w_resolution;
};

// template <std::uint32_t w_frequency_hz, 
//     std::uint32_t w_frequency_divider_hz, 
//     typename w_frequency_type>
// static constexpr frequency_type = Frequency<w_frequency_hz, w_frequency_divider_hz, w_frequency_type>::frequency = frequency_hz / frequency_divider_hz;

template <std::uint32_t pin_number>
struct PwmPin {
    static constexpr std::uint32_t number = pin_number;
};

namespace avr {
/** Specify AVR timer paramerters. */

/** Specify AVR timer phase correct mode. */
struct PhaseCorrectMode {};
struct FastMode {};

enum class TopCountMode {
    ocra,
    icr,
    built_in
};

template <TopCountMode w_mode>
struct TopCount {
    static constexpr TopCountMode mode = w_mode;
};



}  // namespace avr

namespace nfp {
// Not path of the public API.

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
    using Select = typename nfp::SelectionResolver<w_Configs...>::template Select<w_SelectedConfigs...>;

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
