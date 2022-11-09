#ifndef UTILITY_H
#define UTILITY_H 

namespace Utility 
{
  template <typename T>
  void bound(const T& lbound, T& var, const T& ubound)
  {
    if (var < lbound)
      var = lbound;
    if (var > ubound)
      var = ubound;
  }
};

#endif // UTILITY_H
