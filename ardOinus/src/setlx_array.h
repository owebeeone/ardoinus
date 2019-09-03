
#ifndef SETL_ARRAY__H
#define SETL_ARRAY__H

#include "setl_support.h"

#ifdef HAS_STD_LIB
#include <array>
#else

#include "setlx_cstddef.h"

namespace std {

template <typename T, size_t w_Size>
class array {
public:
  using size_type = size_t;
  using value_type = T;
  using difference_type = ptrdiff_t;
  using reference = T & ;
  using pointer = T*;
  using const_pointer = const T*;
  using const_reference = const T&;

  reference operator[](size_t index) {
    return value[index];
  }

  const_reference operator[](size_t index) const {
    return value[index];
  }

private:
  T value[w_Size];
};

} // namespace

#endif

#endif