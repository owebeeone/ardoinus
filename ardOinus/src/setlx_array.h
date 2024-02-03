
#ifndef SETL_ARRAY__H
#define SETL_ARRAY__H

#include "setl_support.h"

#ifndef HAS_STD_LIB
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

  reference at(size_t index) {
    if (index >= w_Size) {
      throw std::out_of_range("array::at");
    }
    return value[index];
  }

  const_reference at(size_t index) const {
    if (index >= w_Size) {
      throw std::out_of_range("array::at");
    }
    return value[index];
  }

  reference front() {
    return value[0];
  }

  const_reference front() const {
    return value[0];
  }

  reference back() {
    return value[w_Size - 1];
  }

  const_reference back() const {
    return value[w_Size - 1];
  }

  pointer data() {
    return value;
  }

  const_pointer data() const {
    return value;
  }

  bool empty() const {
    return w_Size == 0;
  }

  size_t size() const {
    return w_Size;
  }

  size_t max_size() const {
    return w_Size;
  }

  void fill(const T& value) {
    for (size_t i = 0; i < w_Size; ++i) {
      this->value[i] = value;
    }
  }

  void swap(array& other) {
    for (size_t i = 0; i < w_Size; ++i) {
      std::swap(value[i], other.value[i]);
    }
  }

  // Iterators
  using iterator = T*;

  iterator begin() {
    return value;
  }

  iterator end() {
    return value + w_Size;
  }

  using const_iterator = const T*;

  const_iterator begin() const {
    return value;
  }

  const_iterator end() const {
    return value + w_Size;
  }

  const_iterator cbegin() const {
    return value;
  }

  const_iterator cend() const {
    return value + w_Size;
  }


private:
  T value[w_Size];
};

} // namespace

#endif

#endif