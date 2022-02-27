/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 15. 3sum.
 * Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
 * Find all unique triplets in the array which gives the sum of zero.
 */

#ifndef SRC_B_LC_015_1_ROTTING_ORANGE_H_
#define SRC_B_LC_015_1_ROTTING_ORANGE_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace LC_015_1 {

class Solution {
 public:
  std::vector<std::vector<int32_t>> threeSum(std::vector<int32_t>& nums) noexcept;
};
}  // namespace LC_015_1

#endif  // SRC_B_LC_015_1_ROTTING_ORANGE_H_
