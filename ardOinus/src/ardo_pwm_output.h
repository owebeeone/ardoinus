/**
 * PWM output support for ArdOinus.
 */

#ifndef ARDO_PWM_OUTPUT___H
#define ARDO_PWM_OUTPUT___H

#include "ardOinus.h"
#include "setlx_cstdint.h"
#include "setl_int_scaler.h"





namespace ardo {

/*
class SofwarePwm {
};

class AutoImplPwm {
};

template <int pin, int channel, typename w_Implementation>
class PwmPinSpec {

};

template <typename w_PinSpec, typename w_Scaler, setl::Frequency>
class OutputPwm {

};

}

using OutPwm =
ardo::OutputPwm<
  ardo::PwmPinSpec<3, 0, ardo::HardwarePwm>, 
  setl::LinearScaler<8, 8>, 
  setl::Frequency(35000)>;
  

template <typename w_Pin, typename w_Scaler = setl::LinearScaler<8, 8>>
class HardwarePwm : public w_Pin {
protected:
//  OutputPin() {}  // Only the one instance allowed
public:

};

template <
  typename w_Pin, 
  typename w_HwPwmParameters = ardo_system::DefaultHwPwmParameters,
  typename w_ScalerSelector = setl::LinearScalerSelector<8>,
  typename... w_Bases >
class HardwarePwm : public w_Pin, public w_Bases... {
protected:
  HardwarePwm() {}  // Only the one instance allowed
public:

  using Pin = w_Pin;
  using HwPwmParameters = w_HwPwmParameters;
  using Scaler = w_ScalerSelector::template Select<HwPwmParameters::timer_bits>;
  using value_type = typename Scaler::value_type;
  using HardwarePwm = ardo_system::HardwarePwmResources<
    Pin, HwPwmParameters>;

  using Claims = ResourceClaim<GPIOResource<PIN>>;

  void set_pwm(const value_type& value) {
    HardwarePwm::set_pwm(Scaler::scale(value));
  }

};



using PwmOutput = ardo::HardwarePwm<
  ardo::OutputPin<1>, 
  setl::LinearScalerSelector<8>
  >;
  */
}
#endif // ARDO_PWM_OUTPUT___H