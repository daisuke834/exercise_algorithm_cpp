/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_14_B_1. 文字列検索、BM文字列検索アルゴリズム（Boyer-Moore String Search Algorithm）。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AOJ/ALDS1/14_B_1_string_search_bm.h"

namespace ALDS1_14_B_1 {

class Test_ALDS1_14_B_1 : public ::testing::Test {
 protected:
  BoyerMoore* boyer_moore_;
  virtual void SetUp() { boyer_moore_ = new BoyerMoore(); }
  virtual void TearDown() { delete boyer_moore_; }
};

TEST_F(Test_ALDS1_14_B_1, CallStringSearch_1) {
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

TEST_F(Test_ALDS1_14_B_1, CallStringSearch_2) {
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

TEST_F(Test_ALDS1_14_B_1, CallStringSearch_3) {
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

TEST_F(Test_ALDS1_14_B_1, CallNaiveStringSearch_4) {
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

TEST_F(Test_ALDS1_14_B_1, SetPattern) {
  const std::string pattern("xy");
  boyer_moore_->SetPattern(pattern);
  for (int32_t ch = '0'; ch <= '9'; ++ch) {
    ASSERT_EQ(static_cast<int32_t>(pattern.length()), boyer_moore_->offsets_from_right_[ch]);
  }
  for (int32_t ch = 'A'; ch <= 'Z'; ++ch) {
    ASSERT_EQ(static_cast<int32_t>(pattern.length()), boyer_moore_->offsets_from_right_[ch]);
  }
  for (int32_t ch = 'a'; ch <= 'w'; ++ch) {
    ASSERT_EQ(static_cast<int32_t>(pattern.length()), boyer_moore_->offsets_from_right_[ch]);
  }
  EXPECT_EQ(1, boyer_moore_->offsets_from_right_[static_cast<int32_t>('x')]);
  ASSERT_EQ(0, boyer_moore_->offsets_from_right_[static_cast<int32_t>('y')]);
  ASSERT_EQ(static_cast<int32_t>(pattern.length()), boyer_moore_->offsets_from_right_[static_cast<int32_t>('z')]);
}

TEST_F(Test_ALDS1_14_B_1, Search_1) {
  boyer_moore_->SetPattern("xy");
  boyer_moore_->Search("xy");
}

}  // namespace ALDS1_14_B_1
