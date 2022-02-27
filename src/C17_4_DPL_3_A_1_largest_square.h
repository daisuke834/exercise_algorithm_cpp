/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-4. 動的計画法(Dynamic Programming, DP)、最大正方形(Largest Square)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C17_4_DPL_3_A_1_LARGEST_SQUARE_H_
#define SRC_C17_4_DPL_3_A_1_LARGEST_SQUARE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>

namespace DPL_3_A_1 {

constexpr int32_t kMaxHeight = 1400;
constexpr int32_t kMaxWidth = 1400;

void CallLargestSquare(std::istream& input_stream);

class LargestSquare {
 public:
  LargestSquare() noexcept;
  ~LargestSquare() noexcept;
  void SetSize(const int32_t height, const int32_t width);
  void SetTile(const int32_t row, const int32_t column, const int32_t value);
  int32_t FindLargestSquareSize();

 private:
  bool IsSquare(const int32_t row, const int32_t column) const;

  LargestSquare(const LargestSquare& obj) = delete;
  LargestSquare& operator=(const LargestSquare& obj) = delete;
  LargestSquare(LargestSquare&& obj) = delete;
  LargestSquare& operator=(LargestSquare&& obj) = delete;

 private:
  int32_t height_;
  int32_t width_;
  int32_t largest_square_size_;
  bool is_square_[kMaxHeight][kMaxWidth];

 private:
  FRIEND_TEST(Test_DPL_3_A_1, dummy);  // Should be removed from production code
};

}  // namespace DPL_3_A_1

#endif  // SRC_C17_4_DPL_3_A_1_LARGEST_SQUARE_H_
