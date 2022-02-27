/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-4. 動的計画法(Dynamic Programming, DP)、最大正方形(Largest Square)。
 * 計算量はO(H*W*min(H,W))、外部記憶はO(H*W)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C17_4_DPL_3_A_1_largest_square.h"

#include <iostream>
#include <string>

namespace DPL_3_A_1 {

void CallLargestSquare(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  LargestSquare* longest_increasing_subsequence = new LargestSquare();
  try {
    int32_t height, width;
    input_stream >> height >> width;
    longest_increasing_subsequence->SetSize(height, width);
    for (int32_t row = 0; row < height; ++row) {
      for (int32_t column = 0; column < width; ++column) {
        int32_t value;
        input_stream >> value;
        longest_increasing_subsequence->SetTile(row, column, value);
      }
    }
    std::cout << longest_increasing_subsequence->FindLargestSquareSize() << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallLargestSquare()" << std::endl;
    delete longest_increasing_subsequence;
    throw;
  }
  delete longest_increasing_subsequence;
}

// ****************************************************
LargestSquare::LargestSquare() noexcept : height_(0), width_(0), largest_square_size_(0) {}

LargestSquare::~LargestSquare() noexcept {}

void LargestSquare::SetSize(const int32_t height, const int32_t width) {
  if (height > kMaxHeight) {
    std::cerr << "ERROR: SetSize(): height exceeded a limit = " << kMaxHeight << std::endl;
  } else if (width > kMaxWidth) {
    std::cerr << "ERROR: SetSize(): width exceeded a limit = " << kMaxWidth << std::endl;
  } else {
    height_ = height;
    width_ = width;
    largest_square_size_ = 0;
  }
}

void LargestSquare::SetTile(const int32_t row, const int32_t column, const int32_t value) {
  if (row >= height_) {
    std::cerr << "ERROR: SetSize(): Invalid arg: row = " << row << std::endl;
  } else if (column >= width_) {
    std::cerr << "ERROR: SetSize(): Invalid arg: column = " << column << std::endl;
  } else {
    is_square_[row][column] = ((value == 0) ? true : false);
    if (is_square_[row][column]) {
      largest_square_size_ = 1;
    }
  }
}

int32_t LargestSquare::FindLargestSquareSize() {
  const int32_t max_length = ((height_ < width_) ? height_ : width_);
  for (int32_t length = 2; length <= max_length; ++length) {
    bool was_found = false;
    for (int32_t row = 0; row < height_ - length + 1; ++row) {
      for (int32_t column = 0; column < width_ - length + 1; ++column) {
        const bool is_square = IsSquare(row, column);
        was_found |= is_square;
        is_square_[row][column] = is_square;
      }
    }
    if (was_found) {
      largest_square_size_ = length * length;
    } else {
      break;
    }
  }
  return largest_square_size_;
}

bool LargestSquare::IsSquare(const int32_t row, const int32_t column) const {
  const bool is_square = is_square_[row][column] && is_square_[row][column + 1] && is_square_[row + 1][column] &&
                         is_square_[row + 1][column + 1];
  return is_square;
}

}  // namespace DPL_3_A_1
