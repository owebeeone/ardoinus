

#ifndef ARDO_AVR_BASE_GPIO__H
#define ARDO_AVR_BASE_GPIO__H

#include "ardo_avr_base_register.h"

namespace ardo {
namespace sys {
namespace avr {
namespace base {

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


}  // namespace base
}  // namespace avr
}  // namespace sys
}  // namespace ardo



#endif // ARDO_AVR_BASE_GPIO__H