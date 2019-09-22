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
class HardwarePwm : /*public w_Pin,*/ public w_Bases... {
protected:
  HardwarePwm() {}  // Only the one instance allowed
public:

  using Pin = w_Pin;
  using HwPwmParameters = w_HwPwmParameters;
  static constexpr std::int8_t hw_bits = HwPwmParameters::bits;
  using Scaler = typename w_ScalerSelector::template Scaler<hw_bits>;
  using value_type = typename Scaler::value_type;
  using Pwm = ardo_system::HardwarePwmResources<
    Pin, HwPwmParameters>;

  using Claims = ardo::ConcatenateResourceClaims<
    typename w_Pin::Claims, typename Pwm::Claims>;

  inline static void set_pwm(const value_type& value) {
    Pwm::set_pwm(Scaler::scale(value));
  }

  inline static void runSetup() {
    Pin::runSetup();
  }

  inline static void runLoop() {
    Pin::runLoop();
  }
};

}
#endif // ARDO_PWM_OUTPUT___H