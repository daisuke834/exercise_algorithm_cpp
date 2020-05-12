/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. 
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 * You may assume all four edges of the grid are all surrounded by water.
 */

#ifndef SRC_B_LEETCODE_200_1_NUMBER_OF_ISLANDS_UNION_FIND_H_
#define SRC_B_LEETCODE_200_1_NUMBER_OF_ISLANDS_UNION_FIND_H_

#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace leetcode_200_1 {

void CallNumberOfIslands(std::istream &input_stream) noexcept;

class NumberOfIslands {
 public:
  int32_t GetNumberOfIslands(std::vector<std::vector<char>> &grid);

 private:
  int32_t GetIndex(const int32_t x, const int32_t y);
  int32_t GetX(const int32_t index);
  int32_t GetY(const int32_t index);
  bool IsLand(std::vector<std::vector<char>> &grid, const int32_t x, const int32_t y);
  int32_t GetRoot(std::vector<int32_t> &parents, const int32_t index);
  void Unite(std::vector<int32_t> &parents, const int32_t index1, const int32_t index2);

 private:
  int32_t height_;
  int32_t width_;
};

}  // namespace leetcode_200_1

#endif  // SRC_B_LEETCODE_200_1_NUMBER_OF_ISLANDS_UNION_FIND_H_
