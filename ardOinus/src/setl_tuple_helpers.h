
#ifndef SETLX_TUPLE_HELPERS_H
#define SETLX_TUPLE_HELPERS_H 1

#include "setlx_tuple.h"

namespace setl {

/**
 * Concatenate tuples.
 * 
 * Example:
 *  tuple_concat_t<std::tuple<int, char>, std::tuple<short>> == std::tuple<int, char, short>
 */
template <typename...T>
struct tuple_concat;

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
        std::tuple<int, char, short>>, "tuple_concat_t<a,b> failed");

static_assert(
    std::is_same_v<
        tuple_concat_t<std::tuple<int, char>, std::tuple<short>, std::tuple<float>>,
        std::tuple<int, char, short, float>>, "tuple_concat_t<a,b,c> failed");

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

}

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


} // namespace setl

#endif  // SETLX_TUPLE_HELPERS_H