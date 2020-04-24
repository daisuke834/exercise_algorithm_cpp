/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-1. Part7-2. 高等的整列、パーティション(Partition)のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C07_2_ALDS1_6_B_partition.h"

namespace ALDS1_6_B {

class Test_ALDS1_6_B : public ::testing::Test {
 protected:
  Partition *partition_;
  virtual void SetUp() {
    partition_ = new Partition();
  }
  virtual void TearDown() {
    delete partition_;
  }
};

TEST_F(Test_ALDS1_6_B, CallPartition) {
  std::ostringstream answer;
  answer << "9 5 8 7 4 2 6 [11] 21 13 19 12" << std::endl;

  std::ostringstream input_stream;
  input_stream << "12" << std::endl;
  input_stream << "13 19 9 5 12 8 7 4 21 2 6 11" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallPartition(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_6_B, AddData) {
  ASSERT_EQ(0, partition_->size_);

  constexpr int32_t kValue_0 = 3;
  constexpr int32_t kValue_1 = 10;
  partition_->AddData(kValue_0);
  partition_->AddData(kValue_1);
  ASSERT_EQ(2, partition_->size_);
  ASSERT_EQ(kValue_0, partition_->values_[0]);
  ASSERT_EQ(kValue_1, partition_->values_[1]);
}

TEST_F(Test_ALDS1_6_B, Swap) {
  constexpr int32_t kValue_0 = 3;
  constexpr int32_t kValue_1 = 10;
  constexpr int32_t kValue_2 = 17;
  partition_->AddData(kValue_0);
  partition_->AddData(kValue_1);
  partition_->AddData(kValue_2);
  ASSERT_EQ(kValue_0, partition_->values_[0]);
  ASSERT_EQ(kValue_1, partition_->values_[1]);
  ASSERT_EQ(kValue_2, partition_->values_[2]);

  partition_->Swap(0, 1);

  ASSERT_EQ(kValue_1, partition_->values_[0]);
  ASSERT_EQ(kValue_0, partition_->values_[1]);
  ASSERT_EQ(kValue_2, partition_->values_[2]);
}

TEST_F(Test_ALDS1_6_B, ComputePartition_1) {
  partition_->AddData(13);
  partition_->AddData(19);

  const int32_t index_pivot = partition_->ComputePartition(0, 1);
  ASSERT_EQ(1, index_pivot);

  int32_t index = 0;
  ASSERT_EQ(13, partition_->values_[index++]);
  ASSERT_EQ(19, partition_->values_[index++]);
}

TEST_F(Test_ALDS1_6_B, ComputePartition_2) {
  partition_->AddData(13);
  partition_->AddData(19);
  partition_->AddData(9);
  partition_->AddData(5);
  partition_->AddData(12);
  partition_->AddData(8);
  partition_->AddData(7);
  partition_->AddData(4);
  partition_->AddData(21);
  partition_->AddData(2);
  partition_->AddData(6);
  partition_->AddData(11);

  const int32_t index_pivot = partition_->ComputePartition(0, 11);
  ASSERT_EQ(7, index_pivot);

  int32_t index = 0;
  ASSERT_EQ(9, partition_->values_[index++]);
  ASSERT_EQ(5, partition_->values_[index++]);
  ASSERT_EQ(8, partition_->values_[index++]);
  ASSERT_EQ(7, partition_->values_[index++]);
  ASSERT_EQ(4, partition_->values_[index++]);
  ASSERT_EQ(2, partition_->values_[index++]);
  ASSERT_EQ(6, partition_->values_[index++]);
  ASSERT_EQ(11, partition_->values_[index++]);
  ASSERT_EQ(21, partition_->values_[index++]);
  ASSERT_EQ(13, partition_->values_[index++]);
  ASSERT_EQ(19, partition_->values_[index++]);
  ASSERT_EQ(12, partition_->values_[index++]);
}

}  // namespace ALDS1_6_B
