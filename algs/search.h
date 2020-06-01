#ifndef SEARCH_H_
#define SEARCH_H_

#include "algs/common.h"

//~ BEGIN `binary_search_i`
template<typename T>
T binary_search_i(T l, T r, const std::function<bool(lli)>& check) {
  while (r - l > 1) {
    T m = (l + r) / 2;
    if (check(m)) l = m;
    else r = m;
  }
  return (check(r) ? r : l);
}
//~ END `binary_search_i`
//
//~ BEGIN `binary_search_f`
template<typename T, size_t K=200>
T binary_search_f(T l, T r, const std::function<bool(lli)>& check) {
  for (int i = 0; i < K; ++i) {
    T m = (l + r) / 2;
    if (check(m)) l = m;
    else r = m;
  }
  return (l+r) / 2;
}
//~ END `binary_search_f`

//~ BEGIN `ternary_search_i`
template<typename T, size_t K=50>
T ternary_search_i(T l, T r, const std::function<T(T)>& check) {
  while (r - l > K) {
    T diff = (r - l) / 3;
    T m1 = l + diff, m2 = r - diff;
    if (check(m1) > check(m2)) l = m1;
    else r = m2;
  }
  T ans = l;
  T cost = check(l);
  for (T i = l + 1; i <= r; ++i) {
    T icost = check(i);
    if (icost < cost) {
      ans = i;
      cost = icost;
    }
  }
  return ans;
}
//~ END `ternary_search_i`

//~ BEGIN `ternary_search_f`
template<typename T, size_t K=200>
T ternary_search_f(T l, T r, const std::function<T(T)>& check) {
  for (int i = 0; i < K; ++i) {
    T diff = (r - l) / 3;
    T m1 = l + diff, m2 = r - diff;
    if (check(m1) > check(m2)) l = m1;
    else r = m2;
  }
  return (l+r)/2;
}
//~ END `ternary_search_f`

#endif
