
#ifndef ASSERT_THAT___H
#define ASSERT_THAT___H

#include "setlx_limits.h"

namespace setl_test {

/** The base value for the test. */
template <typename T>
struct assert_value {
  assert_value(const T& value)
  : value(value) {}

protected:
  T value;  // This makes a copy.
};

inline void test_assert(bool value, const char* message) {
  if (!value) {
    const char** segv = nullptr;
    *segv = message;
    throw message;
  }
}

enum class AssertTypeSpecifier {
  UNKOWN,
  INTEGER,
  BOOL,
  FLOATING,
};

template <typename T>
struct is_bool { static const bool value = false; };
template <>
struct is_bool<bool> { static const bool value = true; };

template <typename T>
constexpr AssertTypeSpecifier assert_type_specifier =
  is_bool<T>::value ? AssertTypeSpecifier::BOOL
  : std::numeric_limits<T>::is_integer ? AssertTypeSpecifier::INTEGER
  : !std::numeric_limits<T>::is_exact ? AssertTypeSpecifier::FLOATING
  : AssertTypeSpecifier::UNKOWN;

template <AssertTypeSpecifier type, typename T>
struct asserter;

template <typename T>
struct asserter<AssertTypeSpecifier::INTEGER, T> : assert_value<T> {
  asserter(const T& value) : assert_value<T>(value) {}

  ~asserter() {
    test_assert(used, "aseerter was not used");  // a test needs to be made.
  }

  asserter& eq(T expected) {
    used = true;
    test_assert(this->value == expected, "Unexpected value");
    return *this;
  }
  bool used = false;
};

template <typename T>
struct asserter<AssertTypeSpecifier::BOOL, T> : assert_value<T> {
  asserter(const T& value) : assert_value<T>(value) {}

  ~asserter() {
    test_assert(used, "aseerter was not used");  // a test needs to be made.
  }

  asserter& eq(T expected) {
    used = true;
    test_assert(this->value == expected, "Unexpected value");
    return *this;
  }

  asserter& isTrue() {
    used = true;
    test_assert(this->value, "Expected true value");
    return *this;
  }

  asserter& isFalse() {
    used = true;
    test_assert(!this->value, "Expected false value");
    return *this;
  }

  bool used = false;
};

template <typename T>
struct asserter<AssertTypeSpecifier::FLOATING, T> : assert_value<T> {
  asserter(const T& value) : assert_value<T>(value) {}

  ~asserter() {
    test_assert(used, "aseerter was not used");  // a test needs to be made.
  }

  asserter& eq(T expected) {
    used = true;
    test_assert(this->value == expected, "Unexpected value");
    return *this;
  }

  bool used = false;
};

template <typename T>
auto assertThat(const T& value) {
  return asserter<assert_type_specifier<T>, T>(value);
}

} // Namespace setl_test


#endif