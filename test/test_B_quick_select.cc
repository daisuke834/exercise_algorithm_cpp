/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/B_quick_select.h"

namespace my_quick_select {

class Test_QuickSelect : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_QuickSelect, CallQuickSelect_1) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "1" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "6" << std::endl;
  input_stream << "7" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallQuickSelect(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_QuickSelect, CallQuickSelect_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "7" << std::endl;
  input_stream << "6" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallQuickSelect(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_QuickSelect, CallQuickSelect_3) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "6" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallQuickSelect(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_QuickSelect, CallQuickSelect_4) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallQuickSelect(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace my_quick_select
