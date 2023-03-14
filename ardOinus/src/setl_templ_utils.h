
#ifndef SETL_TEMPL_UTILS____H
#define SETL_TEMPL_UTILS____H

#include "setlx_type_traits.h"
#include "setl_optional.h"

namespace setl {

// Basic template utils.

/**
 * Boolean OR evaluator.
 */
struct OrEval {
  using value_type = bool;
  using default_value = std::false_type;

  template <typename RL, typename Rs>
  struct Eval {
    using value_type = bool;
    static constexpr value_type value = RL::value || Rs::value;
  };
};

/**
 * Numeric Add evaluator.
 */
template <typename T>
struct AddEval {
  using value_type = T;

  struct default_value {
    using value_type = T;
    static constexpr value_type value = 0;
  };

  template <typename RL, typename Rs>
  struct Eval {
    using value_type = T;
    static constexpr value_type value = RL::value + Rs::value;
  };
};

/**
 * A null adaptor that always returns the same value.
 */
template <typename intType, intType V>
struct ConstIntegerAdaptor {
  template <typename, typename>
  struct Constant {
    using value_type = intType;
    static constexpr value_type value = V;
  };
};

/**
 * The operator combines an "adaptor" template and an "evaluator" that combines
 * multiple results from the adaptor.
 */
template <template <typename VL, typename VR> class Adaptor, typename Eval>
struct Operator {
  using func = Eval;
  using default_value = typename Eval::default_value;
  
  template <typename VL, typename VR, typename ResultRest>
  struct Call {
    using Adapted = Adaptor<VL, VR>;
    using value_type = typename Eval::value_type;
    static constexpr value_type value = Eval::template Eval<Adapted, ResultRest>::value;
  };
};

/**
 * Apply an operator (Op) across all the variadic types Vs as the tuples
 * (VL, Vs0)...(VL, VsN).  
 */
template <typename Op, typename VL, typename... Vs>
struct For;

template <typename Op, typename VL>
struct For<Op, VL> : Op::func::default_value {};

template <typename Op, typename VL, typename V0, typename... Vs>
struct For<Op, VL, V0, Vs...> : Op::template Call<VL, V0, For<Op, VL, Vs...>> {};


/**
 * AutoFor, apply an operator across all pairs of template parameters.
 */
template <typename... T>
struct AutoFor;

template <>
struct AutoFor<> {
  using type = void;

  template <typename Op, typename VL>
  using Scanner = setl::For<Op, VL>;

  template <typename Op>
  using FirstScanner = typename Op::default_value;

  template <typename Op>
  using FullScanner = typename Op::default_value;
};

template <typename T0, typename... Ts>
struct AutoFor<T0, Ts...> {
  using type = T0;

  template <typename Op, typename VL>
  using Scanner = setl::For<Op, VL, Ts...>;

  // Apply operator across with the first element and all subsequent elements.
  template <typename Op>
  using FirstScanner = Scanner<Op, T0>;

  // Apply operator across all pairs of all elements.
  template <typename Op>
  using FullScanner = typename Op::func::template
    Eval<FirstScanner<Op>, typename AutoFor<Ts...>::template FullScanner<Op>>;
};

/**
 * True if V is contained in T...
 */
template <typename V, typename... T>
class Contains;

template <typename V>
class Contains<V> {
public:
  using type = std::false_type;
};

template <typename P, typename T0, typename... T>
class Contains<P, T0, T...> {
public:
  using type = typename std::conditional<
    std::is_same<P, T0>::value,
    std::true_type,
    typename Contains<P, T...>::type>::type;
};

/**
 * A generic container for varargs type.
 */
template <typename... T>
class TypeArgs {
public:

  /// Evaluate the template arguments across a chosen evaluator.
  template <template <typename... T1> class Evaluator>
  using eval = Evaluator<T...>;

  /// Evaluate the template arguments across a chosen evaluator with an argument.
  template <typename P, template <typename V, typename... T1> class Evaluator>
  using eval_arg1 = Evaluator<P, T...>;

  /// Evaluate the template arguments across a chosen evaluator with 2 arguments.
  template <
    typename P, 
    typename Q, 
    template <typename V, typename U, typename... T1> class Evaluator>
  using eval_arg2 = Evaluator<P, Q, T...>;

  /// Concatentes template arguments with the container's template arguments.
  template <typename... T1>
  using cat = TypeArgs<T..., T1...>;

  /// Reverse concatentes template arguments with the container's template arguments.
  template <typename... T1>
  using catr = TypeArgs<T1..., T...>;

  /// Concatentes TypeArgs with this container's template arguments.
  template <typename Ta>
  using cat_type_arg = typename Ta::template catr<T...>;

