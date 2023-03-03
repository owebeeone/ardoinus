
#ifndef SETLX_TUPLE_H
#define SETLX_TUPLE_H 1

#include "setl_support.h"
#include "setlx_cstddef.h"
#include "setlx_type_traits.h"

#ifdef HAS_STD_LIB
#include <tuple>
#else

namespace std {

template <typename... Ts>
class tuple;


template <>
struct tuple<> {};

template <typename T, typename... Ts>
struct tuple<T, Ts...> : public tuple<Ts...> {
   tuple(const T& value, const Ts&... rest) 
     : tuple<Ts...>(rest...), value(value)
   {}

   T value;
};


template<typename... Ts>
struct tuple_size;

template<typename... Ts>
struct tuple_size<tuple<Ts...>>
  : std::integral_constant<size_t, sizeof...(Ts)> {};


template<size_t I, class T>
struct tuple_element;

template<size_t I, typename T, typename... Ts>
struct tuple_element<I, tuple<T, Ts...>>
  : std::tuple_element<I - 1, tuple<Ts...>> {};

template<typename T, typename... Ts>
struct tuple_element<0, std::tuple<T, Ts...>> {
  using type = T;
};


static_assert(std::is_same<std::tuple_element<0, std::tuple<int, bool, char>>::type, int>::value, "std::tuple_element failed");
static_assert(std::is_same<std::tuple_element<1, std::tuple<int, bool, char>>::type, bool>::value, "std::tuple_element failed");
static_assert(std::is_same<std::tuple_element<2, std::tuple<int, bool, char>>::type, char>::value, "std::tuple_element failed");

}  // namespace std

#endif  // else HAS_STD_LIB
#endif  // SETLX_TUPLE_H