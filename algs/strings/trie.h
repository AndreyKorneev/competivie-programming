#ifndef STRING_TRiE_H_
#define STRING_TRiE_H_
#include "algs/common.h"

//~ BEGIN `Trie`
template <std::size_t N>
struct Trie {
  inline int go(int root, char c) { return nodes[root][c - 'a']; }
  inline int add(int root, char c) {
    int& res = nodes[root][c - 'a'];
    if (res == 0) {
      res = ++nodes_size;
    }
    return res;
  }
  int add(const string& s) {
    int root = 1;
    for (auto c : s) root = add(root, c);
    return root;
  }
  int nodes_size = 1;
  int nodes[N][26];

  void clear() {
    memset(nodes, 0, N*26*sizeof(int));
    nodes_size = 1;
  }
};
//~ END `Trie`

#endif
