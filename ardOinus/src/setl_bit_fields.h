/**
 * A generic bit fields library.
 * 
 */

#ifndef SETL_BIT_FIELDS___H
#define SETL_BIT_FIELDS___H

#include "setlx_cstdint.h"
#include "setlx_tuple.h"

namespace setl {

/**
 * Shift right (<<) for positive shift or right (>>) for negative shift.
 */
template <typename T>
constexpr T bit_shift(T value, int shift) {
  return shift == 0 ? value : shift > 0 ? value << shift : value >> -shift;
}

/**
 * Represents a unit of bit manipulations, i.e. a single "mask" and "shift" operation.
 */
template <typename T, T w_mask, int w_shift>
struct MaskShift {
  static_assert(w_mask, "Mask should not be zero.");
  using type = T;
  static constexpr T mask{w_mask};
  static constexpr int shift{w_shift};
};

/**
 * A collection of MaskShift operations.
 */
template <typename...MS>
struct MaskShifts {
  using mask_shifts = std::tuple<MS...>;
  static constexpr unsigned count = sizeof...(MS);

  /// Concatenate this set of MaskShift operations with the set in the parameter list.
  template <typename...addMS>
  using catenate = MaskShifts<addMS..., MS...>;

  /// Applies a template to the set of MaskShift operations.
  template <template <typename...MS> typename Other>
  using apply = Other<MS...>;

  /// Applies a template to the set of MaskShift operations with an associated
  /// mask and shift operations.
  template <
    typename Ta, 
    Ta w_mask, 
    int w_shift, 
    template <typename Tb, Tb v_mask, int v_shift, typename...MS> typename Other>
  using applyTMS = Other<Ta, w_mask, w_shift, MS...>;
};

/**
 * Coalesce bit shift operations with the same shift into a single MaskShift
 * operation with a new mask coalesced mask.
 */
template <typename T, T w_mask, int w_shift, typename...MSs>
struct AddBitShifts;

template <typename T, T w_mask, int w_shift>
struct AddBitShifts<T, w_mask, w_shift> {
  static_assert(w_mask != 0, "Mask should not be zero.");
  using mask_shifts = MaskShifts<MaskShift<T, w_mask, w_shift>>;
};

template <typename T, T w_mask, int w_shift, T w_curr_mask, typename...MS>
struct AddBitShifts<T, w_mask, w_shift, MaskShift<T, w_curr_mask, w_shift>, MS...> {
  static_assert(w_mask != 0, "Mask should not be zero.");
  using mask_shifts = MaskShifts<MaskShift<T, w_mask | w_curr_mask, w_shift>, MS...>;
};

template <typename T, T w_mask, int w_shift, typename MS, typename...MSs>
struct AddBitShifts<T, w_mask, w_shift, MS, MSs...> {
  static_assert(w_mask != 0, "Mask should not be zero.");
  using mask_shifts = typename AddBitShifts<T, w_mask, w_shift, MSs...>
        ::mask_shifts::template catenate<MS>;
};

/**
 * The bit position that is not used. If the bit position has no corresponding,
 * input bit use NA.
 */
constexpr unsigned NA{~0u};

/**
 * Find the maximum value (ignoring NA).
 */
template <unsigned...Ns>
struct Max;

template <unsigned N>
struct Max<N> {
  static constexpr unsigned value = N;
};

template <unsigned N, unsigned...Ns>
struct Max<N, Ns...> {
  static constexpr unsigned value = 
    Max<Ns...>::value == NA ? N : 
      N == NA ? Max<Ns...>::value : 
        Max<Ns...>::value > N ? Max<Ns...>::value : N;
};

/**
 * Finds the reverse index of a value in a list or NA if not found.
 */
template <unsigned V, unsigned...Ns>
struct RIndexOf {
  static constexpr unsigned value = NA;
};

template <unsigned V, unsigned...Ns>
struct RIndexOf<V, V, Ns...> {
  static constexpr unsigned value = sizeof...(Ns);
};

template <unsigned V, unsigned N, unsigned...Ns>
struct RIndexOf<V, N, Ns...> {
  static constexpr unsigned value = RIndexOf<V, Ns...>::value;
};

/**
 * Generic list of unsigned values.
 */
template <unsigned...Ns>
struct UintList {

  /// concatenate this list of values with the passed list placing the passed
  /// list in the front of the resulting list.
  template <unsigned...wNs>
  using catenate_front = UintList<wNs..., Ns...>;

  /// concatenate this list of values with the passed list placing the passed
  /// list in the back of the resulting list.
  template <unsigned...wNs>
  using catenate_back = UintList<Ns..., wNs...>;

