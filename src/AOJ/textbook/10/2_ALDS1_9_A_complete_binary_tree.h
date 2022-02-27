/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part10-2. ヒープ、完全二分木(Complete Binary Tree)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C10_2_ALDS1_9_A_COMPLETE_BINARY_TREE_H_
#define SRC_C10_2_ALDS1_9_A_COMPLETE_BINARY_TREE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_9_A {

constexpr int32_t kMaxNumberOfNodes = 1000;
constexpr int32_t kTopIndex = -1;
constexpr int32_t kInvalidIndex = -2;

void CallCompleteBinaryTree(std::istream& input_stream);

struct Node {
  bool is_valid{false};
  int32_t key{-1};
};

class CompleteBinaryTree {
 public:
  CompleteBinaryTree() noexcept;
  ~CompleteBinaryTree() noexcept;
  void Add(const int32_t key);
  void Print() const;

 private:
  int32_t GetIndexParent(const int32_t index) const;
  int32_t GetIndexChildLeft(const int32_t index) const;
  int32_t GetIndexChildRight(const int32_t index) const;
  void SetKeyByIndex(const int32_t index, const int32_t key);
  int32_t GetKeyByIndex(const int32_t index) const;
  bool IsInvalidNode(const int32_t index) const noexcept;
  bool IsValidNode(const int32_t index) const noexcept;
  static bool IsInvalidNodeIndex(const int32_t index) noexcept;
  static bool IsValidNodeIndex(const int32_t index) noexcept;
  static int32_t ConvertFromNodeNumberToIndex(const int32_t node_number);
  static int32_t ConvertFromIndexToNodeNumber(const int32_t index);

  CompleteBinaryTree(const CompleteBinaryTree& obj) = delete;
  CompleteBinaryTree& operator=(const CompleteBinaryTree& obj) = delete;
  CompleteBinaryTree(CompleteBinaryTree&& obj) = delete;
  CompleteBinaryTree& operator=(CompleteBinaryTree&& obj) = delete;

 private:
  int32_t size_;
  Node nodes_[kMaxNumberOfNodes];

 private:
  FRIEND_TEST(Test_ALDS1_9_A, Add);  // Should be removed from production code
};

}  // namespace ALDS1_9_A

#endif  // SRC_C10_2_ALDS1_9_A_COMPLETE_BINARY_TREE_H_
