/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 単一始点最短経路(Single Source Shortest Path)。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_GRL_1_A_2_Dijkstra.h"

namespace GRL_1_A_2 {

class Test_GRL_1_A_2 : public ::testing::Test {
 protected:
  DijkstraAlgorithm *single_source_shortest_path_;
  virtual void SetUp() {
    single_source_shortest_path_ = new DijkstraAlgorithm();
  }
  virtual void TearDown() {
    delete single_source_shortest_path_;
  }
};

TEST_F(Test_GRL_1_A_2, CallDijkstraAlgorithm_1) {
  std::ostringstream answer;
  answer << "0" << std::endl;
  answer << "1" << std::endl;
  answer << "3" << std::endl;
  answer << "4" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 5 0" << std::endl;
  input_stream << "0 1 1" << std::endl;
  input_stream << "0 2 4" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "2 3 1" << std::endl;
  input_stream << "1 3 5" << std::endl;
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

TEST_F(Test_GRL_1_A_2, CallDijkstraAlgorithm_2) {
  std::ostringstream answer;
  answer << "3" << std::endl;
  answer << "0" << std::endl;
  answer << "2" << std::endl;
  answer << "INF" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 6 1" << std::endl;
  input_stream << "0 1 1" << std::endl;
  input_stream << "0 2 4" << std::endl;
  input_stream << "2 0 1" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "3 1 1" << std::endl;
  input_stream << "3 2 5" << std::endl;
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

}  // namespace GRL_1_A_2
