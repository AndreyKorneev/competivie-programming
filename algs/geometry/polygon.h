#ifndef GEOMETRY_POINT_H_
#define GEOMETRY_POINT_H_
#include "algs/common.h"
#include "algs/geometry/point.h"
#include "algs/geometry/line.h"

//~ BEGIN `Polygon`
// required: Point, Segment2D, TriangleArea, lli
enum class TestResult {Inside, Outside, OnTheBorder};

template <typename TPoint = Point<int>> struct Polygon {
  Polygon() : Polygon({}) {}
  Polygon(const vector<TPoint>& points) : points(points) {
    sides.reserve(points.size());
    for (int i = 0; i < points.size(); ++i) {
      sides.emplace_back(points[i], points[(i + 1) % points.size()]);
    }
  }

  TestResult Test(const TPoint& p) const {
    int positive = 0, negative = 0;
    for (const auto& [from, to] : sides) {
      auto area = TriangleArea<TPoint, lli>(from, to, p);
      if (area == 0) return TestResult::OnTheBorder;
      if (area > 0) ++positive;
      else ++negative;
    }
    return (positive && negative ? TestResult::Outside : TestResult::Inside);
  }

  bool IsInside(const Polygon<TPoint>& polygon) const {
    for (const auto& point : points) {
      if (polygon.Test(point) == TestResult::Outside) {
        return false;
      }
    }
    return true;
  }

  bool Intersects(const Segment2D<TPoint>& segment) const {
    for (auto& side : sides) {
      if (side.Intersection(segment).has_value()) return true;
    }
    return false;
  }

  bool Intersects(const Polygon<TPoint>& polygon) const {
    if (this->IsInside(polygon) || polygon.IsInside(*this)) {
      return true;
    }
    for (auto& side : polygon.sides) {
      if (this->Intersects(side)) {
        return true;
      }
    }
    return false;
  }

  double Area() const {
    double result = 0.0;
    for (const auto& [from, to] : sides) {
      result += TriangleArea<TPoint, lli>(from, to, {0, 0});
    }
    return result / 2;
  }
  double Perimeter() const {
    double result = 0.0;
    for (const auto& s : sides) result += s.Length();
    return result;
  }

  vector<Segment2D<TPoint>> sides;
  vector<TPoint> points;
};
//~ END `Polygon`

//~ BEGIN `ConvexHull`
// required: Point, Clockwise, CounterClockwise
// source: https://e-maxx.ru/algo/convex_hull_graham
template <typename TPoint, typename TResult = typename TPoint::TCoord>
vector<TPoint> ConvexHull(vector<TPoint> source) {
  if (source.size() <= 1) return source;
  sort(source.begin(), source.end());
  const auto& first = source.front();
  const auto& last = source.back();
  vector<TPoint> up, down;
  up.push_back(first);
  down.push_back(first);
  for (size_t i = 1; i < source.size(); ++i) {
    if (i == source.size() - 1 || Clockwise<TPoint, TResult>(first, source[i], last)) {
      while (up.size() >= 2 && !Clockwise<TPoint, TResult>(*(up.end() - 2), up.back(), source[i])) up.pop_back();
      up.push_back(source[i]);
    }
    if (i == source.size() - 1 || CounterClockwise<TPoint, TResult>(first, source[i], last)) {
      while (down.size() >= 2 && !CounterClockwise<TPoint, TResult>( *(down.end() - 2), down.back(), source[i])) down.pop_back();
      down.push_back(source[i]);
    }
  }
  for (size_t i = down.size() - 2; i > 0; --i) up.push_back(down[i]);
  return up;
}
//~ END `ConvexHull`

#endif
