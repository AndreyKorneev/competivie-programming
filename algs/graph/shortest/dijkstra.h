#ifndef GRAPH_SHORTEST_DIJKSTRA_H_
#define GRAPH_SHORTEST_DIJKSTRA_H_
#include "algs/common.h"
#include "algs/graph/graph.h"
#include "algs/graph/shortest/solver.h"

//~ BEGIN `Dijkstra`
// required: ShortestPathSolver
template<typename TSum = SumF<lli>>
struct Dijkstra : public ShortestPathSolver<TSum>{
  using QT = pair<typename TSum::TCost, int>;

  Dijkstra(const Graph* g, int source) : ShortestPathSolver<TSum>(g, source) {}

  void Run() override {
    priority_queue<QT, vector<QT>, std::greater<QT>> q;
    distances[source_] = TSum::Default();
    q.emplace(distances[source_], source_);
    while (!q.empty()) {
      auto [cost, v] = q.top(); q.pop();
      if (cost > distances[v]) continue;
      for (const auto& e : graph_->g[v]) {
        int to = e.next(v);
        auto total = TSum::Sum(cost, e);
        if (total < distances[to]) {
          distances[to] = total;
          parents[to] = &e;
          q.emplace(total, to);
        }
      }
    }
  }

  using B = ShortestPathSolver<TSum>;
  using B::graph_;
  using B::source_;
  using B::distances;
  using B::parents;
};
//~ END `Dijkstra`

#endif
