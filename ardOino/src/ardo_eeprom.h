
#ifndef ARDO_EEPROM___H
#define ARDO_EEPROM___H

#include "ardoino.h"

#include "setlx_type_traits.h"
#include "setlx_cstdint.h"

namespace ardo {

class EepromResource {};

template <typename T, std::int32_t w_Addr>
class EepromReaderWriter : public setl::not_copyable {
public:
  using value_type = T;
  static_assert(std::is_trivially_copyable<T>::value, "Type is not compatible with EEPROM storage");

  using Claims = ResourceClaim<range_claim<EepromResource, w_Addr, w_Addr + sizeof(T)>>;

  /**
   * Read a value from the EEPROM.
   */
  static value_type read() {
    value_type result{};
    char* addr = reinterpret_cast<char*>(&result);
    for (int i = 0; i < sizeof(value_type); ++i, ++addr) {
      *addr = EEPROM.read(w_Addr + i);
    }
    return result;
  }

  /**
   * Write a value to the EEPROM.
   */
  static void write(const value_type& value) {
    const char* addr = reinterpret_cast<const char*>(&value);
    for (int i = 0; i < sizeof(value_type); ++i, ++addr) {
      EEPROM.update(w_Addr + i, &addr);
    }
  }

  inline static void runSetup() {}

  inline static void runLoop() {}
};

}

#endif