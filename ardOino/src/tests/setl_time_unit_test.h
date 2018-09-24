#include "setl_time_unit.h"
#include "assert_that.h"

#include "setl_test_framework.h"
#include "setlx_cstdint.h"

namespace setl_time_unit_test {

using setl_test::assertThat;

class Setl_TIME_UNIT_TEST_DO_NOT_USE : setl_test::SetlTest {

  static_assert(
    setl::ConvertTime<
      setl::TimeUnit::DAY,
      setl::TimeUnit::HOUR>::Converter<unsigned>::multiplier == 24,
    "conversion error");

  static_assert(
    setl::ConvertTime<
    setl::TimeUnit::DAY, 
    setl::TimeUnit::HOUR>::Converter<std::uint16_t>::multiplier == 24,
    "conversion error");

  static_assert(
    setl::ConvertTime<
      setl::TimeUnit::DAY,
      setl::TimeUnit::HOUR>::Converter<unsigned long long>::multiplier == 24,
    "conversion error");

  static_assert(
    setl::ConvertTime<
      setl::TimeUnit::DAY,
      setl::TimeUnit::MINUTE>::Converter<unsigned>::multiplier == 24 * 60,
    "conversion error");

  static_assert(
    setl::ConvertTime<
      setl::TimeUnit::DAY,
      setl::TimeUnit::MINUTE>::Converter<unsigned long long>::multiplier == 24 * 60,
    "conversion error");

  template <typename T>
  struct TestCollection {
    TestCollection() {
      to_test();
    }

    template <setl::TimeUnit w_from, setl::TimeUnit w_to>
    using ConvertTime = setl::ConvertTime<w_from, w_to>;

    static const auto DAY = setl::TimeUnit::DAY;
    static const auto HOUR = setl::TimeUnit::HOUR;
    static const auto MINUTE = setl::TimeUnit::MINUTE;
    static const auto SECOND = setl::TimeUnit::SECOND;
    static const auto MICROS = setl::TimeUnit::MICROS;
    static const auto NANOS = setl::TimeUnit::NANOS;

    void to_test() {
      assertThat(ConvertTime<DAY, MINUTE>::convert(T(1))).eq(24 * 60);
      assertThat(ConvertTime<MICROS, NANOS>::convert(T(1))).eq(1000);
      assertThat(ConvertTime<NANOS, MICROS>::convert(T(10001))).eq(T(10001)/1000);
    }

  };

  bool run() override {
    TestCollection<unsigned> t1;
    TestCollection<unsigned short> t2;
    TestCollection<unsigned long> t3;
    TestCollection<unsigned long long> t4;
    TestCollection<signed long> t5;
    TestCollection<signed long long> t6;
    TestCollection<float> t7;
    TestCollection<double> t8;
    TestCollection<long double> t9;
    return true;
  }
};

Setl_TIME_UNIT_TEST_DO_NOT_USE time_unit_test;

}