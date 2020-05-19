#ifndef NUMBER_MODULED_H_
#define NUMBER_MODULED_H_
#include "algs/common.h"

//~ BEGIN `ModuledNumber`
// required: lli
template <typename T, std::size_t M>
struct ModuledNumber {
  static size_t MODULO;
  ModuledNumber() : value(0) {}
  ModuledNumber(lli value) : value(((value % MODULO) + MODULO) % MODULO) {}

  T value;

  ModuledNumber<T, M> pow(lli n) const {
    ModuledNumber<T, M> result = 1;
    ModuledNumber<T, M> a = *this;
    while (n) {
      if (n & 1) result *= a;
      a *= a;
      n >>= 1;
    }
    return result;
  }
  operator lli() const { return value; }

  ModuledNumber<T, M>& operator+=(const ModuledNumber<T, M>& rhs) {
    value = this->operator+(rhs).value;
    return *this;
  }
  ModuledNumber<T, M>& operator-=(const ModuledNumber<T, M>& rhs) {
    value = this->operator-(rhs).value;
    return *this;
  }

  ModuledNumber<T, M>& operator*=(const ModuledNumber<T, M>& rhs) {
    value = this->operator*(rhs).value;
    return *this;
  }

  ModuledNumber<T, M>& operator/=(const ModuledNumber<T, M>& rhs) {
    value = this->operator/(rhs).value;
    return *this;
  }

  ModuledNumber<T, M> inverse() const { return pow(MODULO - 2); }

  ModuledNumber<T, M> operator+(const ModuledNumber<T, M>& rhs) const {
    return value + rhs.value;
  }
  ModuledNumber<T, M> operator-(const ModuledNumber<T, M>& rhs) const {
    return value + MODULO - rhs.value;
  }
  ModuledNumber<T, M> operator*(const ModuledNumber<T, M>& rhs) const {
    return value * 1ll * rhs.value;
  }
  ModuledNumber<T, M> operator/(const ModuledNumber<T, M>& rhs) const {
    return this->operator*(rhs.inverse());
  }
};
template <typename T, std::size_t M>
size_t ModuledNumber<T, M>::MODULO = M;
//~ END `ModuledNumber`

#endif
