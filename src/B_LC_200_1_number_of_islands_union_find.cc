/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 200. Number of Islands
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. 
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 * You may assume all four edges of the grid are all surrounded by water.
 */

#include "src/B_LC_200_1_number_of_islands_union_find.h"

namespace LC_200_1 {

void CallNumberOfIslands(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  NumberOfIslands *number_of_islands = new NumberOfIslands();
  constexpr int32_t kMaxLoopCount = 20000000;
  std::vector<std::vector<char>> grid;
  for (int32_t i = 0; i < kMaxLoopCount; ++i) {
    std::vector<char> row;
    std::string text;
    input_stream >> text;
    std::cerr << text << std::endl;
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

int32_t NumberOfIslands::GetIndex(const int32_t x, const int32_t y) const noexcept {
  return (x + y * width_);
}

int32_t NumberOfIslands::GetX(const int32_t index) const noexcept {
  return index % width_;
}
int32_t NumberOfIslands::GetY(const int32_t index) const noexcept {
  return index / width_;
}

bool NumberOfIslands::IsLand(std::vector<std::vector<char>> &grid, const int32_t x, const int32_t y) const noexcept {
  return (grid[y][x] == '1');
}

int32_t NumberOfIslands::GetRoot(const int32_t index) noexcept {
  if (parents_[index] < 0) {
    return -1;
  }
  int32_t c_index = index;
  while (parents_[c_index] != c_index) {
    c_index = parents_[c_index];
  }
  const int32_t root = c_index;
  parents_[index] = root;
  return root;
}

void NumberOfIslands::Unite(const int32_t index1, const int32_t index2) noexcept {
  parents_[GetRoot(index2)] = GetRoot(parents_[index1]);
}

int32_t NumberOfIslands::GetNumberOfIslands(std::vector<std::vector<char>> &grid) noexcept {
  if (static_cast<int32_t>(grid.size()) == 0 || static_cast<int32_t>(grid[0].size()) == 0) {
    return 0;
  }
  height_ = static_cast<int32_t>(grid.size());
  width_ = static_cast<int32_t>(grid[0].size());

  parents_ = std::vector<int32_t>(height_ * width_);

  for (int32_t y = 0; y < height_; ++y) {
    for (int32_t x = 0; x < width_; ++x) {
      const int32_t index = GetIndex(x, y);
      if (IsLand(grid, x, y)) {
        parents_[index] = index;
        if (x - 1 >= 0 && IsLand(grid, x - 1, y)) {
          Unite(GetIndex(x - 1, y), GetIndex(x, y));
        }
        if (y - 1 >= 0 && IsLand(grid, x, y - 1)) {
          Unite(GetIndex(x, y - 1), GetIndex(x, y));
        }
      } else {
        parents_[index] = -1;
      }
    }
  }
  std::set<int32_t> islands;
  for (int32_t index = 0; index < width_ * height_; ++index) {
    const int32_t parent = GetRoot(index);
    if (parent >= 0) {
      islands.insert(parent);
    }
  }
  return static_cast<int32_t>(islands.size());
}

}  // namespace LC_200_1
