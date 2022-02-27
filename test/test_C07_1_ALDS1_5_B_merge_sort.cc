/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-1. 高等的整列、マージソート(Merge Sort)のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/C07_1_ALDS1_5_B_merge_sort.h"

namespace ALDS1_5_B {

class Test_ALDS1_5_B : public ::testing::Test {
 protected:
  MergeSort* merge_sort_;
  virtual void SetUp() { merge_sort_ = new MergeSort(); }
  virtual void TearDown() { delete merge_sort_; }
};

TEST_F(Test_ALDS1_5_B, CallMergeSort) {
  std::ostringstream answer;
  answer << "1 2 3 4 5 6 7 8 9 10" << std::endl;
  answer << "34" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10" << std::endl;
  input_stream << "8 5 9 2 6 3 7 1 10 4" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMergeSort(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_5_B, AddData) {
  ASSERT_EQ(0, merge_sort_->size_);

  constexpr int32_t kValue_0 = 3;
  constexpr int32_t kValue_1 = 10;
  merge_sort_->AddData(kValue_0);
  merge_sort_->AddData(kValue_1);
  ASSERT_EQ(2, merge_sort_->size_);
  ASSERT_EQ(kValue_0, merge_sort_->values_[0]);
  ASSERT_EQ(kValue_1, merge_sort_->values_[1]);
}

TEST_F(Test_ALDS1_5_B, GetCenterIndex) {
  constexpr int32_t kSize = 10;
  merge_sort_->size_ = kSize;
  ASSERT_NO_THROW(merge_sort_->GetCenterIndex(0, kSize));
  ASSERT_ANY_THROW(merge_sort_->GetCenterIndex(-1, kSize));
  ASSERT_ANY_THROW(merge_sort_->GetCenterIndex(0, kSize + 1));

  ASSERT_ANY_THROW(merge_sort_->GetCenterIndex(0, 0));
  ASSERT_ANY_THROW(merge_sort_->GetCenterIndex(1, 0));
  ASSERT_ANY_THROW(merge_sort_->GetCenterIndex(0, 1));

  ASSERT_EQ(1, merge_sort_->GetCenterIndex(0, 2));
  ASSERT_EQ(1, merge_sort_->GetCenterIndex(0, 3));
  ASSERT_EQ(2, merge_sort_->GetCenterIndex(0, 4));
  ASSERT_EQ(2, merge_sort_->GetCenterIndex(0, 5));
  ASSERT_EQ(3, merge_sort_->GetCenterIndex(0, 6));
}

TEST_F(Test_ALDS1_5_B, MergeLeftAndRight) {
  ASSERT_ANY_THROW(merge_sort_->MergeLeftAndRight(0, 1, 2));

  merge_sort_->AddData(6);
  ASSERT_ANY_THROW(merge_sort_->MergeLeftAndRight(0, 1, 2));

  merge_sort_->ResetData();
  merge_sort_->AddData(6);
  merge_sort_->AddData(3);
  ASSERT_EQ(6, merge_sort_->values_[0]);
  ASSERT_EQ(3, merge_sort_->values_[1]);
  ASSERT_EQ(0, merge_sort_->left_values_[0]);
  ASSERT_EQ(0, merge_sort_->right_values_[0]);
  merge_sort_->MergeLeftAndRight(0, 1, 2);
  ASSERT_EQ(6, merge_sort_->left_values_[0]);
  ASSERT_EQ(3, merge_sort_->right_values_[0]);
  ASSERT_EQ(3, merge_sort_->values_[0]);
  ASSERT_EQ(6, merge_sort_->values_[1]);

  merge_sort_->ResetData();
  merge_sort_->AddData(3);
  merge_sort_->AddData(6);
  merge_sort_->AddData(1);
  merge_sort_->AddData(5);
  ASSERT_EQ(3, merge_sort_->values_[0]);
  ASSERT_EQ(6, merge_sort_->values_[1]);
  ASSERT_EQ(1, merge_sort_->values_[2]);
  ASSERT_EQ(5, merge_sort_->values_[3]);
  merge_sort_->MergeLeftAndRight(0, 2, 4);
  ASSERT_EQ(1, merge_sort_->values_[0]);
  ASSERT_EQ(3, merge_sort_->values_[1]);
  ASSERT_EQ(5, merge_sort_->values_[2]);
  ASSERT_EQ(6, merge_sort_->values_[3]);
}

TEST_F(Test_ALDS1_5_B, ComputeMergeSort) {
  merge_sort_->AddData(6);
  merge_sort_->AddData(3);
  merge_sort_->AddData(5);
  merge_sort_->AddData(1);
  merge_sort_->AddData(8);
  merge_sort_->AddData(2);
  merge_sort_->AddData(4);
  merge_sort_->AddData(7);
  int32_t index = 0;
  ASSERT_EQ(6, merge_sort_->values_[index++]);
  ASSERT_EQ(3, merge_sort_->values_[index++]);
  ASSERT_EQ(5, merge_sort_->values_[index++]);
  ASSERT_EQ(1, merge_sort_->values_[index++]);
  ASSERT_EQ(8, merge_sort_->values_[index++]);
  ASSERT_EQ(2, merge_sort_->values_[index++]);
  ASSERT_EQ(4, merge_sort_->values_[index++]);
  ASSERT_EQ(7, merge_sort_->values_[index++]);
  merge_sort_->ComputeMergeSort(0, 8);
  index = 0;
  ASSERT_EQ(1, merge_sort_->values_[index++]);
  ASSERT_EQ(2, merge_sort_->values_[index++]);
  ASSERT_EQ(3, merge_sort_->values_[index++]);
  ASSERT_EQ(4, merge_sort_->values_[index++]);
  ASSERT_EQ(5, merge_sort_->values_[index++]);
  ASSERT_EQ(6, merge_sort_->values_[index++]);
  ASSERT_EQ(7, merge_sort_->values_[index++]);
  ASSERT_EQ(8, merge_sort_->values_[index++]);
}
}  // namespace ALDS1_5_B
