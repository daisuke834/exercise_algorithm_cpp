/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_14_B. 文字列検索、Rolling Hash。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_ALDS1_14_B_2_string_search_rolling_hash.h"

namespace ALDS1_14_B_2 {

class Test_ALDS1_14_B_2 : public ::testing::Test {
 protected:
  RollingHash *rolling_hash_;
  virtual void SetUp() {
    rolling_hash_ = new RollingHash();
  }
  virtual void TearDown() {
    delete rolling_hash_;
  }
};

TEST_F(Test_ALDS1_14_B_2, CallStringSearch_1) {
  std::ostringstream answer;
  answer << "0" << std::endl;
  answer << "3" << std::endl;
  answer << "4" << std::endl;

  std::ostringstream input_stream;
  input_stream << "aabaaa" << std::endl;
  input_stream << "aa" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallStringSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_14_B_2, CallStringSearch_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "xyzz" << std::endl;
  input_stream << "yz" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallStringSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_14_B_2, CallStringSearch_3) {
  std::ostringstream answer;
  // answer << "" << std::endl;

  std::ostringstream input_stream;
  input_stream << "abc" << std::endl;
  input_stream << "xyz" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallStringSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_14_B_2, CallStringSearch_4) {
  std::ostringstream answer;
  answer << "0" << std::endl;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;
  answer << "4" << std::endl;
  answer << "5" << std::endl;
  answer << "6" << std::endl;
  answer << "7" << std::endl;
  answer << "8" << std::endl;

  std::ostringstream input_stream;
  input_stream << "aaaaaaaaaa" << std::endl;
  input_stream << "aa" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallStringSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_14_B_2
