/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part14-1. 高度なデータ構造、Union Find Tree
 * (素集合データ構造, Union Find木, 互いに素な集合, Disjoint Sets Forest)
 * 計算量=O(log(N))
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C14_1_DSL_1_A_UNION_FIND_TREE_H_
#define SRC_C14_1_DSL_1_A_UNION_FIND_TREE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace DSL_1_A {

constexpr int32_t kMaxNumberOfElements = 10000;
constexpr int32_t kInvalidIndex = -1;
constexpr int32_t kMaxLoopCount = 2000000;

// ****************************************************

void CallUnionFindTree(std::istream& input_stream);

// ****************************************************
struct Element {
  int32_t parent{kInvalidIndex};
};

class UnionFindTree {
 public:
  UnionFindTree() noexcept;
  ~UnionFindTree() noexcept;
  void Initialize(const int32_t number_of_elements);
  bool IsSameSet(const int32_t element_1, const int32_t element_2) const;
  void UniteSets(const int32_t element_1, const int32_t element_2);
  void Debug() const noexcept;

 private:
  void SetRootRecursively(const int32_t element_index, const int32_t root_index);
  int32_t GetRoot(const int32_t element_index) const;
  void SetRoot(const int32_t element_index, const int32_t root_index);
  int32_t GetParentIndex(const int32_t element_index) const;
  bool IsRoot(const int32_t element_index) const;
  int32_t GetDepth(const int32_t element_index) const;
  bool InvalidIndex(const int32_t element_index) const noexcept;

  UnionFindTree(const UnionFindTree& obj) = delete;
  UnionFindTree& operator=(const UnionFindTree& obj) = delete;
  UnionFindTree(UnionFindTree&& obj) = delete;
  UnionFindTree& operator=(UnionFindTree&& obj) = delete;

 private:
  int32_t number_of_elements_;
  Element elements_[kMaxNumberOfElements];

 private:
  FRIEND_TEST(Test_DSL_1_A, Initialized);  // Should be removed from production code
};

}  // namespace DSL_1_A

#endif  // SRC_C14_1_DSL_1_A_UNION_FIND_TREE_H_
