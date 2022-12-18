#pragma once

namespace Utility {
  
template<typename T>
void bound(const T& lbound, T& var, const T& ubound) {
  if (var < lbound)
    var = lbound;
  if (var > ubound)
    var = ubound;
}

template<typename T>
T map(T x, T in_min, T in_max, T out_min, T out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


template<typename First, typename... Types>
void print_impl(First f, Types... others)
{
  Serial.print(f);
  if constexpr (sizeof...(Types))
    print_impl(others...);
  else
    Serial.println();
}

template<typename... Types>
void print(const Types &...args) {
  print_impl(args...);
  Serial.println();
}

};