/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-195-4. 1499. Max Value of Equation.
 * https://leetcode.com/contest/weekly-contest-195/problems/max-value-of-equation/
 */

#ifndef SRC_B_LC_WEEKLY_195_4_TWO_POINTERS_H_
#define SRC_B_LC_WEEKLY_195_4_TWO_POINTERS_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace LC_weekly_195_4 {

class Solution {
 public:
  int findMaxValueOfEquation(std::vector<std::vector<int>>& points, int k);
};

}  // namespace LC_weekly_195_4

#endif  // SRC_B_LC_WEEKLY_195_4_TWO_POINTERS_H_
