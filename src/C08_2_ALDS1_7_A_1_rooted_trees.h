/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-2. 木、根付き木の表現(Rooted Trees)。可変長配列＆場所不定版。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C08_2_ALDS1_7_A_1_ROOTED_TREES_H_
#define SRC_C08_2_ALDS1_7_A_1_ROOTED_TREES_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace ALDS1_7_A_1 {

constexpr int32_t kMaxNumberOfNodes = 100000;
constexpr int32_t kTopIdValue = -1;

enum class NodeType : int32_t { kInternal = 0, kLeaf, kRoot };

void CallRootedTrees(std::istream &input_stream);

class NodeId {
 public:
  NodeId() noexcept;
  ~NodeId() noexcept;
  explicit NodeId(const int32_t id_value) noexcept;
  NodeId(const NodeId &obj) noexcept;
  NodeId &operator=(const NodeId &rhs) noexcept;
  NodeId(NodeId &&obj) noexcept;
  NodeId &operator=(NodeId &&rhs) noexcept;

  int32_t GetIdValue() const;
  bool Equals(const NodeId &obj) const noexcept;
  bool operator==(const NodeId &rhs) const noexcept;
  bool operator!=(const NodeId &rhs) const noexcept;
  bool IsValid() const noexcept;
  bool IsInvalid() const noexcept;
  void Reset() noexcept;

 private:
  bool is_valid_;
  int32_t id_;
};

class Node {
 public:
  Node() noexcept;
  ~Node() noexcept;
  explicit Node(const NodeId &node_id) noexcept;
  Node(const Node &obj) noexcept;
  Node &operator=(const Node &rhs) noexcept;
  Node(Node &&obj) noexcept;
  Node &operator=(Node &&rhs) noexcept;

  void SetParentId(const NodeId &parent_id) noexcept;
  void AddChildId(const NodeId &child_id);
  int32_t GetNumberOfChilds() const;
  NodeId GetNodeId() const noexcept;
  NodeId GetParentId() const noexcept;
  NodeId GetChildId(const int32_t child_index) const;
  void Reset() noexcept;
  NodeType GetNodeType() const noexcept;

 private:
  NodeId id_;
  NodeId parent_id_;
  std::vector<NodeId> child_ids_;

 private:
  // FRIEND_TEST(Test_ALDS1_7_A_1, Node);  // Should be removed from production code
};

class RootedTrees {
 public:
  RootedTrees() noexcept;
  ~RootedTrees() noexcept;
  void AddNode(const Node &node);
  void Sort();
  void BuildTree();
  void Print() const;

 private:
  RootedTrees(const RootedTrees &obj) = delete;
  RootedTrees &operator=(const RootedTrees &obj) = delete;
  RootedTrees(RootedTrees &&obj) = delete;
  RootedTrees &operator=(RootedTrees &&obj) = delete;

  int32_t FindNodeIndex(const NodeId &node_id) const;
  int32_t CalculateDepth(const int32_t index_node) const;
  void ComputeMergeSort(const int32_t left_end, const int32_t right_end);
  void MergeLeftAndRight(const int32_t left_end, const int32_t center, const int32_t right_end);
  int32_t GetCenterIndex(const int32_t left_end, const int32_t right_end) const;

 private:
  int32_t size_;
  Node nodes_[kMaxNumberOfNodes];
  int32_t map_from_id_to_index_[kMaxNumberOfNodes];
  Node left_values_[kMaxNumberOfNodes / 2 + 1];   //< 作業領域
  Node right_values_[kMaxNumberOfNodes / 2 + 1];  //< 作業領域

 private:
  FRIEND_TEST(Test_ALDS1_7_A_1, RootedTrees_AddNode);  // Should be removed from production code
};

}  // namespace ALDS1_7_A_1

#endif  // SRC_C08_2_ALDS1_7_A_1_ROOTED_TREES_H_
