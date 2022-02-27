/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 165-C. Depth First Search (DFS).
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AtCoder/ABC/165_C_2_depth_first_search.h"

namespace ABC_165_2 {

class Test_ABC_165_2 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ABC_165_2, CallDepthFirstSearch_1) {
  std::ostringstream answer;
  answer << "110" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3 4 3" << std::endl;
  input_stream << "1 3 3 100" << std::endl;
  input_stream << "1 2 2 10" << std::endl;
  input_stream << "2 3 2 10" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDepthFirstSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}
/*
TEST_F(Test_ABC_165_2, CallDepthFirstSearch_2) {
  std::ostringstream answer;
  answer << "357500" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 6 10" << std::endl;
  input_stream << "2 4 1 86568" << std::endl;
  input_stream << "1 4 0 90629" << std::endl;
  input_stream << "2 3 0 90310" << std::endl;
  input_stream << "3 4 1 29211" << std::endl;
  input_stream << "3 4 3 78537" << std::endl;
  input_stream << "3 4 2 8580" << std::endl;
  input_stream << "1 2 1 96263" << std::endl;
  input_stream << "1 4 2 2156" << std::endl;
  input_stream << "1 2 0 94325" << std::endl;
  input_stream << "1 4 3 94328" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDepthFirstSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ABC_165_2, CallDepthFirstSearch_3) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10 10 1" << std::endl;
  input_stream << "1 10 9 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDepthFirstSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}
*/

}  // namespace ABC_165_2
