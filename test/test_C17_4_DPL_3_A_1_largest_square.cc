/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-4. 動的計画法(Dynamic Programming, DP)、最大正方形(Largest Square)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/C17_4_DPL_3_A_1_largest_square.h"

namespace DPL_3_A_1 {

class Test_DPL_3_A_1 : public ::testing::Test {
 protected:
  LargestSquare* largest_square_;
  virtual void SetUp() { largest_square_ = new LargestSquare(); }
  virtual void TearDown() { delete largest_square_; }
};

TEST_F(Test_DPL_3_A_1, CallLargestSquare_1) {
  std::ostringstream answer;
  answer << "4" << std::endl;

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
    CallLargestSquare(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DPL_3_A_1, CallLargestSquare_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5 4" << std::endl;
  input_stream << "1 1 1 1" << std::endl;
  input_stream << "1 1 0 1" << std::endl;
  input_stream << "1 0 0 0" << std::endl;
  input_stream << "1 1 0 1" << std::endl;
  input_stream << "1 1 1 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallLargestSquare(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DPL_3_A_1, CallLargestSquare_3) {
  std::ostringstream answer;
  answer << "9" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 5" << std::endl;
  input_stream << "0 0 0 0 0" << std::endl;
  input_stream << "0 0 0 0 0" << std::endl;
  input_stream << "0 0 0 1 0" << std::endl;
  input_stream << "0 0 0 1 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallLargestSquare(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DPL_3_A_1, CallLargestSquare_4) {
  std::ostringstream answer;
  answer << "4" << std::endl;

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
    CallLargestSquare(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DPL_3_A_1, CallLargestSquare_5) {
  std::ostringstream answer;
  answer << "4" << std::endl;

  std::ostringstream input_stream;
  input_stream << "2 39" << std::endl;
  input_stream << "1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0 0 1 1 1 0 0 0 0 1" << std::endl;
  input_stream << "1 0 0 0 1 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 1 1 1 1 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallLargestSquare(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace DPL_3_A_1
