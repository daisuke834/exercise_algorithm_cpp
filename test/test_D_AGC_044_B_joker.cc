/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Grand Contest(AGC) 044-B. Joker.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/D_AGC_044_B_joker.h"

namespace AGC_044_B {

class Test_AGC_044_B : public ::testing::Test {
 protected:
  std::vector<int32_t> input_;

 protected:
  virtual void SetUp() { input_.clear(); }
  virtual void TearDown() {}
};

TEST_F(Test_AGC_044_B, test_1) {
  Solution* solution = new Solution(3);
  int32_t inputs[] = {1, 3, 7, 9, 5, 4, 8, 6, 2};
  for (const int32_t value : inputs) {
    input_.push_back(value);
  }
  const int64_t result = solution->CalculateNumberOfPairs(input_);
  ASSERT_EQ(1, result);
  delete solution;
}

TEST_F(Test_AGC_044_B, test_2) {
  Solution* solution = new Solution(4);
  int32_t inputs[] = {6, 7, 1, 4, 13, 16, 10, 9, 5, 11, 12, 14, 15, 2, 3, 8};
  for (const int32_t value : inputs) {
    input_.push_back(value);
  }
  const int64_t result = solution->CalculateNumberOfPairs(input_);
  ASSERT_EQ(3, result);
  delete solution;
}

TEST_F(Test_AGC_044_B, test_3) {
  Solution* solution = new Solution(6);
  int32_t inputs[] = {11, 21, 35, 22, 7,  36, 27, 34, 8, 20, 15, 13, 16, 1,  24, 3, 2, 17,
                      26, 9,  18, 32, 31, 23, 19, 14, 4, 25, 10, 29, 28, 33, 12, 6, 5, 30};
  for (const int32_t value : inputs) {
    input_.push_back(value);
  }
  const int64_t result = solution->CalculateNumberOfPairs(input_);
  ASSERT_EQ(11, result);
  delete solution;
}

TEST_F(Test_AGC_044_B, CallMain_1) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "1 3 7 9 5 4 8 6 2" << std::endl;
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

}  // namespace AGC_044_B
