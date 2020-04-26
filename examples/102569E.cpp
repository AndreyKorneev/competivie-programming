#include "algs/all.h"

int main() {
  ios_base::sync_with_stdio(false);
  auto v = prefix_sums<lli>(read_vector<int>());
  cout << -min(*min_element(all(v)), 0ll);
  return 0;
}
