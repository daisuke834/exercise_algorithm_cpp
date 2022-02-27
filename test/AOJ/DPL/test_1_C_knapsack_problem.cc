/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 動的計画法(Dynamic Programming, DP)、個別制限なしナップザック問題(Knapsack Problem)。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AOJ/DPL/1_C_knapsack_problem.h"

namespace DPL_1_C {

class Test_DPL_1_C : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_DPL_1_C, CallKnapsackProblem_1) {
  std::ostringstream answer;
  answer << "21" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 8" << std::endl;
  input_stream << "4 2" << std::endl;
  input_stream << "5 2" << std::endl;
  input_stream << "2 1" << std::endl;
  input_stream << "8 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKnapsackProblem(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DPL_1_C, CallKnapsackProblem_2) {
  std::ostringstream answer;
  answer << "10" << std::endl;

  std::ostringstream input_stream;
  input_stream << "2 20" << std::endl;
  input_stream << "5 9" << std::endl;
  input_stream << "4 10" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKnapsackProblem(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DPL_1_C, CallKnapsackProblem_3) {
  std::ostringstream answer;
  answer << "27" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3 9" << std::endl;
  input_stream << "2 1" << std::endl;
  input_stream << "3 1" << std::endl;
  input_stream << "5 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKnapsackProblem(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace DPL_1_C
