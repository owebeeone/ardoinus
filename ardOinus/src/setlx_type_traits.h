

#ifndef SETL_TYPE_TRAITS__H
#define SETL_TYPE_TRAITS__H

#include "setl_support.h"
//#define HAS_STD_LIB
#ifdef HAS_STD_LIB
#include <type_traits>

// Only add this for pre C++17 compilers.
#if __cplusplus < 201703L
namespace std {
template <bool B, class T, class F>
using conditional_t = typename conditional<B, T, F>::type;

template <typename T>
struct remove_cvref {
  using type = typename remove_cv<typename remove_reference<T>::type>::type;
};

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

}
#endif // __cplusplus < 201703L

#else

namespace std {

// conditional.
template<bool B, typename T, typename F>
struct conditional {
  using type = T;
};

template<class T, typename F >
struct conditional<false, T, F> {
  using type = F;
};

template <bool B, class T, class F>
using conditional_t = typename conditional<B, T, F>::type;

template<class T, T w_value>
struct integral_constant {
  static constexpr T value = w_value;
  using value_type = T;
  using type = integral_constant;
  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

struct false_type : integral_constant<bool, false> {};

struct true_type : integral_constant<bool, true> {};

// is_volatile
template <typename T>
struct is_volatile : false_type {};

template <typename T>
struct is_volatile<volatile T> : true_type {};

// is_same
template<typename T, typename U>
struct is_same : false_type {};

template<typename T>
struct is_same<T, T> : true_type {};

template <class T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

// remove_const
template <typename T>
struct remove_const {
  using type = T; 
};

template <typename T>
struct remove_const<const T> { 
  using type = T; 
};

static_assert(
  is_same<int, remove_const<const int>::type>::value,
  "remove_const is broken.");

// remove_volatile
template <typename T>
struct remove_volatile { 
  using type = T; 
};

template <typename T>
struct remove_volatile<volatile T> {
  using type = T;
};

// remove_cv
template <typename T>
struct remove_cv {
  using type = typename remove_volatile<typename remove_const<T>::type>::type;
};

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

static_assert(
  is_same<int, remove_cv_t<volatile const int>>::value,
  "remove_cv_t is broken.");

// This needs compiler support so we just make it true.
template< class T >
struct is_trivially_copyable : true_type {
};

template <typename T>
struct remove_reference {
  using type = T;
};

template <typename T>
struct remove_reference<T&> {
  using type = T;
};

template <typename T>
struct remove_reference<T&&> {
  using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

static_assert(
  is_same<int, remove_reference_t<int&>>::value,
  "remove_reference_t is broken.");

template <typename T>
struct remove_cvref {
  using type = typename remove_cv<typename remove_reference<T>::type>::type;
};

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

static_assert(
  is_same<int, remove_cvref<const int&>::type>::value,
  "remove_cvref_t is broken.");

template <typename T>
std::remove_reference_t<T>&& move(T&& arg) noexcept {
  return static_cast<std::remove_reference_t<T>&&>(arg);
}

template<typename Base, typename Derived>
struct is_base_of {
    private:
        static constexpr bool check(const Base*) { return true; }
        static constexpr bool check(...) { return false; }
    public:
        static constexpr bool value = check(static_cast<const Derived*>(nullptr));
};

template<typename Base, typename Derived>
constexpr auto is_base_of_v = is_base_of<Base, Derived>::value;

//static_assert(is_base_of_v<int, int>::value, "is_base_of is broken.");

namespace nfp {

template <typename...T>
struct nfp_tuple {};

/**
 * Returns true_type if T is contained in w_tuple1, false_type otherwise.
 */
template <typename T, typename w_tuple1>
struct tuple_contained_in;

template <typename T>
struct tuple_contained_in<T, nfp_tuple<>> : std::false_type {};

template <typename T, typename...w_types1>
struct tuple_contained_in<T, nfp_tuple<T, w_types1...>>
 : std::true_type {};

template <typename T, typename O, typename...w_types1>
struct tuple_contained_in<T, nfp_tuple<O, w_types1...>>
 : tuple_contained_in<T, nfp_tuple<w_types1...>> {};

template <typename T, typename w_tuple1>
constexpr auto tuple_contained_in_v = tuple_contained_in<T, w_tuple1>::value;

static_assert(tuple_contained_in_v<int, nfp_tuple<int, char, short>>,
              "tuple_contained_in_v failed");
              
static_assert(!tuple_contained_in_v<float, nfp_tuple<int, char, short>>,
              "tuple_contained_in_v failed");

}  // namespace nfp


template <typename T>
inline constexpr bool is_integral_v =
    nfp::tuple_contained_in_v<
      remove_cvref_t<T>, nfp::nfp_tuple<
        bool, char, unsigned char, signed char, int, unsigned, long, unsigned long,
        long long, unsigned long long>>;

template <typename T>
struct is_integral : integral_constant<bool, is_integral_v<T>> {};

template <typename T>
inline constexpr bool is_floating_point_v =
    nfp::tuple_contained_in_v<
      remove_cvref_t<T>, nfp::nfp_tuple<float, double, long double>>;

template <typename T>
struct is_floating_point : integral_constant<bool, is_floating_point_v<T>> {};



} // namespace std

#endif  // HAS_STD_LIB

#endif  // SETL_TYPE_TRAITS__H