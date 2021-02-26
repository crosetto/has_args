#pragma once

#include <type_traits>
#include <utility>

template < typename T >
int val (T const &, int){return 0;};

template <int N, typename Functor>
struct has_args {

    struct derived : Functor{};

  template <typename Derived , int ... Args>
  static auto test(Derived, decltype(val(std::declval<Derived>().Do( Args ... ), 0)), std::integer_sequence<int, Args ...>){
          return std::true_type{};
      };

  template <typename Derived, typename Val, typename Seq>
  static auto test(Derived, Val, Seq){
          return std::false_type{};
      };

  typedef decltype (test(std::declval<derived>(), 0, std::make_integer_sequence<int, N>())) type;
};

