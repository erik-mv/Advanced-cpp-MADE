#include "matrix.h"

using namespace task;

Matrix::Matrix() {
  m = 1;
  n = 1;
  ptr = new double*[1];
  ptr[0] = new double[1];
  ptr[0][0] = 1.;
}

Matrix::Matrix(size_t rows, size_t cols) {
  m = rows;
  n = cols;

  ptr = new double*[m];
  for (size_t i = 0; i < m; ++i) {
    ptr[i] = new double[n];
    for (size_t j = 0; j < n; ++j)
      if (i == j) {
        ptr[i][j] = 1.;
      } else {
        ptr[i][j] = 0.;
      }
  }
}

Matrix::Matrix(const Matrix& copy) {
  m = copy.m;
  n = copy.n;

  ptr = new double*[m];
  for (size_t i = 0; i < m; ++i) {
    ptr[i] = new double[n];
    for (size_t j = 0; j < n; ++j) ptr[i][j] = copy[i][j];
  }
}

Matrix& Matrix::operator=(const Matrix& a) {
  if (this == &a) {
    return *this;
  }

  resize(a.m, a.n);

  for (size_t i = 0; i < m; ++i)
    for (size_t j = 0; j < n; ++j) ptr[i][j] = a[i][j];

  return *this;
}

const size_t& Matrix::sizeRow() const { return m; }

const size_t& Matrix::sizeColumn() const { return n; }

double& Matrix::get(size_t row, size_t col) {
  if (row >= m || col >= n || row < 0 || col < 0) {
    throw OutOfBoundsException();
  }

  return ptr[row][col];
}

const double& Matrix::get(size_t row, size_t col) const {
  if (row >= m || col >= n || row < 0 || col < 0) {
    throw OutOfBoundsException();
  }

  return ptr[row][col];
}

void Matrix::set(size_t row, size_t col, const double& value) {
  if (row >= m || col >= n || row < 0 || col < 0) {
    throw OutOfBoundsException();
  }

  ptr[row][col] = value;
}

void Matrix::resize(size_t new_rows, size_t new_cols) {
  if (m == new_rows && n == new_cols) {
    return;
  }

  double** newPtr = new double*[new_rows];
  for (size_t i = 0; i < new_rows; ++i) newPtr[i] = new double[new_cols];

  for (size_t i = 0; i < new_rows; ++i)
    for (size_t j = 0; j < new_cols; ++j)
      if (i < m && j < n) {
        newPtr[i][j] = ptr[i][j];
      } else {
        newPtr[i][j] = 0;
      }

  for (size_t i = 0; i < m; ++i) delete[] ptr[i];
  delete[] ptr;

  m = new_rows;
  n = new_cols;

  ptr = newPtr;
}

double* Matrix::operator[](size_t row) { return ptr[row]; }

double* Matrix::operator[](size_t row) const { return ptr[row]; }

Matrix& Matrix::operator+=(const Matrix& a) {
  if (m != a.m || n != a.n) {
    throw SizeMismatchException();
  }

  for (size_t i = 0; i < m; ++i)
    for (size_t j = 0; j < n; ++j) ptr[i][j] += a[i][j];

  return *this;
}
Matrix& Matrix::operator-=(const Matrix& a) {
  if (m != a.m || n != a.n) {
    throw SizeMismatchException();
  }

  for (size_t i = 0; i < m; ++i)
    for (size_t j = 0; j < n; ++j) ptr[i][j] -= a[i][j];

  return *this;
}
Matrix& Matrix::operator*=(const Matrix& a) {
  if (n != a.m) {
    throw SizeMismatchException();
  }

  double** newPtr = new double*[m];
  for (size_t i = 0; i < m; ++i) newPtr[i] = new double[a.n];

  for (size_t i = 0; i < m; ++i)
    for (size_t j = 0; j < a.n; ++j) {
      newPtr[i][j] = 0.;
      for (size_t k = 0; k < n; k++) newPtr[i][j] += ptr[i][k] * a[k][j];
    }

  for (size_t i = 0; i < m; ++i) delete[] ptr[i];
  delete[] ptr;

  n = a.n;

  ptr = newPtr;

  return *this;
}

Matrix& Matrix::operator*=(const double& number) {
  for (size_t i = 0; i < m; ++i)
    for (size_t j = 0; j < n; ++j) ptr[i][j] *= number;

  return *this;
}

Matrix Matrix::operator+(const Matrix& a) const {
  if (m != a.m || n != a.n) {
    throw SizeMismatchException();
  }

  Matrix solv(*this);

  return solv += a;
}
Matrix Matrix::operator-(const Matrix& a) const {
  if (m != a.m || n != a.n) {
    throw SizeMismatchException();
  }

  Matrix solv(*this);

  return solv -= a;
}
Matrix Matrix::operator*(const Matrix& a) const {
  if (n != a.m) {
    throw SizeMismatchException();
  }

  Matrix solv(*this);

  return solv *= a;
}

