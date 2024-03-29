/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-3. 木、二分木の表現(Binary Tree)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "3_ALDS1_7_B_binary_tree.h"

#include <iostream>
#include <string>

namespace ALDS1_7_B {

void CallBinaryTree(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  BinaryTree* binary_tree = new BinaryTree();
  try {
    int32_t number_of_nodes;
    input_stream >> number_of_nodes;
    for (int32_t i = 0; i < number_of_nodes; ++i) {
      int32_t current_node_index;
      input_stream >> current_node_index;
      binary_tree->AddNode(current_node_index);
      int32_t child_left_index, child_right_index;
      input_stream >> child_left_index >> child_right_index;
      if (Node::IsValidNodeIndex(child_left_index)) {
        binary_tree->MapLeftChild(current_node_index, child_left_index);
      }
      if (Node::IsValidNodeIndex(child_right_index)) {
        binary_tree->MapRightChild(current_node_index, child_right_index);
      }
    }
    binary_tree->ConfigureRoot();
    binary_tree->Print();
  } catch (...) {
    std::cerr << "ERROR: CallBinaryTree()" << std::endl;
    throw;
  }
  delete binary_tree;
}

// ****************************************************

BinaryTree::BinaryTree() noexcept : root_(kInvalid), size_(0) {}
BinaryTree::~BinaryTree() noexcept {}

void BinaryTree::AddNode(const int32_t node_index) {
  if (Node::IsInvalidNodeIndex(node_index)) {
    std::cerr << "ERROR: AddNode(): Invalid arg: node_index = " << node_index << std::endl;
    throw 1;
  } else if (nodes_[node_index].IsValid()) {
    std::cerr << "ERROR: AddNode(): Node " << node_index << " was already added." << std::endl;
    throw 1;
  } else if (size_ >= kMaxNumberOfNodes) {
    std::cerr << "ERROR: AddNode(): Data size exceeded a limit = " << kMaxNumberOfNodes << std::endl;
    throw 1;
  } else {
    nodes_[node_index].Activate();
    size_++;
  }
}

void BinaryTree::MapLeftChild(const int32_t parent_index, const int32_t left_child_index) {
  if (Node::IsInvalidNodeIndex(parent_index)) {
    std::cerr << "ERROR: MapLeftChild(): Invalid arg: parent_index = " << parent_index << std::endl;
    throw 1;
  } else if (Node::IsInvalidNodeIndex(left_child_index)) {
    std::cerr << "ERROR: MapLeftChild(): Invalid arg: left_child_index = " << left_child_index << std::endl;
    throw 1;
  } else {
    try {
      nodes_[left_child_index].SetParent(parent_index);
      nodes_[parent_index].SetChildLeft(left_child_index);
    } catch (...) {
      std::cerr << "ERROR: MapLeftChild()" << std::endl;
      throw;
    }
  }
}

void BinaryTree::MapRightChild(const int32_t parent_index, const int32_t right_child_index) {
  if (Node::IsInvalidNodeIndex(parent_index)) {
    std::cerr << "ERROR: MapRightChild(): Invalid arg: parent_index = " << parent_index << std::endl;
    throw 1;
  } else if (Node::IsInvalidNodeIndex(right_child_index)) {
    std::cerr << "ERROR: MapRightChild(): Invalid arg: right_child_index = " << right_child_index << std::endl;
    throw 1;
  } else {
    try {
      nodes_[right_child_index].SetParent(parent_index);
      nodes_[parent_index].SetChildRight(right_child_index);
    } catch (...) {
      std::cerr << "ERROR: MapRightChild()" << std::endl;
      throw;
    }
  }
}

void BinaryTree::ConfigureRoot() {
  int32_t number_of_root = 0;
  try {
    for (int32_t node_index = 0; node_index < size_; ++node_index) {
      if (nodes_[node_index].GetParent() == kInvalid) {
        SetTopNode(node_index);
        ++number_of_root;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: ConfigureRoot()" << std::endl;
    throw;
  }
  if (number_of_root != 1) {
    std::cerr << "ERROR: ConfigureRoot(): Invalid number_of_root = " << number_of_root << std::endl;
    throw 1;
  }
}

void BinaryTree::Print() const {
  const char node_type_str[][20] = {"internal node", "leaf", "root"};
  try {
    for (int32_t current_node_index = 0; current_node_index < size_; ++current_node_index) {
      const Node& cnode = nodes_[current_node_index];
      std::cout << "node " << current_node_index << ": ";
      std::cout << "parent = " << cnode.GetParent() << ", ";
      std::cout << "sibling = " << GetSibling(current_node_index) << ", ";
      std::cout << "degree = " << cnode.GetDegree() << ", ";
      std::cout << "depth = " << CalculateDepth(current_node_index) << ", ";
      std::cout << "height = " << CalculateHeight(current_node_index) << ", ";
      std::cout << node_type_str[static_cast<int32_t>(cnode.GetNodeType())] << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: Print()" << std::endl;
    throw;
  }
}

int32_t BinaryTree::GetSibling(const int32_t index) const {
  int32_t sibling;
  if (Node::IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: GetSibling(): Invalid arg index = " << index << std::endl;
    throw 1;
  }
  try {
    const int32_t parent_index = nodes_[index].GetParent();
    if (parent_index == kTop) {
      sibling = -1;
    } else {
      const Node& parent = nodes_[parent_index];
      if (parent.GetChildLeft() == index) {
        sibling = parent.GetChildRight() >= 0 ? parent.GetChildRight() : -1;
      } else {
        sibling = parent.GetChildLeft() >= 0 ? parent.GetChildLeft() : -1;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: GetSibling()" << std::endl;
    throw;
  }
  return sibling;
}

int32_t BinaryTree::CalculateDepth(const int32_t index_node) const {
  if (Node::IsInvalidNodeIndex(index_node)) {
    std::cerr << "ERROR: CalculateDepth(): Invalid arg index = " << index_node << std::endl;
    throw 1;
  }
  int32_t depth = 0;
  int32_t current_index_node = index_node;
  bool was_found = false;
  try {
    for (int32_t i = 0; i < size_; ++i) {
      const int32_t parent_node_index = nodes_[current_index_node].GetParent();
      if (parent_node_index == kTop) {
        was_found = true;
        break;
      } else {
        current_index_node = parent_node_index;
        ++depth;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CalculateDepth()" << std::endl;
    throw;
  }
  if (!was_found) {
    std::cerr << "ERROR: CalculateDepth(): root was not found. index=" << index_node << std::endl;
    throw 1;
  }
  return depth;
}

int32_t BinaryTree::CalculateHeight(const int32_t index_node) const {
  if (Node::IsInvalidNodeIndex(index_node)) {
    std::cerr << "ERROR: CalculateHeight(): Invalid arg index = " << index_node << std::endl;
    throw 1;
  }
  int32_t height = 0;
  try {
    const int32_t index_child_left = nodes_[index_node].GetChildLeft();
    int32_t height_from_left = 0;
    if (Node::IsValidNodeIndex(index_child_left)) {
      height_from_left = 1 + CalculateHeight(index_child_left);
    }

    const int32_t index_child_right = nodes_[index_node].GetChildRight();
    int32_t height_from_right = 0;
    if (Node::IsValidNodeIndex(index_child_right)) {
      height_from_right = 1 + CalculateHeight(index_child_right);
    }
    height = height_from_left > height_from_right ? height_from_left : height_from_right;
  } catch (...) {
    std::cerr << "ERROR: CalculateHeight()" << std::endl;
    throw;
  }
  return height;
}

void BinaryTree::SetTopNode(const int32_t top_node_index) {
  try {
    nodes_[top_node_index].SetParent(kTop);
    root_ = top_node_index;
  } catch (...) {
    std::cerr << "ERROR: SetTopNode()" << std::endl;
    throw;
  }
}

// ****************************************************
Node::Node() noexcept : is_valid_(false), parent_(kInvalid), child_left_(kInvalid), child_right_(kInvalid) {}

Node::~Node() noexcept {}

Node::Node(const Node& obj) noexcept
    : is_valid_(obj.is_valid_), parent_(obj.parent_), child_left_(obj.child_left_), child_right_(obj.child_right_) {}

Node& Node::operator=(const Node& rhs) noexcept {
  if (this != &rhs) {
    this->is_valid_ = rhs.is_valid_;
    this->parent_ = rhs.parent_;
    this->child_left_ = rhs.child_left_;
    this->child_right_ = rhs.child_right_;
  }
  return *this;
}

Node::Node(Node&& obj) noexcept
    : is_valid_(obj.is_valid_), parent_(obj.parent_), child_left_(obj.child_left_), child_right_(obj.child_right_) {
  obj.Reset();
}

Node& Node::operator=(Node&& rhs) noexcept {
  if (this != &rhs) {
    this->is_valid_ = rhs.is_valid_;
    this->parent_ = rhs.parent_;
    this->child_left_ = rhs.child_left_;
    this->child_right_ = rhs.child_right_;
    rhs.Reset();  // 無効化
  }
  return *this;
}

void Node::Reset() noexcept {
  this->is_valid_ = false;
  this->parent_ = kInvalid;
  this->child_left_ = kInvalid;
  this->child_right_ = kInvalid;
}

void Node::Activate() noexcept { is_valid_ = true; }

bool Node::IsValid() const noexcept { return is_valid_; }

void Node::SetParent(const int32_t parent) {
  try {
    if (IsInvalidParent(parent)) {
      std::cerr << "ERROR: SetParent(): Invalid arg: parent = " << parent << std::endl;
      throw 1;
    }
    parent_ = parent;
  } catch (...) {
    std::cerr << "ERROR: SetParent()" << std::endl;
    throw;
  }
}

int32_t Node::GetParent() const noexcept { return parent_; }

bool Node::IsInvalidParent(const int32_t parent_index) noexcept {
  return ((parent_index != kTop) && IsInvalidNodeIndex(parent_index));
}

void Node::SetChildLeft(const int32_t child_left) {
  if (IsInvalidNodeIndex(child_left)) {
    std::cerr << "ERROR: SetChildLeft(): Invalid arg: child_left = " << child_left << std::endl;
    throw 1;
  } else if (IsValidNodeIndex(child_left_)) {
    std::cerr << "ERROR: SetChildLeft(): child_left_ is already configured." << std::endl;
    throw 1;
  } else {
    child_left_ = child_left;
  }
}

int32_t Node::GetChildLeft() const noexcept { return child_left_; }

void Node::SetChildRight(const int32_t child_right) {
  if (IsInvalidNodeIndex(child_right)) {
    std::cerr << "ERROR: SetChildRight(): Invalid arg: child_right = " << child_right << std::endl;
    throw 1;
  } else if (IsValidNodeIndex(child_right_)) {
    std::cerr << "ERROR: SetChildRight(): child_right_ is already configured." << std::endl;
    throw 1;
  } else {
    child_right_ = child_right;
  }
}

int32_t Node::GetChildRight() const noexcept { return child_right_; }

int32_t Node::GetDegree() const noexcept {
  int32_t degree = 0;
  degree += IsValidNodeIndex(GetChildLeft()) ? 1 : 0;
  degree += IsValidNodeIndex(GetChildRight()) ? 1 : 0;
  return degree;
}

bool Node::DoesNotHaveAnyChildren() const noexcept {
  const bool does_not_have_left_child = IsInvalidNodeIndex(GetChildLeft());
  const bool does_not_have_right_child = IsInvalidNodeIndex(GetChildRight());
  return (does_not_have_left_child && does_not_have_right_child);
}

NodeType Node::GetNodeType() const {
  if (!IsValid()) {
    std::cerr << "ERROR: GetNodeType(): Not valid node." << std::endl;
    throw 1;
  }
  NodeType node_type;
  if (parent_ == kTop) {
    node_type = NodeType::kRoot;
  } else if (parent_ == kInvalid) {
    std::cerr << "ERROR: GetNodeType(): Invalid parent." << std::endl;
    throw 1;
  } else if (DoesNotHaveAnyChildren()) {
    node_type = NodeType::kLeaf;
  } else {
    node_type = NodeType::kInternal;
  }
  return node_type;
}

bool Node::IsInvalidNodeIndex(const int32_t index) noexcept { return ((index < 0) || (index >= kMaxNumberOfNodes)); }

bool Node::IsValidNodeIndex(const int32_t index) noexcept { return !IsInvalidNodeIndex(index); }

}  // namespace ALDS1_7_B
