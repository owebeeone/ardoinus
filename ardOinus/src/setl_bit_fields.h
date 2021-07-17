/**
 * A generic bit fields library.
 * 
 */

#ifndef SETL_BIT_FIELDS___H
#define SETL_BIT_FIELDS___H

#include "setl_cat_tuples.h"
#include "setl_system.h"
#include "setl_integers.h"
#include "setlx_cstddef.h"
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
 * True if tuple contains T.
 */
template <typename T, typename w_Tuple>
struct has_type;

template <typename T>
struct has_type<T, std::tuple<>> {
  static constexpr bool value = false;
};

template <typename T, typename U, typename... Ts>
struct has_type<T, std::tuple<U, Ts...>> {
  static constexpr bool value = has_type<T, std::tuple<Ts...>>::value;
};

template <typename T, typename... Ts>
struct has_type<T, std::tuple<T, Ts...>> {
  static constexpr bool value = true;
};

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
  template <template <typename...MT> typename Other>
  using apply = Other<MS...>;

  /// Applies a template to the set of MaskShift operations with an associated
  /// mask and shift operations.
  template <
    typename Ta, 
    Ta w_mask, 
    int w_shift, 
    template <typename Tb, Tb v_mask, int v_shift, typename...MT> typename Other>
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
 * Generic "Not Applicable" value.
 * If used in bit positions, it indicates the bit is not used in the bitfield.
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

static_assert(Max<1, 2>::value == 2, "Max calculation is wrong.");
static_assert(Max<2, 1>::value == 2, "Max calculation is wrong.");
static_assert(Max<1, 1>::value == 1, "Max calculation is wrong.");

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
  template <typename T, template <typename U, unsigned...wNs> typename Func>
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
 * Provides the unsigned type has a size greater than all the given types.
 * Also works for a std::tuple of types.
 */

template <typename...T>
struct UnsignedType {
  using type = typename setl::UnsignedTypes::FindSize<Max<sizeof(T)...>::value>::type;
};

template <typename...T>
struct UnsignedType<std::tuple<T...>> {
  using type = typename  setl::UnsignedTypes::FindSize<Max<sizeof(T)...>::value>::type;
};

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
struct ApplyMaskShift<MaskShift<T, ~(T()), 0>> {
  static constexpr T in_mask = ~(T());
  static constexpr T out_mask = ~(T());
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

/**
 * The value type for a given Format. This can represent the value 
 * of an MCU register containing potentially many "bit field" values.
 */
template <typename w_FormatType>
struct BitValue {
  using FormatType = w_FormatType;
  using type = typename FormatType::type;

  template <typename w_BitType>
  static constexpr bool contains = FormatType::template contains<w_BitType>;

  type value;
};

/**
 * Describes the allowable operations on a bit field.
 */
enum class BitOps : unsigned {
  ReadOnly,
  WriteOnly,
  ReadWrite
};

/**
 * Provides a distinguising type for Bits types.
 */
template <std::uint64_t w_distinguisher_code, typename T>
struct SemanticType {
  using type = T;
  static constexpr ::uint64_t distinguisher_code = w_distinguisher_code;
};

/**
 * Provides a constant evaluator for a hash code from a string.
 */
inline constexpr std::uint32_t hash(const char* s, unsigned shift = 1) {
  return s[0] ? std::uint32_t(s[0]) ^ shift * hash(s + 1, shift + 1) : 0;
}

template <typename T>
struct GetTypeOfHelper {
  using type = T;
};

template <std::uint64_t w_distinguisher_code, typename T>
struct GetTypeOfHelper<SemanticType<w_distinguisher_code, T>> {
  using type = T;
};

template <typename T>
using GetTypeOf = typename GetTypeOfHelper<T>::type;

template <BitOps w_ops, typename T, unsigned...bits>
struct Bits {
  static constexpr BitOps ops{ w_ops };
  using type = T;
  using Sequence = UintList<bits...>;
  template <typename UT>
  using ShiftMaskInfo = GroupMaskShifts<UT, bits...>;

  Bits() = default;
  explicit Bits(const type& value)
    : value{value}
  {}

  operator type() {
    return value;
  }

  template <typename w_FormatType>
  static type read_from(const BitValue<w_FormatType>& value) {

    using unsigned_type = typename UnsignedType<w_FormatType::type, type>::type;

    using applier = typename Bits::template ShiftMaskInfo<unsigned_type>::group::template apply<ApplyMaskShift>;
    return static_cast<type>(
      applier::convert(static_cast<unsigned_type>(value.value)));
  }

  template <typename w_FormatType>
  void read_value(const BitValue<w_FormatType>& value) {
    this->value = read_from(value);
  }

  // Instantiations of this class contain the value read or written.
  type value{};
};

template <typename T, unsigned...bits>
struct BitsRO : Bits<BitOps::ReadOnly, GetTypeOf<T>, bits...> {
  using super = Bits<BitOps::ReadOnly, GetTypeOf<T>, bits...>;
  using type = GetTypeOf<T>;
  using outer_type = T;

  BitsRO() = default;

  BitsRO(const type& value)
    : super{ value }
  {}

  template <typename w_FormatType>
  BitsRO(const BitValue<w_FormatType>& value)
    : super{ super::read_from(value) }
  {
    static_assert(w_FormatType::template contains<BitsRO>,
      "Cannot assign value not containing result type");
  }

