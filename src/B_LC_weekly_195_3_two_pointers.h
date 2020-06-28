/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-195-3. 1498. Number of Subsequences That Satisfy the Given Sum Condition.
 * https://leetcode.com/contest/weekly-contest-195/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
 */

#ifndef SRC_B_LC_WEEKLY_195_3_TWO_POINTERS_H_
#define SRC_B_LC_WEEKLY_195_3_TWO_POINTERS_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace LC_weekly_195_3 {

class Solution {
 public:
  int numSubseq(std::vector<int> &nums, int target);
};

}  // namespace LC_weekly_195_3

#endif  // SRC_B_LC_WEEKLY_195_3_TWO_POINTERS_H_
