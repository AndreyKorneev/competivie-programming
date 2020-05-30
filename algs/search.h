#ifndef SEARCH_H_
#define SEARCH_H_

#include "algs/common.h"
//~ BEGIN `binary_search_`
template<typename T>
T binary_search_(T l, T r, const std::function<bool(lli)>& check) {
  while (r - l > 1) {
    T m = (l + r) / 2;
    if (check(m)) l = m;
    else r = m;
  }
  return (check(r) ? r : l);
}
//~ END `binary_search_`

#endif

