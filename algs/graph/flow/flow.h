#ifndef GRAPH_FLOW_FLOW_H_
#define GRAPH_FLOW_FLOW_H_
#include "algs/common.h"
#include "algs/graph/graph.h"

//~ BEGIN `FlowEdge`
// required: Edge
struct FlowEdge : Edge {
  int capacity;
  int flow;

  FlowEdge() {}
  FlowEdge(int from, int to, int capacity, int cost, int idx)
      : Edge(from, to, cost, idx), capacity(capacity), flow(0) {}

  int remained() const { return capacity - flow; }
};
//~ END `FlowEdge`

//~ BEGIN `FlowSolver`
// required: FlowEdge, lli
struct FlowSolver {
  FlowSolver(int n) : n(n), source(0), sink(n-1), g(n) { }

  void AddEdge(int from, int to, int capacity, int cost = 1,
               bool undirected = false) {
    edges.emplace_back(from, to, capacity, cost, (int)edges.size());
    g[from].push_back(edges.back().idx);
    edges.emplace_back(to, from, 0, -cost, (int)edges.size());
    g[to].push_back(edges.back().idx);
    if (undirected) {
      AddEdge(to, from, capacity, cost, false);
    }
  }

  int n;
  int source, sink;
  vector<vector<int>> g;
  vector<FlowEdge> edges;
  lli flow = 0;
  lli flow_cost = 0;
};
//~ END `FlowSolver`

#endif
