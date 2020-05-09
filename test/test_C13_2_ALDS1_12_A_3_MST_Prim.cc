/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-2. 重み付きグラフ(Weighted Graph)、最小全域木(Minimum Spanning Tree, MST)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C13_2_ALDS1_12_A_3_MST_Prim.h"

namespace ALDS1_12_A_3 {

class Test_ALDS1_12_A_3 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ALDS1_12_A_3, CallPrimAlgorithm_1) {
  std::ostringstream answer;
  answer << "5" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "-1 2 3 1 -1" << std::endl;
  input_stream << "2 -1 -1 4 -1" << std::endl;
  input_stream << "3 -1 -1 1 1" << std::endl;
  input_stream << "1 4 1 -1 3" << std::endl;
  input_stream << "-1 -1 1 3 -1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallPrimAlgorithm(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_12_A_3
