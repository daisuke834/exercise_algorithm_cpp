/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-193-3. 5455. Minimum Number of Days to Make m Bouquets.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_LC_weekly_193_3_binary_search.h"

namespace LC_weekly_193_3 {

class Test_LC_weekly_193_3 : public ::testing::Test {
 protected:
  Solution *solution_;
  virtual void SetUp() {
    solution_ = new Solution();
  }
  virtual void TearDown() {
    delete solution_;
  }
};

TEST_F(Test_LC_weekly_193_3, test_1) {
  std::vector<int32_t> inputs = {1, 10, 3, 10, 2};
  const int m = 3;
  const int k = 1;
  ASSERT_EQ(3, solution_->minDays(inputs, m, k));
}

TEST_F(Test_LC_weekly_193_3, test_2) {
  std::vector<int32_t> inputs = {1, 10, 3, 10, 2};
  const int m = 3;
  const int k = 2;
  ASSERT_EQ(-1, solution_->minDays(inputs, m, k));
}

TEST_F(Test_LC_weekly_193_3, test_3) {
  std::vector<int32_t> inputs = {7, 7, 7, 7, 12, 7, 7};
  const int m = 2;
  const int k = 3;
  ASSERT_EQ(12, solution_->minDays(inputs, m, k));
}

TEST_F(Test_LC_weekly_193_3, test_4) {
  std::vector<int32_t> inputs = {1000000000, 1000000000};
  const int m = 1;
  const int k = 1;
  ASSERT_EQ(1000000000, solution_->minDays(inputs, m, k));
}

TEST_F(Test_LC_weekly_193_3, test_5) {
  std::vector<int32_t> inputs = {1, 10, 2, 9, 3, 8, 4, 7, 5, 6};
  const int m = 4;
  const int k = 2;
  ASSERT_EQ(9, solution_->minDays(inputs, m, k));
}

}  // namespace LC_weekly_193_3
