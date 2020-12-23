#ifndef STRINGS_PALINDROME_H_
#define STRINGS_PALINDROME_H_
#include "algs/common.h"
#include "algs/data_structures/collections.h"

//~ BEGIN IsPalindrome
bool IsPalindrome(const string& s) {
  int n = s.size();
  for (int i = 0, j = n - 1; i < j; i++, j--) {
    if (s[i] != s[j]) return false;
  }
  return true;
}
//~ END IsPalindrome
//
//~ BEGIN MakePalindrome
// required: Counter
std::optional<string> MakePalindrome(const string& s) {
  int n = s.size();
  auto cnt = Counter(s);
  int odd_cnt = 0;
  for (auto& [_, c] : cnt) odd_cnt += c % 2;
  if (odd_cnt > n % 2) return {};
  int i = 0, j = n - 1;
  string res(n, ' ');
  for (auto [ch, count] : cnt) {
    while (count > 1) { count -= 2; res[i++] = ch; res[j--] = ch; }
    if (count) res[n/2] = ch;
  }
  return res;
}
//~ END MakePalindrome

#endif

