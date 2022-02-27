/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 200. Number of Islands. Implemented by Depth First Search (DFS).
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 * You may assume all four edges of the grid are all surrounded by water.
 */

#include "200_2_number_of_islands_dfs.h"

namespace LC_200_2 {

void CallNumberOfIslands(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  NumberOfIslands* number_of_islands = new NumberOfIslands();
  constexpr int32_t kMaxLoopCount = 20000000;
  std::vector<std::vector<char>> grid;
  for (int32_t i = 0; i < kMaxLoopCount; ++i) {
    std::vector<char> row;
    std::string text;
    input_stream >> text;
    if (text.length() > 0) {
      const int32_t length = static_cast<int32_t>(text.length());
      for (int32_t index = 0; index < length; ++index) {
        row.push_back(text.c_str()[index]);
      }
      grid.push_back(row);
    }
    if (input_stream.eof()) {
      break;
    }
  }
  std::cout << number_of_islands->GetNumberOfIslands(grid) << std::endl;
  delete number_of_islands;
}

NumberOfIslands::NumberOfIslands() noexcept {}

NumberOfIslands::~NumberOfIslands() noexcept {}

int32_t NumberOfIslands::GetIndex(const int32_t x, const int32_t y) const noexcept { return (x + y * width_); }

int32_t NumberOfIslands::GetX(const int32_t index) const noexcept { return index % width_; }
int32_t NumberOfIslands::GetY(const int32_t index) const noexcept { return index / width_; }

bool NumberOfIslands::IsLand(std::vector<std::vector<char>>& grid, const int32_t x, const int32_t y) const noexcept {
  return (grid[y][x] == '1');
}

bool NumberOfIslands::NotExploredYet(const int32_t x, const int32_t y) const noexcept {
  return !explored_[GetIndex(x, y)];
}

void NumberOfIslands::Dfs(std::vector<std::vector<char>>& grid, const int32_t x, const int32_t y) noexcept {
  explored_[GetIndex(x, y)] = true;
  if (x - 1 >= 0 && IsLand(grid, x - 1, y) && NotExploredYet(x - 1, y)) {
    Dfs(grid, x - 1, y);
  }
  if (y - 1 >= 0 && IsLand(grid, x, y - 1) && NotExploredYet(x, y - 1)) {
    Dfs(grid, x, y - 1);
  }
  if (x + 1 < width_ && IsLand(grid, x + 1, y) && NotExploredYet(x + 1, y)) {
    Dfs(grid, x + 1, y);
  }
  if (y + 1 < height_ && IsLand(grid, x, y + 1) && NotExploredYet(x, y + 1)) {
    Dfs(grid, x, y + 1);
  }
}

int32_t NumberOfIslands::GetNumberOfIslands(std::vector<std::vector<char>>& grid) noexcept {
  if (static_cast<int32_t>(grid.size()) == 0 || static_cast<int32_t>(grid[0].size()) == 0) {
    return 0;
  }
  height_ = static_cast<int32_t>(grid.size());
  width_ = static_cast<int32_t>(grid[0].size());
  number_of_islands_ = 0;

  explored_ = std::vector<bool>(height_ * width_, false);

  for (int32_t y = 0; y < height_; ++y) {
    for (int32_t x = 0; x < width_; ++x) {
      if (IsLand(grid, x, y) && NotExploredYet(x, y)) {
        ++number_of_islands_;
        Dfs(grid, x, y);
      }
    }
  }
  return number_of_islands_;
}

}  // namespace LC_200_2
