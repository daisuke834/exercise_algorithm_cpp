/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part1. 準備編、Cubicのテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include "src/C1_5_2_cubic.h"

namespace C1P5P2 {
class C1P5P2 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(C1P5P2, Cubic) {
  constexpr int32_t kX = 2;
  constexpr int32_t kAnswer = 8;
  const int32_t result = Cubic(kX);
  ASSERT_EQ(kAnswer, result);
}

TEST_F(C1P5P2, MyMain) {
  const std::string answer("27\n");
  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  MyMain(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.c_str(), captured_stdout.c_str());
}

}  // namespace C1P5P2
