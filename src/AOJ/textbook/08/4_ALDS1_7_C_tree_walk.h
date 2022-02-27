/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-4. 木、木の巡回(Tree Walk)。
 * Preorder Tree Walk(先行順巡回)/Inorder Tree Walk(中間順巡回)/Postorder Tree Walk(後行順巡回)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C08_4_ALDS1_7_C_TREE_WALK_H_
#define SRC_C08_4_ALDS1_7_C_TREE_WALK_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_7_C {

constexpr int32_t kMaxNumberOfNodes = 100;
constexpr int32_t kTop = -1;
constexpr int32_t kInvalid = -2;

enum class NodeType : int32_t { kInternal = 0, kLeaf, kRoot };

void CallTreeWalk(std::istream& input_stream);

class Node {
 public:
  Node() noexcept;
  ~Node() noexcept;
  Node(const Node& obj) noexcept;
  Node& operator=(const Node& rhs) noexcept;
  Node(Node&& obj) noexcept;
  Node& operator=(Node&& rhs) noexcept;

  void Activate() noexcept;
  bool IsValid() const noexcept;
  void Reset() noexcept;
  void SetParent(const int32_t parent);
  int32_t GetParent() const noexcept;
  void SetChildLeft(const int32_t child_left);
  int32_t GetChildLeft() const noexcept;
  void SetChildRight(const int32_t child_right);
  int32_t GetChildRight() const noexcept;
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

 private:
  FRIEND_TEST(Test_ALDS1_7_C, NodeConstructors);  // Should be removed from production code
};

class TreeWalk {
 public:
  TreeWalk() noexcept;
  ~TreeWalk() noexcept;
  void AddNode(const int32_t node_index);
  void MapLeftChild(const int32_t parent_index, const int32_t left_child_index);
  void MapRightChild(const int32_t parent_index, const int32_t right_child_index);
  void ConfigureRoot();
  void Print() const;

 private:
  TreeWalk(const TreeWalk& obj) = delete;
  TreeWalk& operator=(const TreeWalk& obj) = delete;
  TreeWalk(TreeWalk&& obj) = delete;
  TreeWalk& operator=(TreeWalk&& obj) = delete;

  int32_t CalculateDepth(const int32_t index_node) const;
  int32_t CalculateHeight(const int32_t index_node) const;
  void SetTopNode(const int32_t top_node_index);
  int32_t GetSibling(const int32_t index) const;

  void WalkPreorder(const int32_t node_index) const;
  void WalkInorder(const int32_t node_index) const;
  void WalkPostorder(const int32_t node_index) const;

 private:
  int32_t root_;
  int32_t size_;
  Node nodes_[kMaxNumberOfNodes];

 private:
  FRIEND_TEST(Test_ALDS1_7_C, TreeWalk_AddNode);  // Should be removed from production code
};

}  // namespace ALDS1_7_C

#endif  // SRC_C08_4_ALDS1_7_C_TREE_WALK_H_
