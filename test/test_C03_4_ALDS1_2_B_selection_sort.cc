/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-4. 初等的整列、選択ソートのテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/C03_4_ALDS1_2_B_selection_sort.h"

namespace ALDS1_2_B {

class Test_ALDS1_2_B : public ::testing::Test {
 protected:
  SelectionSort* selection_sort_;
  virtual void SetUp() { selection_sort_ = new SelectionSort(); }
  virtual void TearDown() { delete selection_sort_; }
};

TEST_F(Test_ALDS1_2_B, LoadData_abnormal) {
  std::ostringstream input_stream;
  input_stream << kMaxArraySize + 1 << std::endl;
  std::istringstream iss(input_stream.str());
  ASSERT_ANY_THROW(selection_sort_->Load(iss));
}

TEST_F(Test_ALDS1_2_B, MAIN_1) {
  std::ostringstream answer;
  answer << "1 2 3 4 5 6" << std::endl;
  answer << "4" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "5 6 4 2 1 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  selection_sort_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_2_B