  /// Reverse concatentes TypeArfs with this container's template arguments.
  template <typename Ta>
  using catr_type_arg = typename Ta::template cat<T...>;
};

/**
 * Remove a type from the varargs resulting in a TypeArgs container.
 */
template <typename P, typename... T>
class RemoveVa;

template <typename P>
class RemoveVa<P> {
public:
  using type = TypeArgs<>;
};

template <typename P, typename T0, typename... Tr>
class RemoveVa<P, T0, Tr...> {
public:
  using type = typename std::conditional<
    std::is_same<P, T0>::value,
    typename RemoveVa<P, Tr...>::type,
    typename RemoveVa<P, Tr...>::type::template catr<T0>>::type;
};

template <typename P, typename... T>
using Remove = typename RemoveVa<P, T...>::type;

/**
 * Remove all types T and place result it in a TypeArgs container.
 */
template <typename Targs, typename... T>
class RemoveAllVa;

template <typename Targs>
class RemoveAllVa<Targs> {
public:
  using type = Targs;
};

template <typename Targs, typename T0, typename... Tr>
class RemoveAllVa<Targs, T0, Tr...> {
  template <typename... Tq>
  using RemoveT0 = Remove<T0, Tq...>;
  using WithoutT0 = typename Targs::template eval<RemoveT0>;
public:
  using type = typename RemoveAllVa<WithoutT0, Tr...>::type;
};

template <typename Targs1, typename Targs2>
class RemoveAllEvaluator {
  template <typename... T>
  using evaluator = RemoveAllVa<Targs1, T...>;
public:
  using type = typename Targs2::template eval<evaluator>::type;
};

template <typename Targs1, typename Targs2>
using RemoveAll = typename RemoveAllEvaluator<Targs1, Targs2>::type;

/**
 * Create a union of the types in the Targs container and T varargs
 * placing the result in a TypeArgs container.
 */

template <typename Targs, typename... T>
class UnionVa {
  using AllRemoved = typename RemoveAllVa<Targs, T...>::type;
public:
  using type = typename AllRemoved::template cat<T...>;
  /// Reversed concatenation.
  using typer = typename AllRemoved::template catr<T...>;
};

template <typename Targs1, typename Targs2>
class UnionEvaluator {
  template <typename... T>
  using evaluator = UnionVa<Targs1, T...>;
public:
  using type = typename Targs2::template eval<evaluator>::type;
  /// Reversed concatenation.
  using typer = typename Targs2::template eval<evaluator>::typer;
};

template <typename Targs1, typename Targs2>
using Union = typename UnionEvaluator<Targs1, Targs2>::type;

/**
 * Like Union but the concatenated types are placed at the beginning
 * of the resultant container.
 */
template <typename Targs1, typename Targs2>
using UnionR = typename UnionEvaluator<Targs1, Targs2>::typer;

/**
 * A value tuple.
 */
template <typename T, T...w_values>
struct ValueTuple {

