/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-197-4. 1515. Best Position for a Service Centre
 * https://leetcode.com/contest/weekly-contest-197/problems/best-position-for-a-service-centre/
 * 三分探索 (Ternary Search)
 */

#ifndef SRC_B_LC_WEEKLY_197_4_TERNARY_SEARCH_H_
#define SRC_B_LC_WEEKLY_197_4_TERNARY_SEARCH_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

namespace LC_weekly_197_4 {

class Solution {
 public:
  double getMinDistSum(std::vector<std::vector<int>> &positions);
};

}  // namespace LC_weekly_197_4

#endif  // SRC_B_LC_WEEKLY_197_4_TERNARY_SEARCH_H_