  template <typename w_FormatType>
  BitsRO& operator=(const BitValue<w_FormatType>& value) {
    static_assert(w_FormatType::template contains<BitsRO>,
      "Cannot assign value not containing result type");
    this->read_value(value);
    return *this;
  }
};

template <typename T, unsigned...bits>
struct BitsWO : Bits<BitOps::WriteOnly, GetTypeOf<T>, bits...> {
  using super = Bits<BitOps::WriteOnly, GetTypeOf<T>, bits...>;
  using type = GetTypeOf<T>;
  using outer_type = T;

  BitsWO() = default;

  BitsWO(const type& value)
    : super{ value }
  {}
};

template <typename T, unsigned...bits>
struct BitsRW : Bits<BitOps::ReadWrite, GetTypeOf<T>, bits...> {
  using super = Bits<BitOps::ReadWrite, GetTypeOf<T>, bits...>;
  using type = GetTypeOf<T>;
  using outer_type = T;

  BitsRW() = default;

  BitsRW(const type& value)
    : super{value}
  {}

  template <typename w_FormatType>
  BitsRW(const BitValue<w_FormatType>& value)
    : super{ super::read_from(value) }
  {
    static_assert(w_FormatType::template contains<BitsRW>,
      "Cannot assign value not containing result type");
  }

  template <typename w_FormatType>
  BitsRW& operator=(const BitValue<w_FormatType>& value) {
    static_assert(w_FormatType::template contains<BitsRW>,
      "Cannot assign value not containing result type");
    this->read_value(value);
    return *this;
  }
};


// Create list of types from tuple of Bits types.
template <typename...Bs>
struct TypesOfBits;

template <>
struct TypesOfBits<> {
  using type = std::tuple<>;
};

template <typename T, typename...Ts>
struct TypesOfBits<T, Ts...> {
  using type = cat_tuples_t<
      std::tuple<typename T::type>, 
      typename TypesOfBits<Ts...>::type>;
};

template <typename w_UnsignedType, typename w_BitsType>
struct BitTypeAppliers {
  using unsigned_type = w_UnsignedType;
  using BitType = w_BitsType;

  using applier = typename BitType
    ::template ShiftMaskInfo<unsigned_type>::group
    ::template apply<ApplyMaskShift>;

  using inv_applier = typename BitType
    ::template ShiftMaskInfo<unsigned_type>::inverse_group
    ::template apply<ApplyMaskShift>;
};

template <typename w_UnsignedType, 
          typename w_FormatType, 
          typename...w_BitsTypes>
struct BitTypesTraitsHelper;

template <typename w_UnsignedType, typename w_FormatType>
struct BitTypesTraitsHelper<w_UnsignedType, w_FormatType> {
  using FormatType = w_FormatType;
  using unsigned_type = w_UnsignedType;

  static constexpr bool all_contained = true;

  static constexpr unsigned_type in_mask = { 0 };

  static constexpr unsigned_type collision_mask{ 0 };
};

template <typename w_UnsignedType, 
          typename w_FormatType, 
          typename w_BitsType, 
          typename...w_BitsTypes>
struct BitTypesTraitsHelper<
    w_UnsignedType, w_FormatType, w_BitsType, w_BitsTypes...> {
  using BitType = w_BitsType;
  using FormatType = w_FormatType;
  using unsigned_type = w_UnsignedType;
  using appliers = BitTypeAppliers<unsigned_type, BitType>;
  static constexpr bool contained = w_FormatType::template contains<w_BitsType>;

  /// Are all w_BitsTypes are specified in FormatType. 
  static constexpr bool all_contained =
    contained
    && BitTypesTraitsHelper<unsigned_type, FormatType, w_BitsTypes...>::all_contained;

  // This only contribututes to in_mask if it is contained.
  static constexpr auto this_in_mask = 
      (contained ? appliers::applier::in_mask : unsigned_type{ 0 });

  /// The mask of all the incoming bittypes.
  static constexpr unsigned_type in_mask = 
    this_in_mask
    | BitTypesTraitsHelper<unsigned_type, FormatType, w_BitsTypes...>::in_mask;

  /// If non zero there are some w_BitsTypes writing to the same bits.
  static constexpr unsigned_type collision_mask = (this_in_mask
    & BitTypesTraitsHelper<unsigned_type, FormatType, w_BitsTypes...>::in_mask)
    | BitTypesTraitsHelper<unsigned_type, FormatType, w_BitsTypes...>::collision_mask;
};

/**
 * Provides masks and converters for the format/bittypes combination.
 */
template <typename w_FormatType, typename...w_BitsTypes>
struct BitTypesTraits {
  using bits_types = typename TypesOfBits<w_BitsTypes...>::type;
  using all_types = cat_tuples_t<std::tuple<typename w_FormatType::type>, bits_types>;
  using unsigned_type = typename UnsignedType<all_types>::type;

  using traits = BitTypesTraitsHelper<unsigned_type, w_FormatType, w_BitsTypes...>;
};


template <typename w_UnsignedType, typename w_FormatType, typename...w_BitsTypes>
struct BitTypesEvaluatorHelper;

template <typename w_UnsignedType, typename w_FormatType>
struct BitTypesEvaluatorHelper<w_UnsignedType, w_FormatType> {
  using unsigned_type = w_UnsignedType;

  static constexpr unsigned_type evaluate() {
    return unsigned_type{ 0 };
  }
};

template <typename w_UnsignedType, typename w_FormatType, typename w_BitsType, typename...w_BitsTypes>
struct BitTypesEvaluatorHelper<w_UnsignedType, w_FormatType, w_BitsType, w_BitsTypes...> {

