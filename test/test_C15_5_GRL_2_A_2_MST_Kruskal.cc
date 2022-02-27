/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-5. 最小全域木(Minimum Spanning Tree, MST)問題。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/C15_5_GRL_2_A_2_MST_Kruskal.h"

namespace GRL_2_A_2 {

class Test_GRL_2_A_2 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_GRL_2_A_2, CallKruskalAlgorithm_1) {
  std::ostringstream answer;
  answer << "5" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6 9" << std::endl;
  input_stream << "0 1 1" << std::endl;
  input_stream << "0 2 3" << std::endl;
  input_stream << "1 2 1" << std::endl;
  input_stream << "1 3 7" << std::endl;
  input_stream << "2 4 1" << std::endl;
  input_stream << "1 4 3" << std::endl;
  input_stream << "3 4 1" << std::endl;
  input_stream << "3 5 1" << std::endl;
  input_stream << "4 5 6" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKruskalAlgorithm(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_2_A_2, CallKruskalAlgorithm_2) {
  std::ostringstream answer;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 6" << std::endl;
  input_stream << "0 1 2" << std::endl;
  input_stream << "1 2 1" << std::endl;
  input_stream << "2 3 1" << std::endl;
  input_stream << "3 0 1" << std::endl;
  input_stream << "0 2 3" << std::endl;
  input_stream << "1 3 5" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKruskalAlgorithm(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_2_A_2, CallKruskalAlgorithm_3) {
  std::ostringstream answer;
  answer << "0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "1 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKruskalAlgorithm(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_2_A_2, CallKruskalAlgorithm_4) {
  std::ostringstream answer;
  answer << "27999" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10 15" << std::endl;
  input_stream << "8 1 4457" << std::endl;
  input_stream << "1 3 2531" << std::endl;
  input_stream << "3 4 7111" << std::endl;
  input_stream << "4 2 1088" << std::endl;
  input_stream << "2 5 3124" << std::endl;
  input_stream << "9 0 4427" << std::endl;
  input_stream << "6 2 2005" << std::endl;
  input_stream << "7 9 6489" << std::endl;
  input_stream << "3 8 2313" << std::endl;
  input_stream << "1 2 7125" << std::endl;
  input_stream << "5 4 4987" << std::endl;
  input_stream << "1 9 6782" << std::endl;
  input_stream << "1 5 1147" << std::endl;
  input_stream << "7 2 4875" << std::endl;
  input_stream << "1 6 5959" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKruskalAlgorithm(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace GRL_2_A_2