Matrix Matrix::operator*(const double& a) const {
  Matrix solv(*this);

  return solv *= a;
}

Matrix Matrix::operator-() const {
  Matrix solv(*this);

  return solv *= -1.;
}

Matrix Matrix::operator+() const {
  Matrix solv(*this);

  return solv;
}

double Matrix::det() const {
  if (m != n) {
    throw SizeMismatchException();
  }

  double** tempPtr = new double*[m];
  for (size_t i = 0; i < m; ++i) {
    tempPtr[i] = new double[n];
    for (size_t j = 0; j < m; ++j) tempPtr[i][j] = ptr[i][j];
  }

  size_t i = 0;
  size_t r = m;
  double det = 1.;

  while (i < r) {
    size_t v = i;

    for (size_t j = i + 1; j < n; j++) {
      double sgnA = tempPtr[j][i];
      double sgnB = tempPtr[v][i];
      if (sgnA > -sgnB && sgnA > sgnB || sgnA < -sgnB && sgnA < sgnB) {
        v = j;
      }
    }

    if (tempPtr[v][i] < EPS && -tempPtr[v][i] < EPS) {
      return 0.;
    }

    if (v != i) {
      det = -det;
      for (size_t j = 0; j < n; j++) std::swap(tempPtr[i][j], tempPtr[v][j]);
    }

    for (size_t k = i + 1; k < n; k++) {
      double c = tempPtr[k][i] / tempPtr[i][i];
      for (size_t j = i; j < n; j++) tempPtr[k][j] -= c * tempPtr[i][j];
    }

    det *= tempPtr[i][i++];
  }

  for (size_t i = 0; i < n; ++i) delete[] tempPtr[i];
  delete[] tempPtr;

  return det;
}

void Matrix::transpose() {
  double** newPtr = new double*[n];
  for (size_t i = 0; i < n; ++i) {
    newPtr[i] = new double[m];
    for (size_t j = 0; j < m; ++j) newPtr[i][j] = ptr[j][i];
  }

  for (size_t i = 0; i < m; ++i) delete[] ptr[i];
  delete[] ptr;

  std::swap(n, m);

  ptr = newPtr;
}

Matrix Matrix::transposed() const {
  Matrix solv(n, m);

  for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < m; ++j) solv[i][j] = ptr[j][i];

  return solv;
}

double Matrix::trace() const {
  if (m != n) {
    throw SizeMismatchException();
  }

  double trace = ptr[0][0];

  for (size_t i = 1; i < m; ++i) trace += ptr[i][i];

  return trace;
}

std::vector<double> Matrix::getRow(size_t row) {
  std::vector<double> vec(n);

  for (size_t i = 0; i < n; ++i) vec[i] = ptr[row][i];

  return vec;
}

std::vector<double> Matrix::getColumn(size_t column) {
  std::vector<double> vec(m);

  for (size_t i = 0; i < m; ++i) vec[i] = ptr[i][column];

  return vec;
}

bool Matrix::operator==(const Matrix& a) const {
  if (m != a.m || n != a.n) {
    return 0;
  }

  for (size_t i = 0; i < m; ++i)
    for (size_t j = 0; j < n; ++j)
      if (ptr[i][j] - a[i][j] > EPS || a[i][j] - ptr[i][j] > EPS) {
        return 0;
      }

  return 1;
}
bool Matrix::operator!=(const Matrix& a) const {
  if (m != a.m || n != a.n) {
    return 1;
  }

  for (size_t i = 0; i < m; ++i)
    for (size_t j = 0; j < n; ++j)
      if (ptr[i][j] - a[i][j] > EPS || a[i][j] - ptr[i][j] > EPS) {
        return 1;
      }

  return 0;
}

Matrix task::operator*(const double& a, const Matrix& b) {
  Matrix solv(b);

  solv *= a;

  return solv;
}

std::ostream& task::operator<<(std::ostream& output, const Matrix& matrix) {
  for (size_t i = 0; i < matrix.sizeRow(); ++i) {
    output << matrix[i][0];

    for (size_t j = 1; j < matrix.sizeColumn(); ++j)
      output << " " << matrix[i][j];

    output << "\n";
  }

  return output;
}

std::istream& task::operator>>(std::istream& input, Matrix& matrix) {
  size_t m;
  size_t n;
  input >> m >> n;

  matrix.resize(m, n);

  for (size_t i = 0; i < m; ++i)
    for (size_t j = 0; j < n; ++j) input >> matrix[i][j];

  return input;
}