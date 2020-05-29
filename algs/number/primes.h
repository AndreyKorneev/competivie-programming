#ifndef NUMBER_PRIMES_H_
#define NUMBER_PRIMES_H_
#include "algs/common.h"

//~ BEGIN Factorized
// required: all
template<typename T>
void generate_divisors(vector<int>& res, T it, T end, int acc) {
  if (it == end) {
    res.push_back(acc);
  } else {
    for (int k = 0; k <= it->second; ++k, acc *= it->first)
      generate_divisors(res, next(it), end, acc);
  }
}
struct Factorized {
  Factorized(const map<int, int>& fact) : f(fact) { }
  int NumDivisors() {
    int res = 1;
    for (auto& [_, c] : f) res *= (c + 1);
    return res;
  }
  vector<int> Divisors() {
    vector<int> result;
    generate_divisors(result, f.begin(), f.end(), 1);
    sort(all(result));
    return result;
  }
  map<int, int> f;
};
//~ END Factorized

//~ BEGIN `PrimesHelper`
// required: Factorized
template<size_t N>
struct PrimesHelper {
  PrimesHelper() {
    minDivisor[1] = 1;
    for (size_t i = 2; i < N; ++i) {
      if (minDivisor[i] == 0) {
        minDivisor[i] = i;
        primes.push_back(i);
      }
      for (size_t j = 0; j < primes.size() && primes[j] <= minDivisor[i] && i * 1ll * primes[j] < N; ++j) {
        minDivisor[i * primes[j]] = primes[j];
      }
    }
  }

  Factorized Factorize(int a) {
    map<int, int> res;
    while (a > 1) {
      auto d = minDivisor[a];
      while (a % d == 0) {
        res[d]++;
        a /= d;
      }
    }
    if (a > 1) res[a]++;
    return Factorized(res);
  }

  array<int, N> minDivisor;
  vector<int> primes;
};
//~ END `PrimesHelper`

#endif

