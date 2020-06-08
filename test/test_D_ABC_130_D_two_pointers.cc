/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 130-D. しゃくとり法(尺取り法, Two pointers).
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/D_ABC_130_D_two_pointers.h"

namespace ABC_130_D {

class Test_ABC_130_D : public ::testing::Test {
 protected:
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ABC_130_D, test_1) {
  std::ostringstream answer;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 10" << std::endl;
  input_stream << "6 1 2 7" << std::endl;
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

TEST_F(Test_ABC_130_D, test_2) {
  std::ostringstream answer;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3 5" << std::endl;
  input_stream << "3 3 3" << std::endl;
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
TEST_F(Test_ABC_130_D, test_3) {
  std::ostringstream answer;
  answer << "36" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10 53462" << std::endl;
  input_stream << "103 35322 232 342 21099 90000 18843 9010 35221 19352" << std::endl;
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

}  // namespace ABC_130_D
