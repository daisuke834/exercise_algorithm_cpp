/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part11-2. 動的計画法(Dynamic Programming, DP)、フィボナッチ数列(Fibonacci Number)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/C11_2_ALDS1_10_A_fibonacci_number.h"

namespace ALDS1_10_A {

class Test_ALDS1_10_A : public ::testing::Test {
 protected:
  FibonacciNumber* fibonacci_number_;
  virtual void SetUp() { fibonacci_number_ = new FibonacciNumber(); }
  virtual void TearDown() { delete fibonacci_number_; }
};

TEST_F(Test_ALDS1_10_A, CallFibonacciNumber) {
  std::ostringstream answer;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallFibonacciNumber(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_10_A, Calculate) {
  ASSERT_EQ(1, fibonacci_number_->Calculate(0));
  ASSERT_EQ(1, fibonacci_number_->Calculate(1));
  ASSERT_EQ(2, fibonacci_number_->Calculate(2));
  ASSERT_EQ(3, fibonacci_number_->Calculate(3));
  ASSERT_EQ(5, fibonacci_number_->Calculate(4));
  ASSERT_EQ(8, fibonacci_number_->Calculate(5));
  fibonacci_number_->Calculate(40);
}

}  // namespace ALDS1_10_A
