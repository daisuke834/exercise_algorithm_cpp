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

}  // namespace DSL_2_A