  using traits = typename BitTypesTraits<w_FormatType, w_BitsType, w_BitsTypes...>::traits;
  using unsigned_type = typename traits::unsigned_type;
  static constexpr bool contained = w_FormatType::template contains<w_BitsType>;

  static constexpr unsigned_type evaluate(w_BitsType bitValue, w_BitsTypes...bitsValues) {
    return (contained 
      ? traits::appliers::inv_applier::convert(static_cast<unsigned_type>(bitValue.value))
      : unsigned_type{0})
      | BitTypesEvaluatorHelper<w_UnsignedType, w_FormatType, w_BitsTypes...>::evaluate(bitsValues...);
  }
};

template <bool allow_unreferenced, 
          typename w_FormatType,
          typename...w_BitsTypes>
struct BitTypesEvaluator {

  using bits_traits = BitTypesTraits<w_FormatType, w_BitsTypes...>;
  using traits = typename bits_traits::traits;
  using unsigned_type = typename traits::unsigned_type;
  using helper = BitTypesEvaluatorHelper<unsigned_type, w_FormatType, w_BitsTypes...>;

  static_assert(allow_unreferenced || traits::all_contained,
    "The target value does not contain all the bit values provided.");

  static_assert(!traits::collision_mask,
    "The provided bit values have colliding bit positions in the target.");

  static constexpr unsigned_type evaluate(w_BitsTypes...bitsValues) {
    return helper::evaluate(bitsValues...);
  }
};

// Specialization allowing w_BitsTypes to be a tuple.
template <bool allow_unreferenced,
  typename w_FormatType,
  typename...w_BitsTypes>
  struct BitTypesEvaluator<allow_unreferenced, w_FormatType, std::tuple<w_BitsTypes...>>
      : BitTypesEvaluator<allow_unreferenced, w_FormatType, w_BitsTypes...> {
};

/**
 * Assigns multiple bitfields from a single value.
 */
template <typename...w_Proxies>
struct Assigner;

template <typename w_Proxy>
struct Assigner<w_Proxy> {
  using ProxyType = w_Proxy;

  Assigner(const Assigner& rhs) = default;
  Assigner& operator=(const Assigner& rhs) = delete;

  Assigner(w_Proxy& proxy)
    : proxy{&proxy}
  {}

  template <typename w_FormatType, typename T>
  void Assign(const T& value) const {
    static_assert(w_FormatType::template contains<ProxyType>,
      "Cannot assign value not containing result type");
    using appliers = BitTypeAppliers<T, ProxyType>;
    proxy->value = static_cast<typename ProxyType::type>(appliers::applier::convert(value));
  }

  template <typename w_FormatType>
  const Assigner& operator=(const BitValue<w_FormatType>& value) const {
    static_assert(w_FormatType::template contains<ProxyType>,
      "Cannot assign value not containing result type");
    using FormatTypeType = typename w_FormatType::type;
    using TypesOfBitsType = typename TypesOfBits<w_Proxy>::type;
    using unsigned_type = typename UnsignedType<
      cat_tuples_t<std::tuple<FormatTypeType>, TypesOfBitsType>>::type;
    Assign<w_FormatType>(static_cast<unsigned_type>(value.value));
    return *this;
  }

  /**
   * AssignSparse will assign only the fields associated with the format/register
   * provided.
   */
  template <typename w_FormatType, typename w_unsigned_type>
  void AssignSparse(const w_unsigned_type& value) const {
    if (w_FormatType::template contains<ProxyType>) {
      using appliers = BitTypeAppliers<w_unsigned_type, ProxyType>;
      proxy->value = static_cast<typename ProxyType::type>(appliers::applier::convert(value));
    }
  }

  template <typename w_FormatType>
  const Assigner& AssignSparse(const BitValue<w_FormatType>& value) const {
    using FormatTypeType = typename w_FormatType::type;
    using TypesOfBitsType = typename TypesOfBits<ProxyType>::type;

    using unsigned_type = typename UnsignedType<
      cat_tuples_t<std::tuple<FormatTypeType>, TypesOfBitsType>>::type;
    AssignSparse<w_FormatType, unsigned_type>(static_cast<unsigned_type>(value.value));
    return *this;
  }

  ProxyType* const proxy;
};

template <typename w_Proxy, typename...w_Proxies>
struct Assigner<w_Proxy, w_Proxies...> : Assigner<w_Proxies...> {
  using ProxyType = w_Proxy;

  Assigner(const Assigner& rhs) = default;
  Assigner& operator=(const Assigner& rhs) = delete;

  Assigner(w_Proxy& proxy, w_Proxies&... proxies)
    : Assigner<w_Proxies...>{proxies...}, proxy{&proxy}
  {
  }

  template <typename w_FormatType, typename T>
  void Assign(const T& value) const {
    static_assert(w_FormatType::template contains<ProxyType>,
      "Cannot assign value not containing result type");
    const Assigner<w_Proxies...>& super{ *this };
    super.template Assign<w_FormatType, T>(value);

    using appliers = BitTypeAppliers<T, ProxyType>;
    proxy->value = static_cast<typename ProxyType::type>(appliers::applier::convert(value));
  }

