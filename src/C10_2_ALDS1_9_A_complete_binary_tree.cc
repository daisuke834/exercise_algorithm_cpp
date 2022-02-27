/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part10-2. ヒープ、完全二分木(Complete Binary Tree)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C10_2_ALDS1_9_A_complete_binary_tree.h"

#include <iostream>
#include <string>

namespace ALDS1_9_A {

void CallCompleteBinaryTree(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  CompleteBinaryTree* complete_binary_tree = new CompleteBinaryTree();
  try {
    int32_t number_of_nodes;
    input_stream >> number_of_nodes;
    for (int32_t i = 0; i < number_of_nodes; ++i) {
      int32_t key;
      input_stream >> key;
      complete_binary_tree->Add(key);
    }
    complete_binary_tree->Print();
  } catch (...) {
    std::cerr << "ERROR: CallCompleteBinaryTree()" << std::endl;
    throw;
  }
  delete complete_binary_tree;
}

// ****************************************************

CompleteBinaryTree::CompleteBinaryTree() noexcept : size_(0) {}
CompleteBinaryTree::~CompleteBinaryTree() noexcept {}

void CompleteBinaryTree::Add(const int32_t key) {
  if (size_ >= kMaxNumberOfNodes) {
    std::cerr << "ERROR: Add(): Data size exceeded a limit = " << kMaxNumberOfNodes << std::endl;
    throw 1;
  }
  const int32_t store_index = size_;
  ++size_;
  SetKeyByIndex(store_index, key);
}

void CompleteBinaryTree::SetKeyByIndex(const int32_t index, const int32_t key) {
  if (IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: Set(): Invalid arg: index = " << index << std::endl;
    throw 1;
  }
  nodes_[index].key = key;
  nodes_[index].is_valid = true;
}

int32_t CompleteBinaryTree::GetKeyByIndex(const int32_t index) const {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: Set(): Invalid arg: index = " << index << std::endl;
    throw 1;
  }
  return nodes_[index].key;
}

void CompleteBinaryTree::Print() const {
  for (int32_t index = 0; index < size_; ++index) {
    std::cout << "node " << ConvertFromIndexToNodeNumber(index);
    std::cout << ": key = " << GetKeyByIndex(index) << ", ";
    const int32_t parent_index = GetIndexParent(index);
    if (IsValidNodeIndex(parent_index)) {
      std::cout << "parent key = " << GetKeyByIndex(parent_index) << ", ";
    }
    const int32_t child_left_index = GetIndexChildLeft(index);
    if (IsValidNodeIndex(child_left_index)) {
      std::cout << "left key = " << GetKeyByIndex(child_left_index) << ", ";
    }
    const int32_t child_right_index = GetIndexChildRight(index);
    if (IsValidNodeIndex(child_right_index)) {
      std::cout << "right key = " << GetKeyByIndex(child_right_index) << ", ";
    }
    std::cout << std::endl;
  }
}

int32_t CompleteBinaryTree::GetIndexParent(const int32_t index) const {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: GetIndexParent(): Invalid node: index = " << index << std::endl;
    throw 1;
  }
  const int32_t node_number = ConvertFromIndexToNodeNumber(index);
  const int32_t parent = node_number / 2;
  const int32_t parent_index = ((parent == 0) ? kTopIndex : ConvertFromNodeNumberToIndex(parent));
  return parent_index;
}

int32_t CompleteBinaryTree::GetIndexChildLeft(const int32_t index) const {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: GetIndexChildLeft(): Invalid node: index = " << index << std::endl;
    throw 1;
  }
  const int32_t node_number = ConvertFromIndexToNodeNumber(index);
  const int32_t left = node_number * 2;
  int32_t left_index = ConvertFromNodeNumberToIndex(left);
  if (IsInvalidNode(left_index)) {
    left_index = kInvalidIndex;
  }
  return left_index;
}

int32_t CompleteBinaryTree::GetIndexChildRight(const int32_t index) const {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: GetIndexChildLeft(): Invalid node: index = " << index << std::endl;
    throw 1;
  }
  const int32_t node_number = ConvertFromIndexToNodeNumber(index);
  const int32_t right = node_number * 2 + 1;
  int32_t right_index = ConvertFromNodeNumberToIndex(right);
  if (IsInvalidNode(right_index)) {
    right_index = kInvalidIndex;
  }
  return right_index;
}

bool CompleteBinaryTree::IsInvalidNode(const int32_t index) const noexcept { return !IsValidNode(index); }

bool CompleteBinaryTree::IsValidNode(const int32_t index) const noexcept {
  const bool is_valid = IsValidNodeIndex(index) ? nodes_[index].is_valid : false;
  return is_valid;
}

bool CompleteBinaryTree::IsInvalidNodeIndex(const int32_t index) noexcept {
  return ((index < 0) || (index >= kMaxNumberOfNodes));
}

bool CompleteBinaryTree::IsValidNodeIndex(const int32_t index) noexcept { return !IsInvalidNodeIndex(index); }

int32_t CompleteBinaryTree::ConvertFromNodeNumberToIndex(const int32_t node_number) {
  const int32_t index = node_number - 1;
  if (IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: ConvertFromNodeNumberToIndex(): Invalid node: index = " << index << std::endl;
    throw 1;
  }
  return index;
}

int32_t CompleteBinaryTree::ConvertFromIndexToNodeNumber(const int32_t index) {
  if (IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: ConvertFromIndexToNodeNumber(): Invalid node: index = " << index << std::endl;
    throw 1;
  }
  return index + 1;
}

}  // namespace ALDS1_9_A
