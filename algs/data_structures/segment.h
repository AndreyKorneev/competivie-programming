#ifndef DATA_STRUCTURES_SEGMENT_H_
#define DATA_STRUCTURES_SEGMENT_H_
#include "algs/common.h"

//~ BEGIN `Segment`
template <typename T = int>
struct Segment {
  T l, r;
  Segment() : Segment(0, -1) {}
  Segment(const T& l, const T& r) : l(l), r(r) {}
  lli len() const { return r - l + 1; }
  bool valid() const { return r >= l; }
  bool In(const T& v) { return l <= v && v <= r; }
  Segment<T> Intersect(const Segment<T> other) const {
    return {max(l, other.l), min(r, other.r)};
  }
  void IntersectInPlace(const Segment<T> other) {
    l = max(l, other.l);
    r = min(r, other.r);
  }
};
//~ END `Segment`

#endif
