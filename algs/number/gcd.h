#ifndef NUMBER_GCD_H_
#define NUMBER_GCD_H_
#include "algs/common.h"

//~ BEGIN `GcdExtended`
// Source: https://e-maxx.ru/algo/diofant_2_equation
template <typename T>
T GcdExtended(const T a, const T b, T& x, T& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  T x1, y1;
  T d = GcdExtended(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}
//~ END `GcdExtended`

//~ BEGIN `DiophantineSolver`
// required: GcdExtended
//#if __cplusplus <= 201703L
//namespace std {
//template <typename T>
//struct optional {
  //optional() : has_value_(false) {}
  //optional(const T& value) : has_value_(true), value_(value) {}

  //bool has_value() { return has_value_; }
  //T value() { return value_; }

  //T value_;
  //bool has_value_;
//};
//}  // namespace std
//#endif
// Source: https://e-maxx.ru/algo/diofant_2_equation
template <typename T>
struct DiophantineSolver {
  using Solution = std::pair<T, T>;

  DiophantineSolver(T a, T b, T c) : a_(a), b_(b), c_(c) {
    gcd_ = GcdExtended(a_, b_, xi_, yi_);
  }

  std::optional<Solution> AnySolution() {
    if (c_ % gcd_) return {};
    return make_pair(xi_, yi_);
  }

  void ShiftSolution(Solution& s, T cnt) {
    s.first += cnt * b_;
    s.second -= cnt * a_;
  }

  std::optional<Solution> AnySolution(T minx, T maxx, T miny, T maxy) {
    if (c_ % gcd_) return {};
    Solution s = {xi_, yi_};
    T& x = s.first;
    T& y = s.second;

    int sign_a = a_ > 0 ? +1 : -1;
    int sign_b = b_ > 0 ? +1 : -1;

    ShiftSolution(s, (minx - x) / b_);
    if (x < minx) ShiftSolution(s, sign_b);
    if (x > maxx) return {};
    T lx1 = x;

    ShiftSolution(s, (maxx - x) / b_);
    if (x > maxx) ShiftSolution(s, -sign_b);
    T rx1 = x;

    ShiftSolution(s, -(miny - y) / a_);
    if (y < miny) ShiftSolution(s, -sign_a);
    if (y > maxy) return {};
    T lx2 = x;

    ShiftSolution(s, -(maxy - y) / a_);
    if (y > maxy) ShiftSolution(s, sign_a);
    T rx2 = x;

    if (lx2 > rx2) swap(lx2, rx2);
    T lx = max(lx1, lx2);
    T rx = min(rx1, rx2);

    lli cnt = (rx - lx) / abs(b_) + 1;
    return std::pair<T, T>{lx, (c_ - lx * a_) / b_};
  }

  T a_, b_, c_, gcd_, xi_, yi_;
};
//~ END `DiophantineSolver`

#endif
