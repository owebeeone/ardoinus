
#ifndef SETL_DEVICE_MAP__H
#define SETL_DEVICE_MAP__H

#include "setlx_type_traits.h"

namespace setl {
    
/**
 * Maps an pin no to a port type.
 */
template <typename P, std::uint16_t w_pin_no>
struct PortMapping {
  using PinType = P;
  static constexpr std::uint16_t pin_no = w_pin_no;
};

/**
 * Holds a collection of pin mapings.
 */
template <typename w_DigitalMap>
struct DeviceMappings {
  using DigitalMap = w_DigitalMap;  // A tuple of all the PortMapping
};

}  // namespace setl

#endif // SETL_DEVICE_MAP__H