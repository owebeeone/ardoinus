/**
 * std::tuple utilities.
 */

#ifndef SETL_CAT_TUPLES___H
#define SETL_CAT_TUPLES___H

#include "setlx_tuple.h"
#include "setlx_type_traits.h"

namespace setl {

/**
 * Catentate the types in a collection of tuples into a single tuple.
 */
template <typename...Ts>
struct cat_tuples;

// The empty set of tuples.
template <>
struct cat_tuples<> {
  using type = std::tuple<>;
};

// The single tuple.
template <typename...Ts>
struct cat_tuples<std::tuple<Ts...>> {
  using type = std::tuple<Ts...>;
};

// The two tuple case.
template <typename...Us, typename...Vs>
struct cat_tuples<std::tuple<Us...>, std::tuple<Vs...>> {
  using type = std::tuple<Us..., Vs...>;
};

// The more than 2 tuple case.
template <typename U, typename V, typename...Ts>
struct cat_tuples<U, V, Ts...> {
  using type = 
    typename cat_tuples<U, typename cat_tuples<V, Ts...>::type>::type;
};

template <typename...Ts>
using cat_tuples_t = typename cat_tuples<Ts...>::type;

static_assert(
  std::is_same<
    std::tuple<int, char, long, unsigned>,
    cat_tuples<
        std::tuple<int>, 
        std::tuple<char, long>, 
        std::tuple<unsigned>>::type
    >::value,
  "types should be the same."
);

static_assert(
  std::is_same<
    std::tuple<>,
    cat_tuples<>::type
    >::value,
  "No tuples should become the empty tuple."
);

static_assert(
  std::is_same<
    std::tuple<int, char>,
    cat_tuples<std::tuple<int, char>>::type
    >::value,
  "A single tuple should be itself."
);

} // namespace setl

#endif  // SETL_CAT_TUPLES___H