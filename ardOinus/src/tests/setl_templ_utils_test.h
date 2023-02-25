

#include "setl_templ_utils.h"

#include "setlx_type_traits.h"

namespace templ_utils_test {

template <typename... T>
struct A {
  
  template <typename Op, typename VL>
  using Scanner = setl::For<Op, VL, T...>;
};

using AP = A<std::false_type, std::false_type>;
using AP1 = A<std::false_type, std::false_type, std::true_type>;


using Op = setl::Operator<std::is_same, setl::OrEval>;

static_assert(!AP::Scanner<Op, std::true_type>::value, "True type not used.");
static_assert(AP::Scanner<Op, std::false_type>::value, "False type used.");

static_assert(AP1::Scanner<Op, std::true_type>::value, "True type used.");
static_assert(AP1::Scanner<Op, std::false_type>::value, "False type used.");

template <typename A, typename B>
struct is_same_int {
  static constexpr int value = std::is_same<A, B>::value ? 1 : 0;
};

using AddOp = setl::Operator<std::is_same, setl::AddEval<float>>;

static_assert(AP1::Scanner<AddOp, std::true_type>::value == 1, "1 true type.");
static_assert(AP1::Scanner<AddOp, std::false_type>::value == 2, "2 false type.");

}