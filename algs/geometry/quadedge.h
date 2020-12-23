#ifndef GEOMETRY_QUADEDGE_H_
#define GEOMETRY_QUADEDGE_H_
#include "algs/common.h"
#include "algs/geometry/point.h"
#include <limits>

//~ BEGIN `QuadEdge`
// required: Point, Clockwise, CounterClockwise
// source: https://github.com/SYury/algo/blob/master/geom/delaunay.cpp
// docs: https://cp-algorithms.com/geometry/delaunay.html
template <typename TPoint = Point<int>>
struct QuadEdge {
  QuadEdge* rev() const { return rot->rot; }
  QuadEdge* next() const { return rot->rev()->onext->rot; }
  QuadEdge* oprev() const { return rot->onext->rot; }
  TPoint dest() const { return rev()->origin; }

  template <typename TResult>
  bool left_of(const TPoint& p) const {
    return CounterClockwise<TPoint, TResult>(p, origin, dest());
  }
  template <typename TResult>
  bool right_of(const TPoint& p) const {
    return Clockwise<TPoint, TResult>(p, origin, dest());
  }

  TPoint origin;
  QuadEdge* rot = nullptr;
  QuadEdge* onext = nullptr;
  bool used = false;
};

template <typename TPoint = Point<int>>
QuadEdge<TPoint> * make_edge(TPoint from, TPoint to){
  static TPoint inf_pt = {std::numeric_limits<typename TPoint::TCoord>::max(),
                          std::numeric_limits<typename TPoint::TCoord>::max()};
  auto* e1 = new QuadEdge<TPoint>;
  auto* e2 = new QuadEdge<TPoint>;
  auto* e3 = new QuadEdge<TPoint>;
  auto* e4 = new QuadEdge<TPoint>;
  e1->origin = from; e2->origin = to;
  e3->origin = e4->origin = inf_pt;
  e1->rot = e3; e2->rot = e4;
  e3->rot = e2; e4->rot = e1;
  e1->onext = e1; e2->onext = e2;
  e3->onext = e4; e4->onext = e3;
  return e1;
}

template <typename TPoint = Point<int>>
void splice(QuadEdge<TPoint>* a, QuadEdge<TPoint>* b) {
  swap(a->onext->rot->onext, b->onext->rot->onext);
  swap(a->onext, b->onext);
}

template <typename TPoint = Point<int>>
void delete_edge(QuadEdge<TPoint>* e) {
  splice(e, e->oprev());
  splice(e->rev(), e->rev()->oprev());
}

template <typename TPoint = Point<int>>
QuadEdge<TPoint>* connect(QuadEdge<TPoint>* a, QuadEdge<TPoint>* b) {
  QuadEdge<TPoint>* e = make_edge(a->dest(), b->origin);
  splice(e, a->next());
  splice(e->rev(), b);
  return e;
}
//~ END `QuadEdge`

#endif
