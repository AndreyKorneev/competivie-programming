#ifndef GRAPH_DSU_H_
#define GRAPH_DSU_H_
#include "algs/common.h"

//~ BEGIN `DSU`
template <std::size_t N>
struct DSU {
  DSU() { std::iota(all(parents), 0); }

  int parent(int v) {
    return (v == parents[v] ? v : (parents[v] = parent(parents[v])));
  }

  bool merge(int a, int b) {
    a = parent(a);
    b = parent(b);
    if (a == b) {
      return false;
    }
    if (rand() & 1) {
      parents[a] = b;
    } else {
      parents[b] = a;
    }
    return true;
  }

  std::array<int, N> parents;
};
//~ END `DSU`
//
//~ BEGIN `DSURanked`
struct DSURanked {
  DSURanked(int N) : N(N), parents(N), rank(N, 1) { std::iota(all(parents), 0); }

  int parent(int v) {
    return (v == parents[v] ? v : (parents[v] = parent(parents[v])));
  }

  bool merge(int a, int b) {
    a = parent(a);
    b = parent(b);
    if (a == b) {
      return false;
    }
    if (rank[a] < rank[b]) {
      parents[a] = b;
      rank[b] += rank[a];
    } else {
      parents[b] = a;
      rank[a] += rank[b];
    }
    return true;
  }

  int N;
  vector<int> parents;
  vector<int> rank;
};
//~ END `DSURanked`

#endif
