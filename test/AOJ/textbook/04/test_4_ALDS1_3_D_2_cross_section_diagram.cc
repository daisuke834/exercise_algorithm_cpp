/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-6. データ構造の応用、面積計算のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AOJ/textbook/04/4_ALDS1_3_D_2_cross_section_diagram.h"

namespace ALDS1_3_D_2 {

class Test_ALDS1_3_D_2 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ALDS1_3_D_2, CallCrossSectionDiagram_1) {
  std::ostringstream answer;
  answer << "35" << std::endl;
  answer << "5 4 2 1 19 9" << std::endl;

  std::ostringstream input_stream;
  input_stream << "\\\\///\\_/\\/\\\\\\\\/_/\\\\///__\\\\\\_\\\\/_\\/_/\\" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallCrossSectionDiagram(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_3_D_2, CallCrossSectionDiagram_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "1 1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "_/\\//" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallCrossSectionDiagram(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_3_D_2, CallCrossSectionDiagram_3) {
  std::ostringstream answer;
  answer << "25" << std::endl;
  answer << "4 1 20 1 3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "\\/\\\\\\_/\\\\//__\\/_/\\/\\__/" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallCrossSectionDiagram(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_3_D_2
