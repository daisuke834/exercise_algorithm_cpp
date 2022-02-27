/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-5. 動的計画法(Dynamic Programming, DP)、最大長方形(Largest Rectangle)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C17_5_DPL_3_B_largest_rectangle.h"

#include <iostream>
#include <string>

namespace DPL_3_B {

void CallLargestRectangle(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  LargestRectangle* largest_rectangle = new LargestRectangle();
  try {
    int32_t height, width;
    input_stream >> height >> width;
    largest_rectangle->SetSize(height, width);
    for (int32_t row = 0; row < height; ++row) {
      for (int32_t column = 0; column < width; ++column) {
        int32_t value;
        input_stream >> value;
        largest_rectangle->SetTile(row, column, value);
      }
    }
    std::cout << largest_rectangle->FindLargestRectangleArea() << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallLargestRectangle()" << std::endl;
    delete largest_rectangle;
    throw;
  }
  delete largest_rectangle;
}

// ****************************************************
LargestRectangle::LargestRectangle() noexcept : height_(0), width_(0) {}

LargestRectangle::~LargestRectangle() noexcept {}

void LargestRectangle::SetSize(const int32_t height, const int32_t width) {
  if (height > kMaxHeight) {
    std::cerr << "ERROR: SetSize(): height exceeded a limit = " << kMaxHeight << std::endl;
  } else if (width > kMaxWidth) {
    std::cerr << "ERROR: SetSize(): width exceeded a limit = " << kMaxWidth << std::endl;
  } else {
    height_ = height;
    width_ = width;
  }
}

void LargestRectangle::SetTile(const int32_t row, const int32_t column, const int32_t value) {
  if (row >= height_) {
    std::cerr << "ERROR: SetSize(): Invalid arg: row = " << row << std::endl;
  } else if (column >= width_) {
    std::cerr << "ERROR: SetSize(): Invalid arg: column = " << column << std::endl;
  } else {
    const bool is_dirty = (value == 1);
    if (is_dirty) {
      length_to_upper_[row][column] = 0;
    } else if (row == 0) {
      length_to_upper_[row][column] = 1;
    } else {
      length_to_upper_[row][column] = 1 + length_to_upper_[row - 1][column];
    }
  }
}

int32_t LargestRectangle::FindLargestRectangleArea() {
  int32_t largest_rectangle_area = 0;
  try {
    for (int32_t row = 0; row < height_; ++row) {
      const int32_t area = FindLargestRectangleAreaPerRow(row);
      if (area > largest_rectangle_area) {
        largest_rectangle_area = area;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: FindLargestRectangleArea()" << std::endl;
    throw;
  }
  return largest_rectangle_area;
}

int32_t LargestRectangle::FindLargestRectangleAreaPerRow(const int32_t row) const {
  int32_t largest_rectangle_area = 0;
  try {
    std::stack<ExtendableRectangle> stack;
    for (int32_t column = 0; column < width_; ++column) {
      ExtendableRectangle rect;
      rect.height = length_to_upper_[row][column];
      rect.column_of_left = column;
      if (stack.empty()) {
        stack.push(rect);
      } else {
        const ExtendableRectangle top = stack.top();
        if (top.height < rect.height) {
          stack.push(rect);
        } else if (top.height == rect.height) {
          // DO NOTHING
        } else {
          while (!stack.empty()) {
            const ExtendableRectangle top = stack.top();
            if (top.height < rect.height) {
              break;
            }
            stack.pop();
            const int32_t width = column - top.column_of_left;
            const int32_t area = width * top.height;
            if (area > largest_rectangle_area) {
              largest_rectangle_area = area;
            }
            rect.column_of_left = top.column_of_left;
          }
          stack.push(rect);
        }
      }
    }
    while (!stack.empty()) {
      const ExtendableRectangle top = stack.top();
      stack.pop();
      const int32_t width = width_ - top.column_of_left;
      const int32_t area = width * top.height;
      if (area > largest_rectangle_area) {
        largest_rectangle_area = area;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: FindLargestRectangleAreaPerRow()" << std::endl;
    throw;
  }
  return largest_rectangle_area;
}

}  // namespace DPL_3_B
