/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-3. 重み付きグラフ(Weighted Graph)、単一始点最短経路(Single Source Shortest Path)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C13_3_ALDS1_12_C_2_Dijkstra.h"

namespace ALDS1_12_C_2 {

class Test_ALDS1_12_C_2 : public ::testing::Test {
 protected:
  DijkstraAlgorithm *single_source_shortest_path_;
  virtual void SetUp() {
    single_source_shortest_path_ = new DijkstraAlgorithm();
  }
  virtual void TearDown() {
    delete single_source_shortest_path_;
  }
};

TEST_F(Test_ALDS1_12_C_2, CallDijkstraAlgorithm_1) {
  std::ostringstream answer;
  answer << "0 0" << std::endl;
  answer << "1 2" << std::endl;
  answer << "2 2" << std::endl;
  answer << "3 1" << std::endl;
  answer << "4 3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "0 3 2 3 3 1 1 2" << std::endl;
  input_stream << "1 2 0 2 3 4" << std::endl;
  input_stream << "2 3 0 3 3 1 4 1" << std::endl;
  input_stream << "3 4 2 1 0 1 1 4 4 3" << std::endl;
  input_stream << "4 2 2 1 3 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDijkstraAlgorithm(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_12_C_2
