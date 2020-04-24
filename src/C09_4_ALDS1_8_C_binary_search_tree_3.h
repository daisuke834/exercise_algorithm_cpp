/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part9-4. 二分探索木(Binary Search Tree)、削除(Delete)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C09_4_ALDS1_8_C_BINARY_SEARCH_TREE_3_H_
#define SRC_C09_4_ALDS1_8_C_BINARY_SEARCH_TREE_3_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_8_C {

constexpr int32_t kMaxNumberOfNodes = 500000;
constexpr int32_t kTop = -1;
constexpr int32_t kInvalid = -2;

enum class NodeType : int32_t { kInternal = 0, kLeaf, kRoot };

void CallBinarySearchTree(std::istream &input_stream);

enum class InstructionType : int32_t { kInsert = 0, kPrint, kFind, kDelete };

InstructionType JudgeInstructionType(const std::string &str);
void PrintFindResult(const int32_t found_index);

class Node {
 public:
  Node() noexcept;
  ~Node() noexcept;
  Node(const Node &obj) noexcept;
  Node &operator=(const Node &rhs) noexcept;
  Node(Node &&obj) noexcept;
  Node &operator=(Node &&rhs) noexcept;

  void Activate() noexcept;
  bool IsValid() const noexcept;
  void Reset() noexcept;
  void SetKey(const int32_t key);
  int32_t GetKey() const;
  void SetParent(const int32_t parent);
  int32_t GetParent() const noexcept;
  void SetChildLeft(const int32_t child_left);
  int32_t GetChildLeft() const noexcept;
  void SetChildRight(const int32_t child_right);
  int32_t GetChildRight() const noexcept;

  void ResetChildLeft() noexcept;
  void ResetChildRight() noexcept;

  NodeType GetNodeType() const;
  bool DoesNotHaveAnyChildren() const noexcept;
  int32_t GetDegree() const noexcept;

  static bool IsInvalidNodeIndex(const int32_t index) noexcept;
  static bool IsValidNodeIndex(const int32_t index) noexcept;
  static bool IsInvalidParent(const int32_t parent_index) noexcept;

 private:
  bool is_valid_;
  int32_t parent_;
  int32_t child_left_;
  int32_t child_right_;
  int32_t key_;

 private:
  FRIEND_TEST(Test_ALDS1_8_C, NodeConstructors);  // Should be removed from production code
};

class BinarySearchTree {
 public:
  BinarySearchTree() noexcept;
  ~BinarySearchTree() noexcept;

  void Insert(const int32_t key);
  int32_t Find(const int32_t key) const;
  void Delete(const int32_t key);
  void Print() const;
  void Debug() const;

  static bool NotFound(const int32_t found_index);

 private:
  int32_t AllocateNode(const int32_t key);
  void InsertToChild(const int32_t inserted_index, const int32_t parent_index);
  int32_t FindRecursively(const int32_t key, const int32_t find_at) const;
  void MapLeftChild(const int32_t parent_index, const int32_t left_child_index);
  void MapRightChild(const int32_t parent_index, const int32_t right_child_index);
  void UnmapChildFromParent(const int32_t parent_index, const int32_t child_index);
  void BypassParentAndChild(const int32_t parent_index, const int32_t current_child_index,
                            const int32_t new_child_index);
  bool IsLeftChild(const int32_t parent_index, const int32_t child_index) const;
  bool IsRightChild(const int32_t parent_index, const int32_t child_index) const;
  void DeleteByIndex(const int32_t index_to_be_deleted);

  int32_t CalculateDepth(const int32_t index_node) const;
  int32_t CalculateHeight(const int32_t index_node) const;
  void SetTopNode(const int32_t top_node_index);
  int32_t GetSibling(const int32_t index) const;

  void WalkPreorder(const int32_t node_index) const;
  void WalkInorder(const int32_t node_index) const;
  int32_t GetNextNodeIndexInorder(const int32_t walk_from, const int32_t target_node);

  BinarySearchTree(const BinarySearchTree &obj) = delete;
  BinarySearchTree &operator=(const BinarySearchTree &obj) = delete;
  BinarySearchTree(BinarySearchTree &&obj) = delete;
  BinarySearchTree &operator=(BinarySearchTree &&obj) = delete;

 private:
  int32_t root_;
  int32_t size_;
  Node nodes_[kMaxNumberOfNodes];

 private:
  FRIEND_TEST(Test_ALDS1_8_C, BinarySearchTree_AddNode);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_8_C, GetNextNodeIndexInorder);   // Should be removed from production code
};

}  // namespace ALDS1_8_C

#endif  // SRC_C09_4_ALDS1_8_C_BINARY_SEARCH_TREE_3_H_
