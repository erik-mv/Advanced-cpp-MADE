#pragma once
#include <vector>
#include <iostream>


namespace task {
using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::swap;
using std::vector;

vector<double> operator+(const vector<double>& a, const vector<double>& b) {
  vector<double> c(a.size());

  for (size_t i = 0; i < a.size(); ++i) c[i] = a[i] + b[i];

  return c;
}

vector<double> operator+(const vector<double>& a) {
  vector<double> c(a.size());

  for (size_t i = 0; i < a.size(); ++i) c[i] += a[i];

  return c;
}

vector<double> operator-(const vector<double>& a, const vector<double>& b) {
  vector<double> c(a.size());

  for (size_t i = 0; i < a.size(); ++i) c[i] = a[i] - b[i];

  return c;
}

vector<double> operator-(const vector<double>& a) {
  vector<double> c(a.size());

  for (size_t i = 0; i < a.size(); ++i) c[i] -= a[i];

  return c;
}

double operator*(const vector<double>& a, const vector<double>& b) {
  double sum = 0;

  for (size_t i = 0; i < a.size(); ++i) sum += a[i] * b[i];

  return sum;
}

vector<double> operator%(const vector<double>& a, const vector<double>& b) {
  vector<double> c(a.size());

  c[0] = a[1] * b[2] - a[2] * b[1];
  c[1] = a[2] * b[0] - a[0] * b[2];
  c[2] = a[0] * b[1] - a[1] * b[0];

  return c;
}

bool operator||(const vector<double>& a, const vector<double>& b) {
  const double eps = 1e-12;

  double cosFi = (a * a) * (b * b);

  if (cosFi < eps) return 1;

  cosFi = (a * b) * (a * b) / cosFi;

  if (fabs(cosFi - 1.) < eps) return 1;

  return 0;
}

bool operator&&(const vector<double>& a, const vector<double>& b) {
  const double eps = 1e-12;

  double cosFi = sqrt(a * a) * sqrt(b * b);

  if (cosFi < eps) return 1;

  cosFi = (a * b) / cosFi;

  if (fabs(cosFi - 1.) < eps) return 1;

  return 0;
}

void reverse(vector<double>& a) {
  int n = a.size();

  for (size_t i = 0; i < n / 2; ++i) swap(a[i], a[n - 1 - i]);
}

istream& operator>>(istream& strm, vector<double>& b) {
  size_t n;
  strm >> n;

  b.clear();
  b.resize(n);

  for (size_t i = 0; i < n; ++i) strm >> b[i];

  return strm;
}

ostream& operator<<(ostream& strm, const vector<double>& a) {
  if (a.size() == 0) {
    strm << "size vector = 0\n";
    return strm;
  }

  strm << a[0];

  for (size_t i = 1; i < a.size(); ++i) strm << " " << a[i];

  strm << "\n";

  return strm;
}

istream& operator>>(istream& strm, vector<int>& b) {
  size_t n;
  strm >> n;

  b.clear();
  b.resize(n);

  for (size_t i = 0; i < n; ++i) strm >> b[i];

  return strm;
}

ostream& operator<<(ostream& strm, const vector<int>& a) {
  if (a.size() == 0) {
    strm << "size vector = 0\n";
    return strm;
  }

  strm << a[0];

  for (size_t i = 1; i < a.size(); ++i) strm << " " << a[i];

  strm << "\n";

  return strm;
}

vector<int> operator|(const vector<int>& a, const vector<int>& b) {
  vector<int> c(a.size());

  for (size_t i = 0; i < a.size(); ++i) c[i] = a[i] | b[i];

  return c;
}

vector<int> operator&(const vector<int>& a, const vector<int>& b) {
  vector<int> c(a.size());

  for (size_t i = 0; i < a.size(); ++i) c[i] = a[i] & b[i];

  return c;
}
}  // namespace task
