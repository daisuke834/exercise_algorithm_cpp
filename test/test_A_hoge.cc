/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/A_hoge.h"

namespace hoge {
class HogeTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

/**
 * @brief hoge
 */
TEST_F(HogeTest, HogeTest) {
  constexpr int32_t kAnswer = 10;
  const int32_t result = Hoge::MyFunc();
  ASSERT_EQ(kAnswer, result);
}

TEST_F(HogeTest, StdOut) {
  std::ostringstream answer;
  answer << "Hello World." << std::endl;

  testing::internal::CaptureStdout();
  std::cout << "Hello World." << std::endl;
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(HogeTest, StdIn) {
  constexpr int32_t kAnswer = 15;

  std::ostringstream input_stream;
  input_stream << "15" << std::endl;
  std::istringstream iss(input_stream.str());

  const int32_t result = ReadUserInput(iss);
  ASSERT_EQ(kAnswer, result);
}

}  // namespace hoge
