#ifndef GRAPH_FLOW_MIN_COST_MAX_FLOW_H_
#define GRAPH_FLOW_MIN_COST_MAX_FLOW_H_
#include "algs/common.h"
#include "algs/graph/flow/flow.h"

//~ BEGIN `MinCostMaxFlowSolver`
// required: FlowSolver, all
constexpr int FLOW_INF = std::numeric_limits<int>::max() / 3;
struct MinCostMaxFlowSolver : public FlowSolver {

  MinCostMaxFlowSolver(int n)
      : FlowSolver(n), q(2 * n), inq(n), parents(n), distances(n) {}

  inline void qpush(int v) {
    if (!inq[v]) {
      inq[v] = 1;
      q[qt++] = v;
      if (qt == q.size()) qt = 0;
    }
  }
  inline int qempty() const { return qh == qt; }
  inline int qpop() {
    int res = q[qh++];
    if (qh == q.size()) qh = 0;
    inq[res] = 0;
    return res;
  }

  bool shortest_path() {
    qh = qt = 0;
    std::fill(all(distances), FLOW_INF);
    qpush(source);
    distances[source] = 0;
    while (!qempty()) {
      int v = qpop();
      for (auto ei : g[v]) {
        auto& e = edges[ei];
        if (!e.remained()) continue;
        int to = e.next(v);
        if (distances[to] > distances[v] + e.cost) {
          parents[to] = ei;
          distances[to] = distances[v] + e.cost;
          qpush(to);
        }
      }
    }
    return distances[sink] < FLOW_INF;
  }

  int min_path_capacity() const {
    int res = FLOW_INF;
    int v = sink;
    while (v != source) {
      auto& e = edges[parents[v]];
      res = min(res, e.remained());
      v = e.next(v);
    }
    return res;
  }

  void push(int delta) {
    flow += delta;
    flow_cost += delta * 1ll * distances[sink];

    int v = sink;
    while (v != source) {
      auto& e = edges[parents[v]];
      auto& er = edges[parents[v] ^ 1];
      e.flow += delta;
      er.flow -= delta;
      v = e.next(v);
    }
  }

  void solve() {
    while (shortest_path()) {
      push(min_path_capacity());
    }
  }

  vector<int> q;
  vector<int> inq;
  vector<int> parents;
  vector<int> distances;

  int qh = 0, qt = 0;
};
//~ END `MinCostMaxFlowSolver`

#endif
