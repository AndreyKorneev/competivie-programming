#ifndef IO_H_
#define IO_H_
#include "algs/common.h"

//~ BEGIN `read_vector`
template <typename T>
vector<T> read_vector() {
  int n;
  cin >> n;
  vector<T> result(n);
  for (int i = 0; i < n; ++i) cin >> result[i];
  return result;
}
//~ END `read_vector`

//~ BEGIN `print_vector_no_size`
template <typename T>
void print_vector_no_size(const vector<T>& v) {
  for (const auto item : v) cout << item << ' ';
  cout << endl;
}
//~ END `print_vector_no_size`

//~ BEGIN `print_vector`
// required: print_vector_no_size
template <typename T>
void print_vector(const vector<T>& v) {
  cout << v.size() << endl;
  print_vector_no_size(v);
}
//~ END `print_vector`

//~ BEGIN `print_pair`
template <typename T, typename U>
void print_pair(const pair<T, U>& p) {
  cout << p.first << ' ' << p.second << endl;
}
//~ END `print_pair`

#endif
