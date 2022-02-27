/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part11-2. 動的計画法(Dynamic Programming, DP)、フィボナッチ数列(Fibonacci Number)。
 * 計算時間=O(n), 追加作業記憶領域=O(n). 再帰計算の場合には、計算時間=O(2^n), 追加作業記憶領域=O(1)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "2_ALDS1_10_A_fibonacci_number.h"

#include <iostream>
#include <string>

namespace ALDS1_10_A {

void CallFibonacciNumber(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  FibonacciNumber* fibonacci_number = new FibonacciNumber();
  try {
    int32_t n;
    input_stream >> n;
    std::cout << fibonacci_number->Calculate(n) << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallFibonacciNumber()" << std::endl;
    throw;
  }
  delete fibonacci_number;
}

// ****************************************************

FibonacciNumber::FibonacciNumber() noexcept {
  values_[0] = 1;
  values_[1] = 1;
}
FibonacciNumber::~FibonacciNumber() noexcept {}

int32_t FibonacciNumber::Calculate(const int32_t n) {
  for (int32_t index = 2; index <= n; ++index) {
    values_[index] = values_[index - 1] + values_[index - 2];
  }
  return values_[n];
}

}  // namespace ALDS1_10_A
