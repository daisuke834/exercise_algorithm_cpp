/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 153-E. Crested Ibis vs Monster.
 */

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include "src/D_ABC_153_E_knapsack_monster.h"

namespace ABC_153_E {

class Test_ABC_153_E : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ABC_153_E, test_1) {
  std::ostringstream answer;
  answer << "4" << std::endl;

  std::ostringstream input_stream;
  input_stream << "9 3" << std::endl;
  input_stream << "8 3" << std::endl;
  input_stream << "4 2" << std::endl;
  input_stream << "2 1" << std::endl;
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

TEST_F(Test_ABC_153_E, test_2) {
  std::ostringstream answer;
  answer << "100" << std::endl;

  std::ostringstream input_stream;
  input_stream << "100 6" << std::endl;
  input_stream << "1 1" << std::endl;
  input_stream << "2 3" << std::endl;
  input_stream << "3 9" << std::endl;
  input_stream << "4 27" << std::endl;
  input_stream << "5 81" << std::endl;
  input_stream << "6 243" << std::endl;
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

TEST_F(Test_ABC_153_E, test_3) {
  std::ostringstream answer;
  answer << "139815" << std::endl;

  std::ostringstream input_stream;
  input_stream << "9999 10" << std::endl;
  input_stream << "540 7550" << std::endl;
  input_stream << "691 9680" << std::endl;
  input_stream << "700 9790" << std::endl;
  input_stream << "510 7150" << std::endl;
  input_stream << "415 5818" << std::endl;
  input_stream << "551 7712" << std::endl;
  input_stream << "587 8227" << std::endl;
  input_stream << "619 8671" << std::endl;
  input_stream << "588 8228" << std::endl;
  input_stream << "176 2461" << std::endl;
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

}  // namespace ABC_153_E
