#ifndef GRAPH_FLOW_DINIC_H_
#define GRAPH_FLOW_DINIC_H_
#include "algs/common.h"
#include "algs/graph/flow/flow.h"
#include <limits>

//~ BEGIN `Dinic`
// required: FlowSolver, all
struct Dinic : public FlowSolver {
  Dinic(int n)
      : FlowSolver(n), q(2 * n), distances(n), ptr(n) {}

  inline void qpush(int v) { q[qt++] = v; }
  inline int qempty() const { return qh == qt; }
  inline int qpop() { return q[qh++]; }
  inline void qclean() { qh = qt = 0; }

  bool bfs() {
    qh = qt = 0;
    std::fill(all(distances), -1);
    qpush(source);
    distances[source] = 0;
    while (!qempty()) {
      int v = qpop();
      for (auto ei : g[v]) {
        auto& e = edges[ei];
        if (!e.remained()) continue;
        int to = e.next(v);
        if (distances[to] == -1) {
          distances[to] = distances[v] + 1;
          qpush(to);
        }
      }
    }
    return distances[sink] != -1;
  }

  int push(int v, int flow) {
    if (flow == 0) return 0;
    if (v == sink) return flow;
    for (int& i = ptr[v]; i < g[v].size(); ++i) {
      auto& e = edges[g[v][i]];
      int to = e.next(v);
      if (distances[to] != distances[v] + 1) continue;
      if (int pushed = push(to, min(flow, e.remained())); pushed) {
        e.flow += pushed;
        edges[e.idx ^ 1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

  void solve() {
    while (bfs()) {
      std::fill(all(ptr), 0);
      int pushed;
      while ( (pushed = push(0, std::numeric_limits<int>::max())) ) {
        flow += pushed;
      }
    }
  }

  vector<int> q;
  vector<int> distances;
  vector<int> ptr;

  int qh = 0, qt = 0;
};
//~ END `Dinic`

#endif
