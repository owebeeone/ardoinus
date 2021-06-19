/**
 * A generic bit fields library.
 * 
 */

#ifndef SETL_BIT_FIELDS___H
#define SETL_BIT_FIELDS___H

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
 * Provides the unsigned type has a size greater than all the given types.
 * Also works for a std::tuple of types.
 */

template <typename...T>
struct UnsignedType {
  using type = typename nfp::UnsignedTypes::FindSize<Max<sizeof(T)...>::value>::type;
};

template <typename...T>
struct UnsignedType<std::tuple<T...>> {
  using type = typename  nfp::UnsignedTypes::FindSize<Max<sizeof(T)...>::value>::type;
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
  Bits(const type& value)
    : value{value}
  {}

  operator type() {
    return value;
  }
  template <typename w_FormatType>
  void read_value(const BitValue<w_FormatType>& value) {

    using unsigned_type = typename UnsignedType<w_FormatType::type, type>::type;

    using applier = typename Bits::template ShiftMaskInfo<unsigned_type>::group::template apply<ApplyMaskShift>;
    this->value = static_cast<type>(
      applier::convert(static_cast<unsigned_type>(value.value)));
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
  BitsRW& operator=(const BitValue<w_FormatType>& value) {
    static_assert(w_FormatType::template contains<BitsRW>,
      "Cannot assign value not containing result type");
    this->read_value(value);
    return *this;
  }
};


// Catentate two tuples.
template <typename T, typename U>
struct cat_tuples;

template <typename...Ts, typename...Us>
struct cat_tuples<std::tuple<Ts...>, std::tuple<Us...>> {
  using type = std::tuple<Ts..., Us...>;
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
  using type = typename cat_tuples<
      std::tuple<typename T::type>, 
      typename TypesOfBits<Ts...>::type>::type;
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

  /// All w_BitsTypes are specified in FormatType. 
  static constexpr bool all_contained =
    w_FormatType::template contains<w_BitsType>
    && BitTypesTraitsHelper<unsigned_type, FormatType, w_BitsTypes...>::all_contained;

  /// The mask of all the incoming bittypes.
  static constexpr unsigned_type in_mask = appliers::applier::in_mask
    | BitTypesTraitsHelper<unsigned_type, FormatType, w_BitsTypes...>::in_mask;

  /// If non zero there are some w_BitsTypes writing to the same bits.
  static constexpr unsigned_type collision_mask = (appliers::applier::in_mask
    & BitTypesTraitsHelper<unsigned_type, FormatType, w_BitsTypes...>::in_mask)
    | BitTypesTraitsHelper<unsigned_type, FormatType, w_BitsTypes...>::collision_mask;
};

/**
 * Provides masks and converters for the format/bittypes combination.
 */
template <typename w_FormatType, typename...w_BitsTypes>
struct BitTypesTraits {
  using bits_types = typename TypesOfBits<w_BitsTypes...>::type;
  using all_types = typename cat_tuples<std::tuple<typename w_FormatType::type>, bits_types>::type;
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

  static constexpr unsigned_type evaluate(w_BitsType bitValue, w_BitsTypes...bitsValues) {
    return traits::appliers::inv_applier::convert(static_cast<unsigned_type>(bitValue.value))
      | BitTypesEvaluatorHelper<w_UnsignedType, w_FormatType, w_BitsTypes...>::evaluate(bitsValues...);
  }
};

template <typename w_FormatType, typename...w_BitsTypes>
struct BitTypesEvaluator {

  using bits_traits = BitTypesTraits<w_FormatType, w_BitsTypes...>;
  using traits = typename bits_traits::traits;
  using unsigned_type = typename traits::unsigned_type;
  using helper = BitTypesEvaluatorHelper<unsigned_type, w_FormatType, w_BitsTypes...>;

  static_assert(traits::all_contained, 
    "The target value does not contain all the bit values provided.");

  static_assert(!traits::collision_mask,
    "The provided bit values have colliding bit positions in the target.");

  static constexpr unsigned_type evaluate(w_BitsTypes...bitsValues) {
    return helper::evaluate(bitsValues...);
  }
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
    using unsigned_type = typename UnsignedType<
      cat_tuples<std::tuple<w_FormatType::type>, TypesOfBits<w_Proxy>::type>>::type;
    Assign<w_FormatType>(static_cast<unsigned_type>(value.value));
    return *this;
  }

  ProxyType* proxy;
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
    super.Assign<w_FormatType, T>(value);

    using appliers = BitTypeAppliers<T, ProxyType>;
    proxy->value = static_cast<typename ProxyType::type>(appliers::applier::convert(value));
  }

  template <typename w_FormatType>
  const Assigner& operator=(const BitValue<w_FormatType>& value) const {
    static_assert(w_FormatType::template contains<ProxyType>,
      "Cannot assign value not containing result type");
    using unsigned_type = typename UnsignedType<
        cat_tuples<std::tuple<w_FormatType::type>,
        TypesOfBits<w_Proxy, w_Proxies...>::type>>::type;
    Assign<w_FormatType, unsigned_type>(static_cast<unsigned_type>(value.value));
    return *this;
  }

  ProxyType* proxy;
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
  template <typename...BitsTypes>
  static void ReadModifyWrite(BitsTypes...bitsValues) {
    using Evaluator = BitTypesEvaluator<FormatType, BitsTypes...>;
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
   * Perform a write operation with the given  bit field values with the provided
   * default value.
   */
  template <typename...BitsTypes>
  static void Write(
      const BitValue<FormatType>& defaultBits, BitsTypes...bitsValues) {
    using Evaluator = BitTypesEvaluator<FormatType, BitsTypes...>;
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
   * Evaluates a new value from the given bitfields and default bits.
   */
  template <typename...BitsTypes>
  static BitValue<FormatType> Evaluate(
      const BitValue<FormatType>& defaultBits, BitsTypes...bitsValues) {
    using Evaluator = BitTypesEvaluator<FormatType, BitsTypes...>;
    auto new_bits = Evaluator::evaluate(bitsValues...);
    auto mask = Evaluator::traits::in_mask;
    if (~mask) {
      return BitValue<FormatType>{static_cast<type>(new_bits)
        | (static_cast<type>(~mask) & defaultBits.value)};
    }
    return BitValue<FormatType>{static_cast<type>(new_bits)};
  }
};

}  // namespace setl

#endif  // SETL_BIT_FIELDS___H
