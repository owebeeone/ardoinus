
#ifndef SETL_LIMITS__H
#define SETL_LIMITS__H

#include "setl_support.h"

#ifdef HAS_STD_LIB
#include <limits>
#else

namespace std {

template <typename T>
struct numeric_limits {
  static constexpr bool is_integer = (T(1) / 2) == 0;
  static constexpr bool is_exact = (T(1) / 2) == 0;
  static constexpr bool is_signed = T(T(0) - T(1)) < T(0);
};

template <>
struct numeric_limits<bool> {
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = true;
  static constexpr bool is_signed = false;
};

template <>
struct numeric_limits<float> {
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool is_signed = true;
};

template <>
struct numeric_limits<double> {
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool is_signed = true;
};

} // namespace

#endif
#endif