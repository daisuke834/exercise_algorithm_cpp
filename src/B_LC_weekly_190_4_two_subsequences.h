/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-190-4. 1458. Max Dot Product of Two Subsequences.
 * Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same length.
 */

#ifndef SRC_B_LC_WEEKLY_189_3_SUBSEQUENCE_H_
#define SRC_B_LC_WEEKLY_189_3_SUBSEQUENCE_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace LC_weekly_190_4 {

class Solution {
 public:
  int32_t maxDotProduct(std::vector<int32_t> &nums1, std::vector<int32_t> &nums2) noexcept;
};

}  // namespace LC_weekly_190_4

#endif  // SRC_B_LC_WEEKLY_189_3_SUBSEQUENCE_H_
