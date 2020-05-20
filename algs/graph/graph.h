#ifndef GRAPH_GRAPH_H_
#define GRAPH_GRAPH_H_
#include "algs/common.h"

//~ BEGIN `Edge`
struct Edge {
  int from;
  int to;
  int cost;
  int idx;

  Edge() {}
  Edge(int f, int t) : Edge(f, t, 1, -1) {}
  Edge(int f, int t, int c, int i) : from(f), to(t), cost(c), idx(i) {}

  inline int next(int v) const { return v ^ from ^ to; }
};
//~ END `Edge`

//~ BEGIN `Graph`
// required: Edge
struct Graph {
  Graph() {}
  Graph(const vector<vector<Edge>>& g) : g(g) {}
  Graph(int n, const vector<Edge>& edges, bool unordered = true) : g(n) {
    for (const auto& e : edges) {
      g[e.from].push_back(e);
      if (unordered) {
        g[e.to].push_back(e);
      }
    }
  }

  inline int N() const { return g.size(); }

  vector<vector<int>> ToVector() {
    vector<vector<int>> result(g.size());
    for (int i = 0; i < g.size(); ++i) {
      result[i].reserve(g[i].size());
      for (auto& e : g[i]) result[i].push_back(e.next(i));
    }
    return result;
  }

  vector<vector<Edge>> g;
};
//~ END `Graph`

//~ BEGIN `ReadEdges`
// required: Edge
vector<Edge> ReadEdges(int m, bool weighted = false) {
  vector<Edge> edges(m);
  for (int i = 0; i < m; ++i) {
    auto& e = edges[i];
    cin >> e.from >> e.to;
    e.idx = i;
    e.cost = 1;
    --e.from;
    --e.to;
    if (weighted) cin >> e.cost;
  }
  return edges;
}
//~ END `ReadEdges`

//~ BEGIN `ReadGraph`
// required: Graph, ReadEdges
Graph* ReadGraph(bool unordered = true, bool weighted = false) {
  int n, m;
  cin >> n >> m;
  return new Graph(n, ReadEdges(m, weighted), unordered);
}
//~ END `ReadGraph`
#endif
