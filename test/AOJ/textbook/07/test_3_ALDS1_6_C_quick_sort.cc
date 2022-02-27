/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-3. 高等的整列、クイックソート(Quick Sort)のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AOJ/textbook/07/3_ALDS1_6_C_quick_sort.h"

namespace ALDS1_6_C {

class Test_ALDS1_6_C : public ::testing::Test {
 protected:
  QuickSort* quick_sort_;
  virtual void SetUp() { quick_sort_ = new QuickSort(); }
  virtual void TearDown() { delete quick_sort_; }
};

TEST_F(Test_ALDS1_6_C, CallQuickSort) {
  std::ostringstream answer;
  answer << "Not stable" << std::endl;
  answer << "D 1" << std::endl;
  answer << "C 1" << std::endl;
  answer << "D 2" << std::endl;
  answer << "H 2" << std::endl;
  answer << "D 3" << std::endl;
  answer << "S 3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "D 3" << std::endl;
  input_stream << "H 2" << std::endl;
  input_stream << "D 1" << std::endl;
  input_stream << "S 3" << std::endl;
  input_stream << "D 2" << std::endl;
  input_stream << "C 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallQuickSort(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_6_C, AddCard) {
  ASSERT_EQ(0, quick_sort_->size_);

  ASSERT_ANY_THROW(quick_sort_->AddCard(std::string("CC"), 5));

  quick_sort_->AddCard(std::string("C"), 5);
  quick_sort_->AddCard(std::string("D"), 2);
  quick_sort_->AddCard(std::string("H"), 3);
  quick_sort_->AddCard(std::string("S"), 5);

  ASSERT_EQ(4, quick_sort_->size_);
  int32_t index = 0;
  Card card;
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('C', card.symbol);
  ASSERT_EQ(5, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('D', card.symbol);
  ASSERT_EQ(2, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('H', card.symbol);
  ASSERT_EQ(3, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('S', card.symbol);
  ASSERT_EQ(5, card.number);
}

TEST_F(Test_ALDS1_6_C, Swap) {
  quick_sort_->AddCard(std::string("C"), 5);
  quick_sort_->AddCard(std::string("D"), 2);
  quick_sort_->AddCard(std::string("H"), 3);
  quick_sort_->AddCard(std::string("S"), 5);

  quick_sort_->Swap(0, 1);

  int32_t index = 0;
  Card card;
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('D', card.symbol);
  ASSERT_EQ(2, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('C', card.symbol);
  ASSERT_EQ(5, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('H', card.symbol);
  ASSERT_EQ(3, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('S', card.symbol);
  ASSERT_EQ(5, card.number);
}

TEST_F(Test_ALDS1_6_C, ComputePartition_1) {
  quick_sort_->AddCard(std::string("D"), 1);
  quick_sort_->AddCard(std::string("S"), 4);

  const int32_t index_pivot = quick_sort_->ComputePartition(0, 1);
  ASSERT_EQ(1, index_pivot);

  int32_t index = 0;
  Card card;
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('D', card.symbol);
  ASSERT_EQ(1, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('S', card.symbol);
  ASSERT_EQ(4, card.number);
}

TEST_F(Test_ALDS1_6_C, ComputePartition_2) {
  quick_sort_->AddCard(std::string("S"), 4);
  quick_sort_->AddCard(std::string("D"), 1);

  const int32_t index_pivot = quick_sort_->ComputePartition(0, 1);
  ASSERT_EQ(0, index_pivot);

  int32_t index = 0;
  Card card;
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('D', card.symbol);
  ASSERT_EQ(1, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('S', card.symbol);
  ASSERT_EQ(4, card.number);
}

TEST_F(Test_ALDS1_6_C, ComputePartition_3) {
  quick_sort_->AddCard(std::string("S"), 4);
  quick_sort_->AddCard(std::string("D"), 1);
  quick_sort_->AddCard(std::string("H"), 7);
  quick_sort_->AddCard(std::string("C"), 3);

  const int32_t index_pivot = quick_sort_->ComputePartition(0, 3);
  ASSERT_EQ(1, index_pivot);

  int32_t index = 0;
  Card card;
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('D', card.symbol);
  ASSERT_EQ(1, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('C', card.symbol);
  ASSERT_EQ(3, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('H', card.symbol);
  ASSERT_EQ(7, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('S', card.symbol);
  ASSERT_EQ(4, card.number);
}

TEST_F(Test_ALDS1_6_C, ComputePartition_4) {
  quick_sort_->AddCard(std::string("S"), 4);
  quick_sort_->AddCard(std::string("D"), 1);
  quick_sort_->AddCard(std::string("H"), 7);
  quick_sort_->AddCard(std::string("C"), 3);

  const int32_t index_pivot = quick_sort_->ComputePartition(2, 3);
  ASSERT_EQ(2, index_pivot);

  int32_t index = 0;
  Card card;
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('S', card.symbol);
  ASSERT_EQ(4, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('D', card.symbol);
  ASSERT_EQ(1, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('C', card.symbol);
  ASSERT_EQ(3, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('H', card.symbol);
  ASSERT_EQ(7, card.number);
}

TEST_F(Test_ALDS1_6_C, Sort_1) {
  quick_sort_->AddCard(std::string("D"), 1);

  quick_sort_->Sort();

  int32_t index = 0;
  Card card;
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('D', card.symbol);
  ASSERT_EQ(1, card.number);
}

TEST_F(Test_ALDS1_6_C, Sort_2) {
  quick_sort_->AddCard(std::string("D"), 1);
  quick_sort_->AddCard(std::string("S"), 4);

  quick_sort_->Sort();

  int32_t index = 0;
  Card card;
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('D', card.symbol);
  ASSERT_EQ(1, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('S', card.symbol);
  ASSERT_EQ(4, card.number);
}

TEST_F(Test_ALDS1_6_C, Sort_3) {
  quick_sort_->AddCard(std::string("S"), 4);
  quick_sort_->AddCard(std::string("D"), 1);

  quick_sort_->Sort();

  int32_t index = 0;
  Card card;
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('D', card.symbol);
  ASSERT_EQ(1, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('S', card.symbol);
  ASSERT_EQ(4, card.number);
}

TEST_F(Test_ALDS1_6_C, Sort_4) {
  quick_sort_->AddCard(std::string("S"), 4);
  quick_sort_->AddCard(std::string("D"), 1);
  quick_sort_->AddCard(std::string("H"), 7);
  quick_sort_->AddCard(std::string("C"), 3);

  quick_sort_->Sort();

  int32_t index = 0;
  Card card;
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('D', card.symbol);
  ASSERT_EQ(1, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('C', card.symbol);
  ASSERT_EQ(3, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('S', card.symbol);
  ASSERT_EQ(4, card.number);
  card = quick_sort_->GetCard(index++);
  ASSERT_EQ('H', card.symbol);
  ASSERT_EQ(7, card.number);
}

}  // namespace ALDS1_6_C
