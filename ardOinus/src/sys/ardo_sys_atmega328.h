
#ifndef SYS__ARDO_SYS_ATMEGA328___H
#define SYS__ARDO_SYS_ATMEGA328___H

#include "ardo_resources.h"
#include "setl_templ_utils.h"
#include "setlx_cstdint.h"
#include "setlx_type_traits.h"

// Use the provided Arduino API.
#define ARDO_USE_ARDUINO_COREIF
namespace ardo_system {
using ardo::GPIOResource;

#ifndef ARDO_HAS_SERIAL0
#define ARDO_HAS_SERIAL0 1
using Serial0Resources0 = setl::TypeArgs<GPIOResource<0>, GPIOResource<1>>;
#endif  // ARDO_HAS_SERIAL0

#define ARDO_USE_ARDUINO_HARDWARE_PWM 1

/**
 * ArdOinus needs this basic set of parameters, some of which are
 * utilized by some architectures and not others. The goal is to enable
 * source code compatability across different architectures. 
 */
//template <std::int8_t w_bits, std::int32_t w_frequency, std::int8_t w_channel>
//class HwPwmParameters {
//public:
//  static constexpr std::int8_t bits = w_bits;
//  static constexpr std::int32_t frequency = w_frequency;
//  static constexpr std::int8_t channel = w_channel;
//  using value_type = std::uint16_t;
//};
//
//using DefaultHwPwmParameters = HwPwmParameters<8, -1, 0>;

/**
 * From:
 * https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072
 *
 * The Arduino has 3Timers and 6 PWM output pins. 
 * The relation between timers and PWM outputs is:
 * Pins 5 and 6: controlled by timer0
 * Pins 9 and 10: controlled by timer1
 * Pins 11 and 3: controlled by timer2
 */

// This namespace is not part of the public API.
namespace atmega328p_timers {

template <unsigned pin>
class ProvideError {
  static_assert(pin == pin -1, "Selected pin does not support PWM");
};

// Maps pin to hardware timer.
template <unsigned pin>
class PinHwTimerMap {
public:
  static constexpr std::uint8_t value = ProvideError<pin>::value;
};

template <>
class PinHwTimerMap<5> : public std::integral_constant<unsigned, 0> {};
template <>
class PinHwTimerMap<6> : public std::integral_constant<unsigned, 0> {};
template <>
class PinHwTimerMap<9> : public std::integral_constant<unsigned, 1> {};
template <>
class PinHwTimerMap<10> : public std::integral_constant<unsigned, 1> {};
template <>
class PinHwTimerMap<3> : public std::integral_constant<unsigned, 2> {};
template <>
class PinHwTimerMap<11> : public std::integral_constant<unsigned, 2> {};

} // namespace atmega328p_timers

/**
 * Define the resources for GPIO pins for the given set of parameters. The
 * resources declared here are added to the resources associated with the
 * ardo::OutputPin.
 */

//template <typename w_Pin, typename w_Parameters>
//class HardwarePwmResources {
//public:
//  using Pin = w_Pin;
//  using Parameters = w_Parameters;
//  constexpr static unsigned hwtimer =
//    atmega328p_timers::PinHwTimerMap<Pin::PIN>::value;
//
//  // Pins are associated with timers. The range claim will conflict with
//  // any other use of the timer not in a range claim.
//  using Claims = ardo::ResourceClaim<
//    ardo::range_claim<ardo::HardwareTimer<hwtimer>, Pin::PIN>>;
//
//  using value_type = typename Parameters::value_type;
//
//  // Arduino atmega328 only supports 8 bin resoltuion, regardless of what
//  // Parameters says.
//  constexpr static std::uint8_t timer_bits = 8;
//
//  static void setPwm(value_type value) {
//    ::analogWrite(Pin::PIN, value);
//  }
//};

}  // namespace ardo_system

#endif  // SYS__ARDO_SYS_ATMEGA328___H
