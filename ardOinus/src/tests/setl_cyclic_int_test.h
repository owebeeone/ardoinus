

#include "setl_cyclic_int.h"
#include "assert_that.h"

#include "setl_test_framework.h"

//#include <functional>

namespace {

using setl_test::assertThat;

class CyclicIntTest_DO_NOT_USE : setl_test::SetlTest {

  template <std::uint32_t w_size, bool as_volatile = false>
  struct test {
    using test_type = setl::CyclicInt<w_size, as_volatile>;

    test() {
      do_test_add1([](test_type& value) -> void { ++value; });
      do_test_add1([](test_type& value) -> void { value++; });
      do_test_add1([](test_type& value) -> void { value += 1; });
      do_test_add1([](test_type& value) -> void { value = value + 1; });
    
      do_test_sub1([](test_type& value) -> void { value = value + (w_size - 1); });
      do_test_sub1([](test_type& value) -> void { value -= 1; });
      do_test_sub1([](test_type& value) -> void { value--; });
      do_test_sub1([](test_type& value) -> void { --value; });

      do_test_add_any();
    }

    void do_test_add1(void (*add_1)(test_type& value)) {

      test_type value;
      assertThat(value.get()).eq(0);
      assertThat(value == test_type()).eq(true);

      for (long long unsigned i = 0; i < 2 * w_size; ++i) {
        add_1(value);
        assertThat(value.get()).eq((i + 1) % w_size);
      }

      test_type other = value;
      ++other = value;

      assertThat(test_type(-1L).get()).eq(w_size - 1);
    }

    void do_test_sub1(void(*sub_1)(test_type& value)) {
      test_type value;
      assertThat(value.get()).eq(0);

      for (long unsigned i = 0; i < 2 * w_size; ++i) {
        sub_1(value);
        assertThat(value.get()).eq((w_size * 10 - i - 1) % w_size);
      }
    }

    void do_test_add_any() {
      for (long signed i = 0; i < 10 * w_size; ++i) {
        auto result = test_type(i + 1) + ((7 * i) % (w_size + 3));
        assertThat(result.get()).eq((i + 1 + ((7 * i) % (w_size + 3))) % w_size);
      }
    }
  };

  bool run() {
    test<3UL> test3;
    test<3UL, true> test3v;
    test<254UL> test254;
    test<255UL> test255;
    test<(1UL << 13) - 1> test13bm1;
    test<(1UL << 16) - 1> test16bm1;
    test<(1UL << 16)> test16b;
    return true;
  }
};

CyclicIntTest_DO_NOT_USE test_not_for_product_use;
} // namespace
