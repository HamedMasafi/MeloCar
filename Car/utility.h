#ifndef UTILITY_H
#define UTILITY_H

namespace Utility {
template<typename T>
void bound(const T &lbound, T &var, const T &ubound) {
  if (var < lbound)
    var = lbound;
  if (var > ubound)
    var = ubound;
}

template<typename First, typename... Types>
void print_impl(First f, Types... others)
{
  Serial.print(f);
  if constexpr (sizeof...(Types))
    print_impl(others...);
}

template<typename... Types>
void print(const Types &...args) {
  print_impl(args...);
  Serial.println();
}
};

#endif  // UTILITY_H