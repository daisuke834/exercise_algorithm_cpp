/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 200. Number of Islands. Implemented by Union Find Trees.
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. 
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 * You may assume all four edges of the grid are all surrounded by water.
 */

#ifndef SRC_B_LC_200_1_NUMBER_OF_ISLANDS_UNION_FIND_H_
#define SRC_B_LC_200_1_NUMBER_OF_ISLANDS_UNION_FIND_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace LC_200_1 {

void CallNumberOfIslands(std::istream &input_stream) noexcept;

class NumberOfIslands {
 public:
  NumberOfIslands() noexcept;
  ~NumberOfIslands() noexcept;
  int32_t GetNumberOfIslands(std::vector<std::vector<char>> &grid) noexcept;

 private:
  int32_t GetIndex(const int32_t x, const int32_t y) const noexcept;
  int32_t GetX(const int32_t index) const noexcept;
  int32_t GetY(const int32_t index) const noexcept;
  bool IsLand(std::vector<std::vector<char>> &grid, const int32_t x, const int32_t y) const noexcept;
  int32_t GetRoot(const int32_t index) noexcept;
  void Unite(const int32_t index1, const int32_t index2) noexcept;
  void InitializeTree(const int32_t index) noexcept;

 private:
  int32_t height_;
  int32_t width_;
  int32_t number_of_islands_;
  std::vector<int32_t> parents_;
};

}  // namespace LC_200_1

#endif  // SRC_B_LC_200_1_NUMBER_OF_ISLANDS_UNION_FIND_H_
