/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 200. Number of Islands. Implemented by Breadth First Search(BFS).
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. 
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 * You may assume all four edges of the grid are all surrounded by water.
 */

#include "src/B_LC_200_3_number_of_islands_bfs.h"

namespace LC_200_3 {

void CallNumberOfIslands(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  NumberOfIslands *number_of_islands = new NumberOfIslands();
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

int32_t NumberOfIslands::GetIndex(const int32_t x, const int32_t y) const noexcept {
  return (x + y * width_);
}

bool NumberOfIslands::IsLand(std::vector<std::vector<char>> &grid, const int32_t x, const int32_t y) const noexcept {
  return (grid[y][x] == '1');
}

bool NumberOfIslands::NotDiscoveredYet(const int32_t x, const int32_t y) const noexcept {
  return !discovered_[GetIndex(x, y)];
}

void NumberOfIslands::Enqueue(const int32_t x, const int32_t y) noexcept {
  queue_.push(Position(x, y));
  discovered_[GetIndex(x, y)] = true;
}

void NumberOfIslands::SearchSameIsland(std::vector<std::vector<char>> &grid, const int32_t start_x,
                                       const int32_t start_y) noexcept {
  queue_.push(Position(start_x, start_y));
  while (queue_.size() > 0) {
    const Position position = queue_.front();
    queue_.pop();
    const int32_t x = position.first;
    const int32_t y = position.second;

    const int32_t x1 = x - 1;
    if (x1 >= 0 && IsLand(grid, x1, y) && NotDiscoveredYet(x1, y)) {
      Enqueue(x1, y);
    }
    const int32_t y1 = y - 1;
    if (y1 >= 0 && IsLand(grid, x, y1) && NotDiscoveredYet(x, y1)) {
      Enqueue(x, y1);
    }
    const int32_t x2 = x + 1;
    if (x2 < width_ && IsLand(grid, x2, y) && NotDiscoveredYet(x2, y)) {
      Enqueue(x2, y);
    }
    const int32_t y2 = y + 1;
    if (y2 < height_ && IsLand(grid, x, y2) && NotDiscoveredYet(x, y2)) {
      Enqueue(x, y2);
    }
  }
}

int32_t NumberOfIslands::GetNumberOfIslands(std::vector<std::vector<char>> &grid) noexcept {
  if (static_cast<int32_t>(grid.size()) == 0 || static_cast<int32_t>(grid[0].size()) == 0) {
    return 0;
  }
  height_ = static_cast<int32_t>(grid.size());
  width_ = static_cast<int32_t>(grid[0].size());
  number_of_islands_ = 0;

  discovered_ = std::vector<bool>(height_ * width_, false);

  for (int32_t y = 0; y < height_; ++y) {
    for (int32_t x = 0; x < width_; ++x) {
      if (IsLand(grid, x, y) && NotDiscoveredYet(x, y)) {
        ++number_of_islands_;
        SearchSameIsland(grid, x, y);
      }
    }
  }
  return number_of_islands_;
}

}  // namespace LC_200_3
