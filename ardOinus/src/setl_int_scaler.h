
#ifndef SETL_INT_SCALER____H
#define SETL_INT_SCALER____H

#include "type_for_size.h"

namespace setl {

// Computes Mersenne numbers - 2^n-1.
constexpr std::uint32_t mersenne(std::uint32_t n) {
  return n < 32 ? (1 << n) - 1 : ~std::uint32_t(0);
}

/**
 * scale_up_number will scale an integer range, 0..2^q-1, to a larger range,
 * 0..2^m-1 (i.e. m>q) so that the scaled limits are the same as the limits
 * of the target range. i.e. scale_up_number(m, q, mersenne(q)) == mersenne(m).
 * The scaling is linear (apart from rounding aliasing).
 */
namespace nfp {
constexpr std::uint32_t scale_up_number(
  std::uint32_t m, std::uint32_t q, std::uint32_t value, std::uint32_t sum, std::uint32_t shift) {
  return (shift + q) >= m 
    ? (sum >> ((shift + q) % m)) + (value << (shift - ((shift + q) % m)))
    : scale_up_number(m, q, value, sum + (value << shift), shift + q);
}
} // namespace nfp

constexpr std::uint32_t scale_up_number(
  std::uint32_t m, std::uint32_t q, std::uint32_t value) {
  return nfp::scale_up_number(m, q, value, 0, 0);
}

/**
 * scale_up_number<m,q> performs the same operations as above but the
 * template parameters allow for spedifying the input and output types.
 */
template <
  std::uint32_t m, 
  std::uint32_t q,
  typename out_type = typename TypeForMaxBits<m>::selected::type_unsigned,
  typename in_type = typename TypeForMaxBits<q>::selected::type_unsigned>
constexpr out_type scale_up_number(
  in_type value, out_type sum = 0, std::uint32_t shift = 0) {
  return (shift + q) >= m
    ? (sum >> ((shift + q) % m)) + (out_type(value) << (shift - ((shift + q) % m)))
    : scale_up_number<m, q>(value, sum + (out_type(value) << shift), shift + q);
}

// Validate that the functions work as expected.
static_assert(scale_up_number<11, 3>(mersenne(3)) == mersenne(11), "scale_up_number failed");
static_assert(scale_up_number(11, 3, mersenne(3)) == mersenne(11), "scale_up_number failed");
static_assert(scale_up_number<32, 3>(mersenne(3)) == mersenne(32), "scale_up_number failed");

template <
  std::uint8_t in_bits,
  typename T = typename TypeForMaxBits<in_bits>::selected::type_unsigned>
class LinearScalerSelector {
public:
  using in_value_type = T;

  template <
    std::uint8_t out_bits,
    typename O = typename TypeForMaxBits<out_bits>::selected::type_unsigned,
    bool down_scale = (in_bits >= out_bits)> 
  class Scaler {
  public:
    using value_type = O;
    constexpr static value_type scale(in_value_type input) {
      return input >> (in_bits - out_bits);
    }
  };

  template <std::uint8_t out_bits, typename O>
  class Scaler<out_bits, O, false> {
  public:
    using value_type = O;
    constexpr value_type static scale(in_value_type input) {
      return setl::scale_up_number<out_bits, in_bits, value_type, in_value_type>(input);
    }
  };

};

} // namespace setl

#endif // SETL_INT_SCALER____H