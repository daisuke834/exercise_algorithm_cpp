/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-6. 高等的整列、反転数, 転倒数(The Number of Inversions)。
 * Segment Tree.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/AOJ/textbook/07/6_ALDS1_5_D_2_Segment_Tree.h"

namespace ALDS1_5_D_2 {

class Test_ALDS1_5_D_2 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ALDS1_5_D_2, NumberOfInversions_1) {
  std::ostringstream answer;
  answer << "6" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "3 5 2 1 4" << std::endl;

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

TEST_F(Test_ALDS1_5_D_2, NumberOfInversions_2) {
  std::ostringstream answer;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "3 1 2" << std::endl;

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

TEST_F(Test_ALDS1_5_D_2, NumberOfInversions_3) {
  std::ostringstream answer;
  answer << "12" << std::endl;

  std::ostringstream input_stream;
  input_stream << "8" << std::endl;
  input_stream << "6 1 5 8 2 3 4 7" << std::endl;

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

TEST_F(Test_ALDS1_5_D_2, NumberOfInversions_4) {
  std::ostringstream answer;
  answer << "123" << std::endl;

  std::ostringstream input_stream;
  input_stream << "23" << std::endl;
  input_stream << "69 29 30 5 17 93 19 32 68 66 33 62 43 52 47 56 0 23 51 11 72 80 8" << std::endl;

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

}  // namespace ALDS1_5_D_2
