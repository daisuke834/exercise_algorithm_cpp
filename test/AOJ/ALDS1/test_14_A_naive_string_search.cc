/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_14_A. 文字列検索(String Search)、Naive String Search。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AOJ/ALDS1/14_A_naive_string_search.h"

namespace ALDS1_14_A {

TEST(Test_ALDS1_14_A, CallNaiveStringSearch_1) {
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
    CallNaiveStringSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST(Test_ALDS1_14_A, CallNaiveStringSearch_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "xyzz" << std::endl;
  input_stream << "yz" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallNaiveStringSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST(Test_ALDS1_14_A, CallNaiveStringSearch_3) {
  std::ostringstream answer;
  // answer << "" << std::endl;

  std::ostringstream input_stream;
  input_stream << "abc" << std::endl;
  input_stream << "xyz" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallNaiveStringSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST(Test_ALDS1_14_A, CallNaiveStringSearch_4) {
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
    CallNaiveStringSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_14_A
