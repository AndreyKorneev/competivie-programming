#include "algs/all.h"

int n, m, q;
int f[100][100];

struct I {
  int x, y, p;
  void read() {
    cin >> x >> y >> p;
    --x; --y;
  }
};

constexpr int INF = numeric_limits<int>::min() / 2;

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m >> q;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> f[i][j];
    vector<I> v(q);
    for (auto& item : v) item.read();
    int answer_value = INF;
    vector<int> answer(q, -1);
    for (int mask = 0; mask < (1 << v.size()); ++mask) {
      vector<int> la(q, -1);
      for (int j = 0; j < la.size(); ++j) la[j] = ((1 << j) & mask) ? 1 : -1;
      int lv = 0;
      for (int i = 0; i < la.size(); ++i) {
        lv += v[i].p * la[i] * f[v[i].x][v[i].y];
        for (int j = i + 1; j < la.size(); ++j) {
          int dist = abs(v[i].x - v[j].x) + abs(v[i].y - v[j].y);
          if (dist == 1) {
            lv += v[i].p * v[j].p * la[i] * la[j];
          }
        }
      }
      if (lv > answer_value) {
        answer_value = lv;
        answer = la;
      }
    }
    cout << answer_value << endl;
    print_vector_no_size(answer);
  }
  return 0;
}
