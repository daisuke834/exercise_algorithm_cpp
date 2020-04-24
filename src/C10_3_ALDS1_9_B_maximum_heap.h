/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part10-3. ヒープ、最大ヒープ(Maximum Heap)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C10_3_ALDS1_9_B_MAXIMUM_HEAP_H_
#define SRC_C10_3_ALDS1_9_B_MAXIMUM_HEAP_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_9_B {

constexpr int32_t kMaxNumberOfNodes = 500000;
constexpr int32_t kTopIndex = -1;
constexpr int32_t kInvalidIndex = -2;

void CallMaximumHeap(std::istream &input_stream);

struct Node {
  bool is_valid{false};
  int32_t key{-1};
};

class MaximumHeap {
 public:
  MaximumHeap() noexcept;
  ~MaximumHeap() noexcept;
  void Add(const int32_t key);
  void Print() const;
  void Debug() const;
  void BuildMaxHeap();
  int32_t GetSize() const noexcept;
  int32_t GetKeyByIndex(const int32_t index) const;
  void Reset() noexcept;

 private:
  void MaxHeapify(const int32_t index);
  int32_t GetIndexHavingLargestValueFromTargetAndChildren(const int32_t index_current) const;
  void Swap(const int32_t index_a, const int32_t index_b);
  int32_t GetIndexParent(const int32_t index) const;
  int32_t GetIndexChildLeft(const int32_t index) const;
  int32_t GetIndexChildRight(const int32_t index) const;
  void SetKeyByIndex(const int32_t index, const int32_t key);
  bool IsInvalidNode(const int32_t index) const noexcept;
  bool IsValidNode(const int32_t index) const noexcept;
  static bool IsInvalidNodeIndex(const int32_t index) noexcept;
  static bool IsValidNodeIndex(const int32_t index) noexcept;
  static int32_t ConvertFromNodeNumberToIndex(const int32_t node_number);
  static int32_t ConvertFromIndexToNodeNumber(const int32_t index);
  static bool IsInvalidNodeNumber(const int32_t node_number) noexcept;
  static bool IsValidNodeNodeNumber(const int32_t node_number) noexcept;

  MaximumHeap(const MaximumHeap &obj) = delete;
  MaximumHeap &operator=(const MaximumHeap &obj) = delete;
  MaximumHeap(MaximumHeap &&obj) = delete;
  MaximumHeap &operator=(MaximumHeap &&obj) = delete;

 private:
  int32_t size_;
  Node nodes_[kMaxNumberOfNodes];

 private:
  FRIEND_TEST(Test_ALDS1_9_B, GetIndexHavingLargestValue_1);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_9_B, GetIndexHavingLargestValue_2);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_9_B, MaxHeapify);                    // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_9_B, BuildMaxHeap_3);                // Should be removed from production code
};

}  // namespace ALDS1_9_B

#endif  // SRC_C10_3_ALDS1_9_B_MAXIMUM_HEAP_H_
