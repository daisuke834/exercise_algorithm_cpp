/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-5. 初等的整列、安定なソートのテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C03_5_ALDS1_2_C_stable_sort.h"

namespace ALDS1_2_C {

class Test_ALDS1_2_C : public ::testing::Test {
 protected:
  StableSort *stable_sort_;
  virtual void SetUp() {
    stable_sort_ = new StableSort();
  }
  virtual void TearDown() {
    delete stable_sort_;
  }
};

TEST_F(Test_ALDS1_2_C, LoadData_abnormal) {
  std::ostringstream input_stream;
  input_stream << kMaxArraySize + 1 << std::endl;
  std::istringstream iss(input_stream.str());
  ASSERT_ANY_THROW(stable_sort_->Load(iss));
}

TEST_F(Test_ALDS1_2_C, MAIN_1) {
  std::ostringstream answer;
  answer << "D2 C3 H4 S4 C9" << std::endl;
  answer << "Stable" << std::endl;
  answer << "D2 C3 S4 H4 C9" << std::endl;
  answer << "Not stable" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "H4 C9 S4 D2 C3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  stable_sort_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_2_C
