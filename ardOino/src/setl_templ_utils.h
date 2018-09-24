
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

}  // namespace

#endif