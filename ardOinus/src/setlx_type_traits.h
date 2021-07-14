

#ifndef SETL_TYPE_TRAITS__H
#define SETL_TYPE_TRAITS__H

#include "setl_support.h"
//#define HAS_STD_LIB
#ifdef HAS_STD_LIB
#include <type_traits>
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

// This needs compiler support so we just make it true.
template< class T >
struct is_trivially_copyable : true_type {
};

} // namespace

#endif

#endif