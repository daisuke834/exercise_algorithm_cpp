/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 単一始点最短経路(Single Source Shortest Path)。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/B_GRL_1_B_Bellman_Ford.h"

namespace GRL_1_B {

class Test_GRL_1_B : public ::testing::Test {
 protected:
  BellmanFordAlgorithm* single_source_shortest_path_;
  virtual void SetUp() { single_source_shortest_path_ = new BellmanFordAlgorithm(); }
  virtual void TearDown() { delete single_source_shortest_path_; }
};

TEST_F(Test_GRL_1_B, CallBellmanFordAlgorithm_1) {
  std::ostringstream answer;
  answer << "0" << std::endl;
  answer << "2" << std::endl;
  answer << "-3" << std::endl;
  answer << "-1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 5 0" << std::endl;
  input_stream << "0 1 2" << std::endl;
  input_stream << "0 2 3" << std::endl;
  input_stream << "1 2 -5" << std::endl;
  input_stream << "1 3 1" << std::endl;
  input_stream << "2 3 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBellmanFordAlgorithm(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_1_B, CallBellmanFordAlgorithm_2) {
  std::ostringstream answer;
  answer << "NEGATIVE CYCLE" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 6 0" << std::endl;
  input_stream << "0 1 2" << std::endl;
  input_stream << "0 2 3" << std::endl;
  input_stream << "1 2 -5" << std::endl;
  input_stream << "1 3 1" << std::endl;
  input_stream << "2 3 2" << std::endl;
  input_stream << "3 1 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBellmanFordAlgorithm(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_1_B, CallBellmanFordAlgorithm_3) {
  std::ostringstream answer;
  answer << "INF" << std::endl;
  answer << "0" << std::endl;
  answer << "-5" << std::endl;
  answer << "-3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 5 1" << std::endl;
  input_stream << "0 1 2" << std::endl;
  input_stream << "0 2 3" << std::endl;
  input_stream << "1 2 -5" << std::endl;
  input_stream << "1 3 1" << std::endl;
  input_stream << "2 3 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBellmanFordAlgorithm(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace GRL_1_B
