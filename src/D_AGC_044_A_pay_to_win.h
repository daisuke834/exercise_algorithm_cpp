/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Grand Contest 044-A. Pay To Win.
 */

#ifndef SRC_D_AGC_044_A_PAY_TO_WIN_H_
#define SRC_D_AGC_044_A_PAY_TO_WIN_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace AGC_044_A {

class Solution {
 public:
  Solution() = delete;
  Solution(const int64_t N, const int64_t A, const int64_t B, const int64_t C, const int64_t D);
  int64_t Calculate();

 private:
 private:
  const int64_t N_;
  const int64_t A_;
  const int64_t B_;
  const int64_t C_;
  const int64_t D_;
  const int64_t array_max_;
  std::vector<int64_t> min_coins_;
};

}  // namespace AGC_044_A

#endif  // SRC_D_AGC_044_A_PAY_TO_WIN_H_
