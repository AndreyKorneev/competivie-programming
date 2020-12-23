#ifndef DATA_STRUCTURES_COLLECTIONS_H_
#define DATA_STRUCTURES_COLLECTIONS_H_
#include "algs/common.h"

//~ BEGIN Counter
template<typename C, typename T = typename C::value_type>
map<T, int> Counter(const C& container) {
  map<T, int> result;
  for (auto& c : container) result[c]++;
  return result;
}
//~ END Counter
//
//~ BEGIN Unique
template<typename C, typename T = typename C::value_type>
C Unique(const C& container) {
  set<T> res(container.begin(), container.end());
  return {res.begin(), res.end()};
}
//~ END Unique

#endif

