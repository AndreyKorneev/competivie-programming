#ifndef DATA_STRUCTURES_SEGTREE_H_
#define DATA_STRUCTURES_SEGTREE_H_
#include "algs/common.h"

//~ BEGIN `MinMaxSTWithAddition`
template <class T>
struct MinMaxSTWithAddition {
  MinMaxSTWithAddition(const vector<T> &v)
      : n_(v.size()),
        min_(v.size() * 4 + 123),
        max_(v.size() * 4 + 123),
        add_(v.size() * 4 + 123) {
    build(v);
  }

  void build(const vector<T> &source) { build(source, 0, 0, n_ - 1); }

  void build(const vector<T> &source, int v, int l, int r) {
    if (l == r) {
      max_[v] = min_[v] = source[l];
    } else {
      int m = (l + r) / 2;
      int ch = (v << 1) + 1;
      build(source, ch, l, m);
      build(source, ch + 1, m + 1, r);
      upd(v);
    }
  }

  void add(int l, int r, const T &delta) { add(0, 0, n_ - 1, l, r, delta); }

  void add(int v, int l, int r, int ll, int rr, const T &delta) {
    if (ll > rr) return;
    if (l == ll && r == rr) {
      add_[v] += delta;
    } else {
      int m = (l + r) / 2;
      int ch = (v << 1) + 1;
      upd(v);
      add(ch, l, m, ll, min(m, rr), delta);
      add(ch + 1, m + 1, r, max(ll, m + 1), rr, delta);
      upd(v);
    }
  }

  void upd(int v) {
    int ch = (v << 1) + 1;
    if (add_[v]) {
      add_[ch] += add_[v];
      add_[ch + 1] += add_[v];
      add_[v] = 0;
    }
    min_[v] = std::min(getMin(ch), getMin(ch + 1));
    max_[v] = std::max(getMax(ch), getMax(ch + 1));
  }

  inline const T getMax(int v) const { return max_[v] + add_[v]; }
  inline const T getMin(int v) const { return min_[v] + add_[v]; }

  const T getMax(int l, int r) { return getMax(0, 0, n_ - 1, l, r); }
  const T getMin(int l, int r) { return getMin(0, 0, n_ - 1, l, r); }

  const T getMax(int v, int l, int r, int ll, int rr) {
    if (ll > rr) return INT_MIN;
    if (l == ll && r == rr) {
      return getMax(v);
    }
    upd(v);
    int m = (l + r) / 2;
    int ch = (v << 1) + 1;
    return max(getMax(ch, l, m, ll, min(m, rr)),
               getMax(ch + 1, m + 1, r, max(ll, m + 1), rr));
  }

  const T getMin(int v, int l, int r, int ll, int rr) {
    if (ll > rr) return INT_MAX;
    if (l == ll && r == rr) {
      return getMin(v);
    }
    upd(v);
    int m = (l + r) / 2;
    int ch = (v << 1) + 1;
    return min(getMin(ch, l, m, ll, min(m, rr)),
               getMin(ch + 1, m + 1, r, max(ll, m + 1), rr));
  }

  int n_;
  vector<T> min_, max_, add_;
};
//~ END `MinMaxSTWithAddition`

#endif
