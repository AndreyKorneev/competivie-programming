#ifndef DATA_STRUCTURES_SEGTREE_H_
#define DATA_STRUCTURES_SEGTREE_H_
#include "algs/common.h"

//~ BEGIN `SEGT_SIZE`
#define SEGT_SIZE(p) (((p) << 2) + 123)
//~ END `SEGT_SIZE`

//~ BEGIN `MinMaxSTWithAddition`
// required: SEGT_SIZE
template <class T>
struct MinMaxSTWithAddition {
  MinMaxSTWithAddition(const vector<T> &v)
      : n_(v.size()),
        min_(SEGT_SIZE(n_)),
        max_(SEGT_SIZE(n_)),
        add_(SEGT_SIZE(n_)) {
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

//~ BEGIN `SumSegmentTree`
// required: SEGT_SIZE
template <class T>
struct SumSegmentTree {
  SumSegmentTree(int n) : n_(n), t_(SEGT_SIZE(n_))  { }
  SumSegmentTree(const vector<T>& v) : n_(v.size()), t_(SEGT_SIZE(n_)) { build(v); }

  void build(const vector<T> &source) { build(source, 0, 0, n_ - 1); }
  void build(const vector<T> &source, int v, int l, int r) {
    if (l == r) {
      t_[v] = source[l];
    } else {
      int m = (l + r) / 2;
      int ch = (v << 1) + 1;
      build(source, ch, l, m);
      build(source, ch + 1, m + 1, r);
      upd(v, ch);
    }
  }
  inline void upd(int v, int ch) { t_[v] = t_[ch] + t_[ch + 1]; }

  void set(int pos, T val) { set(0, 0, n_ - 1, pos, val); }
  void set(int v, int l, int r, int pos, T val) {
    if (l == r) {
      t_[v] = val;
      return;
    }
    int m = (l + r) / 2;
    int ch = (v << 1) + 1;
    if (pos <= m) set(ch, l, m, pos, val);
    else set(ch + 1, m + 1, r, pos, val);
    upd(v, ch);
  }
  void add(int pos, int delta) { add(0, 0, n_ - 1, pos, delta); }
  void add(int v, int l, int r, int pos, int delta) {
    while (l <= r) {
      t_[v] += delta;
      if (l == r) break;
      int m = (l + r) / 2;
      int ch = (v << 1) + 1;
      if (pos <= m) { v = ch; r = m; }
      else { v = ch + 1; l = m + 1; }
    }
  }
  void add_kth(int k, int delta) { add_kth(0, 0, n_ - 1, k, delta); }
  void add_kth(int v, int l, int r, int k, int delta) {
    if (t_[v] < k) return;
    while (l <= r) {
      t_[v] += delta;
      if (l == r) break;
      int m = (l + r) / 2;
      int ch = (v << 1) + 1;
      if (t_[ch] >= k) { v = ch; r = m; }
      else { v = ch + 1; l = m + 1; k -= t_[ch]; }
    }
  }

  int get_kth(int k) const { return get_kth(0, 0, n_ - 1, k); }
  int get_kth(int v, int l, int r, int k) const {
    if (t_[v] < k) return -1;
    while (l < r) {
      int m = (l + r) / 2;
      int ch = (v << 1) + 1;
      if (t_[ch] >= k) { v = ch; r = m; }
      else { v = ch + 1; l = m + 1; k -= t_[ch]; }
    }
    return l;
  }

  int n_;
  vector<T> t_;
};
//~ END `SumSegmentTree`

//~ BEGIN `SumRangeAssigmentSegmentTree`
// required: SEGT_SIZE
template <class T>
struct SumRangeAssigmentSegmentTree {
  static const T DEFAULT = std::numeric_limits<T>::min();

  SumRangeAssigmentSegmentTree(int n) : SumRangeAssigmentSegmentTree(vector<T>(n)) { }
  SumRangeAssigmentSegmentTree(const vector<T> &v)
      : n_(v.size()),
        t_(SEGT_SIZE(n_)),
        v_(SEGT_SIZE(n_), DEFAULT),
        cnt_(SEGT_SIZE(n_)) {
    build(v);
  }

  void build(const vector<T> &source) { build(source, 0, 0, n_ - 1); }
  void build(const vector<T> &source, int v, int l, int r) {
    if (l == r) {
      t_[v] = source[l];
      cnt_[v] = 1;
    } else {
      int m = (l + r) / 2;
      int ch = (v << 1) + 1;
      build(source, ch, l, m);
      build(source, ch + 1, m + 1, r);
      upd(v, ch);
      cnt_[v] = cnt_[ch] + cnt_[ch+1];
    }
  }
  inline void upd(int v, int ch) {
    if (v_[v] != DEFAULT) {
      v_[ch] = v_[ch + 1] = v_[v];
      t_[ch] = cnt_[ch] * v_[v];
      t_[ch+1] = cnt_[ch+1] * v_[v];
      v_[v] = DEFAULT;
    }
    t_[v] = t_[ch] + t_[ch + 1];
  }
  void setv(int l, int r, const T& val) {setv(0, 0, n_ - 1, l, r, val); }
  void setv(int v, int l, int r, int ll, int rr, const T& val) {
    if (ll > rr) return;
    if (l == ll && r == rr) {
      v_[v] = val;
      t_[v] = val * cnt_[v];
    } else {
      int m = (l + r) / 2;
      int ch = (v << 1) + 1;
      upd(v, ch);
      setv(ch, l, m, ll, min(m, rr), val);
      setv(ch + 1, m + 1, r, max(ll, m + 1), rr, val);
      upd(v, ch);
    }
  }
  int get_kth(int k) { return get_kth(0, 0, n_ - 1, k); }
  int get_kth(int v, int l, int r, int k) {
    if (t_[v] < k) return -1;
    while (l < r) {
      int m = (l + r) / 2;
      int ch = (v << 1) + 1;
      upd(v, ch);
      if (t_[ch] >= k) { v = ch; r = m; }
      else { v = ch + 1; l = m + 1; k -= t_[ch]; }
    }
    return l;
  }

  int n_;
  vector<T> t_;
  vector<T> v_;
  vector<T> cnt_;
};
//~ END `SumRangeAssigmentSegmentTree`

//~ BEGIN `MaxSegmentTree`
// required: SEGT_SIZE
template <class T> struct MaxSegmentTree {
  MaxSegmentTree(int n) : n_(n), t_(SEGT_SIZE(n_))  { }
  MaxSegmentTree(const vector<T>& v) : n_(v.size()), t_(SEGT_SIZE(n_)) { build(v); }

  void build(const vector<T> &source) { build(source, 0, 0, n_ - 1); }
  void build(const vector<T> &source, int v, int l, int r) {
    if (l == r) {
      t_[v] = source[l];
    } else {
      int m = (l + r) / 2;
      int ch = (v << 1) + 1;
      build(source, ch, l, m);
      build(source, ch + 1, m + 1, r);
      upd(v, ch);
    }
  }
  inline void upd(int v, int ch) { t_[v] = max(t_[ch], t_[ch + 1]); }

  int IndexOfFirstGreaterOrEqualThan(int l, const T& given) const {
    return IndexOfFirstGreaterOrEqualThan(0, 0, n_ - 1, l, n_ -1, given);
  }
  int IndexOfFirstGreaterOrEqualThan(int l, int r, const T& given) const {
    return IndexOfFirstGreaterOrEqualThan(0, 0, n_ - 1, l, r, given);
  }
  int IndexOfFirstGreaterOrEqualThan(int v, int l, int r, int ll, int rr, const T& given) const {
    if (ll > rr) return -1;
    if (t_[v] < given) return -1;
    if (l == r) return l;
    int m = (l + r) / 2;
    int ch = (v << 1) + 1;
    int res = IndexOfFirstGreaterOrEqualThan(ch, l, m, ll, min(m, rr), given);
    if (res != -1) return res;
    return IndexOfFirstGreaterOrEqualThan(ch+1, m+1, r, max(ll, m+1), rr, given);
  }
  int n_;
  vector<T> t_;
};
//~ END `MaxSegmentTree`

#endif
