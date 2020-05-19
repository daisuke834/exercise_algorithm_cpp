/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 994. Rotting Oranges.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_LC_994_rotting_oranges.h"

namespace LC_994 {

class Test_LC_994 : public ::testing::Test {
 protected:
  Solution *solution_;
  virtual void SetUp() {
    solution_ = new Solution();
  }
  virtual void TearDown() {
    delete solution_;
  }
};

TEST_F(Test_LC_994, test_1) {
  std::vector<std::vector<int>> inputs;
  const int32_t input_array[3][3] = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
  for (const auto &row : input_array) {
    std::vector<int32_t> temp_vec;
    for (const int32_t value : row) {
      temp_vec.push_back(value);
    }
    inputs.push_back(temp_vec);
  }

  ASSERT_EQ(4, solution_->orangesRotting(inputs));
}

TEST_F(Test_LC_994, test_2) {
  std::vector<std::vector<int>> inputs;
  const int32_t input_array[3][3] = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
  for (const auto &row : input_array) {
    std::vector<int32_t> temp_vec;
    for (const int32_t value : row) {
      temp_vec.push_back(value);
    }
    inputs.push_back(temp_vec);
  }

  ASSERT_EQ(-1, solution_->orangesRotting(inputs));
}

TEST_F(Test_LC_994, test_3) {
  std::vector<std::vector<int>> inputs;
  const int32_t input_array[1][2] = {{0, 2}};
  for (const auto &row : input_array) {
    std::vector<int32_t> temp_vec;
    for (const int32_t value : row) {
      temp_vec.push_back(value);
    }
    inputs.push_back(temp_vec);
  }

  ASSERT_EQ(0, solution_->orangesRotting(inputs));
}

}  // namespace LC_994
