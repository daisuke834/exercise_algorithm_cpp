/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 最大公約数(Greatest Common Divisor, GCD)
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C18_2_ALDS1_1_B_2_GCD_Euclidean.h"

namespace ALDS1_1_B_2 {
class Test_ALDS1_1_B_2 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ALDS1_1_B_2, CallCalculateGreatestCommonDivisor) {
  std::ostringstream answer;
  answer << "21" << std::endl;

  std::ostringstream input_stream;
  input_stream << "147 105" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  CallCalculateGreatestCommonDivisor(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_1_B_2, CalculateGreatestCommonDivisor) {
  ASSERT_EQ(21, CalculateGreatestCommonDivisor(147, 105));
}

}  // namespace ALDS1_1_B_2
