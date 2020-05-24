/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Grand Contest(AGC) 044-B. Joker.
 */

#ifndef SRC_D_AGC_044_B_JOKER_H_
#define SRC_D_AGC_044_B_JOKER_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace AGC_044_B {

class Solution {
 public:
  Solution() = delete;
  explicit Solution(const int32_t N) noexcept;
  int32_t CalculateNumberOfPairs(const std::vector<int32_t> &people_to_exit) noexcept;

 private:
};

}  // namespace AGC_044_B

#endif  // SRC_D_AGC_044_B_JOKER_H_
