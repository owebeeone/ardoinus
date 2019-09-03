
/**
 * Provides types that conforms to some criteria.
 *
  * Size Efficient Template Library - setl.
 * 
 * If a library is to be suitable for all embedded and large CPUs alike, it's
 * important to be memory efficient. This header provides a mechanism to find
 * the smallest type that satisfies the requirement.
 */
#ifndef TYPE_FOR_SIZE___H
#define TYPE_FOR_SIZE___H

#include "setl_utils.h"

#include "setlx_cstdint.h"
#include "setlx_type_traits.h"

namespace setl {

// Provide type information for all types. These are not publicly visible.
class TypeTraits : not_instantiable {

  template <std::uint32_t max_value>
  friend struct TypeForMaxValue;
  template <std::uint32_t max_bits>
  friend struct TypeForMaxBits;

  struct Integer7 {
    static constexpr std::uint32_t max_value = (1UL << 7) - 1;
    static constexpr std::uint32_t max_bits = 8;
    using type_signed = std::int8_t;
    using type_unsigned = std::uint8_t;
  };

  struct Integer8 {
    static constexpr std::uint32_t max_value = (1UL << 8) - 1;
    using type_signed = std::int16_t;
    using type_unsigned = std::uint8_t;
  };

  struct Integer15 {
    static constexpr std::uint32_t max_value = (1UL << 15) - 1;
    static constexpr std::uint32_t max_bits = 16;
    using type_signed = std::int16_t;
    using type_unsigned = std::uint16_t;
  };

  struct Integer16 {
    static constexpr std::uint32_t max_value = (1UL << 16) - 1;
    using type_signed = std::int32_t;
    using type_unsigned = std::uint16_t;
  };

  struct Integer31 {
    static constexpr std::uint32_t max_value = (1UL << 31) - 1;
    static constexpr std::uint32_t max_bits = 32;
    using type_signed = std::int32_t;
    using type_unsigned = std::uint32_t;
  };

  struct Integer32 {
    static constexpr std::uint32_t max_value = (((1UL << 31) - 1) << 1) + 1;
    // No signed type specified.
    using type_unsigned = std::uint32_t;
  };

  struct IntegerError {
    static constexpr std::uint32_t max_value = 0;
    // No type specified.
  };
};

/** Provides integer types that hold up to max_value without oveflow. */
template <std::uint32_t max_value>
struct TypeForMaxValue {
private:
  template <std::uint32_t w_max_value, typename... I>
  struct MaxValueSelectorIter;

  template <std::uint32_t w_max_value>
  struct MaxValueSelectorIter<w_max_value> {
    using selected = TypeTraits::IntegerError;
  };

  template <std::uint32_t w_max_value, typename I, typename... L>
  struct MaxValueSelectorIter<w_max_value, I, L...> {
  public:
    using selected = typename std::conditional<
      (I::max_value >= w_max_value), I, typename MaxValueSelectorIter<w_max_value, L...>::selected >::type;
  };

public:
  using selected = typename MaxValueSelectorIter<
    max_value, TypeTraits::Integer7, TypeTraits::Integer8, TypeTraits::Integer15, 
    TypeTraits::Integer16, TypeTraits::Integer31, TypeTraits::Integer32>::selected;
};

/** Provides integer types that hold up to max_bits bits. */
template <std::uint32_t max_bits>
struct TypeForMaxBits {
private:
  template <std::uint32_t w_max_bits, typename... I>
  struct MaxBitsSelectorIter;

  template <std::uint32_t w_max_bits>
  struct MaxBitsSelectorIter<w_max_bits> {
    using selected = TypeTraits::IntegerError;
  };

  template <std::uint32_t w_max_bits, typename I, typename... L>
  struct MaxBitsSelectorIter<w_max_bits, I, L...> {
  public:
    using selected = typename std::conditional<
      (I::max_bits >= w_max_bits), I, typename MaxBitsSelectorIter<w_max_bits, L...>::selected >::type;
  };

public:
  using selected = typename MaxBitsSelectorIter
    <max_bits, TypeTraits::Integer7, TypeTraits::Integer15, TypeTraits::Integer31>::selected;
};

} // namespace

#endif
