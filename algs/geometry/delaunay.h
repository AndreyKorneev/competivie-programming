#ifndef GEOMETRY_DELAUNAY_H_
#define GEOMETRY_DELAUNAY_H_
#include "algs/common.h"
#include "algs/geometry/point.h"

//~ BEGIN `DelaunayTriangulation`
// required: lli, Point, TriangleArea
// source: https://github.com/SYury/algo/blob/master/geom/delaunay.cpp
// alternative source: https://github.com/Vemmy124/Delaunay-Triangulation-Algorithm
// docs: https://en.wikipedia.org/wiki/Delaunay_triangulation
// docs: http://e-maxx.ru/bookz/files/skvortsov.pdf
template<class T>
T det3(T a1, T a2, T a3, T b1, T b2, T b3, T c1, T c2, T c3){
	return a1 * (b2 * c3 - c2 * b3) - a2 * (b1 * c3 - c1 * b3) + a3 * (b1 * c2 - c1 * b2);
}

template <typename TPoint, typename TResult = typename TPoint::TCoord>
struct DelaunayTriangulation {
  DelaunayTriangulation(const std::vector<TPoint>& points_input)
      : points(points_input) {
  }

  std::vector<TPoint> points{};
  std::vector<int> is_on_hull{};
  //vector<vector<Edge>> point_edges{};
  set<tuple<int, int, int>> triangles;
};
//~ END `DelaunayTriangulation`

#endif
