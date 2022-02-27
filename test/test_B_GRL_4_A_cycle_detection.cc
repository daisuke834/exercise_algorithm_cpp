/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 有向グラフの閉路検査(Cycle Detection for a Directed Graph)。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/B_GRL_4_A_cycle_detection.h"

namespace GRL_4_A {

class Test_GRL_4_A : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_GRL_4_A, CallCycleDetection_1) {
  std::ostringstream answer;
  answer << "0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3 3" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "0 2" << std::endl;
  input_stream << "1 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallCycleDetection(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_4_A, CallCycleDetection_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3 3" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "2 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallCycleDetection(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace GRL_4_A
