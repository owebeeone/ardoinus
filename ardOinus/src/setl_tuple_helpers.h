
#ifndef SETLX_TUPLE_HELPERS_H
#define SETLX_TUPLE_HELPERS_H 1

#include "setlx_tuple.h"
#include "setlx_type_traits.h"

namespace setl {

/**
 * Concatenate tuples.
 * 
 * Example:
 *  tuple_concat_t<std::tuple<int, char>, std::tuple<short>> == std::tuple<int, char, short>
 */
template <typename...T>
struct tuple_concat;

template <>
struct tuple_concat<> {
  using type = std::tuple<>;
};

template <typename... w_types1>
struct tuple_concat<std::tuple<w_types1...>> {
  using type = std::tuple<w_types1...>;
};

template <typename... w_types1, typename... w_types2>
struct tuple_concat<std::tuple<w_types1...>, std::tuple<w_types2...>> {
  using type = std::tuple<w_types1..., w_types2...>;
};

template <typename... w_types1, typename... w_types2, typename...T>
struct tuple_concat<std::tuple<w_types1...>, std::tuple<w_types2...>, T...> {
  using type = typename tuple_concat<std::tuple<w_types1..., w_types2...>, T...>::type;
};

template <typename...T>
using tuple_concat_t = typename tuple_concat<T...>::type;

static_assert(
    std::is_same_v<
        tuple_concat_t<std::tuple<int, char>, std::tuple<short>>,
        std::tuple<int, char, short>>,
    "tuple_concat_t<a,b> failed");

static_assert(
    std::is_same_v<
        tuple_concat_t<std::tuple<int, char>, std::tuple<short>, std::tuple<float>>,
        std::tuple<int, char, short, float>>, 
    "tuple_concat_t<a,b,c> failed");

static_assert(
  std::is_same_v<std::tuple<>, tuple_concat_t<>>,
  "tuple_concat_t<> failed.");


/**
  * Returns true_type if T is contained in w_tuple1, false_type otherwise.
  */
template <typename T, typename w_tuple1>
struct tuple_contained_in;

template <typename T>
struct tuple_contained_in<T, std::tuple<>> : std::false_type {};

template <typename T, typename...w_types1>
struct tuple_contained_in<T, std::tuple<T, w_types1...>>
  : std::true_type {};

template <typename T, typename O, typename...w_types1>
struct tuple_contained_in<T, std::tuple<O, w_types1...>>
  : tuple_contained_in<T, std::tuple<w_types1...>> {};

template <typename T, typename w_tuple1>
constexpr auto tuple_contained_in_v = tuple_contained_in<T, w_tuple1>::value;

static_assert(tuple_contained_in_v<int, std::tuple<int, char, short>>,
  "tuple_contained_in_v failed");

static_assert(!tuple_contained_in_v<float, std::tuple<int, char, short>>,
  "tuple_contained_in_v failed");

/**
 * Extend a tuple with more types.
 * 
 * Example:
 *      tuple_extend_t<std::tuple<int, char>, short, int> == std::tuple<int, char, short, int>
 */
template <typename w_tuple1, typename... w_types2>
struct tuple_extend;

template <typename... w_types1, typename... w_types2>
struct tuple_extend<std::tuple<w_types1...>, w_types2...> {
  using type = std::tuple<w_types1..., w_types2...>;
};

template <typename w_tuple1, typename... w_types2>
using tuple_extend_t = typename tuple_extend<w_tuple1, w_types2...>::type;

static_assert(
    std::is_same_v<
        tuple_extend_t<std::tuple<int, char>, short>,
        std::tuple<int, char, short>>, "tuple_extend_t failed");

/**
 * Normalize a tuple by removing duplicates.
 */
template <typename w_tuple1>
struct tuple_normalize;

template <>
struct tuple_normalize<std::tuple<>> {
  using type = std::tuple<>;
};

template <typename T, typename... w_types1>
struct tuple_normalize<std::tuple<T, w_types1...>> {
  using type = std::conditional_t<
    tuple_contained_in_v<T, std::tuple<w_types1...>>,
    typename tuple_normalize<std::tuple<w_types1...>>::type,
    typename tuple_concat<
      std::tuple<T>, typename tuple_normalize<std::tuple<w_types1...>>::type>::type>;
};

template <typename w_tuple1>
using tuple_normalize_t = typename tuple_normalize<w_tuple1>::type;

static_assert(
    std::is_same_v<
        tuple_normalize_t<std::tuple<int, char, short, int>>,
        std::tuple<char, short, int>>, "tuple_normalize_t failed");

/**
 * Union of tuples.
 * 
 * Example:
 *     tuple_union_t<std::tuple<int, char>, std::tuple<short, int>> == std::tuple<char, short, int>
 */
template <typename...T>
struct tuple_union {
    using type = tuple_normalize_t<tuple_concat_t<T...>>;
};

template <typename...T>
using tuple_union_t = typename tuple_union<T...>::type;

static_assert(
    std::is_same_v<
        tuple_union_t<std::tuple<int, char>, std::tuple<short, int>>,
        std::tuple<char, short, int>>, "tuple_union_t failed");


namespace nfp {
// Internal. Not intended for public use.

template <typename w_tuple1, typename w_tuple2>
struct intersect;

template <typename... w_types2>
struct intersect<std::tuple<>, std::tuple<w_types2...>> {
    using type = std::tuple<>;
};

template <typename T, typename... w_types1, typename... w_types2>
struct intersect<std::tuple<T, w_types1...>, std::tuple<w_types2...>> {
    using rest = typename intersect<std::tuple<w_types1...>, std::tuple<w_types2...>>::type;
    using type = std::conditional_t<
        tuple_contained_in_v<T, std::tuple<w_types2...>>,
        typename tuple_concat<std::tuple<T>, rest>::type,
        rest>;
};

static_assert(
    std::is_same_v<
        intersect<std::tuple<int, char>, std::tuple<short, int>>::type,
        std::tuple<int>>, "intersect failed");
        
static_assert(
    std::is_same_v<
        intersect<std::tuple<int, char, short>, std::tuple<short, int>>::type,
        std::tuple<int, short>>, "intersect failed");


template <typename...T>
struct intersection_helper;

template <typename...w_types1>
struct intersection_helper<std::tuple<w_types1...>> {
    using type = std::tuple<w_types1...>;
};

template <typename... w_types1, typename... w_types2>
struct intersection_helper<std::tuple<w_types1...>, std::tuple<w_types2...>> {
    using type = typename intersect<std::tuple<w_types1...>, std::tuple<w_types2...>>::type;
};

template <typename... w_types1, typename... w_types2, typename...T>
struct intersection_helper<std::tuple<w_types1...>, std::tuple<w_types2...>, T...> {
    using head = typename intersect<std::tuple<w_types1...>, std::tuple<w_types2...>>::type;
    using type = typename intersection_helper<head, T...>::type;
};

static_assert(
    std::is_same_v<
        intersection_helper<std::tuple<int, char>, std::tuple<short, int>>::type,
        std::tuple<int>>, "intersection_helper failed");

static_assert(
    std::is_same_v<
        intersection_helper<
            std::tuple<int, char, short>, 
            std::tuple<short, int>, 
            std::tuple<int, short, char>>::type,
        std::tuple<int, short>>, "intersection_helper failed");

} // namespace nfp

/**
 * Create an intersection of tuples.
 * 
 * Example:
 *    tuple_intersection_t<std::tuple<int, char, int>, std::tuple<short, int>> == std::tuple<int>
 */
template <typename...T>
struct tuple_intersection {
    using type = typename nfp::intersection_helper<tuple_normalize_t<T>...>::type;
};

template <typename...T>
using tuple_intersection_t = 
    typename nfp::intersection_helper<tuple_normalize_t<T>...>::type;

static_assert(
    std::is_same_v<
        tuple_intersection_t<std::tuple<int, char, int>, std::tuple<short, int>>,
        std::tuple<int>>, "tuple_intersection_t failed");


/**
 * Remove a type from a tuple.
 * 
 * Results in a tuple with the all occurrences of T removed.
 * 
 * Example:
 *    tuple_remove_t<int, std::tuple<int, char, short, int>> == std::tuple<char, short>
 */
template <typename T, typename w_tuple1>
struct tuple_remove;

template <typename T>
struct tuple_remove<T, std::tuple<>> {
    using type = std::tuple<>;
};

template <typename T, typename... w_types1>
struct tuple_remove<T, std::tuple<T, w_types1...>> {
    using type = typename tuple_remove<T, std::tuple<w_types1...>>::type;
};

template <typename T, typename O, typename... w_types1>
struct tuple_remove<T, std::tuple<O, w_types1...>> {
    using type = typename tuple_concat<
        std::tuple<O>,
        typename tuple_remove<T, std::tuple<w_types1...>>::type>::type;
};

template <typename T, typename w_tuple>
using tuple_remove_t = typename tuple_remove<T, w_tuple>::type;

static_assert(
    std::is_same_v<
        tuple_remove_t<int, std::tuple<int, char, short, int>>,
        std::tuple<char, short>>, "tuple_remove_t failed");

/**
 * Remove an entry from a tuple if it is found.
 * 
 * Results in a tuple with the first occurrence of T removed. If T is not found, the tuple is
 * unchanged and the not_found_tuple contains a tuple containing T. The static member is_found
 * is std::true_type if T was found and std::false_type otherwise.
 */

template <typename T, typename w_tuple>
struct tuple_remove_entry;

template <typename T>
struct tuple_remove_entry<T, std::tuple<>> {
    using type = std::tuple<>;
    using not_found_tuple = std::tuple<T>;
    using is_found = std::false_type;
};

template <typename T, typename... w_types1>
struct tuple_remove_entry<T, std::tuple<T, w_types1...>> {
    using type = std::tuple<w_types1...>;
    using not_found_tuple = std::tuple<>;
    using is_found = std::true_type;
};

template <typename T, typename O, typename... w_types1>
struct tuple_remove_entry<T, std::tuple<O, w_types1...>> {
    using rest = tuple_remove_entry<T, std::tuple<w_types1...>>;
    using type = tuple_concat_t<std::tuple<O>, typename rest::type>;
    using not_found_tuple = typename rest::not_found_tuple;
    using is_found = typename rest::is_found;
};

template <typename T, typename w_tuple>
using tuple_remove_entry_t = typename tuple_remove_entry<T, w_tuple>::type;

template <typename T, typename w_tuple>
using tuple_remove_entry_not_found_t = typename tuple_remove_entry<T, w_tuple>::not_found_tuple;

template <typename T, typename w_tuple>
constexpr auto tuple_remove_entry_is_found_v = tuple_remove_entry<T, w_tuple>::is_found::value;

static_assert(
    std::is_same_v<
        tuple_remove_entry_t<int, std::tuple<int, char, short, int>>,
        std::tuple<char, short, int>>, "tuple_remove_entry_t failed");

static_assert(
    std::is_same_v<
        tuple_remove_entry_not_found_t<int, std::tuple<int, char, short, int>>,
        std::tuple<>>, "tuple_remove_entry_not_found_t failed");

static_assert(
        tuple_remove_entry_is_found_v<int, std::tuple<int, char, short, int>>,
        "tuple_remove_entry_not_found_t failed");

static_assert(
    std::is_same_v<
        tuple_remove_entry_t<float, std::tuple<int, char, short, int>>,
        std::tuple<int, char, short, int>>, "tuple_remove_entry_t failed");

static_assert(
    std::is_same_v<
        tuple_remove_entry_not_found_t<float, std::tuple<int, char, short, int>>,
        std::tuple<float>>, "tuple_remove_entry_not_found_t failed");

static_assert(
        !tuple_remove_entry_is_found_v<float, std::tuple<int, char, short, int>>,
        "tuple_remove_entry_not_found_t failed");

/**
 * Create a difference of tuples.
 * 
 * Tuple difference results in a tuple that contains all the types in the first tuple
 * that are not in any of the other tuples.
 * 
 * Example:
 *   tuple_difference_t<std::tuple<int, char, short>, std::tuple<short, int>> == std::tuple<char>
 */
template <typename w_tuple, typename...w_tuples>
struct tuple_difference;

template <typename... w_types1>
struct tuple_difference<std::tuple<w_types1...>> {
    using type = std::tuple<w_types1...>;
};

template <typename... w_types1>
struct tuple_difference<std::tuple<w_types1...>, std::tuple<>> {
    using type = std::tuple<w_types1...>;
};

template <typename... w_types1, typename R, typename... w_types2, typename...w_tuples>
struct tuple_difference<std::tuple<w_types1...>, std::tuple<R, w_types2...>, w_tuples...> {
    using type = typename tuple_difference<
        tuple_remove_t<R, std::tuple<w_types1...>>,
        std::tuple<w_types2...>, w_tuples...>::type;
};

template <typename... w_types1, typename...w_tuples>
struct tuple_difference<std::tuple<w_types1...>, std::tuple<>, w_tuples...> {
    using type = typename tuple_difference<
        std::tuple<w_types1...>, w_tuples...>::type;
};

template <typename w_tuple, typename...w_tuples>
using tuple_difference_t = typename tuple_difference<w_tuple, w_tuples...>::type;

static_assert(
    std::is_same_v<
        tuple_difference_t<
            std::tuple<int, char, short, int>, 
            std::tuple<short, int>>,
        std::tuple<char>>, "tuple_difference_t failed");

static_assert(
    std::is_same_v<
        tuple_difference_t<
            std::tuple<int, char, short, int, float>, 
            std::tuple<short, int>,
            std::tuple<float>>,
        std::tuple<char>>, "tuple_difference_t failed");

/**
 * Returns true is the type T has one of the given base classes.
 */

template <typename T, typename w_tuple_of_bases>
constexpr bool tuple_has_base_v = false;

template <typename T>
constexpr bool tuple_has_base_v<T, std::tuple<>> = false;

template <typename D, typename B, typename...w_base_types>
constexpr bool tuple_has_base_v<D, std::tuple<B, w_base_types...>> = 
    std::is_base_of_v<B, D> || tuple_has_base_v<D, std::tuple<w_base_types...>>;

static_assert(
    tuple_has_base_v<int, std::tuple<>> == false, "tuple_has_base_v failed");

namespace nfp_testonly {
struct a {};
struct b : a {};
static_assert(
    !tuple_has_base_v<a, std::tuple<b, b>>, "tuple_has_base_v failed");
static_assert(
    tuple_has_base_v<b, std::tuple<a, a>>, "tuple_has_base_v failed");
} // namespace nfp_testonly

/**
 * Selects all the types from the first tuple that are a base of one of the 
 * types in the second tuple.
 */

template <typename w_tuple, typename w_base_tuple>
struct tuple_select_by_base;

template <typename...w_base_types>
struct tuple_select_by_base<std::tuple<>, std::tuple<w_base_types...>> {
    using type = std::tuple<>;
};

template <typename D, typename...w_derived, typename...w_base>
struct tuple_select_by_base<std::tuple<D, w_derived...>, std::tuple<w_base...>> {
  public:
    using rest = typename tuple_select_by_base<
        std::tuple<w_derived...>, 
        std::tuple<w_base...>>::type;
  public:
    using type = std::conditional_t<
        tuple_has_base_v<D, std::tuple<w_base...>>,
        tuple_concat_t<std::tuple<D>, rest>,
        rest>;
};

template <typename w_tuple, typename w_base_tuple>
using tuple_select_by_base_t = typename tuple_select_by_base<w_tuple, w_base_tuple>::type;

namespace nfp_testonly2 {
struct a {};
struct b {};
struct c : a {};
struct d : b {};
struct e {};

static_assert(
    std::is_same_v<
        tuple_select_by_base_t<
            std::tuple<c, d, e>, 
            std::tuple<a>>,
        std::tuple<c>>, "tuple_select_by_base_t failed");

static_assert(
    std::is_same_v<
        tuple_select_by_base_t<
            std::tuple<c, d, e>, 
            std::tuple<b, e>>,
        std::tuple<d, e>>, "tuple_select_by_base_t failed");
} // namespace nfp_testonly2

} // namespace setl

#endif  // SETLX_TUPLE_HELPERS_H