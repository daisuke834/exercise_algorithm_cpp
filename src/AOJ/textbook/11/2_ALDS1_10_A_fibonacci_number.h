/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part11-2. 動的計画法(Dynamic Programming, DP)、フィボナッチ数列(Fibonacci Number)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C11_2_ALDS1_10_A_FIBONACCI_NUMBER_H_
#define SRC_C11_2_ALDS1_10_A_FIBONACCI_NUMBER_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_10_A {

constexpr int32_t kMaxNumberOfIndex = 100;

void CallFibonacciNumber(std::istream& input_stream);

class FibonacciNumber {
 public:
  FibonacciNumber() noexcept;
  ~FibonacciNumber() noexcept;
  int32_t Calculate(const int32_t n);

 private:
  FibonacciNumber(const FibonacciNumber& obj) = delete;
  FibonacciNumber& operator=(const FibonacciNumber& obj) = delete;
  FibonacciNumber(FibonacciNumber&& obj) = delete;
  FibonacciNumber& operator=(FibonacciNumber&& obj) = delete;

 private:
  int32_t values_[kMaxNumberOfIndex];

 private:
  // FRIEND_TEST(Test_ALDS1_10_A, Add);  // Should be removed from production code
};

}  // namespace ALDS1_10_A

#endif  // SRC_C11_2_ALDS1_10_A_FIBONACCI_NUMBER_H_
