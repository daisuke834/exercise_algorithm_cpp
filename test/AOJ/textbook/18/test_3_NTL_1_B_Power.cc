/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 整数論、べき乗。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AOJ/textbook/18/3_NTL_1_B_Power.h"

namespace NTL_1_B {
class Test_NTL_1_B : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_NTL_1_B, CallCalculatePower) {
  std::ostringstream answer;
  answer << "390625" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5 8" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  CallCalculatePower(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_NTL_1_B, CalculatePower_1) { ASSERT_EQ(390625, CalculatePower(5, 8)); }

TEST_F(Test_NTL_1_B, CalculatePower_2) { ASSERT_EQ(891031477, CalculatePower(31, 8)); }

}  // namespace NTL_1_B
