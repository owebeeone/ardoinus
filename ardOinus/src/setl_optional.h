
#ifndef SETL_OPTIONAL____H
#define SETL_OPTIONAL____H

#include "setlx_type_traits.h"

namespace setl {

/**
 * Template class providing a simple optional value.
 * The interface is similar to std::optional.
 */
template <typename T>
class Optional {
 public:
  using type = T;

  Optional() : value(), has_value(false) {}

  Optional(const T& value) : value(value), has_value(true) {}

  Optional(T&& value) : value(std::move(value)), has_value(true) {}

  Optional(const Optional& other) : value(other.value), has_value(other.has_value) {}

  Optional(Optional&& other) : value(std::move(other.value)), has_value(other.has_value) {}

  Optional& operator=(const Optional& other) {
    value = other.value;
    has_value = other.has_value;
    return *this;
  }

  Optional& operator=(const T& rhs_value) {
    value = rhs_value;
    has_value = true;
    return *this;
  }

  Optional& operator=(Optional&& other) {
    value = std::move(other.value);
    has_value = other.has_value;
    return *this;
  }

  bool is_present() const { return has_value; }

  const T& get() const {
    return value;
  }

  template <typename V>
  Optional<T>& if_then(const V& func) const {
    if (has_value) {
      func(value);
    }
    return *this;
  }

  template <typename V>
  Optional<T>& otherwise(const V& func) const {
    if (has_value) {
      func();
    }
    return *this;
  }

 private:
   T value{};
  bool has_value{};
};


template <typename T>
Optional<T> make_optional(const T& value) {
  return Optional<T>(value);
}

}  // namespace setl

#endif // SETL_OPTIONAL____H
