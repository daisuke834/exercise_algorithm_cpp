/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part10-3. ヒープ、最大ヒープ(Maximum Heap)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/C10_3_ALDS1_9_B_maximum_heap.h"

namespace ALDS1_9_B {

class Test_ALDS1_9_B : public ::testing::Test {
 protected:
  MaximumHeap* maximum_heap_;
  virtual void SetUp() { maximum_heap_ = new MaximumHeap(); }
  virtual void TearDown() { delete maximum_heap_; }
};

TEST_F(Test_ALDS1_9_B, Add) {
  ASSERT_EQ(0, maximum_heap_->GetSize());
  ASSERT_ANY_THROW(maximum_heap_->GetKeyByIndex(0));

  const int32_t kKey_0 = 12;
  const int32_t kKey_1 = 26;
  maximum_heap_->Add(kKey_0);
  maximum_heap_->Add(kKey_1);

  ASSERT_EQ(2, maximum_heap_->GetSize());
  ASSERT_EQ(kKey_0, maximum_heap_->GetKeyByIndex(0));
  ASSERT_EQ(kKey_1, maximum_heap_->GetKeyByIndex(1));
  ASSERT_ANY_THROW(maximum_heap_->GetKeyByIndex(2));
}

TEST_F(Test_ALDS1_9_B, CallMaximumHeap_1) {
  std::ostringstream answer;
  answer << " 16 14 10 8 7 9 3 2 4 1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10" << std::endl;
  input_stream << "4 1 3 2 16 9 10 14 8 7" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMaximumHeap(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_9_B, BuildMaxHeap_1) {
  constexpr int32_t kNumberOfNodes = 5;
  maximum_heap_->Add(4);
  maximum_heap_->Add(3);
  maximum_heap_->Add(2);
  maximum_heap_->Add(1);
  maximum_heap_->Add(0);

  ASSERT_EQ(kNumberOfNodes, maximum_heap_->GetSize());

  maximum_heap_->BuildMaxHeap();
  ASSERT_EQ(kNumberOfNodes, maximum_heap_->GetSize());
  ASSERT_EQ(4, maximum_heap_->GetKeyByIndex(0));
  ASSERT_EQ(3, maximum_heap_->GetKeyByIndex(1));
  ASSERT_EQ(2, maximum_heap_->GetKeyByIndex(2));
  ASSERT_EQ(1, maximum_heap_->GetKeyByIndex(3));
  ASSERT_EQ(0, maximum_heap_->GetKeyByIndex(4));
}

TEST_F(Test_ALDS1_9_B, BuildMaxHeap_2) {
  constexpr int32_t kNumberOfNodes = 5;
  maximum_heap_->Add(0);
  maximum_heap_->Add(1);
  maximum_heap_->Add(2);
  maximum_heap_->Add(3);
  maximum_heap_->Add(4);

  ASSERT_EQ(kNumberOfNodes, maximum_heap_->GetSize());

  maximum_heap_->BuildMaxHeap();
  ASSERT_EQ(kNumberOfNodes, maximum_heap_->GetSize());

  ASSERT_EQ(4, maximum_heap_->GetKeyByIndex(0));
  ASSERT_EQ(3, maximum_heap_->GetKeyByIndex(1));
  ASSERT_EQ(2, maximum_heap_->GetKeyByIndex(2));
  ASSERT_EQ(0, maximum_heap_->GetKeyByIndex(3));
  ASSERT_EQ(1, maximum_heap_->GetKeyByIndex(4));
}

TEST_F(Test_ALDS1_9_B, BuildMaxHeap_3) {
  constexpr int32_t kNumberOfNodes = 500000;
  for (int32_t value = 0; value < kNumberOfNodes; ++value) {
    maximum_heap_->Add(value);
  }

  ASSERT_EQ(249999, maximum_heap_->GetKeyByIndex(249999));
  ASSERT_EQ(499999, maximum_heap_->GetKeyByIndex(499999));
  ASSERT_EQ(250000, maximum_heap_->ConvertFromIndexToNodeNumber(249999));
  ASSERT_TRUE(maximum_heap_->IsValidNodeNodeNumber(500000));
  ASSERT_EQ(499999, maximum_heap_->GetIndexChildLeft(249999));
  ASSERT_EQ(kInvalidIndex, maximum_heap_->GetIndexChildRight(249999));
  ASSERT_EQ(499999, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(249999));

  ASSERT_EQ(kNumberOfNodes, maximum_heap_->GetSize());

  maximum_heap_->BuildMaxHeap();
  ASSERT_EQ(kNumberOfNodes, maximum_heap_->GetSize());

  ASSERT_GT(maximum_heap_->GetKeyByIndex(249999), maximum_heap_->GetKeyByIndex(499999));

  int32_t index_max_value = -1;
  for (int32_t index = 0; index < maximum_heap_->GetSize(); ++index) {
    if (maximum_heap_->GetKeyByIndex(index) == 499999) {
      index_max_value = index;
    }
  }
  ASSERT_EQ(0, index_max_value);
}

TEST_F(Test_ALDS1_9_B, GetIndexHavingLargestValue_1) {
  maximum_heap_->Add(0);
  maximum_heap_->Add(1);
  maximum_heap_->Add(2);
  maximum_heap_->Add(3);
  maximum_heap_->Add(4);
  maximum_heap_->Add(5);
  ASSERT_EQ(2, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(0));
  ASSERT_EQ(4, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(1));
  ASSERT_EQ(5, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(2));
  ASSERT_EQ(3, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(3));
  ASSERT_EQ(4, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(4));
  ASSERT_EQ(5, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(5));
}

TEST_F(Test_ALDS1_9_B, GetIndexHavingLargestValue_2) {
  maximum_heap_->Add(10);
  maximum_heap_->Add(8);
  maximum_heap_->Add(9);
  maximum_heap_->Add(7);
  maximum_heap_->Add(6);
  maximum_heap_->Add(50);
  maximum_heap_->Add(49);
  maximum_heap_->Add(59);
  maximum_heap_->Add(60);
  maximum_heap_->Add(70);
  maximum_heap_->Add(5);
  maximum_heap_->Add(4);
  maximum_heap_->Add(80);
  int32_t index = 0;
  ASSERT_EQ(0, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(1, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(5, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(8, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(9, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(12, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(6, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(7, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(8, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(9, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(10, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(11, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
  ASSERT_EQ(12, maximum_heap_->GetIndexHavingLargestValueFromTargetAndChildren(index++));
}

TEST_F(Test_ALDS1_9_B, MaxHeapify) {
  int32_t index;
  maximum_heap_->Add(2);
  maximum_heap_->Add(1);
  maximum_heap_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(2, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(1, maximum_heap_->GetKeyByIndex(index++));

  maximum_heap_->Reset();
  maximum_heap_->Add(1);
  maximum_heap_->Add(2);
  maximum_heap_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(2, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(1, maximum_heap_->GetKeyByIndex(index++));

  maximum_heap_->Reset();
  maximum_heap_->Add(3);
  maximum_heap_->Add(2);
  maximum_heap_->Add(1);
  maximum_heap_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(2, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(1, maximum_heap_->GetKeyByIndex(index++));

  maximum_heap_->Reset();
  maximum_heap_->Add(3);
  maximum_heap_->Add(1);
  maximum_heap_->Add(2);
  maximum_heap_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(1, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(2, maximum_heap_->GetKeyByIndex(index++));

  maximum_heap_->Reset();
  maximum_heap_->Add(2);
  maximum_heap_->Add(3);
  maximum_heap_->Add(1);
  maximum_heap_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(2, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(1, maximum_heap_->GetKeyByIndex(index++));

  maximum_heap_->Reset();
  maximum_heap_->Add(2);
  maximum_heap_->Add(1);
  maximum_heap_->Add(3);
  maximum_heap_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(1, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(2, maximum_heap_->GetKeyByIndex(index++));

  maximum_heap_->Reset();
  maximum_heap_->Add(1);
  maximum_heap_->Add(2);
  maximum_heap_->Add(3);
  maximum_heap_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(2, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(1, maximum_heap_->GetKeyByIndex(index++));

  maximum_heap_->Reset();
  maximum_heap_->Add(1);
  maximum_heap_->Add(3);
  maximum_heap_->Add(2);
  maximum_heap_->MaxHeapify(0);
  index = 0;
  ASSERT_EQ(3, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(1, maximum_heap_->GetKeyByIndex(index++));
  ASSERT_EQ(2, maximum_heap_->GetKeyByIndex(index++));
}

}  // namespace ALDS1_9_B
