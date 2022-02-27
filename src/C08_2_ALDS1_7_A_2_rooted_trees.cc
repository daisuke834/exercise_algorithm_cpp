/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-2. 木、根付き木の表現(Rooted Trees)。場所固定版＆動的メモリ非使用版。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C08_2_ALDS1_7_A_2_rooted_trees.h"

#include <iostream>
#include <string>

namespace ALDS1_7_A_2 {

void CallRootedTrees(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  RootedTrees* rooted_trees = new RootedTrees();
  try {
    int32_t number_of_nodes;
    input_stream >> number_of_nodes;
    for (int32_t i = 0; i < number_of_nodes; ++i) {
      int32_t current_node_index;
      input_stream >> current_node_index;
      rooted_trees->AddNode(current_node_index);
      int32_t number_of_childs;
      input_stream >> number_of_childs;
      for (int32_t i = 0; i < number_of_childs; ++i) {
        int32_t child_index;
        input_stream >> child_index;
        rooted_trees->MapChild(current_node_index, child_index);
      }
    }
    rooted_trees->ConfigureRoot();
    rooted_trees->Print();
  } catch (...) {
    std::cerr << "ERROR: CallRootedTrees()" << std::endl;
    throw;
  }
  delete rooted_trees;
}

// ****************************************************

RootedTrees::RootedTrees() noexcept : root_(kInvalid), size_(0) {}
RootedTrees::~RootedTrees() noexcept {}

void RootedTrees::AddNode(const int32_t node_index) {
  if (Node::IsInvalidNodeIndex(node_index)) {
    std::cerr << "ERROR: AddNode(): Invalid arg: node_index = " << node_index << std::endl;
    throw 1;
  } else if (nodes_[node_index].IsValid()) {
    std::cerr << "ERROR: AddNode(): Node " << node_index << "was already added." << std::endl;
    throw 1;
  } else if (size_ >= kMaxNumberOfNodes) {
    std::cerr << "ERROR: AddNode(): Data size exceeded a limit = " << kMaxNumberOfNodes << std::endl;
    throw 1;
  } else {
    nodes_[node_index].Activate();
    size_++;
  }
}

void RootedTrees::MapChild(const int32_t parent_index, const int32_t child_index) {
  if (Node::IsInvalidNodeIndex(parent_index)) {
    std::cerr << "ERROR: MapChild(): Invalid arg: parent_index = " << parent_index << std::endl;
    throw 1;
  } else if (Node::IsInvalidNodeIndex(child_index)) {
    std::cerr << "ERROR: MapChild(): Invalid arg: child_index = " << child_index << std::endl;
    throw 1;
  } else {
    try {
      nodes_[child_index].SetParent(parent_index);
      if (DoesNotHaveAnyChildren(parent_index)) {
        nodes_[parent_index].SetChildLeft(child_index);
      } else {
        InsertSiblingAtRightEnd(parent_index, child_index);
      }
    } catch (...) {
      std::cerr << "ERROR: MapChild()" << std::endl;
      throw;
    }
  }
}

void RootedTrees::InsertSiblingAtRightEnd(const int32_t parent_index, const int32_t inserted_child_index) {
  const int32_t current_child_right_edge = nodes_[parent_index].GetChildRight();
  if (Node::IsInvalidNodeIndex(current_child_right_edge)) {
    std::cerr << "ERROR: InsertSiblingAtRightEnd(): invalid right_edge = " << current_child_right_edge << std::endl;
    throw 1;
  }
  try {
    nodes_[current_child_right_edge].SetSiblingRight(inserted_child_index);
    nodes_[parent_index].SetChildRight(inserted_child_index);
  } catch (...) {
    std::cerr << "ERROR: InsertSiblingAtRightEnd()" << std::endl;
    throw;
  }
}

void RootedTrees::ConfigureRoot() {
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

void RootedTrees::Print() const {
  const char node_type_str[][20] = {"internal node", "leaf", "root"};
  try {
    for (int32_t current_node_index = 0; current_node_index < size_; ++current_node_index) {
      const Node& cnode = nodes_[current_node_index];
      std::cout << "node " << current_node_index << ": ";
      std::cout << "parent = " << cnode.GetParent() << ", ";
      std::cout << "depth = " << CalculateDepth(current_node_index) << ", ";
      std::cout << node_type_str[static_cast<int32_t>(cnode.GetNodeType())] << ", ";
      std::cout << "[";
      bool abnormal_loop_end = true;
      int32_t current_child_index = cnode.GetChildLeft();
      for (int32_t i = 0; i < kMaxNumberOfNodes; ++i) {
        if (Node::IsInvalidNodeIndex(current_child_index)) {
          abnormal_loop_end = false;
          break;
        }
        if (i != 0) {
          std::cout << ", ";
        }
        std::cout << current_child_index;
        current_child_index = nodes_[current_child_index].GetSiblingRight();
      }
      std::cout << "]" << std::endl;
      if (abnormal_loop_end) {
        std::cerr << "ERROR: Print(): loop was not correctly completed" << std::endl;
        throw 1;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: Print()" << std::endl;
    throw;
  }
}

int32_t RootedTrees::CalculateDepth(const int32_t index_node) const {
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

void RootedTrees::SetTopNode(const int32_t top_node_index) {
  try {
    nodes_[top_node_index].SetParent(kTop);
    root_ = top_node_index;
  } catch (...) {
    std::cerr << "ERROR: SetTopNode()" << std::endl;
    throw;
  }
}

bool RootedTrees::DoesNotHaveAnyChildren(const int32_t index) const noexcept {
  return (nodes_[index].GetChildLeft() == kInvalid);
}

// ****************************************************
Node::Node() noexcept
    : is_valid_(false),
      parent_(kInvalid),
      child_left_edge_(kInvalid),
      child_right_edge_(kInvalid),
      sibling_right_(kInvalid) {}

Node::~Node() noexcept {}

Node::Node(const Node& obj) noexcept
    : is_valid_(obj.is_valid_),
      parent_(obj.parent_),
      child_left_edge_(obj.child_left_edge_),
      child_right_edge_(obj.child_right_edge_),
      sibling_right_(obj.sibling_right_) {}

Node& Node::operator=(const Node& rhs) noexcept {
  if (this != &rhs) {
    this->is_valid_ = rhs.is_valid_;
    this->parent_ = rhs.parent_;
    this->child_left_edge_ = rhs.child_left_edge_;
    this->child_right_edge_ = rhs.child_right_edge_;
    this->sibling_right_ = rhs.sibling_right_;
  }
  return *this;
}

Node::Node(Node&& obj) noexcept
    : is_valid_(obj.is_valid_),
      parent_(obj.parent_),
      child_left_edge_(obj.child_left_edge_),
      child_right_edge_(obj.child_right_edge_),
      sibling_right_(obj.sibling_right_) {
  obj.Reset();
}

Node& Node::operator=(Node&& rhs) noexcept {
  if (this != &rhs) {
    this->is_valid_ = rhs.is_valid_;
    this->parent_ = rhs.parent_;
    this->child_left_edge_ = rhs.child_left_edge_;
    this->child_right_edge_ = rhs.child_right_edge_;
    this->sibling_right_ = rhs.sibling_right_;
    rhs.Reset();  // 無効化
  }
  return *this;
}

void Node::Reset() noexcept {
  this->is_valid_ = false;
  this->parent_ = kInvalid;
  this->child_left_edge_ = kInvalid;
  this->child_right_edge_ = kInvalid;
  this->sibling_right_ = kInvalid;
}

void Node::Activate() noexcept { is_valid_ = true; }

bool Node::IsValid() const noexcept { return is_valid_; }

void Node::SetParent(const int32_t parent) {
  if (IsInvalidParent(parent)) {
    std::cerr << "ERROR: SetParent(): Invalid arg: parent = " << parent << std::endl;
    throw 1;
  }
  parent_ = parent;
}

int32_t Node::GetParent() const noexcept { return parent_; }

bool Node::IsInvalidParent(const int32_t parent_index) noexcept {
  return ((parent_index != kTop) && IsInvalidNodeIndex(parent_index));
}

void Node::SetChildLeft(const int32_t child_left) {
  if (IsInvalidNodeIndex(child_left)) {
    std::cerr << "ERROR: SetChildLeft(): Invalid arg: child_left = " << child_left << std::endl;
    throw 1;
  }
  child_left_edge_ = child_left;
  child_right_edge_ = child_left;
}

int32_t Node::GetChildLeft() const noexcept { return child_left_edge_; }

void Node::SetChildRight(const int32_t child_right) {
  if (IsInvalidNodeIndex(child_right)) {
    std::cerr << "ERROR: SetChildRight(): Invalid arg: child_right = " << child_right << std::endl;
    throw 1;
  } else if (IsInvalidNodeIndex(child_left_edge_)) {
    std::cerr << "ERROR: SetChildRight(): child_left_edge is not configured yet." << std::endl;
    throw 1;
  } else {
    child_right_edge_ = child_right;
  }
}

int32_t Node::GetChildRight() const noexcept { return child_right_edge_; }

void Node::SetSiblingRight(const int32_t sibling_right) {
  if (IsInvalidNodeIndex(sibling_right)) {
    std::cerr << "ERROR: SetSiblingRight(): Invalid arg: sibling_right = " << sibling_right << std::endl;
    throw 1;
  }
  sibling_right_ = sibling_right;
}

int32_t Node::GetSiblingRight() const noexcept { return sibling_right_; }

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
  } else if (GetChildLeft() == kInvalid) {
    node_type = NodeType::kLeaf;
  } else {
    node_type = NodeType::kInternal;
  }
  return node_type;
}

bool Node::IsInvalidNodeIndex(const int32_t index) noexcept { return ((index < 0) || (index >= kMaxNumberOfNodes)); }

}  // namespace ALDS1_7_A_2
