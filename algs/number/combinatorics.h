#ifndef NUMBER_COMBINATORICS_H_
#define NUMBER_COMBINATORICS_H_
#include "algs/common.h"

//~ BEGIN `Combinatorics`
template <typename T>
struct Combinatorics {
  Combinatorics(int n) : fact(n + 1) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = T(i) * fact[i - 1];
  }

  T Fact(int i) { return fact[i]; }
  T A(int n, int k) {
    if (n == 0 || k > n) return 0;
    return fact[n] / fact[n - k];
  }
  T C(int n, int k) {
    if (n == 0 || k > n) return 0;
    return fact[n] / fact[k] / fact[n - k];
  }
  T C_small(int n, int k) {
    if (n == 0 || k > n) return 0;
    if (n - k > k) k = n - k;
    T result = 1;
    for (int t = k + 1; t <= n; ++t) result *= T(t);
    for (int t = 2; t <= n - k; ++t) result /= T(t);
    return result;
  }
  T Cr(int n, int k) {
    if (n == 0 || k > n) return 0;
    return fact[n + k - 1] / fact[k] / fact[n - 1];
  }

  vector<T> fact;
};
//~ END `Combinatorics`

#endif
