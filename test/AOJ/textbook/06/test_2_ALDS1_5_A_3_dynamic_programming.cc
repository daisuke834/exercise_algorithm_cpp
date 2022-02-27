/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-2. ALDS1_5_A_3を動的計画法(Dynamic Programming, DP)を用いて再実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AOJ/textbook/06/2_ALDS1_5_A_3_dynamic_programming.h"

namespace ALDS1_5_A_3 {

class Test_ALDS1_5_A_3 : public ::testing::Test {
 protected:
  DynamicProgramming* exhaustive_search_;
  virtual void SetUp() { exhaustive_search_ = new DynamicProgramming(); }
  virtual void TearDown() { delete exhaustive_search_; }
};

TEST_F(Test_ALDS1_5_A_3, CallDynamicProgramming) {
  std::ostringstream answer;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "1 5 7 10 21" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "2 4 17 8" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDynamicProgramming(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_5_A_3, AddOneSource) {
  ASSERT_EQ(0, exhaustive_search_->sources_.size);

  constexpr int32_t kValue_1 = 3;
  constexpr int32_t kValue_2 = 16;
  exhaustive_search_->AddOneSource(kValue_1);
  exhaustive_search_->AddOneSource(kValue_2);
  ASSERT_EQ(2, exhaustive_search_->sources_.size);
  ASSERT_EQ(kValue_1, exhaustive_search_->sources_.values[0]);
  ASSERT_EQ(kValue_2, exhaustive_search_->sources_.values[1]);
}

TEST_F(Test_ALDS1_5_A_3, AddOneTarget) {
  ASSERT_EQ(0, exhaustive_search_->targets_.size);

  constexpr int32_t kValue_1 = 3;
  constexpr int32_t kValue_2 = 16;
  exhaustive_search_->AddOneTarget(kValue_1);
  exhaustive_search_->AddOneTarget(kValue_2);
  ASSERT_EQ(2, exhaustive_search_->targets_.size);
  ASSERT_EQ(kValue_1, exhaustive_search_->targets_.values[0]);
  ASSERT_EQ(kValue_2, exhaustive_search_->targets_.values[1]);
}

TEST_F(Test_ALDS1_5_A_3, CanBeCreated_1) {
  int32_t index = 0;
  exhaustive_search_->sources_.values[index++] = 1;
  exhaustive_search_->sources_.values[index++] = 5;
  exhaustive_search_->sources_.values[index++] = 7;
  exhaustive_search_->sources_.values[index++] = 10;
  exhaustive_search_->sources_.values[index++] = 21;
  exhaustive_search_->sources_.size = index;

  ASSERT_TRUE(exhaustive_search_->CanBeCreated(1, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(5, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(7, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(10, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(21, 0));

  ASSERT_TRUE(exhaustive_search_->CanBeCreated(8, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(17, 0));

  EXPECT_FALSE(exhaustive_search_->CanBeCreated(1, 1));
  EXPECT_FALSE(exhaustive_search_->CanBeCreated(1, 2));
  EXPECT_FALSE(exhaustive_search_->CanBeCreated(1, 3));
  EXPECT_FALSE(exhaustive_search_->CanBeCreated(1, 4));
  ASSERT_ANY_THROW(exhaustive_search_->CanBeCreated(1, 5));
  EXPECT_FALSE(exhaustive_search_->CanBeCreated(2, 1));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(2, 0));
  EXPECT_FALSE(exhaustive_search_->CanBeCreated(3, 1));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(4, 0));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(100, 0));
}

TEST_F(Test_ALDS1_5_A_3, CanBeCreated_2) {
  int32_t index = 0;
  exhaustive_search_->sources_.values[index++] = 1;
  exhaustive_search_->sources_.values[index++] = 4;
  exhaustive_search_->sources_.values[index++] = 8;
  exhaustive_search_->sources_.values[index++] = 16;
  exhaustive_search_->sources_.values[index++] = 11;
  exhaustive_search_->sources_.size = index;

  ASSERT_TRUE(exhaustive_search_->CanBeCreated(1, 0));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(2, 0));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(3, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(4, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(5, 0));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(6, 0));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(7, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(8, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(9, 0));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(10, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(11, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(12, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(13, 0));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(14, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(15, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(16, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(17, 0));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(18, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(19, 0));
  ASSERT_TRUE(exhaustive_search_->CanBeCreated(20, 0));
}

}  // namespace ALDS1_5_A_3
