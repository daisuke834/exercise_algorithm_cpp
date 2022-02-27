/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-7. 高等的整列、最小コストソート(Minimum Cost Sort)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/AOJ/textbook/07/7_ALDS1_6_D_minimum_cost_sort.h"

namespace ALDS1_6_D {

class Test_ALDS1_6_D : public ::testing::Test {
 protected:
  MinimumCostSort* minimum_cost_sort_;
  virtual void SetUp() { minimum_cost_sort_ = new MinimumCostSort(); }
  virtual void TearDown() { delete minimum_cost_sort_; }
};

TEST_F(Test_ALDS1_6_D, CallMinimumCostSort) {
  std::ostringstream answer;
  answer << "7" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "1 5 3 4 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMinimumCostSort(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_6_D, AddData) {
  ASSERT_EQ(0, minimum_cost_sort_->size_);

  constexpr int32_t kValue_0 = 3;
  constexpr int32_t kValue_1 = 10;
  minimum_cost_sort_->AddData(kValue_0);
  minimum_cost_sort_->AddData(kValue_1);
  ASSERT_EQ(2, minimum_cost_sort_->size_);
  ASSERT_EQ(kValue_0, minimum_cost_sort_->sorted_values_[0]);
  ASSERT_EQ(kValue_1, minimum_cost_sort_->sorted_values_[1]);
}

TEST_F(Test_ALDS1_6_D, Sort_1) {
  minimum_cost_sort_->AddData(1);
  minimum_cost_sort_->AddData(5);
  minimum_cost_sort_->AddData(3);
  minimum_cost_sort_->AddData(4);
  minimum_cost_sort_->AddData(2);

  minimum_cost_sort_->Sort();

  for (int32_t i = 0; i < minimum_cost_sort_->size_; ++i) {
    ASSERT_EQ(i + 1, minimum_cost_sort_->sorted_values_[i]);
  }
}

TEST_F(Test_ALDS1_6_D, CalculateMinimumCost_1) {
  minimum_cost_sort_->AddData(1);
  minimum_cost_sort_->AddData(5);
  minimum_cost_sort_->AddData(3);
  minimum_cost_sort_->AddData(4);
  minimum_cost_sort_->AddData(2);

  int32_t cost = minimum_cost_sort_->CalculateMinimumCost();
  ASSERT_EQ(7, cost);
}

TEST_F(Test_ALDS1_6_D, CalculateMinimumCost_2) {
  minimum_cost_sort_->AddData(10);
  minimum_cost_sort_->AddData(7);
  minimum_cost_sort_->AddData(8);
  minimum_cost_sort_->AddData(9);

  int32_t cost = minimum_cost_sort_->CalculateMinimumCost();
  ASSERT_EQ(48, cost);
}

TEST_F(Test_ALDS1_6_D, CalculateMinimumCost_3) {
  for (int32_t value = 1000; value >= 1; --value) {
    minimum_cost_sort_->AddData(value);
  }
  int32_t cost = minimum_cost_sort_->CalculateMinimumCost();
  ASSERT_EQ(500500, cost);
}

}  // namespace ALDS1_6_D
