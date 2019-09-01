
#ifndef SETL_TEMPL_UTILS____H
#define SETL_TEMPL_UTILS____H

#include "setlx_type_traits.h"

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

  /// Concatentes TypeArfs with this container's template arguments.
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

}  // namespace

#endif