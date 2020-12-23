#ifndef GEOMETRY_POINT_H_
#define GEOMETRY_POINT_H_
#include "algs/common.h"

//~ BEGIN `EPS`
constexpr double EPS = 1e-9;
//~ END `EPS`

//~ BEGIN `PI`
const double PI = std::atan(1.0)*4;
//~ END `PI`

//~ BEGIN `Determinator`
template<typename T>
inline T Determinator(const T& a1, const T& a2, const T& a3, const T& a4) {
  return a1 * a4 - a2 * a3;
}
//~ END `Determinator`

//~ BEGIN `Point`
// required: PI, Determinator
template <typename T> struct Point {
  using TCoord = T;

  Point<T>() : Point(0, 0) {}
  Point<T>(const T& x, const T& y) : x(x), y(y) {}

  Point<T>& operator+=(const Point<T>& rhs) { *this = this->operator+(rhs); return *this; }
  Point<T>& operator-=(const Point<T>& rhs) { *this = this->operator-(rhs); return *this; }
  Point<T>& operator*=(const T& k) { *this = this->operator*(k); return *this; }
  Point<T>& operator/=(const T& k) { *this = this->operator/(k); return *this; }

  bool operator<(const Point<T> &rhs) const {
    return (this->x < rhs.x || (this->x == rhs.x && this->y < rhs.y));
  }
  bool operator==(const Point<T> &rhs) const {
    return this->x == rhs.x && this->y == rhs.y;
  }

  Point<T> operator-(const Point<T> &rhs) const { return {x - rhs.x, y - rhs.y}; }
  Point<T> operator+(const Point<T> &rhs) const { return {x + rhs.x, y + rhs.y}; }
  Point<T> operator*(const T &k) const { return {x * k, y * k}; }
  Point<T> operator/(const T &k) const { return {x / k, y / k}; }

  Point<T> Rotate(double a) const { return {x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)}; }
  Point<T> Norm() const { return *this / Length(); }
  double Length() const { return sqrtl(x * 1.0 * x + y * 1.0 * y); }
  double Distance(const Point<T> &rhs) const { return (*this - rhs).Length(); }

  double DotProduct(const Point<T> &rhs) const { return x * rhs.x + y * rhs.y; }
  template<typename TResult>
  TResult CrossProduct(const Point<T> &rhs) const { return Determinator<TResult>(x, y, rhs.x, rhs.y); }

  double PolarAngle() const {
    double alpha = atan2(y, x);
    if (alpha < 0) alpha += 2 * PI;
    return alpha;
  }
  double AngleTo(const Point<T>& rhs) { return fabs(PolarAngle() - rhs.PolarAngle()); }

  T x, y;
};
//~ END `Point`

//~ BEGIN `TriangleArea`
// required: Determinator
template <typename TPoint, typename TResult = typename TPoint::TCoord>
inline TResult TriangleArea(const TPoint& p1, const TPoint& p2,
                            const TPoint& p3) {
  auto a = p1 - p3;
  auto b = p2 - p3;
  return Determinator<TResult>(a.x, a.y, b.x, b.y);
}
//~ END `TriangleArea`

//~ BEGIN `TriangleAreaNormalized`
// required: TriangleArea
template <typename TPoint, typename TResult = typename TPoint::TCoord>
inline TResult TriangleAreaNormalized(const TPoint& p1, const TPoint& p2,
                                      const TPoint& p3) {
  auto res = TriangleArea<TPoint, TResult>(p1, p2, p3);
  res = max(res, -res);
  return res / 2;
}
//~ END `TriangleAreaNormalized`

//~ BEGIN `Clockwise`
// required: TriangleArea
template <typename TPoint, typename TResult = typename TPoint::TCoord>
bool Clockwise(const TPoint& a, const TPoint& b, const TPoint& c) {
  return TriangleArea<TPoint, TResult>(a, b, c) < 0;
}
//~ END `Clockwise`

//~ BEGIN `CounterClockwise`
template <typename TPoint, typename TResult = typename TPoint::TCoord>
bool CounterClockwise(const TPoint& a, const TPoint& b, const TPoint& c) {
  return TriangleArea<TPoint, TResult>(a, b, c) > 0;
}
//~ END `CounterClockwise`

#endif
