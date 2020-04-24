#ifndef GRAPH_SHORTEST_SOLVER_H_
#define GRAPH_SHORTEST_SOLVER_H_
#include "algs/common.h"
#include "algs/graph/graph.h"

//~ BEGIN `ShortestPathSolver`
// required: Graph, lli
template <typename T = lli>
struct SumF {
  using TCost = T;
  static T MaxValue() { return std::numeric_limits<T>::max() / 2; }
  static T Default() { return 0ll; }
  static T Sum(const T& from, const Edge& e) { return from + e.cost; }
};
template <typename T = lli>
struct SumLastF {
  using TCost = pair<T, int>;
  static TCost MaxValue() {
    return make_pair(std::numeric_limits<T>::max() / 2, -1);
  }
  static TCost Default() { return make_pair(static_cast<T>(0), 0); }
  static TCost Sum(const TCost& from, const Edge& e) {
    return make_pair(from.first + e.cost, e.cost);
  }
};
template <typename TSum = SumF<lli>>
struct ShortestPathSolver {
 public:
  ShortestPathSolver(const Graph* g, int source)
      : graph_(g),
        source_(source),
        distances(g->N(), TSum::MaxValue()),
        parents(g->N()) {}
  ShortestPathSolver<TSum>& Do() {
    Run();
    return *this;
  }
  virtual void Run() {}
  virtual ~ShortestPathSolver() {}

  const Graph* graph_;
  const int source_;
  vector<typename TSum::TCost> distances;
  vector<const Edge*> parents;
  typename TSum::TCost DistanceOr(int to, typename TSum::TCost value) {
    return parents[to] == nullptr && to != source_ ? value : distances[to];
  }
};
//~ END `ShortestPathSolver`

#endif
