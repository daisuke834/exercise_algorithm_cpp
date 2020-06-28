/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-194-3. 1488. Avoid Flood in The City.
 * https://leetcode.com/contest/weekly-contest-194/problems/avoid-flood-in-the-city/
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_LC_weekly_194_3_binary_search.h"

namespace LC_weekly_194_3 {

class Test_LC_weekly_194_3 : public ::testing::Test {
 protected:
  Solution *solution_;
  virtual void SetUp() {
    solution_ = new Solution();
  }
  virtual void TearDown() {
    delete solution_;
  }
};

TEST_F(Test_LC_weekly_194_3, test_1) {
  std::vector<int32_t> inputs = {1, 2, 3, 4};
  std::vector<int32_t> answers = {-1, -1, -1, -1};
  ASSERT_EQ(answers, solution_->avoidFlood(inputs));
}

TEST_F(Test_LC_weekly_194_3, test_2) {
  std::vector<int32_t> inputs = {1, 2, 0, 0, 2, 1};
  std::vector<int32_t> answers = {-1, -1, 2, 1, -1, -1};
  ASSERT_EQ(answers, solution_->avoidFlood(inputs));
}

TEST_F(Test_LC_weekly_194_3, test_3) {
  std::vector<int32_t> inputs = {1, 2, 0, 1, 2};
  std::vector<int32_t> answers = {};
  ASSERT_EQ(answers, solution_->avoidFlood(inputs));
}

TEST_F(Test_LC_weekly_194_3, test_4) {
  std::vector<int32_t> inputs = {69, 0, 0, 0, 69};
  std::vector<int32_t> answers = {-1, 69, 1, 1, -1};
  ASSERT_EQ(answers, solution_->avoidFlood(inputs));
}

TEST_F(Test_LC_weekly_194_3, test_5) {
  std::vector<int32_t> inputs = {10, 20, 20};
  std::vector<int32_t> answers = {};
  ASSERT_EQ(answers, solution_->avoidFlood(inputs));
}

TEST_F(Test_LC_weekly_194_3, test_6) {
  std::vector<int32_t> inputs = {1, 0, 2, 0, 2, 1};
  std::vector<int32_t> answers = {-1, 1, -1, 2, -1, -1};
  ASSERT_EQ(answers, solution_->avoidFlood(inputs));
}

TEST_F(Test_LC_weekly_194_3, test_7) {
  std::vector<int32_t> inputs = {1, 0, 2, 3, 0, 1, 2};
  std::vector<int32_t> answers = {-1, 1, -1, -1, 2, -1, -1};
  ASSERT_EQ(answers, solution_->avoidFlood(inputs));
}

}  // namespace LC_weekly_194_3
