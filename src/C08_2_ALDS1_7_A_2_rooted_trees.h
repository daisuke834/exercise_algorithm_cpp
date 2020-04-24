/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-2. 木、根付き木の表現(Rooted Trees)。場所固定版＆動的メモリ非使用版。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C08_2_ALDS1_7_A_2_ROOTED_TREES_H_
#define SRC_C08_2_ALDS1_7_A_2_ROOTED_TREES_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_7_A_2 {

constexpr int32_t kMaxNumberOfNodes = 100000;
constexpr int32_t kTop = -1;
constexpr int32_t kInvalid = -2;

enum class NodeType : int32_t { kInternal = 0, kLeaf, kRoot };

void CallRootedTrees(std::istream &input_stream);

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
  void SetParent(const int32_t parent);
  int32_t GetParent() const noexcept;
  void SetChildLeft(const int32_t child_left);
  int32_t GetChildLeft() const noexcept;
  void SetChildRight(const int32_t child_right);
  int32_t GetChildRight() const noexcept;
  void SetSiblingRight(const int32_t sibling_right);
  int32_t GetSiblingRight() const noexcept;
  NodeType GetNodeType() const;

  static bool IsInvalidNodeIndex(const int32_t index) noexcept;
  static bool IsInvalidParent(const int32_t parent_index) noexcept;

 private:
  bool is_valid_;
  int32_t parent_;
  int32_t child_left_edge_;
  int32_t child_right_edge_;
  int32_t sibling_right_;

 private:
  FRIEND_TEST(Test_ALDS1_7_A_2, NodeConstructors);  // Should be removed from production code
};

class RootedTrees {
 public:
  RootedTrees() noexcept;
  ~RootedTrees() noexcept;
  void AddNode(const int32_t node_index);
  void MapChild(const int32_t parent_index, const int32_t child_index);
  void ConfigureRoot();
  void Print() const;

 private:
  RootedTrees(const RootedTrees &obj) = delete;
  RootedTrees &operator=(const RootedTrees &obj) = delete;
  RootedTrees(RootedTrees &&obj) = delete;
  RootedTrees &operator=(RootedTrees &&obj) = delete;

  int32_t CalculateDepth(const int32_t index_node) const;
  void SetTopNode(const int32_t top_node_index);
  bool DoesNotHaveAnyChildren(const int32_t index) const noexcept;
  void InsertSiblingAtRightEnd(const int32_t parent_index, const int32_t inserted_child_index);

 private:
  int32_t root_;
  int32_t size_;
  Node nodes_[kMaxNumberOfNodes];

 private:
  FRIEND_TEST(Test_ALDS1_7_A_2, RootedTrees_AddNode);  // Should be removed from production code
};

}  // namespace ALDS1_7_A_2

#endif  // SRC_C08_2_ALDS1_7_A_2_ROOTED_TREES_H_
