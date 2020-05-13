#ifndef STRINGS_SUFFIX_ARRAY_H_
#define STRINGS_SUFFIX_ARRAY_H_
#include "algs/common.h"

//~ BEGIN SuffixArray
// required: all
// source: https://codeforces.com/edu/course/2/lesson/2/1
struct SuffixArray {
  SuffixArray(const string& input_string) : s(input_string), n(s.size() + 1) {
    // Initialization.
    s += " ";
    order.resize(n);
    std::iota(all(order), 0);
    vector<int> p(n), c(n), new_c(n), cnt(n);
    // Stage 0 - sort by a single character.
    sort(all(order), [&s = s](int a, int b) { return s[a] < s[b]; });
    for (int i = 1; i < n; ++i)
      c[order[i]] = c[order[i - 1]] + (s[order[i]] != s[order[i - 1]]);
    // Radix sort.
    for (int k = 1; k < s.length() && (c.back() + 1 < n); k <<= 1) {
      std::fill(all(cnt), 0);
      for (int i = 0; i < n; ++i) p[i] = (order[i] + n - k) % n;
      for (auto& a : p) cnt[c[a]]++;
      for (int i = 1; cnt[i - 1] < n; ++i) cnt[i] += cnt[i - 1];
      // Compute new order.
      for (int i = n - 1; i >= 0; --i) order[--cnt[c[p[i]]]] = p[i];
      // Re-compute classes of equivalence.
      new_c[order[0]] = 0;
      for (int i = 1; i < n; ++i) {
        new_c[order[i]] = new_c[order[i - 1]] +
                          (c[order[i]] != c[order[i - 1]] ||
                           c[(order[i] + k) % n] != c[(order[i - 1] + k) % n]);
      }
      c = new_c;
    }

    suffix_to_order.resize(n);
    for (int i = 0; i < n; ++i) suffix_to_order[order[i]] = i;
    ComputeLcp();
  }


  void ComputeLcp() {
    lcp.resize(order.size());
    for (int i = 0, common = 0; i + 1 < order.size(); ++i, common = max(0, common - 1)) {
      int j = order[suffix_to_order[i] - 1];
      while (charAt(i + common) == charAt(j + common)) ++common;
      lcp[suffix_to_order[i]] = common;
    }
  }

  pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
  find_range(const string &pattern) const {
    auto l = order.begin(), r = order.end();
    for (int i = 0; i < pattern.size(); ++i) {
      if (l + 1 < r) {
        l = lower_bound(l, r, pattern[i], [this, i](int pos, char c) {
          return charAt(pos + i) < c;
        });
        r = upper_bound(l, r, pattern[i], [this, i](char c, int pos) {
          return c < charAt(pos + i);
        });
      }
      if (l >= r || s[((*l) + i) % s.size()] != pattern[i]) {
        return {order.end(), order.end()};
      }
    }
    return {l, r};
  }

  size_t find(const string& pattern) const {
    auto [l, r] = find_range(pattern);
    return l < r ? static_cast<size_t>(*l) : string::npos;
  }

  char charAt(int pos) const { return s[(n + pos) % n]; }

  string s;
  int n;
  vector<int> order;
  vector<int> suffix_to_order;
  vector<int> lcp;
};
//~ END SuffixArray

#endif
