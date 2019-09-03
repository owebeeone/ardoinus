
#include "circular_buffer.h"
#include "assert_that.h"

#include "setl_test_framework.h"
#include "setlx_cstdint.h"

namespace circular_buffer_test {

using setl_test::assertThat;

class Test_DO_BOT_USE : setl_test::SetlTest {

  template <typename T, std::uint32_t size, bool is_full_use = false>
  struct Tester {
    using nvT = typename std::remove_volatile<T>::type;

    Tester() {
      do_test();
    }

    template<typename U>
    void do_insert(U& buffer, T start, std::uint32_t) {
      for (nvT i = 0; i < nvT(size); ++i) {
        assertThat(buffer.write(start + i)).eq(true);
        assertThat(buffer.overrun()).eq(false);
      }
    }

    template<typename U>
    void do_verify(U& buffer, T start, std::uint32_t, bool overrun = false) {
      for (nvT i = 0; i < nvT(size); ++i) {
        nvT result = ~0;
        assertThat(buffer.read(result)).eq(true);
        assertThat(result).eq(start + i);
        assertThat(buffer.overrun()).eq(overrun);
        assertThat(buffer.overrun()).eq(overrun);
      }
    }

    template<typename U>
    void do_test_fill(U& buffer, bool overrun_test) {
      for (int i = 0; i < 16; ++i) {
        do_insert(buffer, i << 8, size);
        if (overrun_test) {
          assertThat(buffer.write(1)).eq(false);
          assertThat(buffer.overrun()).eq(true);
        }
        do_verify(buffer, i << 8, size, overrun_test);
        if (overrun_test) {
          buffer.clear();
        }
      }
    }

    struct NonIntTestType {
      char a[sizeof(T)]{};
      float b{};
    };

    void do_test() {
      setl::CircularBuffer<T, size, is_full_use> buffer;
      assertThat(int(buffer.is_full_use)).eq(is_full_use);
      nvT result = ~0;

      do_test_fill(buffer, false);
      do_test_fill(buffer, true);

      do_insert(buffer, 4 << 4, 1);
      do_verify(buffer, 4 << 4, 1);
      do_insert(buffer, 5 << 4, 1);
      do_verify(buffer, 5 << 4, 1);
      do_insert(buffer, 6 << 4, 1);
      do_verify(buffer, 6 << 4, 1);

      do_insert(buffer, 7 << 4, size - 1);
      do_verify(buffer, 7 << 4, size - 1);
      do_insert(buffer, 8 << 4, size - 1);
      do_verify(buffer, 8 << 4, size - 1);
      do_insert(buffer, 9 << 4, size - 1);
      do_verify(buffer, 9 << 4, size - 1);

      do_insert(buffer, 0, size);
      buffer.clear();
      assertThat(buffer.read(result)).eq(false);

      // Verify can't read more.
      assertThat(buffer.read(result)).eq(false);

      NonIntTestType niv;
      setl::CircularBuffer<NonIntTestType, size, is_full_use> nivBuffer;
      assertThat(nivBuffer.write(niv)).eq(true);
      assertThat(nivBuffer.read(niv)).eq(true);
      assertThat(nivBuffer.read(niv)).eq(false);
      assertThat(nivBuffer.overrun()).eq(false);
    }

  };

  template <bool is_full_use>
  struct TestCollection {
    Tester<volatile int, 2> test1;
    Tester<volatile int, 3> test2;
    Tester<volatile int, 4> test3;
    Tester<volatile int, 5> test4;
    Tester<int, 255> test5;
    Tester<int, 256> test6;
  };

  bool run() {
    TestCollection<true> faster_tests;
    TestCollection<false> full_tests;
    return true;
  }
};

Test_DO_BOT_USE test_not_for_product_use;
}