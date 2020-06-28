/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-194-3. 1488. Avoid Flood in The City.
 * https://leetcode.com/contest/weekly-contest-194/problems/avoid-flood-in-the-city/
 */

#ifndef SRC_B_LC_WEEKLY_194_3_BINARY_SEARCH_H_
#define SRC_B_LC_WEEKLY_194_3_BINARY_SEARCH_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace LC_weekly_194_3 {

class Solution {
 public:
  std::vector<int32_t> avoidFlood(const std::vector<int32_t> &rains);
};

}  // namespace LC_weekly_194_3

#endif  // SRC_B_LC_WEEKLY_194_3_BINARY_SEARCH_H_
