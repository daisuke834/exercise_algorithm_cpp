/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 150-C.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/D_ABC_150_C_permutation.h"

namespace ABC_150_C {

class Test_ABC_150_C : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ABC_150_C, CallPermutation_1) {
  std::ostringstream answer;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "1 3 2" << std::endl;
  input_stream << "3 1 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallPermutation(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ABC_150_C, CallPermutation_2) {
  std::ostringstream answer;
  answer << "17517" << std::endl;

  std::ostringstream input_stream;
  input_stream << "8" << std::endl;
  input_stream << "7 3 5 4 2 1 6 8" << std::endl;
  input_stream << "3 8 2 5 4 6 7 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallPermutation(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ABC_150_C, CallPermutation_3) {
  std::ostringstream answer;
  answer << "0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "1 2 3" << std::endl;
  input_stream << "1 2 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallPermutation(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ABC_150_C
