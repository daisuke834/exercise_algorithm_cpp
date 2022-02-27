/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-196-4. 1505. Minimum Possible Integer After at Most K Adjacent Swaps On Digits
 * https://leetcode.com/contest/weekly-contest-196/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/LeetCode/weekly/196_4_segment_tree.h"

namespace LC_weekly_196_4 {

class Test_LC_weekly_196_4 : public ::testing::Test {
 protected:
  Solution* solution_;
  virtual void SetUp() { solution_ = new Solution(); }
  virtual void TearDown() { delete solution_; }
};

TEST_F(Test_LC_weekly_196_4, test_1) {
  const std::string input = "4321";
  const int32_t k = 4;
  const std::string answer = "1342";
  ASSERT_EQ(answer, solution_->minInteger(input, k));
}

TEST_F(Test_LC_weekly_196_4, test_2) {
  const std::string input = "100";
  const int32_t k = 1;
  const std::string answer = "010";
  ASSERT_EQ(answer, solution_->minInteger(input, k));
}

TEST_F(Test_LC_weekly_196_4, test_3) {
  const std::string input = "36789";
  const int32_t k = 1000;
  const std::string answer = "36789";
  ASSERT_EQ(answer, solution_->minInteger(input, k));
}

TEST_F(Test_LC_weekly_196_4, test_4) {
  const std::string input = "22";
  const int32_t k = 22;
  const std::string answer = "22";
  ASSERT_EQ(answer, solution_->minInteger(input, k));
}

TEST_F(Test_LC_weekly_196_4, test_5) {
  const std::string input = "9000900";
  const int32_t k = 3;
  const std::string answer = "0009900";
  ASSERT_EQ(answer, solution_->minInteger(input, k));
}

}  // namespace LC_weekly_196_4
