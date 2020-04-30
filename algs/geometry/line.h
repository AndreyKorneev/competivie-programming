#ifndef GEOMETRY_LINE_H_
#define GEOMETRY_LINE_H_
#include "algs/common.h"
#include "algs/geometry/point.h"

//~ BEGIN `Line`
// required: Point, EPS, Determinator
template <typename TPoint = Point<int>> struct Line {
  double a, b, c;

  Line() {}

  Line(const TPoint &p1, const TPoint &p2) {
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = -a * p1.x;
    c += -b * p1.y;
  }

  int test(const TPoint &p) const {
    double res = a * p.x + b * p.y + c;
    if (fabs(res) < EPS)
      return 0;
    return (res > 0 ? 1 : -1);
  }

  double vDist() const { return sqrt(a * a + b * b); }

  double distance(const TPoint &p) const {
    return fabs(a * p.x + b * p.y + c) / vDist();
  }

  optional<Point<double>> Intersection(const Line<TPoint> &second) const {
    auto det = Determinator<double>(a, b, second.a, second.b);
    if (fabs(det) < EPS) return {};
    return Point<double>{-Determinator<double>(c, b, second.c, second.b) / det,
                         -Determinator<double>(a, c, second.a, second.c) / det};
  }
};
//~ END `Line`

//~ BEGIN `Segment2D`
// required: Line
template <typename TPoint = Point<int>>
struct Segment2D {
  TPoint from, to;

  Segment2D() {}
  Segment2D(const TPoint& f, const TPoint& t) : from(f), to(t) {}

  Line<TPoint> ToLine() const { return Line(from, to); }

  template <typename U> bool InRange(const Point<U> &p) const {
    return min(from.x, to.x) - EPS <= p.x && p.x <= max(from.x, to.x) + EPS &&
           min(from.y, to.y) - EPS <= p.y && p.y <= max(from.y, to.y);
  }

  optional<Point<double>> Intersection(const Segment2D<TPoint> other) const {
    auto candidate = ToLine().Intersection(other.ToLine());
    if (!candidate.has_value()) return {};
    auto p = candidate.value();
    if (InRange(p) && other.InRange(p)) {
      return p;
    }
    return {};
  }
};
//~ END `Segment2D`

#endif
