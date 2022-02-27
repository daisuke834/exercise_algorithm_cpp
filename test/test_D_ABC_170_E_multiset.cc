/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 170-E. Smart Infants.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/D_ABC_170_E_multiset.h"

namespace D_ABC_170_E {

class Test_D_ABC_170_E : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_D_ABC_170_E, test_1) {
  std::ostringstream answer;
  answer << "6" << std::endl;
  answer << "2" << std::endl;
  answer << "6" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6 3" << std::endl;
  input_stream << "8 1" << std::endl;
  input_stream << "6 2" << std::endl;
  input_stream << "9 3" << std::endl;
  input_stream << "1 1" << std::endl;
  input_stream << "2 2" << std::endl;
  input_stream << "1 3" << std::endl;
  input_stream << "4 3" << std::endl;
  input_stream << "2 1" << std::endl;
  input_stream << "1 2" << std::endl;
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

TEST_F(Test_D_ABC_170_E, test_2) {
  std::ostringstream answer;
  answer << "3056" << std::endl;
  answer << "4208" << std::endl;

  std::ostringstream input_stream;
  input_stream << "2 2" << std::endl;
  input_stream << "4208 1234" << std::endl;
  input_stream << "3056 5678" << std::endl;
  input_stream << "1 2020" << std::endl;
  input_stream << "2 2020" << std::endl;
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

}  // namespace D_ABC_170_E
