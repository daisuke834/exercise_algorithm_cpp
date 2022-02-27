/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Grand Contest(AGC) 044-A. Pay To Win.
 */

#ifndef SRC_D_AGC_044_A_PAY_TO_WIN_H_
#define SRC_D_AGC_044_A_PAY_TO_WIN_H_

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace AGC_044_A {

enum OperationType : int32_t { kDouble = 0, kTriple, kQuintuple, kIncrement, kDecrement, kNumberOfOperations };

struct Operation {
  int64_t coins{0};
  int64_t ratio{-1};
};

class Solution {
 public:
  Solution() = delete;
  Solution(const int64_t A, const int64_t B, const int64_t C, const int64_t D) noexcept;
  int64_t CalculateMinimumAmountOfCoins(const int64_t goal) noexcept;

 private:
  Operation operations_[kNumberOfOperations];
  std::map<int64_t, int64_t> min_coins_;
};

}  // namespace AGC_044_A

#endif  // SRC_D_AGC_044_A_PAY_TO_WIN_H_
