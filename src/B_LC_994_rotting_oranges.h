/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 994. Rotting Oranges.
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1 instead.
 */

#ifndef SRC_B_LC_994_ROTTING_ORANGE_H_
#define SRC_B_LC_994_ROTTING_ORANGE_H_

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace LC_994 {

enum OrangeType : int32_t { kEmpty = 0, kFresh, kRotten };

using Position = std::pair<int32_t, int32_t>;
using Todo = std::pair<int32_t, Position>;

class Solution {
 public:
  int orangesRotting(const std::vector<std::vector<int>> &grid);

 private:
  bool IsValidPosition(const Position &position) const noexcept;

 private:
  int32_t height_;
  int32_t width_;
  std::priority_queue<Todo> todo_;
};

}  // namespace LC_994

#endif  // SRC_B_LC_994_ROTTING_ORANGE_H_
