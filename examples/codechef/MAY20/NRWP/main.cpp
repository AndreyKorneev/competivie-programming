#include "algs/all.h"

constexpr int INF = numeric_limits<int>::min() / 3;

int n, m, q;
struct Point2 {
  int x, y;

  int value;
  int p_index = -1;
  int p_value;

  bool used;

  int dist(const Point2& that) const {
    return abs(x - that.x) + abs(y - that.y);
  }
};
vector<vector<Point2>> field;
// Vector of signs {-1, +1} and the answer value.
vector<int> answer;
int answer_value;

void read() {
  cin >> n >> m >> q;
  field = vector<vector<Point2>>(n, vector<Point2>(m));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    cin >> field[i][j].value;
    field[i][j].x = i; field[i][j].y = j;
  }
  for (int i = 0; i < q; ++i) {
    int x, y;
    cin >> x >> y;
    --x; --y;
    cin >> field[x][y].p_value;
    field[x][y].p_index = i;
  }
  answer_value = 0;
  answer = vector<int>(q);
}

void print_answer() {
  cout << answer_value << endl;
  for (auto& item : answer) cout << item << ' ';
}

int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};
bool can(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < m && field[x][y].p_index != -1 && !field[x][y].used;
}

// Order points by BFS.
vector<Point2> bfs() {
  vector<Point2> result;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (!can(i, j)) continue;
    queue<int> q; q.push(i); q.push(j);
    field[i][j].used = 1;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      int y = q.front(); q.pop();
      result.push_back(field[x][y]);
      for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (can(nx, ny)) {
          field[nx][ny].used = 1;
          q.push(nx); q.push(ny);
        }
      }
    }
  }
  return result;
}

int get_sign(int state) { return state ? 1 : -1; }

void solve(const vector<Point2>& points) {
  // How many previous values to store in DP.
  int k = 0;
  // For each point compute the indexes of adjacent points.
  vector<vector<int>> prev_points(points.size());
  for (int from = 0; from < points.size(); ++from)
    for (int to = from + 1; to < points.size(); ++to)
      if (points[from].dist(points[to]) == 1) {
        k = max(k, to - from);
        prev_points[to].push_back(from);
      }
  // Compute straight forward dynamic (previous_mask, current vertex) -> max answer
  vector<vector<int>> dp(points.size() + 1, vector<int>((1 << k), INF));
  vector<vector<pii>> parents(points.size() + 1, vector<pii>((1 << k)));

  dp[0][0] = 0;
  for (int i = 0; i < points.size(); ++i) {
    auto& cur_point = points[i];
    for (int prev_mask = 0; prev_mask < (1 << k); ++prev_mask) {
      if (dp[i][prev_mask] == INF) continue;
      for (int cur_value = 0; cur_value < 2; ++cur_value) {
        int sign = get_sign(cur_value);
        int cost = cur_point.value;
        for (auto& prev_index : prev_points[i]) {
          int offset = k - (i - prev_index);
          cost += get_sign(prev_mask & (1 << offset)) * points[prev_index].p_value;
        }
        cost = dp[i][prev_mask] + sign * cur_point.p_value * cost;
        int new_mask = (prev_mask >> 1) | (cur_value * (k > 0) * (1 << (k - 1)));
        if (cost > dp[i+1][new_mask]) {
          dp[i+1][new_mask] = cost;
          parents[i+1][new_mask] = {sign, prev_mask};
        }
      }
    }
  }
  // Find the last max with maximum answer value.
  int mask = 0;
  for (int i = 1; i < (1 << k); ++i) if (dp.back()[i] > dp.back()[mask]) mask = i;
  // Restore answer.
  answer_value += dp.back()[mask];
  for (int i = dp.size() - 2; i >= 0; --i) {
    const auto& p = points[i];
    answer[p.p_index] = parents[i+1][mask].first;
    mask = parents[i+1][mask].second;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T;
  cin >> T;
  while(T--) {
    read();
    solve(bfs());
    print_answer();
  }
  return 0;
}
