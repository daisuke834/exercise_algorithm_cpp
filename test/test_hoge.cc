/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/hoge.h"

namespace hoge {
class HogeTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(HogeTest, HogeTest) {
  constexpr int32_t kAnswer = 10;
  const int32_t result = Hoge::MyFunc();
  ASSERT_EQ(kAnswer, result);
}

TEST_F(HogeTest, CallHoge) {
  std::ostringstream answer;
  answer << "7" << std::endl;

  std::ostringstream input_stream;
  input_stream << "7" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallHoge(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace hoge
