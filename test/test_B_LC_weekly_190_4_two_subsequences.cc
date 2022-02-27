/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-190-4. 1458. Max Dot Product of Two Subsequences.
 * Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same length.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/B_LC_weekly_190_4_two_subsequences.h"

namespace LC_weekly_190_4 {

class Test_LC_weekly_190_4 : public ::testing::Test {
 protected:
  std::vector<int32_t> inputs_1_;
  std::vector<int32_t> inputs_2_;
  Solution* solution_;
  virtual void SetUp() {
    inputs_1_.clear();
    inputs_2_.clear();
    solution_ = new Solution();
  }
  virtual void TearDown() { delete solution_; }
};

TEST_F(Test_LC_weekly_190_4, test_1) {
  const int32_t nums1[] = {2, 1, -2, 5};
  const int32_t nums2[] = {3, 0, -6};
  for (const int32_t value : nums1) {
    inputs_1_.push_back(value);
  }
  for (const int32_t value : nums2) {
    inputs_2_.push_back(value);
  }
  ASSERT_EQ(18, solution_->maxDotProduct(inputs_1_, inputs_2_));
}

TEST_F(Test_LC_weekly_190_4, test_2) {
  const int32_t nums1[] = {3, -2};
  const int32_t nums2[] = {2, -6, 7};
  for (const int32_t value : nums1) {
    inputs_1_.push_back(value);
  }
  for (const int32_t value : nums2) {
    inputs_2_.push_back(value);
  }
  ASSERT_EQ(21, solution_->maxDotProduct(inputs_1_, inputs_2_));
}

TEST_F(Test_LC_weekly_190_4, test_3) {
  const int32_t nums1[] = {-1, -1};
  const int32_t nums2[] = {1, 1};
  for (const int32_t value : nums1) {
    inputs_1_.push_back(value);
  }
  for (const int32_t value : nums2) {
    inputs_2_.push_back(value);
  }
  ASSERT_EQ(-1, solution_->maxDotProduct(inputs_1_, inputs_2_));
}

}  // namespace LC_weekly_190_4
