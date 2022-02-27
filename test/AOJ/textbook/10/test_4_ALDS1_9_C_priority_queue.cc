/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part10-4. ヒープ、優先度付きキュー(Priority Queue)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/AOJ/textbook/10/4_ALDS1_9_C_priority_queue.h"

namespace ALDS1_9_C {

class Test_ALDS1_9_C : public ::testing::Test {
 protected:
  PriorityQueue* priority_queue_;
  virtual void SetUp() { priority_queue_ = new PriorityQueue(); }
  virtual void TearDown() { delete priority_queue_; }
};

TEST_F(Test_ALDS1_9_C, Add) {
  ASSERT_EQ(0, priority_queue_->GetSize());
  ASSERT_ANY_THROW(priority_queue_->GetKeyByIndex(0));

  const int32_t kKey_0 = 12;
  const int32_t kKey_1 = 26;
  priority_queue_->Add(kKey_0);
  priority_queue_->Add(kKey_1);

  ASSERT_EQ(2, priority_queue_->GetSize());
  ASSERT_EQ(kKey_0, priority_queue_->GetKeyByIndex(0));
  ASSERT_EQ(kKey_1, priority_queue_->GetKeyByIndex(1));
  ASSERT_ANY_THROW(priority_queue_->GetKeyByIndex(2));
}

TEST_F(Test_ALDS1_9_C, BuildMaxHeap_1) {
  constexpr int32_t kNumberOfNodes = 5;
  priority_queue_->Add(4);
  priority_queue_->Add(3);
  priority_queue_->Add(2);
  priority_queue_->Add(1);
  priority_queue_->Add(0);

  ASSERT_EQ(kNumberOfNodes, priority_queue_->GetSize());

  priority_queue_->BuildMaxHeap();
  ASSERT_EQ(kNumberOfNodes, priority_queue_->GetSize());
  ASSERT_EQ(4, priority_queue_->GetKeyByIndex(0));
  ASSERT_EQ(3, priority_queue_->GetKeyByIndex(1));
  ASSERT_EQ(2, priority_queue_->GetKeyByIndex(2));
  ASSERT_EQ(1, priority_queue_->GetKeyByIndex(3));
  ASSERT_EQ(0, priority_queue_->GetKeyByIndex(4));
}

TEST_F(Test_ALDS1_9_C, BuildMaxHeap_2) {
  constexpr int32_t kNumberOfNodes = 5;
  priority_queue_->Add(0);
  priority_queue_->Add(1);
  priority_queue_->Add(2);
  priority_queue_->Add(3);
  priority_queue_->Add(4);

  ASSERT_EQ(kNumberOfNodes, priority_queue_->GetSize());

  priority_queue_->BuildMaxHeap();
  ASSERT_EQ(kNumberOfNodes, priority_queue_->GetSize());

  ASSERT_EQ(4, priority_queue_->GetKeyByIndex(0));
  ASSERT_EQ(3, priority_queue_->GetKeyByIndex(1));
  ASSERT_EQ(2, priority_queue_->GetKeyByIndex(2));
  ASSERT_EQ(0, priority_queue_->GetKeyByIndex(3));
  ASSERT_EQ(1, priority_queue_->GetKeyByIndex(4));
}

TEST_F(Test_ALDS1_9_C, BuildMaxHeap_3) {
  constexpr int32_t kNumberOfNodes = 500000;
  for (int32_t value = 0; value < kNumberOfNodes; ++value) {
    priority_queue_->Add(value);
  }

  ASSERT_EQ(249999, priority_queue_->GetKeyByIndex(249999));
  ASSERT_EQ(499999, priority_queue_->GetKeyByIndex(499999));
  ASSERT_EQ(250000, priority_queue_->ConvertFromIndexToNodeNumber(249999));
  ASSERT_TRUE(priority_queue_->IsValidNodeNodeNumber(500000));
  ASSERT_EQ(499999, priority_queue_->GetIndexChildLeft(249999));
  ASSERT_EQ(kInvalidIndex, priority_queue_->GetIndexChildRight(249999));
  ASSERT_EQ(499999, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(249999));

  ASSERT_EQ(kNumberOfNodes, priority_queue_->GetSize());

  priority_queue_->BuildMaxHeap();
  ASSERT_EQ(kNumberOfNodes, priority_queue_->GetSize());

  ASSERT_GT(priority_queue_->GetKeyByIndex(249999), priority_queue_->GetKeyByIndex(499999));

  int32_t index_max_value = -1;
  for (int32_t index = 0; index < priority_queue_->GetSize(); ++index) {
    if (priority_queue_->GetKeyByIndex(index) == 499999) {
      index_max_value = index;
    }
  }
  ASSERT_EQ(0, index_max_value);
}

TEST_F(Test_ALDS1_9_C, GetIndexHavingLargestValue_1) {
  priority_queue_->Add(0);
  priority_queue_->Add(1);
  priority_queue_->Add(2);
  priority_queue_->Add(3);
  priority_queue_->Add(4);
  priority_queue_->Add(5);
  ASSERT_EQ(2, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(0));
  ASSERT_EQ(4, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(1));
  ASSERT_EQ(5, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(2));
  ASSERT_EQ(3, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(3));
  ASSERT_EQ(4, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(4));
  ASSERT_EQ(5, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(5));
}

TEST_F(Test_ALDS1_9_C, GetIndexHavingLargestValue_2) {
  priority_queue_->Add(10);
  priority_queue_->Add(8);
  priority_queue_->Add(9);
  priority_queue_->Add(7);
  priority_queue_->Add(6);
  priority_queue_->Add(50);
  priority_queue_->Add(49);
  priority_queue_->Add(59);
  priority_queue_->Add(60);
  priority_queue_->Add(70);
  priority_queue_->Add(5);
  priority_queue_->Add(4);
  priority_queue_->Add(80);
  int32_t index = 0;
  ASSERT_EQ(0, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(1, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(5, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(8, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(9, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(12, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(6, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(7, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(8, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(9, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(10, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(11, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(12, priority_queue_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
}

TEST_F(Test_ALDS1_9_C, MaxHeapify) {
  int32_t index;
  priority_queue_->Add(2);
  priority_queue_->Add(1);
  priority_queue_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(2, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(1, priority_queue_->GetKeyByIndex(index++));

  priority_queue_->Reset();
  priority_queue_->Add(1);
  priority_queue_->Add(2);
  priority_queue_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(2, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(1, priority_queue_->GetKeyByIndex(index++));

  priority_queue_->Reset();
  priority_queue_->Add(3);
  priority_queue_->Add(2);
  priority_queue_->Add(1);
  priority_queue_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(2, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(1, priority_queue_->GetKeyByIndex(index++));

  priority_queue_->Reset();
  priority_queue_->Add(3);
  priority_queue_->Add(1);
  priority_queue_->Add(2);
  priority_queue_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(1, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(2, priority_queue_->GetKeyByIndex(index++));

  priority_queue_->Reset();
  priority_queue_->Add(2);
  priority_queue_->Add(3);
  priority_queue_->Add(1);
  priority_queue_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(2, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(1, priority_queue_->GetKeyByIndex(index++));

  priority_queue_->Reset();
  priority_queue_->Add(2);
  priority_queue_->Add(1);
  priority_queue_->Add(3);
  priority_queue_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(1, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(2, priority_queue_->GetKeyByIndex(index++));

  priority_queue_->Reset();
  priority_queue_->Add(1);
  priority_queue_->Add(2);
  priority_queue_->Add(3);
  priority_queue_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(2, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(1, priority_queue_->GetKeyByIndex(index++));

  priority_queue_->Reset();
  priority_queue_->Add(1);
  priority_queue_->Add(3);
  priority_queue_->Add(2);
  priority_queue_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(1, priority_queue_->GetKeyByIndex(index++));
  ASSERT_EQ(2, priority_queue_->GetKeyByIndex(index++));
}

TEST_F(Test_ALDS1_9_C, CallPriorityQueue_1) {
  std::ostringstream answer;
  answer << "8" << std::endl;
  answer << "10" << std::endl;
  answer << "11" << std::endl;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "insert 8" << std::endl;
  input_stream << "insert 2" << std::endl;
  input_stream << "extract" << std::endl;
  input_stream << "insert 10" << std::endl;
  input_stream << "extract" << std::endl;
  input_stream << "insert 11" << std::endl;
  input_stream << "extract" << std::endl;
  input_stream << "extract" << std::endl;
  input_stream << "end" << std::endl;

  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallPriorityQueue(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_9_C, InsertAndExtract_4) {
  constexpr int32_t kInitKey = 0;
  priority_queue_->Insert(kInitKey);
  constexpr int32_t kMaxKey = 100;
  for (int32_t key = 1; key <= kMaxKey; ++key) {
    priority_queue_->Insert(key);
    const int32_t correct_size_before = 2;
    ASSERT_EQ(correct_size_before, priority_queue_->GetSize());
    ASSERT_EQ(key, priority_queue_->Extract());
    const int32_t correct_size_after = 1;
    ASSERT_EQ(correct_size_after, priority_queue_->GetSize());
  }
  for (int32_t key = 1; key <= kMaxKey; ++key) {
    priority_queue_->Insert(key);
    const int32_t correct_size = key + 1;
    ASSERT_EQ(correct_size, priority_queue_->GetSize());
  }
  for (int32_t key = kMaxKey; key >= 1; --key) {
    const int32_t correct_size_before = key + 1;
    ASSERT_EQ(correct_size_before, priority_queue_->GetSize());
    ASSERT_EQ(key, priority_queue_->Extract());
    const int32_t correct_size_after = key;
    ASSERT_EQ(correct_size_after, priority_queue_->GetSize());
  }
  ASSERT_EQ(kInitKey, priority_queue_->Extract());
}

TEST_F(Test_ALDS1_9_C, InsertAndExtract_5) {
  priority_queue_->Insert(120);
  priority_queue_->Insert(88);
  priority_queue_->Insert(3);
  priority_queue_->Insert(999999999);
  priority_queue_->Insert(7);
  ASSERT_EQ(999999999, priority_queue_->Extract());
  priority_queue_->Insert(100);
  priority_queue_->Insert(21);
  priority_queue_->Insert(100);
  priority_queue_->Insert(100);
  priority_queue_->Insert(10);
  ASSERT_EQ(120, priority_queue_->Extract());
  priority_queue_->Insert(100);
  ASSERT_EQ(100, priority_queue_->Extract());
  priority_queue_->Insert(777);
  priority_queue_->Insert(100);
  ASSERT_EQ(777, priority_queue_->Extract());
  ASSERT_EQ(100, priority_queue_->Extract());
  ASSERT_EQ(100, priority_queue_->Extract());
  ASSERT_EQ(100, priority_queue_->Extract());
  ASSERT_EQ(100, priority_queue_->Extract());
  priority_queue_->Insert(120);
  ASSERT_EQ(120, priority_queue_->Extract());
  ASSERT_EQ(88, priority_queue_->Extract());
}

}  // namespace ALDS1_9_C
