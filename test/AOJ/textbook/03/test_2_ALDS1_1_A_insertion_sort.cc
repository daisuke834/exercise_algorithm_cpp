/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-2. 初等的整列、挿入ソートのテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AOJ/textbook/03/2_ALDS1_1_A_insertion_sort.h"

namespace ALDS1_1_A {
class Test_ALDS1_1_A : public ::testing::Test {
 protected:
  InsertionSort* insertion_sort_;
  virtual void SetUp() { insertion_sort_ = new InsertionSort(); }
  virtual void TearDown() { delete insertion_sort_; }
};

TEST_F(Test_ALDS1_1_A, LoadData_abnormal) {
  std::ostringstream input_stream;
  input_stream << kMaxArraySize + 1 << std::endl;
  std::istringstream iss(input_stream.str());
  ASSERT_ANY_THROW(insertion_sort_->Load(iss));
}

TEST_F(Test_ALDS1_1_A, MAIN_1) {
  std::ostringstream answer;
  answer << "5 2 4 6 1 3" << std::endl;
  answer << "2 5 4 6 1 3" << std::endl;
  answer << "2 4 5 6 1 3" << std::endl;
  answer << "2 4 5 6 1 3" << std::endl;
  answer << "1 2 4 5 6 3" << std::endl;
  answer << "1 2 3 4 5 6" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "5 2 4 6 1 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  insertion_sort_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_1_A
