/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-5. 動的計画法(Dynamic Programming, DP)、最大長方形(Largest Rectangle)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C17_5_DPL_3_B_largest_rectangle.h"

namespace DPL_3_B {

class Test_DPL_3_B : public ::testing::Test {
 protected:
  LargestRectangle *largest_rectangle_;
  virtual void SetUp() {
    largest_rectangle_ = new LargestRectangle();
  }
  virtual void TearDown() {
    delete largest_rectangle_;
  }
};

TEST_F(Test_DPL_3_B, SetTile) {
  constexpr int32_t kDirty = 1;
  constexpr int32_t kClean = 0;
  largest_rectangle_->SetSize(4, 4);
  int32_t row, column;

  row = 0;
  column = 0;
  largest_rectangle_->SetTile(row, column++, kClean);
  largest_rectangle_->SetTile(row, column++, kClean);
  largest_rectangle_->SetTile(row, column++, kDirty);
  largest_rectangle_->SetTile(row, column++, kClean);

  ++row;
  column = 0;
  largest_rectangle_->SetTile(row, column++, kClean);
  largest_rectangle_->SetTile(row, column++, kClean);
  largest_rectangle_->SetTile(row, column++, kClean);
  largest_rectangle_->SetTile(row, column++, kClean);

  ++row;
  column = 0;
  largest_rectangle_->SetTile(row, column++, kDirty);
  largest_rectangle_->SetTile(row, column++, kClean);
  largest_rectangle_->SetTile(row, column++, kClean);
  largest_rectangle_->SetTile(row, column++, kClean);

  ++row;
  column = 0;
  largest_rectangle_->SetTile(row, column++, kClean);
  largest_rectangle_->SetTile(row, column++, kClean);
  largest_rectangle_->SetTile(row, column++, kClean);
  largest_rectangle_->SetTile(row, column++, kDirty);

  row = 0;
  column = 0;
  ASSERT_EQ(1, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(1, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(0, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(1, largest_rectangle_->length_to_upper_[row][column++]);

  ++row;
  column = 0;
  ASSERT_EQ(2, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(2, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(1, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(2, largest_rectangle_->length_to_upper_[row][column++]);

  ++row;
  column = 0;
  ASSERT_EQ(0, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(3, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(2, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(3, largest_rectangle_->length_to_upper_[row][column++]);

  ++row;
  column = 0;
  ASSERT_EQ(1, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(4, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(3, largest_rectangle_->length_to_upper_[row][column++]);
  ASSERT_EQ(0, largest_rectangle_->length_to_upper_[row][column++]);
}

TEST_F(Test_DPL_3_B, CallLargestRectangle_1) {
  std::ostringstream answer;
  answer << "6" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 5" << std::endl;
  input_stream << "0 0 1 0 0" << std::endl;
  input_stream << "1 0 0 0 0" << std::endl;
  input_stream << "0 0 0 1 0" << std::endl;
  input_stream << "0 0 0 1 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallLargestRectangle(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DPL_3_B, CallLargestRectangle_2) {
  std::ostringstream answer;
  answer << "10" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 5" << std::endl;
  input_stream << "0 0 0 0 0" << std::endl;
  input_stream << "0 0 0 0 0" << std::endl;
  input_stream << "0 1 0 1 0" << std::endl;
  input_stream << "0 0 0 1 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallLargestRectangle(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace DPL_3_B
