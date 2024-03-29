/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-3. 動的計画法(Dynamic Programming, DP)、最長増加部分列(Longest Increasing Subsequence, LIS)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AOJ/textbook/17/3_DPL_1_D_3_longest_increasing_subsequence.h"

namespace DPL_1_D_3 {

class Test_DPL_1_D_3 : public ::testing::Test {
 protected:
  LongestIncreasingSubsequence* lis_;
  virtual void SetUp() { lis_ = new LongestIncreasingSubsequence(); }
  virtual void TearDown() { delete lis_; }
};

TEST_F(Test_DPL_1_D_3, FindLengthOfLis_1) {
  lis_->AppendValue(5);
  lis_->AppendValue(1);
  lis_->AppendValue(3);
  lis_->AppendValue(2);
  lis_->AppendValue(4);

  ASSERT_EQ(3, lis_->FindLengthOfLis());
}

TEST_F(Test_DPL_1_D_3, FindLengthOfLis_2) {
  lis_->AppendValue(1);
  lis_->AppendValue(2);

  const int32_t lis_length = lis_->FindLengthOfLis();
  EXPECT_EQ(2, lis_length);
}

TEST_F(Test_DPL_1_D_3, FindLengthOfLis_3) {
  lis_->AppendValue(3);
  lis_->AppendValue(3);
  lis_->AppendValue(2);
  lis_->AppendValue(9);
  lis_->AppendValue(0);
  lis_->AppendValue(8);
  lis_->AppendValue(2);
  lis_->AppendValue(6);
  lis_->AppendValue(6);
  lis_->AppendValue(9);
  lis_->AppendValue(1);
  lis_->AppendValue(1);
  lis_->AppendValue(3);
  lis_->AppendValue(5);
  lis_->AppendValue(8);
  lis_->AppendValue(3);
  lis_->AppendValue(0);
  lis_->AppendValue(6);
  lis_->AppendValue(9);
  lis_->AppendValue(2);
  lis_->AppendValue(7);
  lis_->AppendValue(7);
  lis_->AppendValue(2);
  lis_->AppendValue(8);
  lis_->AppendValue(0);
  lis_->AppendValue(3);
  lis_->AppendValue(9);
  lis_->AppendValue(2);
  lis_->AppendValue(4);
  lis_->AppendValue(9);
  lis_->AppendValue(1);
  lis_->AppendValue(7);
  lis_->AppendValue(0);
  lis_->AppendValue(4);
  lis_->AppendValue(5);
  lis_->AppendValue(0);
  lis_->AppendValue(4);
  lis_->AppendValue(0);
  lis_->AppendValue(2);
  lis_->AppendValue(4);
  lis_->AppendValue(3);
  lis_->AppendValue(1);
  lis_->AppendValue(0);
  lis_->AppendValue(6);
  lis_->AppendValue(6);
  lis_->AppendValue(1);
  lis_->AppendValue(9);
  lis_->AppendValue(7);
  lis_->AppendValue(5);
  lis_->AppendValue(1);

  const int32_t lis_length = lis_->FindLengthOfLis();
  EXPECT_EQ(8, lis_length);
}

TEST_F(Test_DPL_1_D_3, CallLongestIncreasingSubsequence_1) {
  std::ostringstream answer;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "4" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallLongestIncreasingSubsequence(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DPL_1_D_3, CallLongestIncreasingSubsequence_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallLongestIncreasingSubsequence(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DPL_1_D_3, CallLongestIncreasingSubsequence_3) {
  std::ostringstream answer;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "2" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallLongestIncreasingSubsequence(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace DPL_1_D_3
