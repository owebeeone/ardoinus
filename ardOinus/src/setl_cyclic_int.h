
#ifndef CYCLIC_INT___H
#define CYCLIC_INT___H

#include "type_for_size.h"

#include "setlx_cstdint.h"
#include "setlx_limits.h"
#include "setlx_type_traits.h"

namespace setl {

/**
 * Implements a modulo number group over 0..size-1.
 * The size of the type used is optimized to the size of the group.
 */
template <std::uint32_t w_size, bool as_volatile = false>
class CyclicInt {
public:
  static_assert(w_size > 1, "Single element group not supported.");
  using nv_type = typename setl::TypeForMaxValue<w_size>::selected::type_unsigned;
  using type = typename std::conditional<as_volatile, volatile nv_type, nv_type>::type;
  static const nv_type size = w_size;
  static const nv_type OVERFLOW_OFFSET = (~nv_type(0)) - size + 1;

  CyclicInt() {}

  CyclicInt(nv_type value) : value(fix_range(value)) {}


  template <typename W>
  CyclicInt(const W& value) : value(fix_range_any(value)) {}

  CyclicInt(const CyclicInt<w_size, !as_volatile>& value) : value(value.get()) {}

private:
  // For cases where no fix is required (internal).
  CyclicInt(nv_type value, bool) : value(value) {}
  
  static nv_type fix_range(nv_type value) {
    return value % size;
  }

  template <typename W>
  static nv_type fix_range_any(const W& value) {
    if (value >= 0) {
      return nv_type(value % size);
    } else {
      return nv_type(size - ((~value + 1) % size));
    }
  }

public:

  nv_type get() const {
    return this->value;
  }

  CyclicInt operator+(const CyclicInt& rhs) const {
    nv_type tmp = rhs.get() + value;
    // Check for overflow. Note this is strictly not correct since it is undefined.
    if (tmp < rhs.get() || tmp < value) {
      tmp += OVERFLOW_OFFSET;
    } else if (tmp >= size) {
      tmp -= size;
    }
    return CyclicInt(tmp, false);
  }

  CyclicInt operator-(const CyclicInt& rhs) const {
    return *this + (size - rhs.get());
  }

  CyclicInt operator+=(const CyclicInt& rhs) {
    return *this = *this + rhs;
  }

  CyclicInt operator-=(const CyclicInt& rhs) {
    return *this = *this - rhs;
  }

  bool operator==(const CyclicInt& rhs) const {
    return get() == rhs.get();
  }

  bool operator!=(const CyclicInt& rhs) const {
    return get() != rhs.get();
  }

  CyclicInt& operator++() {
    nv_type tmp = value;
    if (tmp >= (size -1)) {
      value = 0;
      return *this;
    }
    ++value;
    return *this;
  }

  const CyclicInt operator++(int) {
    nv_type tmp = value;
    if (tmp >= (size - 1)) {
      value = 0;
      return CyclicInt(tmp, false);
    }
    value = tmp + 1;
    return CyclicInt(tmp, false);
  }

  CyclicInt& operator--() {
    nv_type tmp = value;
    if (tmp == 0) {
      value = size - 1;
      return *this;
    }
    --value;
    return *this;
  }

  const CyclicInt operator--(int) {
    nv_type tmp = value;
    if (tmp == 0) {
      value = size - 1;
      return CyclicInt(tmp, false);
    }
    value = tmp - 1;
    return CyclicInt(tmp, false);
  }

  const CyclicInt& setLsb() {
    nv_type tmp = value;
    value = tmp | nv_type(1u);
    return *this;
  }

  const CyclicInt& unsetLsb() {
    nv_type tmp = value;
    value = tmp & ~nv_type(1u);
    return *this;
  }

private:
  type value{};
};

}  // namespace
#endif