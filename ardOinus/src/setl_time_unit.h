/**
 * Time unit conversion library.
 * Header only library providing basic utils for conversion of time units.
 * The convertion tables are only compile time defined and take no space in
 * executables. The umtimate time type is a template parameter so rounding
 * errors are entirely in control of the client.
 *
 * The time scale from WEEKS to YOCTOS may very likely be larger than the 
 * requested data type. This library only instantiates conversions between
 * units that are supported by the chosen data type. While some diagnostics
 * are provided, it is up to the user to ensure the range of accurate
 * conversions are appropriate for the application.
 */

#ifndef SETL_TIME_UNIT___H
#define SETL_TIME_UNIT___H

#include "setl_utils.h"

#include "setlx_limits.h"
#include "setlx_type_traits.h"
#include "setlx_cstdint.h"

namespace setl {

/** Time unit names. */
enum class TimeUnit : std::uint8_t {
  YOCTOS = 1,     // yoctoseconds
  ATTOS = 2,      // attoseconds
  FEMTOS = 3,     // femtoseconds
  PICOS = 4,      // picosseconds
  NANOS = 4,      // nanoseconds
  MICROS = 5,     // microseconds
  MILLIS = 6,     // milliseconds
  CENTIS = 7,     // centiseconds
  JIFFY = 7,      // Synonym for centis
  SECOND = 8,
  MINUTE = 9,
  HOUR = 10,
  DAY = 11,
  WEEK = 12,
};

/**
 * TimeUnitScale encapsulates the conversion factor for one unit to the next.
 */
template <TimeUnit w_unit_from, TimeUnit w_unit_to, std::uint16_t w_scale>
struct TimeUnitScale : not_instantiable {
  static const TimeUnit UNIT_FROM = w_unit_from;
  static const TimeUnit UNIT_TO = w_unit_to;
  static const unsigned SCALE = w_scale;
};

/**
 * TimeUnitScalarsFinder finds the TimeUnitScale for a TimeUnit.
 */
template <TimeUnit w_unit, typename... T>
struct TimeUnitScalarsFinder;

template <TimeUnit w_unit, typename W, typename... T>
struct TimeUnitScalarsFinder<w_unit, W, T...> : not_instantiable {

  using type = typename std::conditional<
    w_unit == W::UNIT_FROM,
    W,
    typename TimeUnitScalarsFinder<w_unit, T...>::type
  >::type;
};

template <TimeUnit w_unit, typename W>
struct TimeUnitScalarsFinder<w_unit, W> {
  using type = typename std::conditional<
    w_unit == W::UNIT_FROM,
    W,
    void
  >::type;
};

/**
 * TimeUnitScalars is a TimeUnitScalarsFinder containing a list of all the specific
 * time units supported.
 */
// TODO - The current limitation is that these TimeUnitScale specializations must
// create a single chain of units. Consider adding support for ad-hoc units.
template <TimeUnit w_unit>
using TimeUnitScalars = typename TimeUnitScalarsFinder<w_unit,
  TimeUnitScale<TimeUnit::WEEK, TimeUnit::DAY, std::uint16_t(7)>,
  TimeUnitScale<TimeUnit::DAY, TimeUnit::HOUR, std::uint16_t(24)>,
  TimeUnitScale<TimeUnit::HOUR, TimeUnit::MINUTE, std::uint16_t(60)>,
  TimeUnitScale<TimeUnit::MINUTE, TimeUnit::SECOND, std::uint16_t(60)>,
  TimeUnitScale<TimeUnit::SECOND, TimeUnit::CENTIS, std::uint16_t(100)>,
  TimeUnitScale<TimeUnit::CENTIS, TimeUnit::MILLIS, std::uint16_t(10)>,
  TimeUnitScale<TimeUnit::MILLIS, TimeUnit::MICROS, std::uint16_t(1000)>,
  TimeUnitScale<TimeUnit::MICROS, TimeUnit::NANOS, std::uint16_t(1000)>,
  TimeUnitScale<TimeUnit::NANOS, TimeUnit::PICOS, std::uint16_t(1000)>,
  TimeUnitScale<TimeUnit::PICOS, TimeUnit::FEMTOS, std::uint16_t(1000)>,
  TimeUnitScale<TimeUnit::FEMTOS, TimeUnit::ATTOS, std::uint16_t(1000)>,
  TimeUnitScale<TimeUnit::ATTOS, TimeUnit::YOCTOS, std::uint16_t(1000)>>::type;

/**
 * timeScale will find a scale from largest unit to smaller units. All timeScale 
 * values will be >= 1.
 */

template <TimeUnit w_from, TimeUnit w_to, typename TS>
struct timeScale {
  static constexpr TS value =
    TS(TimeUnitScalars<w_from>::SCALE)
    * timeScale<TimeUnitScalars<w_from>::UNIT_TO, w_to, TS>::value;
};

template <TimeUnit w_self, typename TS>
struct timeScale<w_self, w_self, TS> {
  static constexpr TS value = TS(1);
};

template <TimeUnit w_from, TimeUnit w_to, typename TS>
struct timeScaleCheckOverflow {
  static constexpr bool value =
    ((timeScale<w_from, w_to, TS>::value) / (TS(TimeUnitScalars<w_from>::SCALE))
      == timeScale<TimeUnitScalars<w_from>::UNIT_TO, w_to, TS>::value)
    && timeScaleCheckOverflow<TimeUnitScalars<w_from>::UNIT_TO, w_to, TS>::value;
};

template <TimeUnit w_self, typename TS>
struct timeScaleCheckOverflow<w_self, w_self, TS> {
  static constexpr bool value = true;
};

/**
 * Converts times from a TimeUnit to another TimeUnit. The conversion factor
 * may be less than 1 (i.e. minutes to days) or greater than 1 (days to minutes).
 * It is the developer's responsibility to manage the rouding errors.
 */
template <TimeUnit w_from, TimeUnit w_to>
struct ConvertTime : not_instantiable {
private:
  template <bool forward, bool integral, typename TS>
  struct ConverterMultiplier;

