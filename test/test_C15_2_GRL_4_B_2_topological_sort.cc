/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-2. 高度なグラフアルゴリズム、トポロジカルソート(Topological Sort)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C15_2_GRL_4_B_2_topological_sort.h"

namespace GRL_4_B_2 {

class Test_GRL_4_B_2 : public ::testing::Test {
 protected:
  TopologicalSort *topological_sort_;
  virtual void SetUp() {
    topological_sort_ = new TopologicalSort();
  }
  virtual void TearDown() {
    delete topological_sort_;
  }
};

TEST_F(Test_GRL_4_B_2, CallTopologicalSort_1) {
  std::ostringstream answer;
  answer << "0" << std::endl;
  answer << "3" << std::endl;
  answer << "1" << std::endl;
  answer << "4" << std::endl;
  answer << "5" << std::endl;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6 6" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "3 1" << std::endl;
  input_stream << "3 4" << std::endl;
  input_stream << "4 5" << std::endl;
  input_stream << "5 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTopologicalSort(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace GRL_4_B_2
