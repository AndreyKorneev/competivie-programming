#ifndef GRAPH_SHORTEST_BFS_H_
#define GRAPH_SHORTEST_BFS_H_
#include "algs/common.h"
#include "algs/graph/graph.h"
#include "algs/graph/shortest/solver.h"

//~ BEGIN `BfsSolver`
// required: ShortestPathSolver
template<typename TSum = SumF<lli>>
struct BfsSolver : public ShortestPathSolver<TSum>{
  void Run() override {
    queue<int> q;
    distances[source_] = TSum::Default();
    q.emplace(source_);
    while (!q.empty()) {
      auto v = q.front(); q.pop();
      for (const auto& e : graph_->g[v]) {
        int to = e.next(v);
        if (parents[to] == nullptr && to != source_) {
          distances[to] = TSum::Sum(distances[v], e);
          parents[to] = &e;
          q.emplace(to);
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
//~ END `BfsSolver`

#endif
