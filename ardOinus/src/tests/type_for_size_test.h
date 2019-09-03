
// This header is provides no interface.
// This provides a test for functionality in "type_for_size.h".

#include "type_for_size.h"

#include "setl_test_framework.h"
#include "setlx_limits.h"

namespace tfs_test {  // run tests in a namespace to hide.

using setl_test::assertThat;

class Test_DO_NO_USE : setl_test::SetlTest {

  template <typename T, unsigned size, bool is_signed>
  struct type_asserter {
    static_assert(sizeof(T) == size, "Unexpected size.");
    static_assert(std::numeric_limits<T>::is_signed == is_signed, "Expected signed/unsigned.");
    using type = type_asserter;
  };

  template <std::uint32_t size, std::uint32_t size_unsigned>
  struct tfs_tester_just_unsigned {
    using tt = typename setl::TypeForMaxValue<size>::selected;
    using tu = typename tt::type_unsigned;
    using assert_type = typename type_asserter<tu, size_unsigned, false>::type;
  };

  template <std::uint32_t size, std::uint32_t size_signed, std::uint32_t size_unsigned>
  struct tfs_tester {
    using tt = typename setl::TypeForMaxValue<size>::selected;
    using ts = typename tt::type_signed;

    using assert_type = typename type_asserter<ts, size_signed, true>::type;
    //static_assert(sizeof(ts) == size_signed, "Unexpected signed size.");
    //static_assert(std::numeric_limits<ts>::is_signed, "Expected signed type.");

    tfs_tester_just_unsigned<size, size_unsigned> tv;
  };

  tfs_tester<127U, 1, 1>::tt t11;
  tfs_tester<128U, 2, 1>::tt t12;
  tfs_tester<255U, 2, 1>::tt t21;
  tfs_tester<256U, 2, 2>::tt t22;
  tfs_tester<(1UL << 15) - 1, 2, 2>::tt t31;
  tfs_tester<(1UL << 15), 4, 2>::tt t32;
  tfs_tester<(1UL << 16) - 1, 4, 2>::tt t41;
  tfs_tester<(1UL << 16), 4, 4>::tt t42;
  tfs_tester<(1UL << 31) - 1, 4, 4>::tt t51;
  tfs_tester_just_unsigned<~std::uint32_t(0), 4>::tt t61;


  template <std::uint32_t size, std::uint32_t size_bytes>
  struct tfs_bits_tester {
    using tt = typename setl::TypeForMaxBits<size>::selected;

    using ts = typename tt::type_signed;
    static_assert(sizeof(ts) == size_bytes, "Unexpected signed size.");
    static_assert(std::numeric_limits<ts>::is_signed, "Expected signed type.");

    using tu = typename tt::type_unsigned;
    static_assert(sizeof(tu) == size_bytes, "Unexpected unsigned size.");
    static_assert(!std::numeric_limits<tu>::is_signed, "Expected unsigned type.");
  };


  bool run() {
    tfs_bits_tester<8U, 1>::tt tb11;
    tfs_bits_tester<9U, 2>::tt tb12;
    tfs_bits_tester<15U, 2>::tt tb2x;
    assertThat(sizeof(setl::TypeForMaxBits<15>::selected::type_unsigned)).eq(2);
    tfs_bits_tester<16U, 2>::tt tb21;
    tfs_bits_tester<17U, 4>::tt tb22;
    tfs_bits_tester<32U, 4>::tt tb31;

    Test_DO_NO_USE* const s = this;

    return true;
  }
};

Test_DO_NO_USE test_not_for_product_use;
}