  template <typename w_FormatType>
  const Assigner& operator=(const BitValue<w_FormatType>& value) const {
    static_assert(w_FormatType::template contains<ProxyType>,
      "Cannot assign value not containing result type");

    using FormatTypeType = typename w_FormatType::type;
    using TypesOfBitsType = typename TypesOfBits<w_Proxy, w_Proxies...>::type;
    using unsigned_type = typename UnsignedType<
      cat_tuples_t<std::tuple<FormatTypeType>, TypesOfBitsType>>::type;
    Assign<w_FormatType, unsigned_type>(static_cast<unsigned_type>(value.value));
    return *this;
  }

  /**
   * AssignSparse will assign only the fields associated with the format/register
   * provided.
   */
  template <typename w_FormatType, typename T>
  void AssignSparse(const T& value) const {
    const Assigner<w_Proxies...>& super{ *this };
    super.template AssignSparse<w_FormatType, T>(value);
    if (w_FormatType::template contains<ProxyType>) {
      using appliers = BitTypeAppliers<T, ProxyType>;
      proxy->value = static_cast<typename ProxyType::type>(appliers::applier::convert(value));
    }
  }

  template <typename w_FormatType>
  const Assigner& AssignSparse(const BitValue<w_FormatType>& value) const {
    using FormatTypeType = typename w_FormatType::type;
    using TypesOfBitsType = typename TypesOfBits<w_Proxy, w_Proxies...>::type;
    using unsigned_type = typename UnsignedType<
      cat_tuples_t<std::tuple<FormatTypeType>, TypesOfBitsType>>::type;
    AssignSparse<w_FormatType, unsigned_type>(static_cast<unsigned_type>(value.value));
    return *this;
  }

  ProxyType* const proxy;
};

template <typename...w_Proxies>
Assigner<w_Proxies...> Assign(w_Proxies&... proxies) {
  return Assigner<w_Proxies...>(proxies...);
}

template <typename T, typename...w_BitTypes>
struct Format {
  using type = T;
  using bit_types = std::tuple<w_BitTypes...>;

  template <typename w_BitType>
  static constexpr bool contains = has_type<w_BitType, bit_types>::value;

  // TODO: Check that all bit_types have bit positions within size of T.
};

template <typename...w_BitTypes>
struct BitFields {
  using bit_types = std::tuple<w_BitTypes...>;

  template <typename w_BitType>
  static constexpr bool contains = has_type<w_BitType, bit_types>::value;

  template <typename T>
  using FormatOf = Format<T, w_BitTypes...>;
};

/**
 * MCU io i/o accessor for writing/reading MCU control registers.
 */
template <typename T, ptrdiff_t w_addrx>
struct McuRegister {
  static constexpr ptrdiff_t addrx{ w_addrx };
  using nv_type = typename std::remove_cv<T>::type;
  using type = volatile nv_type;

  inline static type* ptr() {
    return reinterpret_cast<type*>(addrx);
  }

  inline static void set(nv_type value) {
    *ptr() = value;
  }

  inline static void set_mask(nv_type value, nv_type mask) {
    *ptr() = (*ptr() & ~mask) | value;
  }

  inline static nv_type get() {
    return *ptr();
  }
};

/**
 * MCU io i/o accessor for writing/reading MCU control registers.
 */
template <typename T, ptrdiff_t w_addrx, unsigned Size, unsigned char* const& w_io_memory>
struct DebugMcuRegister {
  static constexpr ptrdiff_t addrx{ w_addrx };
  static_assert(
      w_addrx + sizeof(T) <= Size,
      "MCU register offset is out of bounds of provided debug memory array.");
  using nv_type = typename std::remove_cv<T>::type;

#pragma pack(push, 1)
  // As this is for debugging, it may not be aligned correctly for the target CPU
  // so we use a packed wrapper which will use unaligned load/store instructions.
  struct Wrapper {
    nv_type value;
  };
#pragma pack(pop)

  inline static Wrapper* ptr() {
    return reinterpret_cast<Wrapper*>(addrx + w_io_memory);
  }

  inline static void set(nv_type value) {
    ptr()->value = value;
  }
  
  inline static void set_mask(nv_type value, nv_type mask) {
    ptr()->value = (ptr()->value & ~mask) | value;
  }

  inline static nv_type get() {
    return ptr()->value;
  }
};

/**
 * Defines an MCU register. Provides register read and write functions for
 * the bitfields defined in the bitfields format.
 */
template <typename w_BitFields, 
          typename w_Register, 
          template <typename T, ptrdiff_t u_addrx> typename RegisterType = McuRegister>
struct IoRegister {
  using register_def = w_Register;
  using type = typename register_def::type;
  using FormatType = typename w_BitFields::template FormatOf<type>;
  static constexpr ptrdiff_t addrx = register_def::addr;
  using ioregister = RegisterType<type, addrx>;

  static BitValue<FormatType> Read() {
    return Read(ioregister::get());
  }

  static BitValue<FormatType> Read(const type& value) {
    return BitValue<FormatType>{value};
  }

  /**
   * Perform a write operation with the given bit field values by first reading
   * the register (if any bits will survive the write) and then writing the new
   * values in a single write.
   */
  template <bool allow_unreferenced, typename...BitsTypes>
  static void ReadModifyWriteEx(BitsTypes...bitsValues) {
    using Evaluator = BitTypesEvaluator<allow_unreferenced, FormatType, BitsTypes...>;
    auto new_bits = Evaluator::evaluate(bitsValues...);
    auto mask = Evaluator::traits::in_mask;
    if (~mask) {
      ioregister::set_mask(static_cast<type>(new_bits), static_cast<type>(mask));
    } else {
      ioregister::set(static_cast<type>(new_bits));
    }
    return;
  }

