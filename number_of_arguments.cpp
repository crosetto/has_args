#include "number_of_arguments.h"

struct func {
  func(int &arg) : arg{arg} {}
  template <typename T> int operator()(T) {}
  int &arg;
};

struct func2 {
  template <typename T1, typename T2> int operator()(T1, T2) const {}
};

struct func3 {
  template <typename T1, typename T2, typename T3> int operator()(T1, T2, T3) {}
};

struct func4 {
  template <typename T1, typename T2, typename T3, typename T4>
  int operator()(T1, T2, T3, T4) {}
};

int main() {

  static_assert(has_args<1, func>::type::value == true, "error");
  static_assert(has_args<2, func>::type::value == false, "error");
  static_assert(has_args<2, func2>::type::value == true, "error");
  static_assert(has_args<3, func3>::type::value == true, "error");
  static_assert(has_args<4, func4>::type::value == true, "error");
  static_assert(has_args<4, func3>::type::value == false, "error");
  static_assert(has_args<4, func2>::type::value == false, "error");

  func3 f;
  static_assert(has_args<3, decltype(f)>::type::value == true, "error");

  auto lambda=[](auto arg){};
  static_assert(has_args<1, decltype(lambda)>::type::value == true, "error");

}
