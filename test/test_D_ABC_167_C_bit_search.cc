/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 165-B. ビット全探索(bit全探索).
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/D_ABC_167_C_bit_search.h"

namespace ABC_167_C {

class Test_ABC_167_C : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ABC_167_C, CallBitSearch_1) {
  std::ostringstream answer;
  answer << "120" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3 3 10" << std::endl;
  input_stream << "60 2 2 4" << std::endl;
  input_stream << "70 8 7 9" << std::endl;
  input_stream << "50 2 3 9" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBitSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ABC_167_C, CallBitSearch_2) {
  std::ostringstream answer;
  answer << "-1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3 3 10" << std::endl;
  input_stream << "100 3 1 4" << std::endl;
  input_stream << "100 1 5 9" << std::endl;
  input_stream << "100 2 6 5" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBitSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ABC_167_C, CallBitSearch_3) {
  std::ostringstream answer;
  answer << "1067" << std::endl;

  std::ostringstream input_stream;
  input_stream << "8 5 22" << std::endl;
  input_stream << "100 3 7 5 3 1" << std::endl;
  input_stream << "164 4 5 2 7 8" << std::endl;
  input_stream << "334 7 2 7 2 9" << std::endl;
  input_stream << "234 4 7 2 8 2" << std::endl;
  input_stream << "541 5 4 3 3 6" << std::endl;
  input_stream << "235 4 8 6 9 7" << std::endl;
  input_stream << "394 3 6 1 6 2" << std::endl;
  input_stream << "872 8 4 3 7 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBitSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ABC_167_C
