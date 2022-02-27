/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-2. 再帰・分割統治法、全探索(Exhaustive Search)のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/C06_2_ALDS1_5_A_2_exhaustive_search.h"

namespace ALDS1_5_A_2 {

class Test_ALDS1_5_A_2 : public ::testing::Test {
 protected:
  ExhaustiveSearch* exhaustive_search_;
  virtual void SetUp() { exhaustive_search_ = new ExhaustiveSearch(); }
  virtual void TearDown() { delete exhaustive_search_; }
};

TEST_F(Test_ALDS1_5_A_2, CallExhaustiveSearch) {
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
    CallExhaustiveSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_5_A_2, AddOneSource) {
  ASSERT_EQ(0, exhaustive_search_->sources_.size);

  constexpr int32_t kValue_1 = 3;
  constexpr int32_t kValue_2 = 16;
  exhaustive_search_->AddOneSource(kValue_1);
  exhaustive_search_->AddOneSource(kValue_2);
  ASSERT_EQ(2, exhaustive_search_->sources_.size);
  ASSERT_EQ(kValue_1, exhaustive_search_->sources_.values[0]);
  ASSERT_EQ(kValue_2, exhaustive_search_->sources_.values[1]);
}

TEST_F(Test_ALDS1_5_A_2, AddOneTarget) {
  ASSERT_EQ(0, exhaustive_search_->targets_.size);

  constexpr int32_t kValue_1 = 3;
  constexpr int32_t kValue_2 = 16;
  exhaustive_search_->AddOneTarget(kValue_1);
  exhaustive_search_->AddOneTarget(kValue_2);
  ASSERT_EQ(2, exhaustive_search_->targets_.size);
  ASSERT_EQ(kValue_1, exhaustive_search_->targets_.values[0]);
  ASSERT_EQ(kValue_2, exhaustive_search_->targets_.values[1]);
}

TEST_F(Test_ALDS1_5_A_2, CanBeCreated) {
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

  ASSERT_FALSE(exhaustive_search_->CanBeCreated(2, 0));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(4, 0));
  ASSERT_FALSE(exhaustive_search_->CanBeCreated(100, 0));
}

}  // namespace ALDS1_5_A_2