  template <typename TS>
  struct ConverterMultiplier<true, true, TS> {
    static constexpr bool has_not_overflowed = timeScaleCheckOverflow<w_from, w_to, TS>::value;
    static_assert(has_not_overflowed, "Time scale factor overflow.");
    static const TS multiplier = TS(timeScale<w_from, w_to, TS>::value);
  };

  template <typename TS>
  struct ConverterMultiplier<false, true, TS> {
    static constexpr bool has_not_overflowed = timeScaleCheckOverflow<w_to, w_from, TS>::value;
    static_assert(has_not_overflowed, "Time scale factor overflow.");
    static const TS multiplier = TS(1) / TS(timeScale<w_to, w_from, TS>::value);
  };

  template <typename TS>
  struct ConverterMultiplier<true, false, TS> {
    static const TS multiplier;  // Non integer must be initialized outside class.
  };

  template <typename TS>
  struct ConverterMultiplier<false, false, TS> {
    static const TS multiplier;  // Non integer must be initialized outside class.
  };


  template <bool forward, typename TS>
  struct ConverterSelector;

  template <typename TS>
  struct ConverterSelector<true, TS> 
    : ConverterMultiplier<true, std::numeric_limits<TS>::is_integer, TS>
  {
    enum { factor_gt1 = true };

    static TS convert(const TS& value) {
      return value * timeScale<w_from, w_to, TS>::value;
    }

    static TS convert_remainder(const TS&) {
      return TS(0);
    }
  };

  template <typename TS>
  struct ConverterSelector<false, TS>
    : ConverterMultiplier<false, std::numeric_limits<TS>::is_integer, TS>
  {
    enum { factor_gt1 = false };

    static TS convert(const TS& value) {
      return value / timeScale<w_to, w_from, TS>::value;
    }

    static TS convert_remainder(const TS& value) {
      return value % timeScale<w_to, w_from, TS>::value;
    }
  };
public:

  template <typename TS>
  using Converter = ConverterSelector<(w_from >= w_to), TS>;

  template <typename TS>
  static TS convert(const TS& value) {
    return Converter<TS>::convert(value);
  }

  template <typename TS>
  static TS convert_remainder(const TS& value) {
    return Converter<TS>::convert_remainder(value);
  }
};

template <TimeUnit w_from, TimeUnit w_to>
template <typename TS>
const TS ConvertTime<w_from, w_to>
    ::ConverterMultiplier<false, false, TS>
        ::multiplier = TS(1) / TS(timeScale<w_to, w_from, TS>::value);

template <TimeUnit w_from, TimeUnit w_to>
template <typename TS>
const TS ConvertTime<w_from, w_to>
    ::ConverterMultiplier<true, false, TS>
        ::multiplier = TS(timeScale<w_from, w_to, TS>::value);

}

#endif // SETL_TIME_UNIT___H