/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 173-E. Multiplication 4.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/D_ABC_173_E_multiplication4.h"

namespace D_ABC_173_E {

class Test_D_ABC_173_E : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_D_ABC_173_E, test_1) {
  std::ostringstream answer;
  answer << "12" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 2" << std::endl;
  input_stream << "1 2 -3 -4" << std::endl;
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

TEST_F(Test_D_ABC_173_E, test_2) {
  std::ostringstream answer;
  answer << "1000000001" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 3" << std::endl;
  input_stream << "-1 -2 -3 -4" << std::endl;
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
TEST_F(Test_D_ABC_173_E, test_3) {
  std::ostringstream answer;
  answer << "1000000000" << std::endl;

  std::ostringstream input_stream;
  input_stream << "2 1" << std::endl;
  input_stream << "-1 1000000000" << std::endl;
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
TEST_F(Test_D_ABC_173_E, test_4) {
  std::ostringstream answer;
  answer << "999983200" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10 10" << std::endl;
  input_stream << "1000000000 100000000 10000000 1000000 100000 10000 1000 100 10 1" << std::endl;
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

}  // namespace D_ABC_173_E
