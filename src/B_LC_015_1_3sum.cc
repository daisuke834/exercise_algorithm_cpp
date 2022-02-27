/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 15. 3sum.
 * Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
 * Find all unique triplets in the array which gives the sum of zero.
 */

#include "src/B_LC_015_1_3sum.h"

namespace LC_015_1 {

std::vector<std::vector<int32_t>> Solution::threeSum(std::vector<int32_t>& nums) noexcept {
  std::vector<std::vector<int>> result;
  std::sort(nums.begin(), nums.end());
  const int32_t length = static_cast<int32_t>(nums.size());
  for (int32_t lowest = 0; lowest < length; ++lowest) {
    if (nums[lowest] <= 0 && (lowest == 0 || nums[lowest - 1] != nums[lowest])) {
      int32_t middle = lowest + 1;
      int32_t highest = length - 1;
      while (middle < highest) {
        const int32_t c_sum = nums[lowest] + nums[middle] + nums[highest];
        if (c_sum == 0) {
          std::vector<int32_t> temp;
          temp.push_back(nums[lowest]);
          temp.push_back(nums[middle]);
          temp.push_back(nums[highest]);
          result.push_back(temp);
          ++middle;
          while (middle < highest && nums[middle - 1] == nums[middle]) {
            ++middle;
          }
          --highest;
          while (middle < highest && nums[highest] == nums[highest + 1]) {
            --highest;
          }
        } else if (c_sum < 0) {
          ++middle;
          while (middle < highest && nums[middle - 1] == nums[middle]) {
            ++middle;
          }
        } else {
          --highest;
          while (middle < highest && nums[highest] == nums[highest + 1]) {
            --highest;
          }
        }
      }
    }
  }
  return result;
}

}  // namespace LC_015_1
