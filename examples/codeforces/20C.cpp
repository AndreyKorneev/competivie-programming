#include "algs/all.h"

int main() {
  ios_base::sync_with_stdio(false);
  auto* g = ReadGraph(/*unordered=*/true, /*weighted=*/true);
  auto path = Dijkstra(g, 0).Do().PathTo(g->N() - 1);
  if (path.empty()) {
    cout << -1;
  } else {
    int v = 0;
    cout << v + 1 << ' ';
    for (const auto* edge : path) {
      v = edge->next(v);
      cout << (v + 1) << ' ';
    }
  }
  return 0;
}
