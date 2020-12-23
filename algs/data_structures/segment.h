#ifndef DATA_STRUCTURES_SEGMENT_H_
#define DATA_STRUCTURES_SEGMENT_H_
#include "algs/common.h"

//~ BEGIN `Segment`
// required: lli
template <typename T = int>
struct Segment {
  T l, r;
  Segment() : Segment(0, -1) {}
  Segment(const T& l, const T& r) : l(l), r(r) {}

  lli len() const { return r - l + 1; }
  bool valid() const { return r >= l; }
  bool In(const T& v) { return l <= v && v <= r; }

  Segment<T> Intersect(const Segment<T>& other) const {
    return {max(l, other.l), min(r, other.r)};
  }
  bool Intersects(const Segment<T>& other) const {
    if (r < other.l) return false;
    if (l > other.r) return false;
    return true;
  }
  void IntersectInPlace(const Segment<T>& other) {
    l = max(l, other.l);
    r = min(r, other.r);
  }

  bool operator<(const Segment<T>& other) {
    if (l != other.l) return l < other.l;
    return r < other.r;
  }

};
//~ END `Segment`

#endif
