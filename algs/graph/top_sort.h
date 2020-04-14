#ifndef GRAPH_TOP_SORT_H_
#define GRAPH_TOP_SORT_H_
#include "algs/common.h"
#include "algs/graph/graph.h"

//~ BEGIN `TopologicalSort`
//required: Graph
struct TopologicalSort {
  TopologicalSort(const Graph* g) : graph_(g), used(g->N()) {}

  vector<int> Order() {
    if (order.empty()) {
      for (int i = 0; i < graph_->N(); ++i) {
        dfs(i);
      }
      reverse(all(order));
    }
    return order;
  }

  void dfs(int v) {
    if (used[v]) return;
    used[v] = 1;
    for (const auto& e : graph_->g[v]) {
      dfs(e.next(v));
    }
    order.push_back(v);
  }

  const Graph* graph_;
  vector<bool> used;
  vector<int> order;
};
//~ END `TopologicalSort`
#endif
