/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Educational DP Contest. F. LCS(Longest-common subsequence, 最長共通部分列).
 * https://atcoder.jp/contests/dp/tasks/dp_f
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AtCoder/Educational_DP/F_LCS.h"

namespace AtCoder_Educational_DP_F {

class Test_AtCoder_Educational_DP_F : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_AtCoder_Educational_DP_F, LCS_1) {
  std::ostringstream answer;
  answer << "axb" << std::endl;

  std::ostringstream input_stream;
  input_stream << "axyb" << std::endl;
  input_stream << "abyxb" << std::endl;
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

TEST_F(Test_AtCoder_Educational_DP_F, LCS_2) {
  std::ostringstream answer;
  answer << "aa" << std::endl;

  std::ostringstream input_stream;
  input_stream << "aa" << std::endl;
  input_stream << "xayaz" << std::endl;
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
TEST_F(Test_AtCoder_Educational_DP_F, LCS_3) {
  std::ostringstream answer;
  answer << "" << std::endl;

  std::ostringstream input_stream;
  input_stream << "a" << std::endl;
  input_stream << "z" << std::endl;
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

TEST_F(Test_AtCoder_Educational_DP_F, LCS_4) {
  std::ostringstream answer;
  answer << "aaadara" << std::endl;

  std::ostringstream input_stream;
  input_stream << "abracadabra" << std::endl;
  input_stream << "avadakedavra" << std::endl;
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

}  // namespace AtCoder_Educational_DP_F
