#ifndef RANDOM_H_
#define RANDOM_H_

#include "algs/common.h"
//~ BEGIN `rand_float`
float rand_float() {
  return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
//~ END `rand_float`

//~ BEGIN `rand_int`
int rand_int(int from, int to) {
  int m = (to - from + 1);
  return from + (rand() + m) % m;
}
int rand_int(int to) { return rand_int(0, to); }
//~ END `rand_int`

#endif
