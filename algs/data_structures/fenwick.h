#ifndef DATA_STRUCTURES_FENWICK_H_
#define DATA_STRUCTURES_FENWICK_H_
#include "algs/common.h"

//~ BEGIN `FenwickTree`
#define NEXT(p) ((p) | ((p) + 1))
#define PREV(p) (((p) & ((p) + 1)) - 1)
template <class T>
struct FenwickTree {
  FenwickTree(int n) : n_(n), t_(n_ + 123) { }
  void add(int p, const T& delta) { for (; p < n_; p = NEXT(p)) t_[p] += delta; }
  T sum(int r) const {
    if (r < 0) return 0;
    T res = 0;
    for (; r >= 0; r = PREV(r)) res += t_[r];
    return res;
  }
  T sum(int l, int r) const {
    if (r < l) return 0;
    return sum(r) - sum(l - 1);
  }
  int n_;
  vector<T> t_;
};
//~ END `FenwickTree`

#endif
