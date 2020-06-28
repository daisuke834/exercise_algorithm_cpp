/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-195-3. 1498. Number of Subsequences That Satisfy the Given Sum Condition.
 * https://leetcode.com/contest/weekly-contest-195/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_LC_weekly_195_3_two_pointers.h"

namespace LC_weekly_195_3 {

class Test_LC_weekly_195_3 : public ::testing::Test {
 protected:
  Solution *solution_;
  virtual void SetUp() {
    solution_ = new Solution();
  }
  virtual void TearDown() {
    delete solution_;
  }
};

TEST_F(Test_LC_weekly_195_3, test_1) {
  std::vector<int> inputs = {3, 5, 6, 7};
  const int target = 9;
  const int answer = 4;
  ASSERT_EQ(answer, solution_->numSubseq(inputs, target));
}

TEST_F(Test_LC_weekly_195_3, test_2) {
  std::vector<int> inputs = {3, 3, 6, 8};
  const int target = 10;
  const int answer = 6;
  ASSERT_EQ(answer, solution_->numSubseq(inputs, target));
}

TEST_F(Test_LC_weekly_195_3, test_3) {
  std::vector<int> inputs = {2, 3, 3, 4, 6, 7};
  const int target = 12;
  const int answer = 61;
  ASSERT_EQ(answer, solution_->numSubseq(inputs, target));
}

TEST_F(Test_LC_weekly_195_3, test_4) {
  std::vector<int> inputs = {5, 2, 4, 1, 7, 6, 8};
  const int target = 16;
  const int answer = 127;
  ASSERT_EQ(answer, solution_->numSubseq(inputs, target));
}

}  // namespace LC_weekly_195_3
