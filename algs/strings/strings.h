#ifndef STRINGS_STRINGS_H_
#define STRINGS_STRINGS_H_
#include "algs/common.h"

//~ BEGIN ZFunction
vector<int> ZFunction(string s) {
  vector<int> z(s.size());
  for (int i = 1, l = 0, r = 1; i < z.size(); ++i) {
    if (i < r) z[i] = min(z[i - l], r - i);
    while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] > r) { l = i; r = i + z[i]; }
  }
  return z;
}
//~ END ZFunction

#endif
