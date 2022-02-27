/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-198-2. 1519. Number of Nodes in the Sub-Tree With the Same Label
 * https://leetcode.com/contest/weekly-contest-198/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
 */

#ifndef SRC_B_LC_WEEKLY_198_2_TREE_H_
#define SRC_B_LC_WEEKLY_198_2_TREE_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace LC_weekly_198_2 {

class Solution {
 public:
  std::vector<int> countSubTrees(int n, std::vector<std::vector<int>>& edges, std::string labels);
};

}  // namespace LC_weekly_198_2

#endif  // SRC_B_LC_WEEKLY_198_2_TREE_H_
