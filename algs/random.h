#ifndef RANDOM_H_
#define RANDOM_H_

#include "algs/common.h"
//~ BEGIN `rand_float`
float rand_float() {
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(0, 1);
    return dis(e);
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
