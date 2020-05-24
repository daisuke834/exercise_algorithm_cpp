/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Grand Contest(AGC) 044-A. Pay To Win.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/D_AGC_044_A_pay_to_win.h"

namespace AGC_044_A {

class Test_AGC_044_A : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_AGC_044_A, test_1) {
  Solution *solution = new Solution(11, 1, 2, 4, 8);
  const int64_t result = solution->Calculate();
  ASSERT_EQ(20, result);
  delete solution;
}

TEST_F(Test_AGC_044_A, test_2) {
  Solution *solution = new Solution(11, 1, 2, 2, 8);
  const int64_t result = solution->Calculate();
  ASSERT_EQ(19, result);
  delete solution;
}

TEST_F(Test_AGC_044_A, test_3) {
  Solution *solution = new Solution(32, 10, 8, 5, 4);
  const int64_t result = solution->Calculate();
  ASSERT_EQ(26, result);
  delete solution;
}

/*
TEST_F(Test_AGC_044_A, test_4) {
  Solution *solution = new Solution(29384293847243, 454353412, 332423423, 934923490, 1);
  const int64_t result = solution->Calculate();
  ASSERT_EQ(3821859835, result);
  delete solution;
}

TEST_F(Test_AGC_044_A, test_5) {
  Solution *solution = new Solution(900000000000000000, 332423423, 454353412, 934923490, 987654321);
  const int64_t result = solution->Calculate();
  ASSERT_EQ(23441258666, result);
  delete solution;
}
*/

}  // namespace AGC_044_A
