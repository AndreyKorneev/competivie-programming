#ifndef GRAPH_GRAPH_H_
#define GRAPH_GRAPH_H_
#include "algs/common.h"
#include "algs/graph/graph.h"

//~ BEGIN `Tree`
// required: Graph
struct Tree : public Graph {
  Tree() : Graph() {}
  Tree(const vector<vector<Edge>>& g) : Graph(g) {}
  Tree(int n, const vector<Edge>& edges, bool unordered = true)
      : Graph(n, edges, unordered) {}

  void dfs(int v, int parent, int d) {
    depth[v] = d;
    parents[v][0] = parent;
    tin[v] = time_++;
    for (int i = 1; i < L_; ++i) {
      parents[v][i] = parents[parents[v][i - 1]][i - 1];
    }
    for (const auto& e : g[v]) {
      if (e.next(v) == parent) continue;
      dfs(e.next(v), v, d + 1);
    }
    tout[v] = time_++;
  }

  void PrebuildLCA(int root) {
    if (!parents.empty()) return;
    while ((1 << L_) <= 2 * N()) ++L_;
    parents = vector<vector<int>>(N(), vector<int>(L_, root));
    depth.resize(N());
    tin.resize(N());
    tout.resize(N());
    dfs(root, root, 0);
  }

  bool IsParent(int a, int b) { return tin[a] <= tin[b] && tout[a] >= tout[b]; }

  int LCA(int a, int b) {
    if (IsParent(a, b)) return a;
    if (IsParent(b, a)) return b;
    for (int l = L_ - 1; l >= 0; --l) {
      if (!IsParent(parents[a][l], b)) {
        a = parents[a][l];
      }
    }
    return parents[a][0];
  }

  int Distance(int a, int b) {
    PrebuildLCA(0);
    int p = LCA(a, b);
    return depth[a] + depth[b] - 2 * depth[p];
  }

  int L_ = 1, time_ = 1;
  vector<int> depth, tin, tout;
  vector<vector<int>> parents;
};
//~ END `Tree`
#endif
