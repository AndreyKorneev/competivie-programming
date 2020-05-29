#ifndef DATA_STRUCTURES_ARRAY_H_
#define DATA_STRUCTURES_ARRAY_H_

#include "algs/common.h"
//~ BEGIN prefix_sums
template<typename T, typename U>
vector<T> prefix_sums(const U& c) {
  vector<T> result(c.size());
  for (int i = 0; i < c.size(); ++i) {
    result[i] = c[i] + (i > 0) * result[i - 1];
  }
  return result;
}
//~ END prefix_sums

//~ BEGIN Vec
// source: https://codeforces.com/blog/entry/76149?#comment-606688
template<class T, class... Args>
auto Vec(size_t n, Args&&... args) {
	if constexpr(sizeof...(args) == 1)
		return vector<T>(n, args...);
	else
		return vector(n, create<T>(args...));
}
//~ END Vec

#endif
