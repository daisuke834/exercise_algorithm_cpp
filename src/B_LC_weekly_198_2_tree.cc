/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-198-2. 1519. Number of Nodes in the Sub-Tree With the Same Label
 * https://leetcode.com/contest/weekly-contest-198/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
 */

#include "src/B_LC_weekly_198_2_tree.h"

namespace LC_weekly_198_2 {

std::vector<int> Solution::countSubTrees(int n, std::vector<std::vector<int>> &edges, std::string labels) {
  std::vector<std::vector<int64_t>> neighbours(n, std::vector<int64_t>());
  std::vector<std::vector<int64_t>> counts(n, std::vector<int64_t>(26, 0));
  std::vector<bool> visited(n, false);
  std::vector<int> ans(n, 0);
  for (const auto &edge : edges) {
    neighbours[edge[0]].emplace_back(edge[1]);
    neighbours[edge[1]].emplace_back(edge[0]);
  }
  auto Dfs = [&](auto &&Func, const int64_t node) -> void {
    if (visited[node]) {
      return;
    }
    visited[node] = true;
    ++counts[node][labels[node] - 'a'];
    for (const int64_t child : neighbours[node]) {
      if (!visited[child]) {
        Func(Func, child);
        for (char c = 'a'; c <= 'z'; ++c) {
          counts[node][c - 'a'] += counts[child][c - 'a'];
        }
      }
    }
    ans[node] = counts[node][labels[node] - 'a'];
  };
  Dfs(Dfs, 0);
  return ans;
}

}  // namespace LC_weekly_198_2
