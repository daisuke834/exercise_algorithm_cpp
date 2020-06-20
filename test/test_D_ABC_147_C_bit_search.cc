/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 147-C. ビット全探索.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/D_ABC_147_C_bit_search.h"

namespace D_ABC_147_C {

class Test_D_ABC_147_C : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_D_ABC_147_C, test_1) {
  std::ostringstream answer;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "2 1" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "1 1" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "2 0" << std::endl;
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

TEST_F(Test_D_ABC_147_C, test_2) {
  std::ostringstream answer;
  answer << "0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "2 1" << std::endl;
  input_stream << "3 0" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "3 1" << std::endl;
  input_stream << "1 0" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "1 1" << std::endl;
  input_stream << "2 0" << std::endl;
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

TEST_F(Test_D_ABC_147_C, test_3) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "2" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "2 0" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "1 0" << std::endl;
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

}  // namespace D_ABC_147_C
