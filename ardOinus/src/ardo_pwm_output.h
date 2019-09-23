/**
 * PWM output support for ArdOinus.
 */

#ifndef ARDO_PWM_OUTPUT___H
#define ARDO_PWM_OUTPUT___H

#include "ardOinus.h"
#include "setlx_cstdint.h"
#include "setl_int_scaler.h"

namespace ardo {

/**
 * HardwarePwm provides support for the PWM hardware.
 */
template <
  typename w_Pin,
  typename w_ScalerSelector = setl::LinearScalerSelector<8>,
  typename w_HwPwmParameters = ardo_system::DefaultHwPwmParameters,
  typename... w_Bases >
class HardwarePwm : public w_Bases..., public setl::not_copyable {
protected:
  HardwarePwm() {}  // Only the one instance allowed
public:

  using Pin = w_Pin;
  using HwPwmParameters = w_HwPwmParameters;
  using Pwm = ardo_system::HardwarePwmResources<Pin, HwPwmParameters>;
  static constexpr std::int8_t timer_bits = Pwm::timer_bits;
  using Scaler = typename w_ScalerSelector::template Scaler<timer_bits>;
  using value_type = typename Scaler::value_type;

  static const HardwarePwm pwm_pin;

  // 
  using Claims = ardo::ConcatenateResourceClaims<
    typename w_Pin::Claims, typename Pwm::Claims>;

  inline static void setPwm(const value_type& value) {
    Pwm::setPwm(Scaler::scale(value));
  }

  inline static void runSetup() {
    Pin::runSetup();
  }

  inline static void runLoop() {
    Pin::runLoop();
  }

  // Overrides base class interface if given.
  void setPwmPin(const std::uint32_t value) const {
    setPwm(value_type(value));
  }
};

template <  typename P, typename S, typename H, typename... B>
  const HardwarePwm<P, S, H, B...> HardwarePwm<P, S, H, B...>::pwm_pin;

}
#endif // ARDO_PWM_OUTPUT___H