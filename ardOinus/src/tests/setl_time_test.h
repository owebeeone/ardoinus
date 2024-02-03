

#include "setl_time.h"

#include "setl_test_framework.h"

#include "assert_that.h"


namespace {
  
using setl_test::assertThat;

#if 0
template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) * Rhs(1))>
struct Mul {};

template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) / Rhs(1))>
struct Div {};

template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) + Rhs(1))>
struct Add {};

template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) - Rhs(1))>
struct Sub {};

template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) == Rhs(1))>
struct Eq {};

template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) != Rhs(1))>
struct Neq {};

template <template <typename Lhs, typename Rhs, int n = 1> class OP>
struct OpTest {
  template <typename Lhs, typename Rhs>
  static int allowed(const Lhs& x, const Rhs& y, int q,
    int(*z)[sizeof(OP<Lhs, Rhs>)] = 0) {
    return true;
  }

  template <typename Lhs, typename Rhs>
  static char allowed(const Lhs& x, const Rhs& y, long q) {
    return false;
  }
};

template <template <typename Lhs, typename Rhs, int n = 1> class Op, typename Lhs, typename Rhs>
constexpr bool allowed = sizeof(OpTest<Op>::allowed(Lhs(1), Rhs(1), 0)) == sizeof(int);

static_assert(!allowed<Mul, setl::Time<int>, setl::Time<int>>, "t*t should not be allowed");
static_assert(allowed<Sub, setl::Time<int>, setl::Time<int>>, "t-t should be allowed");
static_assert(allowed<Add, setl::Time<int>, setl::Period<int>>, "t+p should be allowed");
#endif

// Test time...
class SetlTimeTest_DO_NOT_USE : setl_test::SetlTest {

  template <typename T>
  struct TimeTest {
    using TType = setl::Time<T>;
    using PType = setl::Period<T>;
    using PTypeSecs = setl::Period<T, setl::TimeUnit::SECOND>;
    using PTypeWeek = setl::Period<T, setl::TimeUnit::WEEK>;
    using PTypeNanos = setl::Period<T, setl::TimeUnit::NANOS>;

    TimeTest() {
      do_test();
    }

    void do_test() {
      assertThat(((TType(2) + PType(4)) == TType(6))).eq(true);
      assertThat(((PType(2) + TType(4)) == TType(6))).eq(true);
      assertThat((t2 - t1) == PType(t2.get() - t1.get())).eq(true);
      assertThat(((PType(4) * 1.5) == PType(6))).eq(true);
      assertThat(((PType(4) * 1.5f) == PType(6))).eq(true);
      assertThat(((PType(4) * 1.5) != PType(6))).eq(false);
      assertThat(((PType(4) += PType(2)) == PType(6))).eq(true);
      assertThat((PType(PTypeSecs(4)) == PType(4000))).eq(true);
      // PTypeNanos n{ PTypeWeek(1) }; // should fail to compile. Overflow of scale.
    }

    TType t1{ 5 };
    TType t2{ 11 };
    PType p1{ 5 };
    PType p2{ 11 };
  };


  bool run() {
    TimeTest<int> test0;
    TimeTest<unsigned> test1;
    TimeTest<unsigned long long> test2;
    TimeTest<float> test3;
    TimeTest<double> test4;

    using setl::operator"" _sec;
    using setl::operator"" _min;

    assertThat((12.1_sec == setl::Period<long double, setl::TimeUnit::SECOND>(12.1L))).isTrue();
    assertThat((12.1_sec == setl::period<setl::TimeUnit::SECOND>(12.1L))).isTrue();
    assertThat((12_sec == setl::Period<unsigned long long, setl::TimeUnit::SECOND>(12))).isTrue();

    assertThat((1.1_min == (66.0_sec).to<setl::TimeUnit::MINUTE>())).isTrue();

    assertThat((1.1_min == (66.0_sec).to())).isTrue();

    return true;
  }

};

SetlTimeTest_DO_NOT_USE time_test;

}