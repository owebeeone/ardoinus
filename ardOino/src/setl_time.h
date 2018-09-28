/**
 * A time library.
 * The two main classes Time (absolute time) and Period (relative time) provide
 * a type safe way to manage time. These classes are also associated with time
 * units as part of their type signature and conversion between time units is
 * provided only explicitly.
 * 
 * The functionality of this library is similar to std::chrono but it allows
 * the client to choose the underlying type and also allows for conversions
 * between time units without any large number support. The client must however
 * limit itself to a range of units that is suitable for the application 
 * constraints.
 */

#ifndef SETL_TIME___H
#define SETL_TIME___H

#include "setl_utils.h"
#include "setl_time_unit.h"

namespace setl {

template <typename T, TimeUnit w_units = TimeUnit::MILLIS>
class Period;

template <typename T, TimeUnit w_units = TimeUnit::MILLIS>
class Time;

/** Representation of an absolute time.
 * Very little can be done with an absolute time except for subtraction and creating
 * Period objects.
 */
template <typename T, TimeUnit w_units>
class Time {
  template <typename W, TimeUnit u_units>
  friend class Period;
public:
  using type = T;
  static constexpr TimeUnit UNITS = w_units;
  using period_type = Period<T, UNITS>;

  Time() {}

  explicit Time(T value)
    : value{ value }
  {}

  period_type operator-(const Time<T, UNITS>& rhs) const {
    return period_type(value - rhs.value);
  }

  Time operator-(const period_type& rhs) const {
    return Time(value - rhs.value);
  }

  Time operator+(const period_type& rhs) const {
    return Time(value + rhs.value);
  }

  Time& operator +=(const period_type& rhs) {
    value += rhs.value;
    return *this;
  }

  Time& operator -=(const period_type& rhs) {
    value -= rhs.value;
    return *this;
  }

  bool operator ==(const Time& rhs) const {
    return value == rhs.value;
  }

  bool operator !=(const Time& rhs) const {
    return value != rhs.value;
  }

  // Relative comparisons of Time are not allowed. Compare period instead.

  T get() const {
    return value;
  }

private:
  T value = {};
};

template <typename T, TimeUnit w_units>
class Period {
  template <typename W, TimeUnit u_units>
  friend class Time;
  struct Converter;
public:
  using type = T;
  static constexpr TimeUnit UNITS = w_units;
  using time_type = Time<T, UNITS>;

  Period() {}

  explicit Period(T value)
    : value{ value }
  {}

  // Unit conversion constructor.
  template <typename U, TimeUnit u_units>
  explicit Period(const Period<U, u_units>& value)
    : value{ static_cast<type>(ConvertTime<u_units, UNITS>::convert(value.get())) }
  {}

  // Convert to other units shortcut.
  template <TimeUnit u_units> 
  Period<T, u_units> to() const {
    return Period<T, u_units>(*this);
  }
  
  // Convert to other Period types shortcut.
  Converter to() const {
    return Converter(*this);
  }

  Period operator +(const Period& rhs) const {
    return Period(value + rhs.value);
  }

  Period operator -(const Period& rhs) const {
    return Period(value - rhs.value);
  }

  template <typename W>
  Period operator -() const {
    return Period(-value);
  }

  template <typename W>
  Period operator /(W rhs) const {
    return Period(value * rhs);
  }

  bool operator ==(const Period& rhs) const {
    return value == rhs.value;
  }

  bool operator !=(const Period& rhs) const {
    return value != rhs.value;
  }

  bool operator <(const Period& rhs) const {
    return value < rhs.value;
  }

  bool operator <=(const Period& rhs) const {
    return value <= rhs.value;
  }

  bool operator >(const Period& rhs) const {
    return value > rhs.value;
  }

  bool operator >=(const Period& rhs) const {
    return value >= rhs.value;
  }

  Period& operator +=(const Period& rhs) {
    value += rhs.value;
    return *this;
  }

  Period& operator -=(const Period& rhs) {
    value -= rhs.value;
    return *this;
  }

  T get() const {
    return value;
  }

private:
  T value = {};

  // Helper class for short hand conversion.
  struct Converter {
    Converter(const Period& value) : value(value) {}

