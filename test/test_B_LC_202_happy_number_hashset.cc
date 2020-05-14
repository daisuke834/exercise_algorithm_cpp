/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 202. Happy Number.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_LC_202_happy_number_hashset.h"

namespace LC_202 {

class Test_LC_202 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_LC_202, CallHappyNumber_1) {
  std::ostringstream answer;
  answer << "Is happy." << std::endl;

  std::ostringstream input_stream;
  input_stream << "19" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallHappyNumber(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_LC_202, CallHappyNumber_2) {
  std::ostringstream answer;
  answer << "Is not happy." << std::endl;

  std::ostringstream input_stream;
  input_stream << "2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallHappyNumber(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace LC_202