  /**
   * Concatenates a values with this value tuple.
   */
  template <T...w_values1>
  using cat_values = ValueTuple<T, w_values..., w_values1...>;
};

static_assert(
  std::is_same<
    ValueTuple<int, 1, 2, 3>::cat_values<4, 5, 6>::cat_values<7, 8, 9>,
    ValueTuple<int, 1, 2, 3, 4, 5, 6, 7, 8, 9>>::value,
  "ValueTuple::cat");

/**
 * Concatenates two value tuples.
 */
template <typename...T>
struct ValueTupleCat_T;

template <typename T, T...w_values1>
struct ValueTupleCat_T<ValueTuple<T, w_values1...>> {
  using type = ValueTuple<T, w_values1...>;
};

template <typename T, T...w_values1, T...w_values2>
struct ValueTupleCat_T<ValueTuple<T, w_values1...>, ValueTuple<T, w_values2...>> {
  using type = ValueTuple<T, w_values1..., w_values2...>;
};

template <typename T, T...w_values1, T...w_values2, typename...W>
struct ValueTupleCat_T<ValueTuple<T, w_values1...>, ValueTuple<T, w_values2...>, W...> {
  using type = typename ValueTupleCat_T<ValueTuple<T, w_values1..., w_values2...>, W...>::type;
};

template <typename...T>
using ValueTupleCat = typename ValueTupleCat_T<T...>::type;

static_assert(
  std::is_same_v<
    ValueTupleCat<ValueTuple<int, 1, 2, 3>>,
    ValueTuple<int, 1, 2, 3>
  >,
  "ValueTupleCat<ValueTuple<int, 1, 2, 3>> failed");
  
static_assert(
  std::is_same_v<
    ValueTupleCat<ValueTuple<int, 1, 2, 3>, ValueTuple<int, 4, 5, 6>>,
    ValueTuple<int, 1, 2, 3, 4, 5, 6>
  >,
  "ValueTupleCat<ValueTuple<int, 1, 2, 3>, ValueTuple<int, 4, 5, 6>>");

static_assert(
  std::is_same_v<
    ValueTupleCat<ValueTuple<int, 1, 2, 3>, ValueTuple<int, 4, 5, 6>, ValueTuple<int, 7, 8, 9>>,
    ValueTuple<int, 1, 2, 3, 4, 5, 6, 7, 8, 9>
  >,
  "ValueTupleCat<ValueTuple<int, 1, 2, 3>, ValueTuple<int, 4, 5, 6>, ValueTuple<int, 7, 8, 9>>");

/**
 * Finds the return type of a function type.
 */

template <typename T>
struct return_type_of;

template <typename R, typename...P>
struct return_type_of<R(P...)> {
  using type = R;
};

template <typename T>
using return_type_of_t = typename return_type_of<T>::type;

static_assert(std::is_same_v<return_type_of_t<float(int, int)>, float>, 
  "return_type_of_t<float(int, int) should be float>");

/**
 * A value tuple getter.
 * 
 * This is a template class that is used to get a value from a tuple of value types
 * based on a selector value and a getter function.
 * 
 * This is intended to be a run-time evaluated value.
 */

template <typename T, typename w_ValueTuple, template <T w_selector> typename w_GetFuncType, typename w_ResultType>
struct ValueTupleGetterTyped;

template <typename T, T w_value, template <T selector> typename w_GetFuncType, typename w_ResultType>
struct ValueTupleGetterTyped<T, ValueTuple<T, w_value>, w_GetFuncType, w_ResultType> {
  template <typename ...P>
  static constexpr w_ResultType get(const T& selector, const P&...params) {
    return selector == w_value
      ? w_ResultType{w_GetFuncType<w_value>::get(params...)}
      : w_ResultType{};
  }
};

template <typename T, T w_value, T...w_values, template <T w_selector> typename w_GetFuncType, typename w_ResultType>
struct ValueTupleGetterTyped<T, ValueTuple<T, w_value, w_values...>, w_GetFuncType, w_ResultType> {
  template <typename ...P>
  static constexpr w_ResultType get(const T& selector, const P&...params) {
    return selector == w_value
      ? w_ResultType{w_GetFuncType<w_value>::get(params...)}
      : ValueTupleGetterTyped<T, ValueTuple<T, w_values...>, w_GetFuncType, w_ResultType>::get(selector, params...);
  }
};

template <typename T, typename w_ValueTuple, template <T w_selector> typename w_GetFuncType, typename ...P>
struct ValueTupleGetterTypeFinder;

template <typename T, T w_value, template <T w_selector> typename w_GetFuncType, typename ...P>
struct ValueTupleGetterTypeFinder<T, ValueTuple<T, w_value>, w_GetFuncType, P...> {

  static auto func_for_type(P...params) -> std::remove_cvref_t<decltype(w_GetFuncType<w_value>::get(params...))>;

};

template <typename T, T w_value, T...w_values, template <T w_selector> typename w_GetFuncType, typename ...P>
struct ValueTupleGetterTypeFinder<T, ValueTuple<T, w_value, w_values...>, w_GetFuncType, P...> {
  using Others = ValueTupleGetterTypeFinder<T, ValueTuple<T, w_values...>, w_GetFuncType, P...>;

  template <typename T1, typename T2>
  struct PickLarger {
    using type = std::conditional_t<(sizeof(T1) > sizeof(T2)), T1, T2>;
    //static_assert(std::is_assignable<type, T1>::value && std::is_assignable<type, T2>::value,
    //  "w_GetFuncType template results in incompatible types.");
  };

  static auto func_for_type(P...params) -> 
      typename PickLarger<std::remove_cvref_t<decltype(w_GetFuncType<w_value>::get(params...))>,
                          std::remove_cvref_t<decltype(Others::func_for_type(params...))>>::type;
};


template <typename T, typename w_ValueTuple, template <T w_selector> typename w_GetFuncType>
struct ValueTupleGetter;

template <typename T, T w_value, T...w_values, template <T w_selector> typename w_GetFuncType>
struct ValueTupleGetter<T, ValueTuple<T, w_value, w_values...>, w_GetFuncType> {

  template <typename ...P>
  using TypeFinder = ValueTupleGetterTypeFinder<T, ValueTuple<T, w_value, w_values...>, w_GetFuncType, P...>;

  template <typename ...P>
  using ReturnType = return_type_of_t<decltype(TypeFinder<P...>::func_for_type)> ;

  template <typename ...P>
  static constexpr auto get(const T& selector, const P&...params)
    -> setl::Optional<std::remove_cvref_t<ReturnType<P...>>> {
    using Type = std::remove_cvref_t<decltype(TypeFinder<P...>::func_for_type(params...))> ;
    using ResultType = setl::Optional<Type>;

    return ValueTupleGetterTyped<T, ValueTuple<T, w_value, w_values...>, w_GetFuncType, ResultType>
          ::get(selector, params...);
  }
};



}  // namespace

#endif