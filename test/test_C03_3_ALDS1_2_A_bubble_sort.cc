/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-3. 初等的整列、バブルソートのテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/C03_3_ALDS1_2_A_bubble_sort.h"

namespace ALDS1_2_A {

class Test_ALDS1_2_A : public ::testing::Test {
 protected:
  BubbleSort* bubble_sort_;
  virtual void SetUp() { bubble_sort_ = new BubbleSort(); }
  virtual void TearDown() { delete bubble_sort_; }
};

TEST_F(Test_ALDS1_2_A, LoadData_abnormal) {
  std::ostringstream input_stream;
  input_stream << kMaxArraySize + 1 << std::endl;
  std::istringstream iss(input_stream.str());
  ASSERT_ANY_THROW(bubble_sort_->Load(iss));
}

TEST_F(Test_ALDS1_2_A, MAIN_1) {
  std::ostringstream answer;
  answer << "1 2 3 4 5" << std::endl;
  answer << "8" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "5 3 2 4 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bubble_sort_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_2_A
