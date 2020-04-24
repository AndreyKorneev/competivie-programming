#ifndef DEBUG_H_
#define DEBUG_H_
#include "algs/common.h"

//~ BEGIN `debug`
// required: all
#ifdef LOCAL
// Source: tourist's submission https://codeforces.com/contest/1338/submission/76397300
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(const char *s) { return to_string((string)s); }
string to_string(char c) { return to_string(string(1, c)); }
template <typename A, typename B> string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template <typename A> string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}
string to_string(const vector<bool>& v) {
  vector<string> transformed;
  transform(all(v), back_inserter(transformed), [](bool b){ return to_string(b); });
  return to_string(transformed);
}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
//~ END `debug`

#endif