  /**
   * Perform a write operation with the given bit field values by first reading
   * the register (if any bits will survive the write) and then writing the new
   * values in a single write.
   */
  template <typename...BitsTypes>
  static void ReadModifyWrite(BitsTypes...bitsValues) {
    ReadModifyWriteEx<false>(bitsValues...);
  }

  /**
   * Perform a write operation with the given bit field values with the provided
   * default value.
   */
  template <typename...BitsTypes>
  static void Write(
      const BitValue<FormatType>& defaultBits, const BitsTypes&...bitsValues) {
    using Evaluator = BitTypesEvaluator<false, FormatType, BitsTypes...>;
    auto new_bits = Evaluator::evaluate(bitsValues...);
    auto mask = Evaluator::traits::in_mask;
    if (~mask) {
      ioregister::set(static_cast<type>(new_bits) 
          | (static_cast<type>(~mask) & defaultBits.value));
    } else {
      ioregister::set(static_cast<type>(new_bits));
    }
  }

  /**
   * Perform a write operation with the given bit field values.
   */
  template <typename...BitsTypes>
  static void Write(const BitsTypes&...bitsValues) {
    using Evaluator = BitTypesEvaluator<false, FormatType, BitsTypes...>;
    auto new_bits = Evaluator::evaluate(bitsValues...);
    auto mask = Evaluator::traits::in_mask;
    ioregister::set(static_cast<type>(new_bits));
  }

  /**
   * Evaluates a new value from the given bitfields and default bits.
   */
  template <typename...BitsTypes>
  static BitValue<FormatType> Evaluate(
      const BitValue<FormatType>& defaultBits, BitsTypes...bitsValues) {
    using Evaluator = BitTypesEvaluator<false, FormatType, BitsTypes...>;
    auto new_bits = Evaluator::evaluate(bitsValues...);
    auto mask = Evaluator::traits::in_mask;
    if (~mask) {
      return BitValue<FormatType>{static_cast<type>(new_bits)
        | (static_cast<type>(~mask) & defaultBits.value)};
    }
    return BitValue<FormatType>{static_cast<type>(new_bits)};
  }
};


// For FindRegisterForField.
namespace nfp {
template <typename w_BitField, typename...w_Registers>
struct FindRegisterForFieldHelper;

template <typename w_BitField>
struct FindRegisterForFieldHelper<w_BitField> {
  using type = void;
  static constexpr bool value = false;
};

template <typename w_BitField, typename w_Register, typename...w_Registers>
struct FindRegisterForFieldHelper<w_BitField, w_Register, w_Registers...> {
private:
  static constexpr bool selected = w_Register::FormatType::template contains<w_BitField>;
public:
  using type = typename std::conditional<selected,
    w_Register,
    FindRegisterForFieldHelper<w_BitField, w_Registers...>>::type;
  static constexpr bool value = std::conditional<selected,
    std::true_type,
    FindRegisterForFieldHelper<w_BitField, w_Registers...>>::type::value;
};
}  // namespace nfp

/**
 * Find the register in the given tuple that supports the given bit field.
 * value is true if the supporting register is found.
 */
template <typename w_BitField, typename w_RegistersTuple>
struct FindRegisterForField;

template <typename w_BitField, typename...w_Registers>
struct FindRegisterForField<w_BitField, std::tuple<w_Registers...>> {
private:
  using HelperType = nfp::FindRegisterForFieldHelper<w_BitField, w_Registers...>;
public:
  // True if the corresponding register for bitfield was found.
  static constexpr bool value = HelperType::value;
  /// Register that supports the bitfield.
  using type = typename HelperType::type;
};

template <typename...Rs>
struct RegisterSelectorHelper;

template <>
struct RegisterSelectorHelper<> {

};

template <typename R, typename...Rs>
struct RegisterSelectorHelper<R, Rs...> {
  // ?? Collect all the bitfields for R.
};

namespace nfp {

template <bool do_not_assert, typename Bs, typename Rs>
struct BitsToRegistersChecker;

template <bool do_not_assert, typename...Rs>
struct BitsToRegistersChecker<do_not_assert, std::tuple<>, std::tuple<Rs...>> {
  static constexpr bool value = true;
};

template <bool do_not_assert, typename B, typename...Bs, typename...Rs>
struct BitsToRegistersChecker<do_not_assert, std::tuple<B, Bs...>, std::tuple<Rs...>> {
  using MapperForRest = BitsToRegistersChecker<do_not_assert, std::tuple<Bs...>, std::tuple<Rs...>>;
  using FinderResult = FindRegisterForField<B, std::tuple<Rs...>>;
  static constexpr bool value = MapperForRest::value && FinderResult::value;

  static_assert(
    do_not_assert || FinderResult::value, 
    "Bitfield was not contained in any of the registers provided.");
};

template <typename R, typename...Bs>
struct RegisterToBitsFinder;

template <typename R>
struct RegisterToBitsFinder<R> : std::false_type {};

template <typename R, typename B, typename...Bs>
struct RegisterToBitsFinder<R, B, Bs...> {
  using type = bool;
  static constexpr type value = R::FormatType::template contains<B>
      || RegisterToBitsFinder<R, Bs...>::value;
};

} // Namespace nfp

/**
 * Support bitfield operations across a number of registers, automatically
 * choosing the correct register for each associated bitfield.
 */
template <typename Tuple>
struct RegisterSelector;

template <>
struct RegisterSelector<std::tuple<>> {
  template <typename Tuple>
  friend struct RegisterSelector;
 private:
  template <typename...BitsTypes>
  static void ReadModifyWriteImpl(BitsTypes...bitsValues) {
  }
};

namespace nfp { // For internal use only. This API can change.

// Helper class to find and select operations for registers provided.
template <typename Rt, typename Bt, bool selected>
struct RegisterSelectorHelper;

template <typename R0, typename...Bs>
struct RegisterSelectorHelper<std::tuple<R0>, std::tuple<Bs...>, false> {
  // Last register's RMW function must exist.
  static void ReadModifyWrite(Bs...bitsValues) {
  }

