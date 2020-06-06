/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Practical Algorithm Skill Test (PAST) 003-J. 回転寿司.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/D_PAST_003_J_upper_bound.h"

namespace PAST_003_J {

class Test_PAST_003_J : public ::testing::Test {
 protected:
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_PAST_003_J, test_1) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "-1" << std::endl;
  answer << "2" << std::endl;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "2 5" << std::endl;
  input_stream << "5 3 2 4 8" << std::endl;
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

TEST_F(Test_PAST_003_J, test_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;
  answer << "1" << std::endl;
  answer << "3" << std::endl;
  answer << "2" << std::endl;
  answer << "4" << std::endl;
  answer << "5" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5 10" << std::endl;
  input_stream << "13 16 6 15 10 18 13 17 11 3" << std::endl;
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

TEST_F(Test_PAST_003_J, test_3) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;
  answer << "4" << std::endl;
  answer << "2" << std::endl;
  answer << "5" << std::endl;
  answer << "6" << std::endl;
  answer << "2" << std::endl;
  answer << "7" << std::endl;
  answer << "6" << std::endl;
  answer << "3" << std::endl;
  answer << "7" << std::endl;
  answer << "6" << std::endl;
  answer << "1" << std::endl;
  answer << "7" << std::endl;
  answer << "4" << std::endl;
  answer << "8" << std::endl;
  answer << "9" << std::endl;
  answer << "6" << std::endl;
  answer << "9" << std::endl;
  answer << "9" << std::endl;
  answer << "4" << std::endl;
  answer << "4" << std::endl;
  answer << "10" << std::endl;
  answer << "9" << std::endl;
  answer << "8" << std::endl;
  answer << "-1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10 30" << std::endl;
  input_stream << "35 23 43 33 38 25 22 39 22 6 41 1 15 41 3 20 50 17 25 14 1 22 5 10 34 38 1 12 15 1" << std::endl;
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

}  // namespace PAST_003_J
