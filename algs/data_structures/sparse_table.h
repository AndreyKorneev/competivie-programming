#ifndef DATA_STRUCTURES_SPARSE_TABLE_H_
#define DATA_STRUCTURES_SPARSE_TABLE_H_

#include "algs/common.h"
//~ BEGIN SparseTable
template<typename T, const T& (*Func)(const T&, const T&)>
struct SparseTable {
  SparseTable(const vector<T>& v) : n(v.size()), level_(n + 1) {
    for (int i = 2; i < level_.size(); ++i) level_[i] = 1 + level_[i / 2];
    table_.resize(level_.back() + 1);
    table_[0] = v;
    for (int k = 1; k < table_.size(); ++k) {
      int offset = (1 << (k - 1));
      table_[k].resize(n);
      for (int i = 0; i + offset < n; ++i) {
        table_[k][i] = Func(table_[k-1][i], table_[k-1][i + offset]);
      }
    }
  }

  const T& Query(int from, int to) const {
    auto level = level_[to - from + 1];
    return Func(table_[level][from], table_[level][to + 1 - (1 << level)]);
  }

  int n;
  vector<int> level_;
  vector<vector<T>> table_;
};
//~ END SparseTable

#endif
