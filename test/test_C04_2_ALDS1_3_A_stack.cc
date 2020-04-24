/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-2. データ構造、スタックのテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "src/C04_2_ALDS1_3_A_stack.h"

namespace ALDS1_3_A {
constexpr int32_t kMaxLengthTestPattern = 1000;

struct TestPattern {
  int32_t length{0};
  int32_t values[kMaxLengthTestPattern];
};

class Test_ALDS1_3_A : public ::testing::Test {
 protected:
  Stack *stack_;
  TestPattern *test_pattern_;
  virtual void SetUp() {
    stack_ = new Stack();
    test_pattern_ = new TestPattern();
  }
  virtual void TearDown() {
    delete stack_;
    delete test_pattern_;
  }
};

TEST_F(Test_ALDS1_3_A, LoadData_JudgeDataType) {
  ASSERT_EQ(DataType::kValue, JudgeDataType("0"));
  ASSERT_EQ(DataType::kValue, JudgeDataType("1"));
  ASSERT_EQ(DataType::kValue, JudgeDataType("12"));
  ASSERT_EQ(DataType::kValue, JudgeDataType("1111111"));

  ASSERT_EQ(DataType::kPlus, JudgeDataType("+"));
  ASSERT_EQ(DataType::kMinus, JudgeDataType("-"));
  ASSERT_EQ(DataType::kMultiply, JudgeDataType("*"));

  ASSERT_ANY_THROW(JudgeDataType("-12"));
  ASSERT_ANY_THROW(JudgeDataType("1.2"));
  ASSERT_ANY_THROW(JudgeDataType("++"));
  ASSERT_ANY_THROW(JudgeDataType("**"));
  ASSERT_ANY_THROW(JudgeDataType("a"));
}

TEST_F(Test_ALDS1_3_A, LoadOne_normal) {
  std::ostringstream input_stream;
  constexpr int32_t kValue1 = 1;
  constexpr int32_t kValue2 = 10;
  constexpr int32_t kValue4 = 20;
  constexpr int32_t kValue6 = 23;
  input_stream << kValue1 << " " << kValue2 << " + " << kValue4 << " * " << kValue6 << " -" << std::endl;
  std::istringstream iss(input_stream.str());

  const LoadedData result_1 = LoadOne(iss);
  ASSERT_EQ(DataType::kValue, result_1.data_type);
  ASSERT_EQ(1, result_1.value);

  const LoadedData result_2 = LoadOne(iss);
  ASSERT_EQ(DataType::kValue, result_2.data_type);
  ASSERT_EQ(10, result_2.value);

  const LoadedData result_3 = LoadOne(iss);
  ASSERT_EQ(DataType::kPlus, result_3.data_type);

  const LoadedData result_4 = LoadOne(iss);
  ASSERT_EQ(DataType::kValue, result_4.data_type);
  ASSERT_EQ(kValue4, result_4.value);

  const LoadedData result_5 = LoadOne(iss);
  ASSERT_EQ(DataType::kMultiply, result_5.data_type);

  const LoadedData result_6 = LoadOne(iss);
  ASSERT_EQ(DataType::kValue, result_6.data_type);
  ASSERT_EQ(kValue6, result_6.value);

  const LoadedData result_7 = LoadOne(iss);
  ASSERT_EQ(DataType::kMinus, result_7.data_type);

  const LoadedData result_8 = LoadOne(iss);
  ASSERT_EQ(DataType::kEOF, result_8.data_type);
}

TEST_F(Test_ALDS1_3_A, Empty) {
  ASSERT_TRUE(stack_->IsEmpty());
  ASSERT_FALSE(stack_->IsFull());

  ASSERT_ANY_THROW(stack_->Pop());
}

TEST_F(Test_ALDS1_3_A, Full) {
  for (int32_t i = 0; i < kMaxArraySize; ++i) {
    stack_->Push(0);
  }
  ASSERT_TRUE(stack_->IsFull());
  ASSERT_FALSE(stack_->IsEmpty());

  ASSERT_ANY_THROW(stack_->Push(0));
}

TEST_F(Test_ALDS1_3_A, PopAndVerity) {
  test_pattern_->length = 100;
  for (int32_t index = 0; index < test_pattern_->length; ++index) {
    test_pattern_->values[index] = index * 3 + 1;  // Any value
  }

  // Push
  for (int32_t index = 0; index < test_pattern_->length; ++index) {
    stack_->Push(test_pattern_->values[index]);
  }

  // Pop and Verify
  for (int32_t index = test_pattern_->length - 1; index >= 0; --index) {
    const int32_t value = stack_->Pop();
    ASSERT_EQ(test_pattern_->values[index], value);
  }
}

TEST_F(Test_ALDS1_3_A, PushAndPopAndPushAndPop) {
  constexpr int32_t kValue_0 = 0;
  stack_->Push(kValue_0);
  ASSERT_EQ(kValue_0, stack_->Pop());

  constexpr int32_t kValue_1 = 1;
  stack_->Push(kValue_1);
  ASSERT_EQ(kValue_1, stack_->Pop());
  ASSERT_TRUE(stack_->IsEmpty());
}

TEST_F(Test_ALDS1_3_A, LoadAndCompute_normal) {
  constexpr int32_t kAnswer = -3;
  std::ostringstream input_stream;
  input_stream << "1 2 + 3 4 - *" << std::endl;
  std::istringstream iss(input_stream.str());
  stack_->LoadAndCompute(iss);
  ASSERT_EQ(kAnswer, stack_->Pop());
}

TEST_F(Test_ALDS1_3_A, Main) {
  constexpr int32_t kAnswer = -3;
  std::ostringstream answer;
  answer << kAnswer << std::endl;

  std::ostringstream input_stream;
  input_stream << "1 2 + 3 4 - *" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  stack_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_3_A, Main_full) {
  constexpr int32_t kInput = 1;
  constexpr int32_t kNumberOfOperands = 100;
  constexpr int32_t kNumberOfOperators = kNumberOfOperands - 1;
  std::ostringstream input_stream;
  for (int i = 0; i < kNumberOfOperands; ++i) {
    input_stream << kInput << std::endl;
  }
  for (int i = 0; i < kNumberOfOperators; ++i) {
    input_stream << "+" << std::endl;
  }
  std::istringstream iss(input_stream.str());

  constexpr int32_t kAnswer = kInput * kNumberOfOperands;
  std::ostringstream answer;
  answer << kAnswer << std::endl;

  testing::internal::CaptureStdout();
  stack_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_3_A
