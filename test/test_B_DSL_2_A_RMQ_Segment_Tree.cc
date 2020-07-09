/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AOJ DSL_2_A Range Minimum Query問題(RMQ)。セグメント木(Segment Tree)。
 * https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_DSL_2_A_RMQ_Segment_Tree.h"

namespace DSL_2_A {

class Test_DSL_2_A : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_DSL_2_A, RangeMinimumQuery_1) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3 5" << std::endl;
  input_stream << "0 0 1" << std::endl;
  input_stream << "0 1 2" << std::endl;
  input_stream << "0 2 3" << std::endl;
  input_stream << "1 0 2" << std::endl;
  input_stream << "1 1 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DSL_2_A, RangeMinimumQuery_2) {
  std::ostringstream answer;
  answer << "2147483647" << std::endl;
  answer << "5" << std::endl;

  std::ostringstream input_stream;
  input_stream << "1 3" << std::endl;
  input_stream << "1 0 0" << std::endl;
  input_stream << "0 0 5" << std::endl;
  input_stream << "1 0 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DSL_2_A, RangeMinimumQuery_3) {
  std::ostringstream answer;
  answer << "2147483647" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "8" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "8" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "8" << std::endl;
  answer << "8" << std::endl;
  answer << "4" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "4" << std::endl;
  answer << "4" << std::endl;
  answer << "4" << std::endl;
  answer << "3" << std::endl;
  answer << "4" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "3" << std::endl;
  answer << "4" << std::endl;
  answer << "3" << std::endl;
  answer << "3" << std::endl;
  answer << "4" << std::endl;
  answer << "3" << std::endl;
  answer << "3" << std::endl;
  answer << "3" << std::endl;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3 34" << std::endl;
  input_stream << "1 0 0" << std::endl;
  input_stream << "1 1 1" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "1 0 1" << std::endl;
  input_stream << "1 1 2" << std::endl;
  input_stream << "1 0 2" << std::endl;
  input_stream << "0 0 8" << std::endl;
  input_stream << "1 0 0" << std::endl;
  input_stream << "1 1 1" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "1 0 1" << std::endl;
  input_stream << "1 1 2" << std::endl;
  input_stream << "1 0 2" << std::endl;
  input_stream << "0 1 4" << std::endl;
  input_stream << "1 0 0" << std::endl;
  input_stream << "1 1 1" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "1 0 1" << std::endl;
  input_stream << "1 1 2" << std::endl;
  input_stream << "1 0 2" << std::endl;
  input_stream << "0 0 3" << std::endl;
  input_stream << "1 0 0" << std::endl;
  input_stream << "1 1 1" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "1 0 1" << std::endl;
  input_stream << "1 1 2" << std::endl;
  input_stream << "1 0 2" << std::endl;
  input_stream << "0 2 3" << std::endl;
  input_stream << "1 0 0" << std::endl;
  input_stream << "1 1 1" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "1 0 1" << std::endl;
  input_stream << "1 1 2" << std::endl;
  input_stream << "1 0 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DSL_2_A, RangeMinimumQuery_4) {
  std::ostringstream answer;
  answer << "2147483647" << std::endl;
  answer << "22" << std::endl;
  answer << "22" << std::endl;
  answer << "11" << std::endl;
  answer << "11" << std::endl;
  answer << "11" << std::endl;
  answer << "30" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "2147483647" << std::endl;
  answer << "11" << std::endl;
  answer << "30" << std::endl;
  answer << "11" << std::endl;
  answer << "22" << std::endl;
  answer << "19" << std::endl;
  answer << "19" << std::endl;
  answer << "19" << std::endl;
  answer << "6" << std::endl;
  answer << "38" << std::endl;
  answer << "19" << std::endl;
  answer << "27" << std::endl;
  answer << "18" << std::endl;
  answer << "19" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10 50" << std::endl;
  input_stream << "0 2 43" << std::endl;
  input_stream << "0 8 0" << std::endl;
  input_stream << "1 6 6" << std::endl;
  input_stream << "0 1 11" << std::endl;
  input_stream << "0 8 5" << std::endl;
  input_stream << "0 6 30" << std::endl;
  input_stream << "0 7 32" << std::endl;
  input_stream << "0 8 22" << std::endl;
  input_stream << "1 3 9" << std::endl;
  input_stream << "1 4 9" << std::endl;
  input_stream << "0 0 27" << std::endl;
  input_stream << "1 0 5" << std::endl;
  input_stream << "1 0 2" << std::endl;
  input_stream << "1 1 3" << std::endl;
  input_stream << "1 6 6" << std::endl;
  input_stream << "0 7 29" << std::endl;
  input_stream << "0 0 41" << std::endl;
  input_stream << "1 4 5" << std::endl;
  input_stream << "0 7 30" << std::endl;
  input_stream << "1 3 4" << std::endl;
  input_stream << "1 0 9" << std::endl;
  input_stream << "1 2 6" << std::endl;
  input_stream << "1 0 3" << std::endl;
  input_stream << "0 5 19" << std::endl;
  input_stream << "0 7 49" << std::endl;
  input_stream << "0 4 47" << std::endl;
  input_stream << "1 6 9" << std::endl;
  input_stream << "1 3 5" << std::endl;
  input_stream << "0 9 6" << std::endl;
  input_stream << "1 2 5" << std::endl;
  input_stream << "0 1 38" << std::endl;
  input_stream << "1 0 7" << std::endl;
  input_stream << "0 3 6" << std::endl;
  input_stream << "0 2 27" << std::endl;
  input_stream << "1 2 8" << std::endl;
  input_stream << "0 0 10" << std::endl;
  input_stream << "1 1 1" << std::endl;
  input_stream << "1 4 7" << std::endl;
  input_stream << "0 8 25" << std::endl;
  input_stream << "0 7 18" << std::endl;
  input_stream << "0 3 37" << std::endl;
  input_stream << "0 0 45" << std::endl;
  input_stream << "1 2 3" << std::endl;
  input_stream << "1 3 7" << std::endl;
  input_stream << "0 0 30" << std::endl;
  input_stream << "0 6 28" << std::endl;
  input_stream << "0 8 47" << std::endl;
  input_stream << "0 8 38" << std::endl;
  input_stream << "0 8 43" << std::endl;
  input_stream << "1 1 6" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace DSL_2_A
