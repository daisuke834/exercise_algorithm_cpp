/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-1. 高度なグラフアルゴリズム、全点対間最短経路(All Pairs Shortest Path, APSP)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C15_1_GRL_1_C_2_Warshall_Floyd.h"

namespace GRL_1_C_2 {

class Test_GRL_1_C_2 : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

TEST_F(Test_GRL_1_C_2, CallWarshallFloyd_1) {
  std::ostringstream answer;
  answer << "0 1 3 4" << std::endl;
  answer << "INF 0 2 3" << std::endl;
  answer << "INF INF 0 1" << std::endl;
  answer << "INF INF 7 0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 6" << std::endl;
  input_stream << "0 1 1" << std::endl;
  input_stream << "0 2 5" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "1 3 4" << std::endl;
  input_stream << "2 3 1" << std::endl;
  input_stream << "3 2 7" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallWarshallFloyd(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_1_C_2, CallWarshallFloyd_2) {
  std::ostringstream answer;
  answer << "0 1 -5 -4" << std::endl;
  answer << "INF 0 2 3" << std::endl;
  answer << "INF INF 0 1" << std::endl;
  answer << "INF INF 7 0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 6" << std::endl;
  input_stream << "0 1 1" << std::endl;
  input_stream << "0 2 -5" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "1 3 4" << std::endl;
  input_stream << "2 3 1" << std::endl;
  input_stream << "3 2 7" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallWarshallFloyd(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_1_C_2, CallWarshallFloyd_3) {
  std::ostringstream answer;
  answer << "NEGATIVE CYCLE" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 6" << std::endl;
  input_stream << "0 1 1" << std::endl;
  input_stream << "0 2 5" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "1 3 4" << std::endl;
  input_stream << "2 3 1" << std::endl;
  input_stream << "3 2 -7" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallWarshallFloyd(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace GRL_1_C_2
