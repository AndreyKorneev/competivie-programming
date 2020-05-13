#include "algs/all.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")


constexpr int INF = numeric_limits<int>::min() / 3;

int n, m, q;
vvi field;
vvi used;
vvi p;
vi ps;
vi answer;
int answer_value;

void read() {
  cin >> n >> m >> q;
  field = vvi(n, vi(m));
  p = vvi(n, vi(m, -1000));
  ps = vi(q);
  answer = vi(q);
  used = vvi(n, vi(m));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> field[i][j];
  for (int i = 0; i < q; ++i) {
    int x, y;
    cin >> x >> y >> ps[i];
    p[x-1][y-1] = i;
  }
  answer_value = 0;
}

void print_answer() {
  cout << answer_value << endl;
  print_vector_no_size(answer);
}

struct P {
  int x, y, pv, pi, fv;
  int level, index;
  int first, second;

  P(int x, int y) : x(x), y(y) {
    pi = p[x][y];
    pv = ps[pi];
    fv = field[x][y];
  }

  void transpose() { swap(x, y); }

  bool operator<(const P& other) const {
    if (level != other.level) return level < other.level;
    if (x != other.x) return x < other.x;
    return false;
  }
};

struct Area {
  Area(const vpii& v) {
    map<int, int> correct, inverse;
    int cmax = 0, imax = 0;
    for (auto& [x, y] : v) {
      points.emplace_back(x, y);
      correct[x+y]++;
      inverse[x-y]++;
      cmax = max(cmax, correct[x+y]);
      imax = max(imax, inverse[x-y]);
    }
    if (imax < cmax) for (auto& p : points) p.transpose();
    for (auto& p : points) p.level = p.x + p.y;
    sort(all(points));
    for (int i = 1; i < points.size(); ++i) points[i].level -= points[0].level;
    points[0].level = 0;
    for (int i = 0; i < points.size(); ++i) {
      points[i].index = i;
      if (levels.size() <= points[i].level) levels.push_back({});
      levels.back().push_back(i);
    }
  }
  vector<P> points;
  vector<vector<int>> levels;
  vector<vector<int>> d;
  vector<vector<int>> parents_mask;
  vector<vector<int>> parents_s;
  vi dmask;

  P main() { return points.front(); }

  void prepare() {
    d.resize(points.size() + 1);
    dmask.resize(d.size(), 0);
    parents_mask.resize(d.size());
    parents_s.resize(d.size());
    for (int i = 0; i < points.size(); ++i) {
      auto& pi = points[i];
      pi.first = i;
      pi.second = i;
      int level = points[i].level - 1;
      if (level >= 0) {
        for (int j : levels[level]) {
          const auto& pj = points[j];
          if (pi.x == pj.x || pi.y == pj.y) {
            if (pi.first == i) pi.first = j;
            else pi.second = j;
          }
        }
      }
      dmask[i] = (pi.index - pi.first);
    }
    for (int i = dmask.size() - 2; i >= 0; --i)
      dmask[i] = max(dmask[i], dmask[i + 1] - 1);
    for (int i = 0; i < d.size(); ++i) {
      d[i].resize(1 << dmask[i], INF);
      parents_mask[i].resize(1 << dmask[i]);
      parents_s[i].resize(1 << dmask[i]);
    }
    debug(dmask);
  }

  int solve() {
    prepare();
    d[0][0] = 0;
    for (int i = 0; i < points.size(); ++i) {
      const auto& p = points[i];
      for (int prev_mask = 0; prev_mask < d[i].size(); ++prev_mask) {
        if (d[i][prev_mask] == INF) continue;
        debug();
        for (int lb = 0; lb < 2; ++lb) {

          int sign = (lb ? 1 : -1);
          int cost = d[i][prev_mask] + p.fv * p.pv * sign;
          if (p.first < i) {
            int offset = p.first - p.index + dmask[i];
            cost += ((prev_mask & (1 << offset)) ? 1 : -1) * sign * p.pv *
                    points[p.first].pv;
            if (p.second < i) {
              cost += ((prev_mask & (1 << (offset + 1))) ? 1 : -1) * sign *
                      p.pv * points[p.second].pv;
            }
          }

          int new_mask = prev_mask + (1 << (dmask[i])) * lb;
          // new mask had dm[i] + 1 bit, needed d[i+1]
          int diff = max(0, dmask[i]+1 - dmask[i+1]);
          debug(prev_mask, new_mask, (new_mask >> diff));
          new_mask >>= diff;

          debug(i, prev_mask, d[i][prev_mask]);
          debug(i + 1, new_mask, cost);

          if (cost > d[i+1][new_mask]) {
            d[i+1][new_mask] = cost;
            parents_mask[i+1][new_mask] = prev_mask;
            parents_s[i+1][new_mask] = sign;
          }
        }
      }
    }
    restore_answer();
    return d.back()[0];
  }

  void restore_answer() {
    answer_value += d.back()[0];
    int mask = 0;
    for (int i = d.size() - 2; i >= 0; --i) {
      const auto& p = points[i];
      answer[p.pi] = parents_s[i+1][mask];
      mask = parents_mask[i+1][mask];
    }
  }
};

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
bool can(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < m && p[x][y] != -1000 && !used[x][y];
}

vector<Area> split() {
  vector<Area> result;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (!can(i, j)) continue;
    vpii points;
    queue<int> q; q.push(i); q.push(j);
    used[i][j] = 1;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      int y = q.front(); q.pop();
      points.emplace_back(x, y);
      for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (can(nx, ny)) {
          used[nx][ny] = 1;
          q.push(nx); q.push(ny);
        }
      }
    }
    debug(points);
    result.emplace_back(points);
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T;
  cin >> T;
  while(T--) {
    read();
    vvi tmps;
    for (auto& area : split()) {
      int res = area.solve();
      tmps.push_back({area.main().x, area.main().y, res});
    }
    print_answer();
    for (auto& v : tmps) debug(v);
  }
  return 0;
}
