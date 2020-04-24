#ifndef NUMBER_FRACTION_H_
#define NUMBER_FRACTION_H_
#include "algs/common.h"

//~ BEGIN `Fraction`
template <typename T> struct Fraction {
  Fraction(const T &n) : numerator(n), denominator(1) {}
  Fraction(const T &n, const T &d) : numerator(n), denominator(d) {
    auto g = __gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
  }

  Fraction<T>& operator+=(const Fraction<T>& rhs) { *this = this->operator+(rhs); return *this; }
  Fraction<T>& operator-=(const Fraction<T>& rhs) { *this = this->operator-(rhs); return *this; }
  Fraction<T>& operator*=(const Fraction<T>& rhs) { *this = this->operator*(rhs); return *this; }
  Fraction<T>& operator/=(const Fraction<T>& rhs) { *this = this->operator/(rhs); return *this; }

  bool operator<(const Fraction<T> &rhs) const { return this->numerator * rhs.denominator < rhs.numerator * this->denominator; }
  bool operator<=(const Fraction<T> &rhs) const { return this->numerator * rhs.denominator <= rhs.numerator * this->denominator; }
  bool operator>(const Fraction<T> &rhs) const { return this->numerator * rhs.denominator > rhs.numerator * this->denominator; }
  bool operator>=(const Fraction<T> &rhs) const { return this->numerator * rhs.denominator >= rhs.numerator * this->denominator; }
  bool operator==(const Fraction<T> &rhs) const { return this->numerator * rhs.denominator == rhs.numerator * this->denominator; }

  Fraction<T> inverse() const { return {this->denominator, this->numerator}; }
  Fraction<T> operator-() const { return {-(this->numerator), this->denominator}; }

  Fraction<T> operator+(const Fraction<T> &rhs) const {
    auto g = __gcd(this->denominator, rhs.denominator);
    auto lcm = this->denominator / g * rhs.denominator;
    auto x = lcm / this->denominator, y = lcm / rhs.denominator;
    return {this->numerator * x + rhs.numerator * y, lcm};
  }
  Fraction<T> operator*(const Fraction<T> &rhs) const {
    return {this->numerator * rhs.numerator, this->denominator * rhs.denominator};
  }
  Fraction<T> operator-(const Fraction<T> &rhs) const { return (*this) + (-rhs); }

  T numerator;
  T denominator;
};
//~ END `Fraction`

#endif
