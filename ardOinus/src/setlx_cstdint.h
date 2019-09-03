

#ifndef SETL_CSTDINT__H
#define SETL_CSTDINT__H

#include "setl_support.h"

#ifdef HAS_STD_LIB
#include <cstdint>
#else

#include "setlx_type_traits.h"

namespace std {

namespace nfp {

template <unsigned size, typename... T>
struct FindBySize;

template <unsigned size, typename W, typename... T>
struct FindBySize<size, W, T...> {
  using type = typename std::conditional<
      size == sizeof(W), W, typename FindBySize<size, T...>::type>::type;
};

template <unsigned size, typename W>
struct FindBySize<size, W> {
  using type = typename std::conditional<size == sizeof(W), W, void>::type;
};

template <typename... T>
struct TypeList {
  template <unsigned size>
  struct FindSize {
    using type = typename FindBySize<size, T...>::type;
  };
};

using SignedTypes = TypeList<signed char, short, int, long, long long>;
using UnsignedTypes = TypeList<
  unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;

} // namespace nfp

using int8_t = nfp::SignedTypes::FindSize<1>::type;
using int16_t = nfp::SignedTypes::FindSize<2>::type;
using int32_t = nfp::SignedTypes::FindSize<4>::type;
using int64_t = nfp::SignedTypes::FindSize<8>::type;

using uint8_t = nfp::UnsignedTypes::FindSize<1>::type;
using uint16_t = nfp::UnsignedTypes::FindSize<2>::type;
using uint32_t = nfp::UnsignedTypes::FindSize<4>::type;
using uint64_t = nfp::UnsignedTypes::FindSize<8>::type;

} // namespace
#endif

#endif