  // Last register's assign function must exist.
  static void Read(Bs&...bitsValues) {
  }
};

template <typename R0, typename...Bs>
struct RegisterSelectorHelper<std::tuple<R0>, std::tuple<Bs...>, true> {
  static void ReadModifyWrite(Bs...bitsValues) {
    R0::template ReadModifyWriteEx<true>(bitsValues...);
  }

  static void Read(Bs&...bitsValues) {
    Assigner<Bs...>(bitsValues...).AssignSparse(R0::Read());
  }
};

// If a register does not participate with the given bitfields, then
// no fuctions to read or or write are provided.
template <typename R0, typename R1, typename...Rs, typename...Bs>
struct RegisterSelectorHelper<std::tuple<R0, R1, Rs...>, std::tuple<Bs...>, false>
  : RegisterSelectorHelper<std::tuple<R1, Rs...>,
                           std::tuple<Bs...>,
                           RegisterToBitsFinder<R1, Bs...>::value> {
};

template <typename R0, typename R1, typename...Rs, typename...Bs>
struct RegisterSelectorHelper<std::tuple<R0, R1, Rs...>, std::tuple<Bs...>, true>
  : RegisterSelectorHelper<std::tuple<R1, Rs...>,
                           std::tuple<Bs...>,
                           RegisterToBitsFinder<R1, Bs...>::value> {

  using super = RegisterSelectorHelper<std::tuple<R1, Rs...>,
    std::tuple<Bs...>,
    RegisterToBitsFinder<R1, Bs...>::value>;

  static void ReadModifyWrite(Bs...bitsValues) {
    R0::template ReadModifyWriteEx<true>(bitsValues...);
    super::ReadModifyWrite(bitsValues...);
  }

  static void Read(Bs&...bitsRefs) {
    // Assign the bit fields for this register.
    Assigner<Bs...>(bitsRefs...).AssignSparse(R0::Read());
    // Assign the bit fields for the next available register.
    super::Read(bitsRefs...);
  }
};

}  // namespace nfp

/**
 * Provides multi-register operations. Sometimes bitfields are defined in
 * different registers for semantically the same bitfields. This allows
 * client code to specify all the possible destination registers and the
 * required bitfield values to operate on. Only the registers whose bitfields
 * are present will have their values changed.
 */
template <typename R, typename...Rs>
struct RegisterSelector<std::tuple<R, Rs...>> {
 private:
  template <typename...BitsTypes>
  static void ReadModifyWriteImpl(BitsTypes...bitsValues) {
    static constexpr bool contained = nfp::RegisterToBitsFinder<R, BitsTypes...>::value;
    using RSHelper = nfp::RegisterSelectorHelper<
        std::tuple<R, Rs...>, std::tuple<BitsTypes...>, contained>;

    // RSHelper::ReadModifyWrite functions are only provided for registers whose
    // bitfields are present in the parameters.
    RSHelper::ReadModifyWrite(bitsValues...);
  }
 public:
  using Registers = std::tuple<R, Rs...>;

  /**
   * Perform a write operation with the given bit field values by first reading
   * the register (if any bits will survive the write) and then writing the new
   * values in a single write.
   */
  template <typename...BitsTypes>
  static void ReadModifyWrite(BitsTypes...bitsValues) {
    // Make sure all bits are used.
    static_assert(
      nfp::BitsToRegistersChecker<
          false, std::tuple<BitsTypes...>, std::tuple<R, Rs...>>::value,
      "A bitfield was not contained in any of the registers provided.");
    ReadModifyWriteImpl(bitsValues...);
  }

  /**
   * Read the passed in bit field values from the selected registers.
   * Only the registers whose associated bitfields will be read and only once.
   */
  template <typename...BitsTypes>
  static void Read(BitsTypes&...bitsRefs) {
    // Make sure all bit types can be read.
    static_assert(
      nfp::BitsToRegistersChecker<
      false, std::tuple<BitsTypes...>, std::tuple<R, Rs...>>::value,
      "Bitfield was not contained in any of the registers provided.");

    static constexpr bool contained = nfp::RegisterToBitsFinder<R, BitsTypes...>::value;
    using RSHelper = nfp::RegisterSelectorHelper<
      std::tuple<R, Rs...>, std::tuple<BitsTypes...>, contained>;
    RSHelper::Read(bitsRefs...);
  }
};

/**
 * Provides a utility to read a bitfield from a register selection..
 */
template <typename w_BitField>
struct ApplierReader {
  using BitField = w_BitField;

  template <typename Register>
  static BitField read() {
    BitField value;
    Register::Read(value);
    return value;
  }
};

// Trap any attempts to read from a void bitfield.
template <>
struct ApplierReader<void> {
  using BitField = void;

