/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-4. 高等的整列、計数ソート(Counting Sort)のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C07_4_ALDS1_6_A_counting_sort.h"

namespace ALDS1_6_A {

class Test_ALDS1_6_A : public ::testing::Test {
 protected:
  CountingSort *counting_sort_;
  virtual void SetUp() {
    counting_sort_ = new CountingSort();
  }
  virtual void TearDown() {
    delete counting_sort_;
  }
};

TEST_F(Test_ALDS1_6_A, CallCountingSort) {
  std::ostringstream answer;
  answer << "0 1 2 2 3 3 5" << std::endl;

  std::ostringstream input_stream;
  input_stream << "7" << std::endl;
  input_stream << "2 5 1 3 2 3 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallCountingSort(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_6_A, AddData) {
  ASSERT_EQ(0, counting_sort_->size_);

  constexpr int32_t kValue_0 = 3;
  constexpr int32_t kValue_1 = 10;
  counting_sort_->AddData(kValue_0);
  counting_sort_->AddData(kValue_1);
  ASSERT_EQ(2, counting_sort_->size_);
  ASSERT_EQ(kValue_0, counting_sort_->input_values_[0]);
  ASSERT_EQ(kValue_1, counting_sort_->input_values_[1]);
}

}  // namespace ALDS1_6_A
