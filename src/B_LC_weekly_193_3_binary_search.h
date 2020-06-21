/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-193-3. 5455. Minimum Number of Days to Make m Bouquets.
 * https://leetcode.com/contest/weekly-contest-193/problems/minimum-number-of-days-to-make-m-bouquets/
 */

#ifndef SRC_B_LC_WEEKLY_189_3_SUBSEQUENCE_H_
#define SRC_B_LC_WEEKLY_189_3_SUBSEQUENCE_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace LC_weekly_193_3 {

class Solution {
 public:
  int minDays(std::vector<int> &bloomDay, int m, int k);

 private:
  bool IsOkay(const std::vector<int> &bloomDay, const int m, const int k, const int day);
};

}  // namespace LC_weekly_193_3

#endif  // SRC_B_LC_WEEKLY_189_3_SUBSEQUENCE_H_
