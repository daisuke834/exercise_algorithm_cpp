/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-2. 動的計画法(Dynamic Programming, DP)、0-1ナップザック問題(Knapsack Problem)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/C17_2_DPL_1_B_01knapsack_problem.h"

namespace DPL_1_B {

class Test_DPL_1_B : public ::testing::Test {
 protected:
  KnapsackProblem* knapsack_problem_;
  virtual void SetUp() { knapsack_problem_ = new KnapsackProblem(); }
  virtual void TearDown() { delete knapsack_problem_; }
};

TEST_F(Test_DPL_1_B, Call01KnapsackProblem_1) {
  std::ostringstream answer;
  answer << "13" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 5" << std::endl;
  input_stream << "4 2" << std::endl;
  input_stream << "5 2" << std::endl;
  input_stream << "2 1" << std::endl;
  input_stream << "8 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    Call01KnapsackProblem(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DPL_1_B, Call01KnapsackProblem_2) {
  std::ostringstream answer;
  answer << "9" << std::endl;

  std::ostringstream input_stream;
  input_stream << "2 20" << std::endl;
  input_stream << "5 9" << std::endl;
  input_stream << "4 10" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    Call01KnapsackProblem(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace DPL_1_B
