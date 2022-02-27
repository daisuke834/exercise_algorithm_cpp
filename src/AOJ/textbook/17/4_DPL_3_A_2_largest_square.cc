/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-4. 動的計画法(Dynamic Programming, DP)、最大正方形(Largest Square)。
 * 計算量はO(H*W)、外部記憶はO(H*W)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "4_DPL_3_A_2_largest_square.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace DPL_3_A_2 {

void CallLargestSquare(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  LargestSquare* largest_square = new LargestSquare();
  try {
    int32_t height, width;
    input_stream >> height >> width;
    largest_square->SetSize(height, width);
    for (int32_t row = 0; row < height; ++row) {
      for (int32_t column = 0; column < width; ++column) {
        int32_t value;
        input_stream >> value;
        largest_square->SetTile(row, column, value);
      }
    }
    std::cout << largest_square->FindLargestSquareSize() << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallLargestSquare()" << std::endl;
    delete largest_square;
    throw;
  }
  delete largest_square;
}

// ****************************************************
LargestSquare::LargestSquare() noexcept : height_(0), width_(0) {}

LargestSquare::~LargestSquare() noexcept {}

void LargestSquare::SetSize(const int32_t height, const int32_t width) {
  if (height > kMaxHeight) {
    std::cerr << "ERROR: SetSize(): height exceeded a limit = " << kMaxHeight << std::endl;
  } else if (width > kMaxWidth) {
    std::cerr << "ERROR: SetSize(): width exceeded a limit = " << kMaxWidth << std::endl;
  } else {
    height_ = height;
    width_ = width;
  }
}

void LargestSquare::SetTile(const int32_t row, const int32_t column, const int32_t value) {
  if (row >= height_) {
    std::cerr << "ERROR: SetSize(): Invalid arg: row = " << row << std::endl;
  } else if (column >= width_) {
    std::cerr << "ERROR: SetSize(): Invalid arg: column = " << column << std::endl;
  } else {
    length_to_upper_and_left_[row][column] = ((value == 0) ? 1 : 0);
  }
}

int32_t LargestSquare::FindLargestSquareSize() {
  int32_t largest_square_size = 0;
  for (int32_t row = 0; row < height_; ++row) {
    for (int32_t column = 0; column < width_; ++column) {
      const int32_t square_length = GetSquareLengthToUpperAndLeft(row, column);
      length_to_upper_and_left_[row][column] = square_length;
      if (square_length * square_length > largest_square_size) {
        largest_square_size = square_length * square_length;
      }
    }
  }
  return largest_square_size;
}

int32_t LargestSquare::GetSquareLengthToUpperAndLeft(const int32_t row, const int32_t column) const {
  int32_t length;
  if (length_to_upper_and_left_[row][column] > 0) {
    if ((row > 0) && (column > 0)) {
      const int32_t neighbour_upper_left = length_to_upper_and_left_[row - 1][column - 1];
      const int32_t neighbour_left = length_to_upper_and_left_[row][column - 1];
      const int32_t neighbour_top = length_to_upper_and_left_[row - 1][column];
      length = 1 + std::min(neighbour_upper_left, std::min(neighbour_left, neighbour_top));
    } else {
      length = 1;
    }
  } else {
    length = 0;
  }
  return length;
}

}  // namespace DPL_3_A_2
