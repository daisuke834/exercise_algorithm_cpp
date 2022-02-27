/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-197-4. 1515. Best Position for a Service Centre
 * https://leetcode.com/contest/weekly-contest-197/problems/best-position-for-a-service-centre/
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/LeetCode/weekly/197_4_ternary_search.h"

namespace LC_weekly_197_4 {

class Test_LC_weekly_197_4 : public ::testing::Test {
 protected:
  Solution* solution_;
  virtual void SetUp() { solution_ = new Solution(); }
  virtual void TearDown() { delete solution_; }
};

TEST_F(Test_LC_weekly_197_4, test_1) {
  std::vector<std::vector<int>> inputs = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};
  const double answer = 4.00000;
  ASSERT_NEAR(answer, solution_->getMinDistSum(inputs), 1e-5);
}

TEST_F(Test_LC_weekly_197_4, test_2) {
  std::vector<std::vector<int>> inputs = {{1, 1}, {3, 3}};
  const double answer = 2.82843;
  ASSERT_NEAR(answer, solution_->getMinDistSum(inputs), 1e-5);
}

TEST_F(Test_LC_weekly_197_4, test_3) {
  std::vector<std::vector<int>> inputs = {{1, 1}};
  const double answer = 0.00000;
  ASSERT_NEAR(answer, solution_->getMinDistSum(inputs), 1e-5);
}

TEST_F(Test_LC_weekly_197_4, test_4) {
  std::vector<std::vector<int>> inputs = {{1, 1}, {0, 0}, {2, 0}};
  const double answer = 2.73205;
  ASSERT_NEAR(answer, solution_->getMinDistSum(inputs), 1e-5);
}

TEST_F(Test_LC_weekly_197_4, test_5) {
  std::vector<std::vector<int>> inputs = {{0, 1}, {3, 2}, {4, 5}, {7, 6}, {8, 9}, {11, 1}, {2, 12}};
  const double answer = 32.94036;
  ASSERT_NEAR(answer, solution_->getMinDistSum(inputs), 1e-5);
}

TEST_F(Test_LC_weekly_197_4, test_6) {
  std::vector<std::vector<int>> inputs = {{9, 9}, {31, 1}, {28, 61}, {14, 42}, {95, 98}, {37, 69}};
  const double answer = 224.76750;
  ASSERT_NEAR(answer, solution_->getMinDistSum(inputs), 1e-5);
}

TEST_F(Test_LC_weekly_197_4, test_7) {
  std::vector<std::vector<int>> inputs = {{44, 23}, {18, 45}, {6, 73},  {0, 76},  {10, 50}, {30, 7},  {92, 59},
                                          {44, 59}, {79, 45}, {69, 37}, {66, 63}, {10, 78}, {88, 80}, {44, 87}};
  const double answer = 499.28078;
  ASSERT_NEAR(answer, solution_->getMinDistSum(inputs), 1e-5);
}

}  // namespace LC_weekly_197_4
