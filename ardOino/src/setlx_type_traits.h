

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

struct false_type {
  static constexpr bool value = false;
};

struct true_type {
  static constexpr bool value = true;
};

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

} // namespace

#endif

#endif