/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-5. 木、木の復元(Reconstruction of the Tree)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C08_5_ALDS1_7_D_RECONSTRUCT_TREE_H_
#define SRC_C08_5_ALDS1_7_D_RECONSTRUCT_TREE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_7_D {

constexpr int32_t kMaxNumberOfNodes = 100;
constexpr int32_t kTop = -1;
constexpr int32_t kInvalid = -2;

enum class NodeType : int32_t { kInternal = 0, kLeaf, kRoot };

void CallTreeReconstruction(std::istream &input_stream);

int32_t ConvertFromNodeNumberToNodeIndex(const int32_t node_number);
int32_t ConvertFromNodeIndexToNodeNumber(const int32_t node_index);

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
  FRIEND_TEST(Test_ALDS1_7_D, NodeConstructors);  // Should be removed from production code
};

struct IndexRange {
  int32_t start{-1};
  int32_t end{-1};
};

class TreeReconstruction {
 public:
  TreeReconstruction() noexcept;
  ~TreeReconstruction() noexcept;

  void AddResultOfPreorder(const int32_t node_index);
  void AddResultOfInorder(const int32_t node_index);
  void ReconstructTree();
  void ReconstructSubTree(const IndexRange &range_preorder, const IndexRange &range_inorder);

  void AddNode(const int32_t node_index);
  void MapLeftChild(const int32_t parent_index, const int32_t left_child_index);
  void MapRightChild(const int32_t parent_index, const int32_t right_child_index);
  void ConfigureRoot();
  void Print() const;
  void Debug() const;

 private:
  TreeReconstruction(const TreeReconstruction &obj) = delete;
  TreeReconstruction &operator=(const TreeReconstruction &obj) = delete;
  TreeReconstruction(TreeReconstruction &&obj) = delete;
  TreeReconstruction &operator=(TreeReconstruction &&obj) = delete;

  static bool OnlyOneNode(const IndexRange &range);

  int32_t CalculateDepth(const int32_t index_node) const;
  int32_t CalculateHeight(const int32_t index_node) const;
  void SetTopNode(const int32_t top_node_index);
  int32_t GetSibling(const int32_t index) const;
  int32_t FindLocalRootIndexAtInorderResults(const int32_t local_root, const int32_t start_index_in_inorder) const;

  void WalkPostorder(const int32_t node_index) const;

 private:
  int32_t root_;
  int32_t size_;
  Node nodes_[kMaxNumberOfNodes];
  int32_t outputs_preorder_[kMaxNumberOfNodes];
  int32_t size_outputs_preorder_;
  int32_t outputs_inorder_[kMaxNumberOfNodes];
  int32_t size_outputs_inorder_;

 private:
  FRIEND_TEST(Test_ALDS1_7_D, TreeReconstruction_AddNode);  // Should be removed from production code
};

}  // namespace ALDS1_7_D

#endif  // SRC_C08_5_ALDS1_7_D_RECONSTRUCT_TREE_H_
