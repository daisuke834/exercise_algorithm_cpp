/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Educational DP Contest. G - Longest Path.
 * https://atcoder.jp/contests/dp/tasks/dp_g
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/D_AtCoder_Educational_DP_G_LongestPath.h"

namespace AtCoder_Educational_DP_G {

class Test_AtCoder_Educational_DP_G : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_AtCoder_Educational_DP_G, LongestPath_1) {
  std::ostringstream answer;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 5" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "1 3" << std::endl;
  input_stream << "3 2" << std::endl;
  input_stream << "2 4" << std::endl;
  input_stream << "3 4" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_AtCoder_Educational_DP_G, LongestPath_2) {
  std::ostringstream answer;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6 3" << std::endl;
  input_stream << "2 3" << std::endl;
  input_stream << "4 5" << std::endl;
  input_stream << "5 6" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_AtCoder_Educational_DP_G, LongestPath_3) {
  std::ostringstream answer;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5 8" << std::endl;
  input_stream << "5 3" << std::endl;
  input_stream << "2 3" << std::endl;
  input_stream << "2 4" << std::endl;
  input_stream << "5 2" << std::endl;
  input_stream << "5 1" << std::endl;
  input_stream << "1 4" << std::endl;
  input_stream << "4 3" << std::endl;
  input_stream << "1 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace AtCoder_Educational_DP_G
