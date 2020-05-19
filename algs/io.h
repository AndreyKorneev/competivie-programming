#ifndef IO_H_
#define IO_H_
#include "algs/common.h"

//~ BEGIN `read_vector`
template <typename T> vector<T> read_vector(int n) { vector<T> r(n); for (auto& a : r) cin >> a; return r; }
template <typename T> vector<T> read_vector() { int n; cin >> n; return read_vector<T>(n); }
//~ END `read_vector`

//~ BEGIN `print_vector_no_size`
template <typename T, char SEP = ' '> void print_vector_no_size(T start, T end) { while(start < end) cout << *(start++) << SEP; cout << endl; }
template <typename T, char SEP = ' '> void print_vector_no_size(const vector<T>& v) { print_vector_no_size<T, SEP>(v.begin(), v.end()); }
//~ END `print_vector_no_size`

//~ BEGIN `print_vector`
// required: print_vector_no_size
template <typename T, char SEP = ' '> void print_vector(const vector<T>& v) { cout << v.size() << endl; print_vector_no_size<T, SEP>(v); }
//~ END `print_vector`

//~ BEGIN `print_pair`
template <typename T, typename U, char SEP = ' '> void print_pair(const pair<T, U>& p) { cout << p.first << SEP << p.second << endl; }
//~ END `print_pair`

//~ BEGIN `read`
template <typename T> T read() { T a; cin >> a; return a; }
//~ END `read`

#endif
