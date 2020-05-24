/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-190-4. 1458. Max Dot Product of Two Subsequences.
 * Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same length.
 */

#include "src/B_LC_weekly_190_4_two_subsequences.h"

namespace LC_weekly_190_4 {

int32_t Solution::maxDotProduct(std::vector<int32_t> &nums1, std::vector<int32_t> &nums2) noexcept {
  const int32_t length_1 = static_cast<int32_t>(nums1.size());
  const int32_t length_2 = static_cast<int32_t>(nums2.size());
  std::vector<std::vector<int32_t>> dp(length_1 + 1, std::vector<int32_t>(length_2 + 1, INT32_MIN));
  dp[0][0] = 0;
  for (int32_t i = 0; i <= length_1; ++i) {
    for (int32_t j = 0; j <= length_2; ++j) {
      if (i + 1 <= length_1) {
        dp[i + 1][j] = std::max(dp[i + 1][j], dp[i][j]);
      }
      if (j + 1 <= length_2) {
        dp[i][j + 1] = std::max(dp[i][j + 1], dp[i][j]);
      }
      if (i + 1 <= length_1 && j + 1 <= length_2) {
        dp[i + 1][j + 1] = std::max(dp[i + 1][j + 1], dp[i][j] + nums1[i] * nums2[j]);
      }
    }
  }
  int32_t result = dp[length_1][length_2];
  if (result == 0) {
    result = INT32_MIN;
    for (int32_t i = 0; i < length_1; ++i) {
      for (int32_t j = 0; j < length_2; ++j) {
        result = std::max(result, nums1[i] * nums2[j]);
      }
    }
  }
  return result;
}

}  // namespace LC_weekly_190_4
