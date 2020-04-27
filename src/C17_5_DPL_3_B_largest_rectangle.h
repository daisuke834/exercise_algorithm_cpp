/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-5. 動的計画法(Dynamic Programming, DP)、最大長方形(Largest Rectangle)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C17_5_DPL_3_B_LARGEST_RECTANGLE_H_
#define SRC_C17_5_DPL_3_B_LARGEST_RECTANGLE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <stack>

namespace DPL_3_B {

constexpr int32_t kMaxHeight = 1400;
constexpr int32_t kMaxWidth = 1400;

void CallLargestRectangle(std::istream &input_stream);

struct ExtendableRectangle {
  int32_t height{-1};
  int32_t column_of_left{-1};
};

class LargestRectangle {
 public:
  LargestRectangle() noexcept;
  ~LargestRectangle() noexcept;
  void SetSize(const int32_t height, const int32_t width);
  void SetTile(const int32_t row, const int32_t column, const int32_t value);
  int32_t FindLargestRectangleArea();

 private:
  int32_t FindLargestRectangleAreaPerRow(const int32_t row) const;

  LargestRectangle(const LargestRectangle &obj) = delete;
  LargestRectangle &operator=(const LargestRectangle &obj) = delete;
  LargestRectangle(LargestRectangle &&obj) = delete;
  LargestRectangle &operator=(LargestRectangle &&obj) = delete;

 private:
  int32_t height_;
  int32_t width_;
  int32_t length_to_upper_[kMaxHeight][kMaxWidth];

 private:
  FRIEND_TEST(Test_DPL_3_B, SetTile);  // Should be removed from production code
};

}  // namespace DPL_3_B

#endif  // SRC_C17_5_DPL_3_B_LARGEST_RECTANGLE_H_
