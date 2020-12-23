#include "algs/all.h"

constexpr int N = 1001 * 1001;
int psums[26][N];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  int n, q;
  cin >> n >> s >> q;
  for (int i = 0; i < s.size(); ++i) {
    for (int j = 0; j < 26; ++j) {
      psums[j][i + 1] = psums[j][i] + ((s[i] - 'a') == j);
    }
  }
  while (q--) {
    int l, r;
    cin >> l >> r;
    for (int i = l; i <= min(l + 51, r); ++i) {
      for (int j = i; j <= max(r - 51, r); ++j) {
        int ans = 0;

      }
    }
  }
  return 0;
}
