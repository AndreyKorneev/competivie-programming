#ifndef DATA_STRUCTURES_PERMUTATION_H_
#define DATA_STRUCTURES_PERMUTATION_H_

#include "algs/common.h"
//~ BEGIN SplitToCycles
using Permutation = vector<int>;
vector<vector<int>> SplitToCycles(const Permutation& permutation) {
  vector<vector<int>> result;
  vector<int> used(permutation.size());
  for (int i = 0; i < permutation.size(); ++i) {
    if (used[i]) continue;
    vector<int> cycle;
    while (!used[i]) {
      used[i] = 1;
      cycle.push_back(i);
      i = permutation[i];
    }
    result.push_back(cycle);
  }
  return result;
}
//~ END SplitToCycles

#endif
