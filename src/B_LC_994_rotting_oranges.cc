/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 994. Rotting Oranges.
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1 instead.
 */

#include "src/B_LC_994_rotting_oranges.h"

namespace LC_994 {

const int32_t directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int Solution::orangesRotting(const std::vector<std::vector<int>> &grid) {
  height_ = static_cast<int32_t>(grid.size());
  width_ = static_cast<int32_t>(grid[0].size());
  std::vector<std::vector<int32_t>> minimum_rotten_time(height_, std::vector<int32_t>(width_, INT32_MAX));
  std::vector<Position> fresh_group;
  for (int32_t row = 0; row < height_; ++row) {
    for (int32_t column = 0; column < width_; ++column) {
      if (grid[row][column] == kRotten) {
        todo_.push(Todo(0, Position(row, column)));
      } else if (grid[row][column] == kFresh) {
        fresh_group.push_back(Position(row, column));
      }
    }
  }

  while (todo_.size() > 0) {
    Todo target = todo_.top();
    todo_.pop();
    const int32_t c_count = target.first;
    const int32_t c_row = target.second.first;
    const int32_t c_column = target.second.second;
    const int32_t next_count = c_count + 1;
    for (auto direction : directions) {
      const int32_t next_row = c_row + direction[0];
      const int32_t next_column = c_column + direction[1];
      if (IsValidPosition(Position(next_row, next_column)) && grid[next_row][next_column] == kFresh) {
        if (next_count < minimum_rotten_time[next_row][next_column]) {
          minimum_rotten_time[next_row][next_column] = next_count;
          todo_.push(Todo(next_count, Position(next_row, next_column)));
        }
      }
    }
  }
  int32_t time_to_all_rotten = 0;
  for (const auto &fresh : fresh_group) {
    if (minimum_rotten_time[fresh.first][fresh.second] > time_to_all_rotten) {
      time_to_all_rotten = minimum_rotten_time[fresh.first][fresh.second];
    }
  }
  if (time_to_all_rotten == INT32_MAX) {
    time_to_all_rotten = -1;
  }
  return time_to_all_rotten;
}

bool Solution::IsValidPosition(const Position &position) const noexcept {
  return position.first >= 0 && position.first < height_ && position.second >= 0 && position.second < width_;
}

}  // namespace LC_994
