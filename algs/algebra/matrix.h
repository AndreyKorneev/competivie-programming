#ifndef ALGEBRA_MATRIX_H_
#define ALGEBRA_MATRIX_H_

#include "algs/common.h"
//~ BEGIN `Matrix`
template<typename T>
struct Matrix {
  Matrix(int r, int c, const T& value = 0)
      : Matrix(vector<vector<T>>(r, vector<T>(c, value))) {}
  Matrix(const vector<vector<T>>& v)
      : rows(v.size()), columns(v[0].size()), data(v) {}

  // Brackets access.
  const vector<T>& operator[](int i) const { return data[i]; }
  vector<T>& operator[](int i) { return data[i]; }

  int rows;
  int columns;
  vector<vector<T>> data;
};
//~ END `Matrix`

//~ BEGIN `Gauss`
// required: Matrix
// source: https://e-maxx.ru/algo/linear_systems_gauss
template <typename T>
struct GaussFloatKernel {
  constexpr static float EPS = 1e-9;
  static bool IsZero(const T& a) { return fabs(a) < EPS; }
  static int GetSelectedRow(const Matrix<T>& a, int row, int col) {
    int sel = row;
    for (int i = row; i < a.rows; ++i) {
      if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
    }
    return sel;
  }
};
template <typename T>
struct GaussIntegerKernel {
  static bool IsZero(const T& a) { return a == 0; }
  static int GetSelectedRow(const Matrix<T>& a, int row, int col) {
    for (int i = row; i < a.rows; ++i) {
      if (a[i][col] != 0) return i;
    }
    return row;
  }
};

enum class Solution { NONE, UNIQUE, INF };
template<typename T, typename Kernel = GaussFloatKernel<T>>
struct Gauss {
  Gauss(const Matrix<T>& source)
      : rows(source.rows),
        columns(source.columns - 1),
        m(source),
        answer(columns, T{}) {}

  Solution solve() {
    vector<int> where (columns, -1);

    for (int col = 0, row = 0; col < columns && row < rows; ++col) {
      int selected = Kernel::GetSelectedRow(m, row, col);
      if (Kernel::IsZero(m[selected][col])) continue;
      for (int i = col; i <= columns; ++i) swap(m[selected][i], m[row][i]);
      where[col] = row;

      for (int i = 0; i < rows; ++i)
        if (i != row) {
          auto c = m[i][col] / m[row][col];
          for (int j = col; j <= columns; ++j) m[i][j] -= m[row][j] * c;
        }
      // Next iteraion.
      ++row;
    }

    // Restore the solution..
    for (int i = 0; i < columns; ++i)
      if (where[i] != -1) answer[i] = m[where[i]][columns] / m[where[i]][i];

    // Check whether the solution exists.
    for (int i = 0; i < rows; ++i) {
      T sum = 0;
      for (int j = 0; j < columns; ++j) sum += answer[j] * m[i][j];
      if (!Kernel::IsZero(sum - m[i][columns])) return Solution::NONE;
    }

    // Check whether the solution is unique.
    for (int i = 0; i < columns; ++i) if (where[i] == -1) return Solution::INF;

    return Solution::UNIQUE;
  }

  int rows;
  int columns;
  Matrix<T> m;
  vector<T> answer;
};
//~ END `Gauss`

#endif