  /// Apply this list of values to another template.
  template <typename T, template <typename T, unsigned...wNs> typename Func>
  using eval = Func<T, Ns...>;
};

/**
 * Creates an inverse map of bit locations. If bit locations are not
 * provided the NA is inserted.
 */
template <unsigned K, unsigned...bits>
struct InverseMapHelper {
  static_assert(K > 0, "Should not get the 0 case here.");
  using previous = InverseMapHelper<K - 1, bits...>;
  using inverse_map = typename previous::inverse_map::template catenate_front<RIndexOf<K, bits...>::value>;
};

/// Specialization for NA. It should never happen.
template <unsigned...bits>
struct InverseMapHelper<NA, bits...>;

// Finds 0 in the
template <unsigned...bits>
struct InverseMapHelper<0u, bits...> {
  using inverse_map = UintList<RIndexOf<0, bits...>::value>;
};

/**
 * Inverse mapping for the given set of bits.
 */
template <unsigned...bits>
struct InverseMap {
  static constexpr unsigned max_value = Max<bits...>::value;
  static_assert(max_value < 128, "Bit number is out of range.");
  using inverse_map = typename InverseMapHelper<max_value, bits...>::inverse_map;
};

template <>
struct InverseMap<> {
  static constexpr unsigned max_value = NA;
  using inverse_map = UintList<>;
};

/**
 * Converts a set of bit locations to MaskShifts providing a set of
 * shift and mask and shift operations. Also provides an inverse 
 * of MaskShifts.
 */
template <typename T, unsigned size, unsigned...bits>
struct GroupMaskShiftsHelper {
  using group = GroupMaskShiftsHelper<T, size, bits...>;
};

template <typename T, unsigned size>
struct GroupMaskShiftsHelper<T, size, NA> {
  using group = MaskShifts<>;
};

template <typename T, unsigned size, unsigned...bits>
struct GroupMaskShiftsHelper<T, size, NA, bits...> {
  using group = typename GroupMaskShiftsHelper<T, size, bits...>::group;
};

template <typename T, unsigned size, unsigned bit>
struct GroupMaskShiftsHelper<T, size, bit> {
  using group = MaskShifts<MaskShift<T, bit_shift(T{1}, bit), -int(bit)>> ;
};

template <typename T, unsigned size, unsigned bit, unsigned...bits>
struct GroupMaskShiftsHelper<T, size, bit, bits...> {
  using rest = typename GroupMaskShiftsHelper<T, size, bits...>::group;

  using group = typename rest::template
    applyTMS<T, bit_shift(T{1}, bit), int(sizeof...(bits)) - int(bit), AddBitShifts>::mask_shifts;
};

template <typename T, unsigned...bits>
struct GroupMaskShifts {
  using group = typename GroupMaskShiftsHelper<T, sizeof...(bits), bits...>::group;
  using group_bits = UintList<bits...>;
  using inverse_bits = typename InverseMap<bits...>::inverse_map;
  using inverse = typename inverse_bits::template eval<T, GroupMaskShifts>;
  using inverse_group = typename inverse::group;
};

/**
 * Provides the unsigned integer type that has a sizeof greater or equal to size.
 */
template <unsigned size>
struct UnsignedForSize;

template <>
struct UnsignedForSize<1> {
  using type = std::uint8_t;
};

template <>
struct UnsignedForSize<2> {
  using type = std::uint16_t;
};

template <>
struct UnsignedForSize<4> {
  using type = std::uint32_t;
};

template <>
struct UnsignedForSize<8> {
  using type = std::uint64_t;
};

/**
 * Provides the unsigned type has a size greater than all the given types.
 * Also works for a std::tuple of types.
 */
template <typename...T>
struct UnsignedType {
  using type = typename UnsignedForSize<Max<sizeof(T)...>::value>::type;
};

template <typename...T>
struct UnsignedType<std::tuple<T...>> {
  using type = typename UnsignedForSize<Max<sizeof(T)...>::value>::type;
};

using TestUnsignedType = UnsignedType<char, short, signed char, unsigned char, char>::type;

/**
 * Converter function that applies the given set of MaskShift operations.
 */
template <typename...MSs>
struct ApplyMaskShift;

// Single mask and shift case.
template <typename T, T w_mask, int w_shift>
struct ApplyMaskShift<MaskShift<T, w_mask, w_shift>> {
  static constexpr T in_mask = w_mask;
  static constexpr T out_mask = bit_shift(w_mask, w_shift);
  static constexpr T convert(T value) {
    return bit_shift(value & w_mask, w_shift);
  }
};

/// Case of ApplyMaskShift for masking all bits and zero shift.
template <typename T>
struct ApplyMaskShift<MaskShift<T, ~T{0}, 0>> {
  static constexpr T in_mask = ~T{0};
  static constexpr T out_mask = ~T{0};
  static constexpr T convert(T value) {
    return value;
  }
};

template <typename T, T w_mask, int w_shift, typename...MSs>
struct ApplyMaskShift<MaskShift<T, w_mask, w_shift>, MSs...> {
  static constexpr T in_mask = w_mask | ApplyMaskShift<MSs...>::in_mask;
  static constexpr T out_mask = bit_shift(w_mask, w_shift) | ApplyMaskShift<MSs...>::out_mask;
  static constexpr T convert(T value) {
    return bit_shift(value & w_mask, w_shift) | ApplyMaskShift<MSs...>::convert(value);
  }
};

}  // namespace setl

#endif  // SETL_BIT_FIELDS___H
