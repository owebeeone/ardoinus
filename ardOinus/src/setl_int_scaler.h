
#ifndef SETL_INT_SCALER____H
#define SETL_INT_SCALER____H

#include "type_for_size.h"

namespace setl {

/**
 * Evaluates Mersenne numbers, i.e. 2^n-1.
 */
constexpr std::uint32_t mersenne(std::uint8_t n) {
  return n < 32 ? (1 << n) - 1 : ~std::uint32_t(0);
}

template <std::uint8_t n>
constexpr UnsignedTypeForMaxBits<n> mersenne_u =
   n < (sizeof(UnsignedTypeForMaxBits<n>) * 8) 
      ? (UnsignedTypeForMaxBits<n>(1) << n) - 1 : ~UnsignedTypeForMaxBits<n>(0);;

/**
 * scale_mersenne will scale an integer range, 0..2^q-1 (q=in_bits), to 
 * a range, 0..2^m-1 (i.e. m=out_bist and m>q) so that the scaled limits 
 * are the same as the limits of the target range. 
 * i.e. scale_mersenne(m, q, mersenne(q)) == mersenne(m).
 * The scaling is linear (apart from rounding aliasing). The scale factor is
 * double(mersenne(out_bits)) / double(mersenne(in_bits)) but this code does
 * no floating point math.
 */
inline std::uint32_t scale_mersenne(
  std::uint8_t out_bits, std::uint8_t in_bits, std::uint32_t value) {
  if (out_bits <= in_bits) {
    return value >> (in_bits - out_bits);
  }

  std::uint32_t result = value << (out_bits - in_bits);

  if (out_bits > in_bits) {
    result += result >> in_bits;
  }

  if (out_bits > 2 * in_bits) {
    result += result >> (2 * in_bits);
  }

  if (out_bits > 4 * in_bits) {
    result += result >> (4 * in_bits);
  }

  if (out_bits > 8 * in_bits) {
    result += result >> (8 * in_bits);
  }

  if (out_bits > 16 * in_bits) {
    result += result >> (16 * in_bits);
  }

  if (out_bits > 32 * in_bits) {  // 64 bit support!
    result += result >> (32 * in_bits);
  }

  return result;
}

/**
 * scale_mersenne<m,q> performs the same operations as above but the
 * template parameters allow for specifying the input and output types.
 */
template <
  std::uint8_t out_bits, 
  std::uint8_t in_bits,
  typename out_type = typename TypeForMaxBits<out_bits>::selected::type_unsigned,
  typename in_type = typename TypeForMaxBits<in_bits>::selected::type_unsigned>
inline out_type scale_mersenne(in_type value) {
  static_assert(sizeof(out_type) * 8 >= out_bits, "Result type is too small");
  static_assert(sizeof(in_type) * 8 >= in_bits, "Input type is too small");

  if (out_bits <= in_bits) {
    return value >> (in_bits - out_bits);
  }

  out_type result = value << (out_bits - in_bits);

  if (out_bits > in_bits) {
    result += result >> in_bits;
  }

  if (out_bits > 2 * in_bits) {
    result += result >> (2 * in_bits);
  }

  if (out_bits > 4 * in_bits) {
    result += result >> (4 * in_bits);
  }

  if (out_bits > 8 * in_bits) {
    result += result >> (8 * in_bits);
  }

  if (out_bits > 16 * in_bits) {
    result += result >> (16 * in_bits);
  }

  if (out_bits > 32 * in_bits) {  // 64 bit support!
    result += result >> (32 * in_bits);
  }

  return result;
}

/**
 * LinearScalerSelector will provide a scaler that will map a value
 * range in unsigned bits to another range in unsigned bits linerarly.
 * Importantly, the full range is mapped, even from smaller resolutions
 * to higher resolutions. (i.e. zero is mapped to zero and max input
 * is mapped to max output.
 */
template <
  std::uint8_t in_bits,
  typename T = typename TypeForMaxBits<in_bits>::selected::type_unsigned>
class LinearScalerSelector {
public:
  using in_value_type = T;

  template <
    std::uint8_t out_bits,
    typename O = typename TypeForMaxBits<out_bits>::selected::type_unsigned> 
  class Scaler {
  public:
    using value_type = O;
    constexpr static value_type scale(in_value_type input) {
      return setl::scale_mersenne<out_bits, in_bits, value_type, in_value_type>(input);
    }
  };
};

} // namespace setl

#endif // SETL_INT_SCALER____H