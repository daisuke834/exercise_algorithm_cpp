/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-2. 木、根付き木の表現(Rooted Trees)。可変長配列＆場所不定版。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "2_ALDS1_7_A_1_rooted_trees.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

namespace ALDS1_7_A_1 {
namespace {
const NodeId kTop(kTopIdValue);
}  // namespace

void CallRootedTrees(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  RootedTrees* rooted_trees = new RootedTrees();
  try {
    int32_t number_of_nodes;
    input_stream >> number_of_nodes;
    for (int32_t index_node = 0; index_node < number_of_nodes; ++index_node) {
      int32_t node_id_number;
      input_stream >> node_id_number;
      const NodeId cnode_id(node_id_number);
      Node cnode(cnode_id);
      int32_t number_of_childs;
      input_stream >> number_of_childs;
      for (int32_t index_child = 0; index_child < number_of_childs; ++index_child) {
        int32_t child_id;
        input_stream >> child_id;
        cnode.AddChildId(NodeId(child_id));
      }
      rooted_trees->AddNode(cnode);
    }
    rooted_trees->Sort();
    rooted_trees->BuildTree();
    rooted_trees->Print();
  } catch (...) {
    std::cerr << "ERROR: CallRootedTrees()" << std::endl;
    throw;
  }
  delete rooted_trees;
}

// ****************************************************

RootedTrees::RootedTrees() noexcept : size_(0) {}
RootedTrees::~RootedTrees() noexcept {}

void RootedTrees::AddNode(const Node& node) {
  if (size_ >= kMaxNumberOfNodes) {
    std::cerr << "ERROR: AddNode(): Data size exceeded a limit = " << kMaxNumberOfNodes << std::endl;
    throw 1;
  }
  nodes_[size_] = node;
  size_++;
}

void RootedTrees::BuildTree() {
  try {
    for (int32_t node_index = 0; node_index < size_; ++node_index) {
      const int32_t cvalue = nodes_[node_index].GetNodeId().GetIdValue();
      map_from_id_to_index_[cvalue] = node_index;
    }

    for (int32_t node_index = 0; node_index < size_; ++node_index) {
      Node& cnode = nodes_[node_index];
      for (int32_t i = 0; i < cnode.GetNumberOfChilds(); ++i) {
        const NodeId child_node_id = cnode.GetChildId(i);
        const int32_t child_node_index = FindNodeIndex(child_node_id);
        nodes_[child_node_index].SetParentId(cnode.GetNodeId());
      }
    }
    int32_t number_of_tops = 0;
    for (int32_t node_index = 0; node_index < size_; ++node_index) {
      if (nodes_[node_index].GetParentId().IsInvalid()) {
        nodes_[node_index].SetParentId(kTop);
        ++number_of_tops;
        if (number_of_tops > 1) {
          std::cerr << "ERROR: BuildTree(): number of tops are greater than zero." << std::endl;
          throw;
        }
      }
    }
  } catch (...) {
    std::cerr << "ERROR: BuildTree()" << std::endl;
    throw;
  }
}

void RootedTrees::Print() const {
  const char node_type_str[][20] = {"internal node", "leaf", "root"};
  try {
    for (int32_t node_index = 0; node_index < size_; ++node_index) {
      const Node& cnode = nodes_[node_index];
      std::cout << "node " << cnode.GetNodeId().GetIdValue() << ": ";
      std::cout << "parent = " << cnode.GetParentId().GetIdValue() << ", ";
      std::cout << "depth = " << CalculateDepth(node_index) << ", ";
      std::cout << node_type_str[static_cast<int32_t>(cnode.GetNodeType())] << ", ";
      std::cout << "[";
      for (int32_t child_node_index = 0; child_node_index < cnode.GetNumberOfChilds(); ++child_node_index) {
        if (child_node_index != 0) {
          std::cout << ", ";
        }
        std::cout << cnode.GetChildId(child_node_index).GetIdValue();
      }
      std::cout << "]" << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: Print()" << std::endl;
    throw;
  }
}

int32_t RootedTrees::FindNodeIndex(const NodeId& node_id) const {
  int32_t found_node_index = -1;
  try {
    found_node_index = map_from_id_to_index_[node_id.GetIdValue()];
  } catch (...) {
    std::cerr << "ERROR: GetNodeIndex()" << std::endl;
    throw;
  }
  if (found_node_index < 0) {
    std::cerr << "ERROR: FindNodeIndex(): Not found id=" << node_id.GetIdValue() << std::endl;
    throw 1;
  }
  return found_node_index;
}

int32_t RootedTrees::CalculateDepth(const int32_t index_node) const {
  int32_t depth = 0;
  int32_t current_index_node = index_node;
  bool was_found = false;
  try {
    for (int32_t i = 0; i < size_; ++i) {
      const NodeId parent_node_id = nodes_[current_index_node].GetParentId();
      if (parent_node_id == kTop) {
        was_found = true;
        break;
      } else {
        current_index_node = FindNodeIndex(parent_node_id);
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

void RootedTrees::Sort() {
  try {
    ComputeMergeSort(0, size_);
  } catch (...) {
    std::cerr << "ERROR: Sort()" << std::endl;
    throw;
  }
}

void RootedTrees::ComputeMergeSort(const int32_t left_end, const int32_t right_end) {
  if ((right_end < left_end) || ((left_end < 0) || (right_end > size_))) {
    std::cerr << "ERROR: ComputeMergeSort: invalid args. left_end=" << left_end << ", right_end=" << right_end
              << std::endl;
    throw 1;
  }
  try {
    if (left_end + 1 < right_end) {
      const int32_t center = GetCenterIndex(left_end, right_end);
      ComputeMergeSort(left_end, center);
      ComputeMergeSort(center, right_end);
      MergeLeftAndRight(left_end, center, right_end);
    } else {
      // DO NOTHING
    }
  } catch (...) {
    std::cerr << "ERROR: ComputeMergeSort()" << std::endl;
    throw;
  }
}

void RootedTrees::MergeLeftAndRight(const int32_t left_end, const int32_t center, const int32_t right_end) {
  // endは右端indexの右一つ隣のindex (無効領域の先頭)left_end(有効) < center(有効) < right_end(無効)
  if (((left_end < 0) || (right_end > size_) || (center <= left_end) || (right_end <= center))) {
    std::cerr << "ERROR: MergeLeftAndRight: invalid args. left_end=" << left_end << ", center=" << center
              << ", right_end=" << right_end << std::endl;
    throw 1;
  }
  const int32_t left_size = center - left_end;
  const int32_t right_size = right_end - center;
  if (left_size > kMaxNumberOfNodes / 2) {
    std::cerr << "ERROR: MergeLeftAndRight: Invalid left_size. left_size=" << left_size << std::endl;
    throw 1;
  } else if (right_size > kMaxNumberOfNodes / 2) {
    std::cerr << "ERROR: MergeLeftAndRight: Invalid right_size. right_size=" << right_size << std::endl;
    throw 1;
  }
  try {
    for (int32_t index_left = 0; index_left < left_size; ++index_left) {
      left_values_[index_left] = nodes_[left_end + index_left];
    }
    left_values_[left_size] = Node(NodeId(INT32_MAX));
    for (int32_t index_right = 0; index_right < right_size; ++index_right) {
      right_values_[index_right] = nodes_[center + index_right];
    }
    right_values_[right_size] = Node(NodeId(INT32_MAX));

    int32_t index_left = 0;
    int32_t index_right = 0;
    for (int32_t index_target = left_end; index_target < right_end; ++index_target) {
      if (left_values_[index_left].GetNodeId().GetIdValue() <= right_values_[index_right].GetNodeId().GetIdValue()) {
        nodes_[index_target] = left_values_[index_left];
        ++index_left;
      } else {
        nodes_[index_target] = right_values_[index_right];
        ++index_right;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: MergeLeftAndRight()" << std::endl;
    throw;
  }
}

int32_t RootedTrees::GetCenterIndex(const int32_t left_end, const int32_t right_end) const {
  // endは右端indexの右一つ隣のindex (無効領域の先頭)left_end(有効) < center(有効) < right_end(無効)
  if ((right_end <= left_end + 1) || ((left_end < 0) || (right_end > size_))) {
    std::cerr << "ERROR: GetCenterIndex: invalid args. left_end=" << left_end << ", right_end=" << right_end
              << std::endl;
    throw 1;
  }
  return (left_end + right_end) / 2;
}

// ****************************************************
Node::Node() noexcept { child_ids_.clear(); }

Node::~Node() noexcept {}

Node::Node(const NodeId& node_id) noexcept : id_(node_id) { child_ids_.clear(); }

Node::Node(const Node& obj) noexcept : id_(obj.id_), parent_id_(obj.parent_id_) {
  this->child_ids_.clear();
  copy(obj.child_ids_.begin(), obj.child_ids_.end(), back_inserter(this->child_ids_));
}

Node& Node::operator=(const Node& rhs) noexcept {
  if (this != &rhs) {
    this->id_ = rhs.id_;
    this->parent_id_ = rhs.parent_id_;
    this->child_ids_.clear();
    copy(rhs.child_ids_.begin(), rhs.child_ids_.end(), back_inserter(this->child_ids_));
  }
  return *this;
}

Node::Node(Node&& obj) noexcept : id_(obj.id_), parent_id_(obj.parent_id_) {
  this->child_ids_.clear();
  copy(obj.child_ids_.begin(), obj.child_ids_.end(), back_inserter(this->child_ids_));
  obj.Reset();
}

Node& Node::operator=(Node&& rhs) noexcept {
  if (this != &rhs) {
    this->id_ = rhs.id_;
    this->parent_id_ = rhs.parent_id_;
    this->child_ids_.clear();
    copy(rhs.child_ids_.begin(), rhs.child_ids_.end(), back_inserter(this->child_ids_));
    rhs.Reset();  // 無効化
  }
  return *this;
}

void Node::Reset() noexcept {
  this->id_.Reset();
  this->parent_id_.Reset();
  this->child_ids_.clear();
}

void Node::SetParentId(const NodeId& parent_id) noexcept { parent_id_ = parent_id; }

void Node::AddChildId(const NodeId& child_id) {
  try {
    child_ids_.push_back(child_id);
  } catch (...) {
    std::cerr << "ERROR: AddChild()" << std::endl;
    throw;
  }
}

int32_t Node::GetNumberOfChilds() const {
  int32_t count;
  try {
    count = static_cast<int32_t>(child_ids_.size());
  } catch (...) {
    std::cerr << "ERROR: GetNumberOfChilds()" << std::endl;
    throw;
  }
  return count;
}

NodeId Node::GetNodeId() const noexcept { return id_; }

NodeId Node::GetParentId() const noexcept { return parent_id_; }

NodeId Node::GetChildId(const int32_t child_index) const {
  if ((child_index < 0) || (child_index >= static_cast<int32_t>(child_ids_.size()))) {
    std::cerr << "ERROR: GetChildId(): invalid child_index=" << child_index << ", size=" << child_ids_.size()
              << std::endl;
    throw 1;
  }
  NodeId id;
  try {
    id = child_ids_[child_index];
  } catch (...) {
    std::cerr << "ERROR: GetChildId(): child_index=" << child_index << std::endl;
    throw;
  }
  return id;
}

NodeType Node::GetNodeType() const noexcept {
  NodeType node_type;
  if (parent_id_ == kTop) {
    node_type = NodeType::kRoot;
  } else if (GetNumberOfChilds() == 0) {
    node_type = NodeType::kLeaf;
  } else {
    node_type = NodeType::kInternal;
  }
  return node_type;
}

// ****************************************************
NodeId::NodeId() noexcept : is_valid_{false}, id_{-1} {}
NodeId::~NodeId() noexcept {}

NodeId::NodeId(const int32_t id_value) noexcept : is_valid_(true), id_(id_value) {}

NodeId::NodeId(const NodeId& obj) noexcept : is_valid_(obj.is_valid_), id_(obj.id_) {}

NodeId& NodeId::operator=(const NodeId& rhs) noexcept {
  if (this != &rhs) {
    this->is_valid_ = rhs.is_valid_;
    this->id_ = rhs.id_;
  }
  return *this;
}

NodeId::NodeId(NodeId&& obj) noexcept : is_valid_(obj.is_valid_), id_(obj.id_) { obj.Reset(); }

NodeId& NodeId::operator=(NodeId&& rhs) noexcept {
  if (this != &rhs) {
    this->is_valid_ = rhs.is_valid_;
    this->id_ = rhs.id_;
    rhs.Reset();  // 無効化
  }
  return *this;
}

void NodeId::Reset() noexcept {
  is_valid_ = false;
  id_ = -1;
}

int32_t NodeId::GetIdValue() const {
  if (!is_valid_) {
    std::cerr << "ERROR: GetIdValue(): invalid ID" << std::endl;
    throw 1;
  }
  return id_;
}

bool NodeId::Equals(const NodeId& obj) const noexcept { return (IsValid() && obj.IsValid() && (this->id_ == obj.id_)); }

bool NodeId::operator==(const NodeId& rhs) const noexcept { return this->Equals(rhs); }

bool NodeId::operator!=(const NodeId& rhs) const noexcept { return !(this->Equals(rhs)); }

bool NodeId::IsValid() const noexcept { return is_valid_; }

bool NodeId::IsInvalid() const noexcept { return (!is_valid_); }

}  // namespace ALDS1_7_A_1
