
#ifndef SETL_INTEGERS__H
#define SETL_INTEGERS__H

namespace setl {
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

} // namespace nfp

/**
 * Tools for finding integers of specific sizes or types.
 */
using SignedTypes = nfp::TypeList<signed char, short, int, long, long long>;
using UnsignedTypes = nfp::TypeList<
  unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;
} // namespace setl

#endif  // SETL_INTEGERS__H