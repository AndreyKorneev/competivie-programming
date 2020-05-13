#include "algs/all.h"

constexpr int MAXV = 10;
constexpr int MAXP = 10;
constexpr int MAXS = 10;
constexpr int MAXQ = 10;

int main() {
  std::srand(std::time(nullptr));
  ios_base::sync_with_stdio(false);
  int n = rand_int(1, MAXS), m = rand_int(1, MAXS);
  int q = 0;
  auto probability = rand_float();
  vector<vector<int>> v(n, vector<int>(m));
  vector<vector<int>> p(n, vector<int>(m, -1000));
  q = 1;
  int k = rand_int(0, (n + 1) / 2);
  p[0][k] = rand_int(-MAXP, MAXP);
  int mi = 0, mj = k;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    v[i][j] = rand_int(-MAXV, MAXV);
    auto v = rand_float();
    debug(v, probability);
    if ((i != 0 || j != k) && v < probability && q < MAXQ) {
      p[i][j] = rand_int(-MAXP, MAXP);
      ++q;
      mi = max(mi, i); mj = max(mj, j);
    }
  }
  n = mi + 1; m = mj + 1;
  cout << 1 << endl;
  cout << n << ' ' << m << ' ' << q << endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) cout << v[i][j] << ' ';
    cout << endl;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (p[i][j] == -1000) continue;
      cout << (i + 1) << ' ' << (j + 1) << ' ' << p[i][j] << endl;
    }
  }
  cout << endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (p[i][j] == -1000) cout << "     ";
      else cout << setw(4) << p[i][j] << ' ';
    }
    cout << endl;
  }
  return 0;
}
