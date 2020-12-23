#ifndef GRAPH_BRIDGES_H_
#define GRAPH_BRIDGES_H_
#include "algs/common.h"
#include "algs/graph/graph.h"
#include "algs/graph/tree.h"

//~ BEGIN `BridgeFinder`
// required: Graph, Tree
struct BridgeFinder {
  BridgeFinder(const Graph* graph)
      : graph_(graph),
        tin(graph->N()),
        tout(graph->N()),
        min_tin(graph->N()),
        is_cut_point(graph->N()),
        scc_id(graph->N()) {
    dfs(0, -1);
    //mark_visited(-1);
  }

  void mark_visited(int v) {
    while (!visited.empty()) {
      int vertex = visited.top();
      visited.pop();
      scc_id[vertex] = scc_cnt;
      if (vertex == v) break;
    }
    ++scc_cnt;
  }

  void dfs(int v, int p) {
    tin[v] = time_++;
    min_tin[v] = tin[v];
    visited.push(v);
    int children = 0;
    for (const auto& e : graph_->g[v]) {
      auto to = e.next(v);
      if (to == p) continue;
      if (tin[to] == 0) {
        dfs(to, v);
        min_tin[v] = min(min_tin[v], min_tin[to]);
        ++children;
      }
      min_tin[v] = min(min_tin[v], tin[to]);
      if (min_tin[to] >= tin[v]) is_cut_point[to] = 1;
      if (min_tin[to] > tin[v]) {
        bridges.push_back(e);
        mark_visited(to);
      }
    }
    if (p == -1 && children <= 1) {
      is_cut_point[v] = 1;
    }
    tout[v] = time_++;
  }

  Tree* GetSCCTree() {
    vector<Edge> scc_edges;
    for (const auto& e : bridges) {
      scc_edges.push_back(Edge(scc_id[e.from], scc_id[e.to]));
    }
    return new Tree(scc_cnt, scc_edges);
  }

  const Graph* graph_;
  int time_ = 1;
  vector<int> tin, tout, min_tin;
  vector<Edge> bridges;
  vector<bool> is_cut_point;

  int scc_cnt = 0;
  vector<int> scc_id;
  stack<int> visited;
};
//~ END `BridgeFinder`

#endif