    template <typename U, TimeUnit u_units>
    operator Period<U, u_units>() {
      return Period<U, u_units>(value);
    }

    const Period& value;
  };
};

template <typename T, typename W, TimeUnit w_units>
Period<T, w_units> operator*(const Period<T, w_units>& lhs, const W& rhs) {
  return Period<T, w_units>(lhs.get() * rhs);
}

template <typename T, typename W, TimeUnit w_units>
Period<T, w_units> operator*(const W& lhs, const Period<T, w_units>& rhs) {
  return Period<T, w_units>(lhs * rhs.get());
}

template <typename T, typename W, TimeUnit w_units>
Time<W, w_units> operator+(const Period<T, w_units>& lhs, const Time<W, w_units>& rhs) {
  return Time<W, w_units>(lhs.get() + rhs.get());
}

template <typename T, typename W, TimeUnit w_units>
Time<T, w_units> operator+(const Time<T, w_units>& lhs, const Period<W, w_units>& rhs) {
  return Time<T, w_units>(lhs.get() + rhs.get());
}

template <TimeUnit w_units, typename T>
setl::Time<T, w_units> time(const T& v) {
  return setl::Time<T, w_units>(v);
}

template <TimeUnit w_units, typename T>
setl::Period<T, w_units> period(const T& v) {
  return setl::Period<T, w_units>(v);
}

namespace time_suffix_ops {

// Suffix operators for various time units.
inline setl::Period<long double, TimeUnit::WEEK> operator"" _wk(long double v) {
  return period<TimeUnit::WEEK>(v);
}

inline setl::Period<unsigned long long, TimeUnit::WEEK>  operator"" _wk(unsigned long long v) {
  return period<TimeUnit::WEEK>(v);
}

inline setl::Period<long double, TimeUnit::DAY>  operator"" _day(long double v) {
  return period<TimeUnit::DAY>(v);
}

inline setl::Period<unsigned long long, TimeUnit::DAY>  operator"" _day(unsigned long long v) {
  return period<TimeUnit::DAY>(v);
}

inline setl::Period<long double, TimeUnit::HOUR>  operator"" _hr(long double v) {
  return period<TimeUnit::HOUR>(v);
}

inline setl::Period<unsigned long long, TimeUnit::HOUR>  operator"" _hr(unsigned long long v) {
  return period<TimeUnit::HOUR>(v);
}

#undef _min  // gcc 5.2 defines _min as a macro.
inline setl::Period<long double, TimeUnit::MINUTE>  operator"" _min(long double v) {
  return period<TimeUnit::MINUTE>(v);
}

inline setl::Period<unsigned long long, TimeUnit::MINUTE>  operator"" _min(unsigned long long v) {
  return period<TimeUnit::MINUTE>(v);
}

inline setl::Period<long double, TimeUnit::SECOND>  operator"" _sec(long double v) {
  return period<TimeUnit::SECOND>(v);
}

inline setl::Period<unsigned long long, TimeUnit::SECOND>  operator"" _sec(unsigned long long v) {
  return period<TimeUnit::SECOND>(v);
}

inline setl::Period<long double, TimeUnit::MILLIS>  operator"" _msec(long double v) {
  return period<TimeUnit::MILLIS>(v);
}

inline setl::Period<unsigned long long, TimeUnit::MILLIS>  operator"" _msec(unsigned long long v) {
  return period<TimeUnit::MILLIS>(v);
}

inline setl::Period<long double, TimeUnit::MICROS>  operator"" _usec(long double v) {
  return period<TimeUnit::MICROS>(v);
}

inline setl::Period<unsigned long long, TimeUnit::MICROS>  operator"" _usec(unsigned long long v) {
  return period<TimeUnit::MICROS>(v);
}

inline setl::Period<long double, TimeUnit::NANOS>  operator"" _nsec(long double v) {
  return period<TimeUnit::NANOS>(v);
}

inline setl::Period<unsigned long long, TimeUnit::NANOS>  operator"" _nsec(unsigned long long v) {
  return period<TimeUnit::NANOS>(v);
}

} // namepsace time_suffix_ops

// Introduce the operators in the setl namespace so that specific
// operators can be added.
using namespace time_suffix_ops;
} // namespace

#endif // !SETL_TIME___H
