#ifndef DATA_STRUCTURES_COMPRESSED_H_
#define DATA_STRUCTURES_COMPRESSED_H_
#include "algs/common.h"
#include "algs/data_structures/collections.h"

//~ BEGIN Compressed
// required: all, Unique
template<typename C, typename T = typename C::value_type> struct Compressed {
  Compressed(const C& container) : data(Unique(container)) { }
  int Order(const T& item) const { return lower_bound(all(data), item) - data.begin(); }
  const T& At(int index) const { return data[index]; }
  vector<T> data;
};
//~ END Compressed

#endif


