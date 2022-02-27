/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-195-4. 1499. Max Value of Equation.
 * https://leetcode.com/contest/weekly-contest-195/problems/max-value-of-equation/
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/LeetCode/weekly/195_4_two_pointers.h"

namespace LC_weekly_195_4 {

class Test_LC_weekly_195_4 : public ::testing::Test {
 protected:
  Solution* solution_;
  virtual void SetUp() { solution_ = new Solution(); }
  virtual void TearDown() { delete solution_; }
};

TEST_F(Test_LC_weekly_195_4, test_1) {
  std::vector<std::vector<int>> inputs = {{1, 3}, {2, 0}, {5, 10}, {6, -10}};
  const int k = 1;
  const int answer = 4;
  ASSERT_EQ(answer, solution_->findMaxValueOfEquation(inputs, k));
}

TEST_F(Test_LC_weekly_195_4, test_2) {
  std::vector<std::vector<int>> inputs = {{0, 0}, {3, 0}, {9, 2}};
  const int k = 3;
  const int answer = 3;
  ASSERT_EQ(answer, solution_->findMaxValueOfEquation(inputs, k));
}

}  // namespace LC_weekly_195_4
