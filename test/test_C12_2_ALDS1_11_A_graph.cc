/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-2. グラフ(Graph)、グラフの表現。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C12_2_ALDS1_11_A_graph.h"

namespace ALDS1_11_A {

class Test_ALDS1_11_A : public ::testing::Test {
 protected:
  Graph *graph_;
  virtual void SetUp() {
    graph_ = new Graph();
  }
  virtual void TearDown() {
    delete graph_;
  }
};

TEST_F(Test_ALDS1_11_A, CallGraph_1) {
  std::ostringstream answer;
  answer << "0 1 0 1" << std::endl;
  answer << "0 0 0 1" << std::endl;
  answer << "0 0 0 0" << std::endl;
  answer << "0 0 1 0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4" << std::endl;
  input_stream << "1 2 2 4" << std::endl;
  input_stream << "2 1 4" << std::endl;
  input_stream << "3 0" << std::endl;
  input_stream << "4 1 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallGraph(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_11_A
