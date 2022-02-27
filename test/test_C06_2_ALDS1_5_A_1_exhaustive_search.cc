/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-2. 再帰・分割統治法、全探索(Exhaustive Search)のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/C06_2_ALDS1_5_A_1_exhaustive_search.h"

namespace ALDS1_5_A_1 {

class Test_ALDS1_5_A_1 : public ::testing::Test {
 protected:
  ExhaustiveSearch* exhaustive_search_;
  virtual void SetUp() { exhaustive_search_ = new ExhaustiveSearch(); }
  virtual void TearDown() { delete exhaustive_search_; }
};

TEST_F(Test_ALDS1_5_A_1, CallExhaustiveSearch) {
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

TEST_F(Test_ALDS1_5_A_1, AddOneSource) {
  ASSERT_EQ(0U, exhaustive_search_->sources_.size());

  constexpr int32_t kValue_1 = 3;
  constexpr int32_t kValue_2 = 16;
  exhaustive_search_->AddOneSource(kValue_1);
  exhaustive_search_->AddOneSource(kValue_2);
  ASSERT_EQ(2U, exhaustive_search_->sources_.size());
  std::list<int>::iterator itr = exhaustive_search_->sources_.begin();
  ASSERT_EQ(kValue_1, *(itr++));
  ASSERT_EQ(kValue_2, *(itr++));
}

TEST_F(Test_ALDS1_5_A_1, AddOneTarget) {
  ASSERT_EQ(0, exhaustive_search_->targets_.size);

  constexpr int32_t kValue_1 = 3;
  constexpr int32_t kValue_2 = 16;
  exhaustive_search_->AddOneTarget(kValue_1);
  exhaustive_search_->AddOneTarget(kValue_2);
  ASSERT_EQ(2, exhaustive_search_->targets_.size);
  ASSERT_EQ(kValue_1, exhaustive_search_->targets_.values[0]);
  ASSERT_EQ(kValue_2, exhaustive_search_->targets_.values[1]);
}

TEST_F(Test_ALDS1_5_A_1, CanBeCreated) {
  std::list<int32_t> sources;
  sources.push_back(1);
  sources.push_back(5);
  sources.push_back(7);
  sources.push_back(10);
  sources.push_back(21);
  // input_stream << "2 4 17 8" << std::endl;
  ASSERT_TRUE(ExhaustiveSearch::CanBeCreated(1, sources));
  ASSERT_TRUE(ExhaustiveSearch::CanBeCreated(5, sources));
  ASSERT_TRUE(ExhaustiveSearch::CanBeCreated(7, sources));
  ASSERT_TRUE(ExhaustiveSearch::CanBeCreated(10, sources));
  ASSERT_TRUE(ExhaustiveSearch::CanBeCreated(21, sources));

  ASSERT_TRUE(ExhaustiveSearch::CanBeCreated(8, sources));
  ASSERT_TRUE(ExhaustiveSearch::CanBeCreated(17, sources));

  ASSERT_FALSE(ExhaustiveSearch::CanBeCreated(2, sources));
  ASSERT_FALSE(ExhaustiveSearch::CanBeCreated(4, sources));
  ASSERT_FALSE(ExhaustiveSearch::CanBeCreated(100, sources));
}

}  // namespace ALDS1_5_A_1
