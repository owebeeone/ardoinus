
#ifndef SETL_OPTIONAL____H
#define SETL_OPTIONAL____H

// Include std::move
namespace setl {

template <typename T>
struct remove_reference {
    using type = T;
};

template <typename T>
struct remove_reference<T&> {
    using type = T;
};

template <typename T>
struct remove_reference<T&&> {
    using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;


/**
 * Like std::move function.
 */
template <typename T>
remove_reference_t<T>&& move(T&& arg) noexcept {
    using ReturnType = remove_reference_t<T>&&;
    return static_cast<ReturnType>(arg);
}

/**
 * Template class providing a simple optional value.
 * The interface is similar to std::optional.
 */
template <typename T>
class Optional {
 public:
  using type = T;

  Optional() : value(), is_present(false) {}

  Optional(const T& value) : value(value), is_present(true) {}

  Optional(T&& value) : value(move(value)), is_present(true) {}

  Optional(const Optional& other) : value(other.value), is_present(other.is_present) {}

  Optional(Optional&& other) : value(move(other.value)), is_present(other.is_present) {}

  Optional& operator=(const Optional& other) {
    value = other.value;
    is_present = other.is_present;
    return *this;
  }

  Optional& operator=(const T& rhs_value) {
    value = rhs_value;
    is_present = true;
    return *this;
  }

  Optional& operator=(Optional&& other) {
    value = move(other.value);
    is_present = other.is_present;
    return *this;
  }

  bool has_value() const { return is_present; }

  operator bool() const { return is_present; }

  const T& get() const {
    return value;
  }

  template <typename V>
  Optional<T>& if_then(const V& func) const {
    if (is_present) {
      func(value);
    }
    return *this;
  }

  template <typename V>
  Optional<T>& otherwise(const V& func) const {
    if (is_present) {
      func();
    }
    return *this;
  }

 private:
  T value{};
  boolean is_present;
};


template <typename T>
Optional<T> make_optional(const T& value) {
  return Optional<T>(value);
}

}  // namespace setl

#endif // SETL_OPTIONAL____H
