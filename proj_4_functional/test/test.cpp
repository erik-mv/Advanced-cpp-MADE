#include <cmath>
#include <iostream>
#include <memory>
#include "src/function.h"

void FailWithMsg(const std::string& msg, int line) {
  std::cerr << "Test failed!\n";
  std::cerr << "[Line " << line << "] " << msg << std::endl;
  std::exit(EXIT_FAILURE);
}

#define ASSERT_TRUE_MSG(cond, msg) \
  if (!(cond)) {                   \
    FailWithMsg(msg, __LINE__);    \
  };

const double EPS = 1e-12;

int multi(int a, int b) { return a * b; }

struct Multi {
  int operator()(int a, int b) const { return a * b; }
};

struct Sqrt {
  double operator()(double a) const { return std::sqrt(a); }
};

bool test_can_function_work_with_func(int a, int b) {
  function<int(int, int)> f = multi;

  return (f(a, b) == a * b);
}

bool test_can_function_work_with_struck(int a, int b) {
  function<int(int, int)> f = Multi();

  return (f(a, b) == a * b);
}

bool test_can_function_work_with_double_math(double a) {
  function<double(double)> f = Sqrt();

  return (fabs(f(a) - std::sqrt(a)) < EPS);
}

bool test_can_function_work_with_lambda_without_parametr() {
  function<int()> f = []() { return 620; };

  return (f() == 620);
}

bool test_can_function_work_with_lambda_with_parametr(int a, int b) {
  function<int(int, int)> f2 = [](int i, int j) { return i + j; };
  return (f2(a, b) == a + b);
}

int main() {
  ASSERT_TRUE_MSG(test_can_function_work_with_func(2, 3) == 1,
                  "Default constructor")

  ASSERT_TRUE_MSG(test_can_function_work_with_struck(4, 6) == 1,
                  "Default constructor")

  ASSERT_TRUE_MSG(test_can_function_work_with_double_math(9.0) == 1,
                  "Default constructor")

  ASSERT_TRUE_MSG(test_can_function_work_with_lambda_without_parametr() == 1,
                  "Default constructor")

  ASSERT_TRUE_MSG(test_can_function_work_with_lambda_with_parametr(5, 6) == 1,
                  "Default constructor")

  return 0;
}