  template <typename Register>
  static void read() {
  }
};

/**
 * Defines a bitfield and a corrsponding value.
 */
template <typename w_BitField, typename w_BitField::type w_value>
struct ApplierValue {
  template <typename...w_Appliers>
  friend struct Appliers;
  template <typename v_BitField, typename v_BitField::type v_value, typename v_Register>
  friend struct Applier;

  using BitField = w_BitField;
  static constexpr typename BitField::type value = w_value;

 private:
  template <typename Register>
  static void apply() {
    Register::ReadModifyWrite(BitField{ w_value });
  }
};

// Tools for value applier.
namespace nfp {

// Convert a list of ApplierValue types to a list of bitfields.
template <typename...AVs>
struct ToBitFields;

template <>
struct ToBitFields<> {
  using type = std::tuple<>;
};

template <typename AV, typename...AVs>
struct ToBitFields<AV, AVs...> {
  using Rest = ToBitFields<AVs...>;
  using type = setl::cat_tuples_t<
      std::tuple<typename AV::BitField>, typename Rest::type>;
};

// Collects all the ApplierValue types specific to register R.
template <typename AVT, typename R>
struct ApplierValuesRegHelper;

template <typename R>
struct ApplierValuesRegHelper<std::tuple<>, R> {
  using AVsForRegister = std::tuple<>;
};

template <typename AV, typename...AVs, typename R>
struct ApplierValuesRegHelper<std::tuple<AV, AVs...>, R> {
  using Rest = ApplierValuesRegHelper<std::tuple<AVs...>, R>;
  static constexpr bool contains = R::FormatType::template contains<typename AV::BitField>;
  using AVsForRegister = std::conditional_t<
      contains,
      setl::cat_tuples_t<std::tuple<AV>, typename Rest::AVsForRegister>,
      typename Rest::AVsForRegister>;
};


template <typename w_unsigned_type, typename w_FormatType, typename...AVs>
struct ApplierValueEvaluator;

template <typename w_unsigned_type, typename w_FormatType>
struct ApplierValueEvaluator<w_unsigned_type, w_FormatType> {
  using unsigned_type = w_unsigned_type;
  static constexpr unsigned_type value = unsigned_type{0};
};


template <typename w_unsigned_type, typename w_FormatType, typename AV, typename...AVs>
struct ApplierValueEvaluator<w_unsigned_type, w_FormatType, AV, AVs...> {
  using unsigned_type = w_unsigned_type;
  using FormatType = w_FormatType;
  using Rest = ApplierValueEvaluator<unsigned_type, FormatType, AVs...>;
  using Bitfields = typename ToBitFields<AV, AVs...>::type;
  using Evaluator = BitTypesEvaluator<false, FormatType, Bitfields>;
  using traits = typename Evaluator::traits;
  using inv_applier = typename traits::appliers::inv_applier;

  static constexpr unsigned_type this_value = inv_applier::convert(
    static_cast<unsigned_type>(AV::value));

  static constexpr unsigned_type value = this_value | Rest::value;
};

template <typename AVT, typename R, typename w_Base>
struct ApplierValuesForRegister;

template <typename R, typename w_Base>
struct ApplierValuesForRegister<std::tuple<>, R, w_Base> {
  using ApplierT = w_Base;
};

enum class AVsApplierType {
  partial_write,
  full_mask,
  null_op
};

// Default case for non zero and non all set bits mask.
template<
    typename w_Register, 
    typename w_Base, 
    typename w_register_type,
    w_register_type w_new_bits,
    w_register_type w_in_mask,
    AVsApplierType w_applier_type>
struct AVsApplier : w_Base {
  using Register = w_Register;
  using Base = w_Base;
  using register_type = w_register_type;
  static constexpr w_register_type new_bits = w_new_bits;
  static constexpr w_register_type in_mask = w_in_mask;
  static void apply() {
    Base::apply();
    // Uses the read/modify write API on the register.
    Register::ioregister::set_mask(
      static_cast<register_type>(new_bits), static_cast<register_type>(in_mask));
  }
};

// All bits being written, no point in doing a read.
template<
    typename w_Register, 
    typename w_Base, 
    typename w_register_type,
    w_register_type w_new_bits,
    w_register_type w_in_mask>
struct AVsApplier<
    w_Register, 
    w_Base, 
    w_register_type, 
    w_new_bits, 
    w_in_mask, 
    AVsApplierType::full_mask> : w_Base {
  using Register = w_Register;
  using Base = w_Base;
  using register_type = w_register_type;
  static constexpr w_register_type new_bits = w_new_bits;
  static constexpr w_register_type in_mask = w_in_mask;
  static void apply() {
    Base::apply();
    Register::ioregister::set(static_cast<register_type>(new_bits));
  }
};

// Register is not being accessed hence no apply() function.
template<
    typename w_Register, 
    typename w_Base, 
    typename w_register_type,
    w_register_type w_new_bits,
    w_register_type w_in_mask>
struct AVsApplier<
    w_Register, 
    w_Base, 
    w_register_type, 
    w_new_bits, 
    w_in_mask, 
    AVsApplierType::null_op> : w_Base {
  using Register = w_Register;
  using Base = w_Base;
  using register_type = w_register_type;
  static constexpr w_register_type new_bits = w_new_bits;
  static constexpr w_register_type in_mask = w_in_mask;
};


template <typename AV, typename...AVs, typename R, typename w_Base>
struct ApplierValuesForRegister<std::tuple<AV, AVs...>, R, w_Base> {
  using Base = w_Base;
  using Bitfields = typename ToBitFields<AV, AVs...>::type;
  using Register = R;
  using FormatType = typename Register::FormatType;
  using Evaluator = BitTypesEvaluator<false, FormatType, Bitfields>;
  using unsigned_type = typename Evaluator::unsigned_type;
  using ApplierEvaluator = ApplierValueEvaluator<
      unsigned_type, FormatType, AV, AVs...>;
  static constexpr unsigned_type new_bits = ApplierEvaluator::value;
  static constexpr unsigned_type in_mask = Evaluator::traits::in_mask;
  using register_type = typename Register::type;

