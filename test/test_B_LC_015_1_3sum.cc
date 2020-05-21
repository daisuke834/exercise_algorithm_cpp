/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 15. 3sum.
 * Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
 * Find all unique triplets in the array which gives the sum of zero.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_LC_015_1_3sum.h"

namespace LC_015_1 {

class Test_LC_015_1 : public ::testing::Test {
 protected:
  Solution *solution_;
  virtual void SetUp() {
    solution_ = new Solution();
  }
  virtual void TearDown() {
    delete solution_;
  }
};

TEST_F(Test_LC_015_1, test_1) {
  std::vector<int> inputs;
  const int32_t input_array[] = {-1, 0, 1, 2, -1, -4};
  for (const int value : input_array) {
    inputs.push_back(value);
  }

  const int32_t answer[][3] = {{-1, -1, 2}, {-1, 0, 1}};
  std::vector<std::vector<int>> results = solution_->threeSum(inputs);

  // for (int32_t i = 0; i < static_cast<int32_t>(results.size()); ++i) {
  //   for (int32_t j = 0; j < static_cast<int32_t>(results[0].size()); ++j) {
  //     std::cout << " " << results[i][j];
  //   }
  //   std::cout << std::endl;
  // }

  for (int32_t i = 0; i < static_cast<int32_t>(results.size()); ++i) {
    for (int32_t j = 0; j < static_cast<int32_t>(results[0].size()); ++j) {
      ASSERT_EQ(answer[i][j], results[i][j]);
    }
  }
}

TEST_F(Test_LC_015_1, test_2) {
  std::vector<int> inputs;
  const int32_t input_array[] = {-2, 0, 0, 2, 2};
  for (const int value : input_array) {
    inputs.push_back(value);
  }

  const int32_t answer[][3] = {{-2, 0, 2}, {-2, 0, 2}};
  std::vector<std::vector<int>> results = solution_->threeSum(inputs);

  for (int32_t i = 0; i < static_cast<int32_t>(results.size()); ++i) {
    for (int32_t j = 0; j < static_cast<int32_t>(results[0].size()); ++j) {
      ASSERT_EQ(answer[i][j], results[i][j]);
    }
  }
}

}  // namespace LC_015_1