  static constexpr AVsApplierType op = 
    (in_mask == register_type{0}) ? AVsApplierType::null_op
    : (in_mask == ~register_type{0}) ? AVsApplierType::full_mask
    : AVsApplierType::partial_write;


  using ApplierT = AVsApplier<Register, Base, register_type, new_bits, in_mask, op>;
};

// Appliers chain via inheritance and only those Appliers containing
// values to apply implement the apply() method. This means the compiler
// only needs to generate apply() functions for registers that have
// mutating values.
struct BaseApplier {
  // The applier that does nothing.
  struct ApplierT {
    static void apply() {
    }
  };
};

template <typename AVT, typename RT>
struct ApplierValuesRegApplier;

template <typename...AVs>
struct ApplierValuesRegApplier<std::tuple<AVs...>, std::tuple<>> {

  using ApplierT = BaseApplier::ApplierT;
};


template <typename...AVs, typename R, typename...Rs>
struct ApplierValuesRegApplier<std::tuple<AVs...>, std::tuple<R, Rs...>> {
  using RegAvs = ApplierValuesRegHelper<std::tuple<AVs...>, R>;
  using RegAvsTuple = typename RegAvs::AVsForRegister;
  //using Bitfields = typename ToBitFields<AVs...>::type;
  //static_assert(
  //  nfp::BitsToRegistersChecker<false, BitFields, std::tuple<R, Rs...>>::value,
  //  "A bitfield was not contained in any of the registers provided.");

  using Rest = ApplierValuesRegApplier<std::tuple<AVs...>, std::tuple<Rs...>>;
  using BaseApplier = typename Rest::ApplierT;

  using ApplierT = typename ApplierValuesForRegister<
      RegAvsTuple, R, BaseApplier>::ApplierT;
};

}  // namespace nfp

/**
 * Appliers provides a template class that may be used to perform a number
 * bitfield operations.
 */
template <typename...w_ApplierValues>
struct ApplierValues {
  using ApplierValueTypes = std::tuple<w_ApplierValues...>;

  template <typename w_RegisterSelector>
  static void apply() {
    using Registers = typename w_RegisterSelector::Registers;
    using AVApplier = nfp::ApplierValuesRegApplier<ApplierValueTypes, Registers>;
    using BitFields = typename nfp::ToBitFields<w_ApplierValues...>::type;
    static_assert(
      nfp::BitsToRegistersChecker<false, BitFields, Registers>::value,
      "A bitfield was not contained in any of the registers provided.");
    AVApplier::ApplierT::apply();
  }
};

/**
 * Appliers provides a template class that may be used to perform a number
 * bitfield operations.
 */
template <typename...w_Appliers>
struct Appliers;

/**
 * Applied the given bit field in a ReadModifyWrite.
 */
template <typename w_BitField, typename w_BitField::type w_value, typename w_Register>
struct Applier {
  template <typename...w_Appliers>
  friend struct Appliers;

  using ApplierValueType = ApplierValue<w_BitField, w_value>;
  using Register = w_Register;

 private:
  static void apply() {
    ApplierValueType::template apply<Register>();
  }
};

/**
 * Applier taking a set of registers in a tuple. The register selected
 * is the register that supports the given field.
 */
template <typename w_BitField, typename w_BitField::type w_value, typename...w_Registers>
struct Applier<w_BitField, w_value, std::tuple<w_Registers...>> {
  template <typename...w_Appliers>
  friend struct Appliers;

  using Finder = setl::FindRegisterForField<w_BitField, std::tuple<w_Registers...>>;
  static_assert(Finder::value, "Given bitfield is not supported in the given registers.");
  using Register = typename Finder::type;

 private:
  static void apply() {
    Register::ReadModifyWrite(w_BitField{ w_value });
  }
};

template <>
struct Appliers<> {
  template <typename...v_Appliers>
  friend struct Appliers;

  using types = std::tuple<>;
  static void apply() {
  }
};

template <typename w_Applier, typename...w_Appliers>
struct Appliers<w_Applier, w_Appliers...> {
  template <typename...v_Appliers>
  friend struct Appliers;
  friend struct ApplierRunner;

  using types = std::tuple<w_Applier, w_Appliers...>;

private:
  static void apply() {
    w_Applier::apply();
    Appliers<w_Appliers...>::apply();
  }
};

/**
 * Provides "apply" frunctions that execute the given bit Appliers. One of the
 * functions performs a synchronization (memory barrier) as may be needed on some
 * microcontrollers.
 */
struct ApplierRunner {
protected:
  /// Applies the given "Appliers" and performs a sync barrier.
  template <typename w_Appliers>
  static void applySync() {
    setl::System::MemoryBarrier barrier;
    w_Appliers::apply();
  }

  /// Applies the given "Appliers".
  template <typename w_Appliers>
  static void applyNoSync() {
    w_Appliers::apply();
  }
};

}  // namespace setl

#endif  // SETL_BIT_FIELDS___H
