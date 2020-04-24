/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-5. 木、木の復元(Reconstruction of the Tree)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C08_5_ALDS1_7_D_reconstruct_tree.h"
#include <iostream>
#include <string>
namespace ALDS1_7_D {

int32_t count;

void CallTreeReconstruction(std::istream &input_stream) {
  count = 0;
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  TreeReconstruction *reconstruct_tree = new TreeReconstruction();
  try {
    int32_t number_of_nodes;
    input_stream >> number_of_nodes;

    for (int32_t i = 0; i < number_of_nodes; ++i) {
      int32_t node_number;
      input_stream >> node_number;
      const int32_t node_index = ConvertFromNodeNumberToNodeIndex(node_number);
      reconstruct_tree->AddResultOfPreorder(node_index);
    }
    for (int32_t i = 0; i < number_of_nodes; ++i) {
      int32_t node_number;
      input_stream >> node_number;
      const int32_t node_index = ConvertFromNodeNumberToNodeIndex(node_number);
      reconstruct_tree->AddResultOfInorder(node_index);
    }
    reconstruct_tree->ReconstructTree();
    reconstruct_tree->Print();
  } catch (...) {
    std::cerr << "ERROR: CallTreeReconstruction()" << std::endl;
    reconstruct_tree->Debug();
    throw;
  }
  delete reconstruct_tree;
}

// ****************************************************

TreeReconstruction::TreeReconstruction() noexcept
    : root_(kInvalid), size_(0), size_outputs_preorder_(0), size_outputs_inorder_(0) {}
TreeReconstruction::~TreeReconstruction() noexcept {}

void TreeReconstruction::ReconstructTree() {
  IndexRange range_preorder;
  range_preorder.start = 0;
  range_preorder.end = size_outputs_preorder_ - 1;
  IndexRange range_inorder;
  range_inorder.start = 0;
  range_inorder.end = size_outputs_preorder_ - 1;
  ReconstructSubTree(range_preorder, range_inorder);
  ConfigureRoot();
}

void TreeReconstruction::ReconstructSubTree(const IndexRange &range_preorder, const IndexRange &range_inorder) {
  try {
    const int32_t local_root_index_in_preorder = range_preorder.start;
    const int32_t local_root = outputs_preorder_[local_root_index_in_preorder];
    AddNode(local_root);
    const int32_t local_root_index_in_inorder = FindLocalRootIndexAtInorderResults(local_root, range_inorder.start);

    const int32_t size_left_subtree = local_root_index_in_inorder - range_inorder.start;
    if (size_left_subtree == 0) {
      // DO NOTHING
    } else if (size_left_subtree == 1) {
      int32_t left_child = outputs_inorder_[range_inorder.start];
      AddNode(left_child);
      MapLeftChild(local_root, left_child);
    } else {
      int32_t next_sub_root = outputs_preorder_[local_root_index_in_preorder + 1];
      MapLeftChild(local_root, next_sub_root);
      IndexRange next_range_preorder;
      next_range_preorder.start = local_root_index_in_preorder + 1;
      next_range_preorder.end = local_root_index_in_preorder + size_left_subtree;
      IndexRange next_range_inorder;
      next_range_inorder.start = range_inorder.start;
      next_range_inorder.end = local_root_index_in_inorder - 1;
      ReconstructSubTree(next_range_preorder, next_range_inorder);
    }

    const int32_t size_right_subtree = range_inorder.end - local_root_index_in_inorder;
    if (size_right_subtree == 0) {
      // DO NOTHING
    } else if (size_right_subtree == 1) {
      int32_t right_child = outputs_inorder_[range_inorder.end];
      AddNode(right_child);
      MapRightChild(local_root, right_child);
    } else {
      int32_t next_sub_root = outputs_preorder_[local_root_index_in_preorder + 1 + size_left_subtree];
      MapRightChild(local_root, next_sub_root);
      IndexRange next_range_preorder;
      next_range_preorder.start = range_preorder.end - size_right_subtree + 1;
      next_range_preorder.end = range_preorder.end;
      IndexRange next_range_inorder;
      next_range_inorder.start = local_root_index_in_inorder + 1;
      next_range_inorder.end = range_inorder.end;
      ReconstructSubTree(next_range_preorder, next_range_inorder);
    }
  } catch (...) {
    std::cerr << "ERROR: ReconstructSubTree()" << std::endl;
    throw;
  }
}

void TreeReconstruction::Print() const {
  try {
    WalkPostorder(root_);
    std::cout << std::endl;
  } catch (...) {
    std::cerr << "ERROR: Print()" << std::endl;
    throw;
  }
}

int32_t TreeReconstruction::FindLocalRootIndexAtInorderResults(const int32_t local_root,
                                                               const int32_t start_index_in_inorder) const {
  int32_t found_index = -1;
  for (int32_t index = start_index_in_inorder; index < size_outputs_inorder_; ++index) {
    if (outputs_inorder_[index] == local_root) {
      found_index = index;
      break;
    }
  }
  if (found_index < 0) {
    std::cerr << "ERROR: FindLocalRootIndexAtInorderResults(): Not found. local_root=" << local_root
              << ", start_index_in_inorder=" << start_index_in_inorder
              << ", size_outputs_inorder_=" << size_outputs_inorder_ << std::endl;
    throw 1;
  }
  return found_index;
}

bool TreeReconstruction::OnlyOneNode(const IndexRange &range) {
  if (Node::IsInvalidNodeIndex(range.start)) {
    std::cerr << "ERROR: AddResultOfPreorder(): Invalid arg: range.start = " << range.start << std::endl;
    throw 1;
  } else if (Node::IsInvalidNodeIndex(range.end)) {
    std::cerr << "ERROR: AddResultOfPreorder(): Invalid arg: range.end = " << range.end << std::endl;
    throw 1;
  } else if (range.end < range.start) {
    std::cerr << "ERROR: AddResultOfPreorder(): Invalid arg: range.start = " << range.start
              << ", range.start = " << range.start << std::endl;
    throw 1;
  }
  return (range.start == range.end);
}

void TreeReconstruction::AddResultOfPreorder(const int32_t node_index) {
  if (Node::IsInvalidNodeIndex(node_index)) {
    std::cerr << "ERROR: AddResultOfPreorder(): Invalid arg: node_index = " << node_index << std::endl;
    throw 1;
  } else if (size_outputs_preorder_ >= kMaxNumberOfNodes) {
    std::cerr << "ERROR: AddResultOfPreorder(): Data size exceeded a limit = " << kMaxNumberOfNodes << std::endl;
    throw 1;
  }
  outputs_preorder_[size_outputs_preorder_] = node_index;
  ++size_outputs_preorder_;
}

void TreeReconstruction::AddResultOfInorder(const int32_t node_index) {
  if (Node::IsInvalidNodeIndex(node_index)) {
    std::cerr << "ERROR: AddResultOfInorder(): Invalid arg: node_index = " << node_index << std::endl;
    throw 1;
  } else if (size_outputs_inorder_ >= kMaxNumberOfNodes) {
    std::cerr << "ERROR: AddResultOfInorder(): Data size exceeded a limit = " << kMaxNumberOfNodes << std::endl;
    throw 1;
  }
  outputs_inorder_[size_outputs_inorder_] = node_index;
  ++size_outputs_inorder_;
}

void TreeReconstruction::AddNode(const int32_t node_index) {
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

void TreeReconstruction::MapLeftChild(const int32_t parent_index, const int32_t left_child_index) {
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

void TreeReconstruction::MapRightChild(const int32_t parent_index, const int32_t right_child_index) {
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

void TreeReconstruction::ConfigureRoot() {
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

void TreeReconstruction::WalkPostorder(const int32_t node_index) const {
  // Postorder Tree Walk (後行順巡回)
  if (Node::IsInvalidNodeIndex(node_index)) {
    std::cerr << "ERROR: WalkPostorder(): Invalid arg node_index = " << node_index << std::endl;
    throw 1;
  }
  try {
    const int32_t left_child = nodes_[node_index].GetChildLeft();
    if (Node::IsValidNodeIndex(left_child)) {
      WalkPostorder(left_child);
    }

    const int32_t right_child = nodes_[node_index].GetChildRight();
    if (Node::IsValidNodeIndex(right_child)) {
      WalkPostorder(right_child);
    }

    if (count != 0) {
      std::cout << " ";
    }
    std::cout << ConvertFromNodeIndexToNodeNumber(node_index);
    ++count;
  } catch (...) {
    std::cerr << "ERROR: WalkPostorder()" << std::endl;
    throw 1;
  }
}

int32_t TreeReconstruction::GetSibling(const int32_t index) const {
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
      const Node &parent = nodes_[parent_index];
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

int32_t TreeReconstruction::CalculateDepth(const int32_t index_node) const {
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

int32_t TreeReconstruction::CalculateHeight(const int32_t index_node) const {
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

void TreeReconstruction::SetTopNode(const int32_t top_node_index) {
  try {
    nodes_[top_node_index].SetParent(kTop);
    root_ = top_node_index;
  } catch (...) {
    std::cerr << "ERROR: SetTopNode()" << std::endl;
    throw;
  }
}

void TreeReconstruction::Debug() const {
  const char node_type_str[][20] = {"internal node", "leaf", "root"};
  try {
    for (int32_t current_node_index = 0; current_node_index < size_; ++current_node_index) {
      const Node &cnode = nodes_[current_node_index];
      std::cerr << "node " << ConvertFromNodeIndexToNodeNumber(current_node_index) << ": ";
      std::cerr << "parent = " << ConvertFromNodeIndexToNodeNumber(cnode.GetParent()) << ", ";
      std::cerr << "sibling = " << ConvertFromNodeIndexToNodeNumber(GetSibling(current_node_index)) << ", ";
      std::cerr << "degree = " << cnode.GetDegree() << ", ";
      std::cerr << "depth = " << CalculateDepth(current_node_index) << ", ";
      std::cerr << "height = " << CalculateHeight(current_node_index) << ", ";
      std::cerr << node_type_str[static_cast<int32_t>(cnode.GetNodeType())] << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: Print()" << std::endl;
    throw;
  }
}

// ****************************************************
Node::Node() noexcept : is_valid_(false), parent_(kInvalid), child_left_(kInvalid), child_right_(kInvalid) {}

Node::~Node() noexcept {}

Node::Node(const Node &obj) noexcept
    : is_valid_(obj.is_valid_), parent_(obj.parent_), child_left_(obj.child_left_), child_right_(obj.child_right_) {}

Node &Node::operator=(const Node &rhs) noexcept {
  if (this != &rhs) {
    this->is_valid_ = rhs.is_valid_;
    this->parent_ = rhs.parent_;
    this->child_left_ = rhs.child_left_;
    this->child_right_ = rhs.child_right_;
  }
  return *this;
}

Node::Node(Node &&obj) noexcept
    : is_valid_(obj.is_valid_), parent_(obj.parent_), child_left_(obj.child_left_), child_right_(obj.child_right_) {
  obj.Reset();
}

Node &Node::operator=(Node &&rhs) noexcept {
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

void Node::Activate() noexcept {
  is_valid_ = true;
}

bool Node::IsValid() const noexcept {
  return is_valid_;
}

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

int32_t Node::GetParent() const noexcept {
  return parent_;
}

bool Node::IsInvalidParent(const int32_t parent_index) noexcept {
  return ((parent_index != kTop) && IsInvalidNodeIndex(parent_index));
}

void Node::SetChildLeft(const int32_t child_left) {
  if (IsInvalidNodeIndex(child_left)) {
    std::cerr << "ERROR: SetChildLeft(): Invalid arg: child_left = " << child_left << std::endl;
    throw 1;
  } else {
    child_left_ = child_left;
  }
}

int32_t Node::GetChildLeft() const noexcept {
  return child_left_;
}

void Node::SetChildRight(const int32_t child_right) {
  if (IsInvalidNodeIndex(child_right)) {
    std::cerr << "ERROR: SetChildRight(): Invalid arg: child_right = " << child_right << std::endl;
    throw 1;
  } else {
    child_right_ = child_right;
  }
}

int32_t Node::GetChildRight() const noexcept {
  return child_right_;
}

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

bool Node::IsInvalidNodeIndex(const int32_t index) noexcept {
  return ((index < 0) || (index >= kMaxNumberOfNodes));
}

bool Node::IsValidNodeIndex(const int32_t index) noexcept {
  return !IsInvalidNodeIndex(index);
}

int32_t ConvertFromNodeNumberToNodeIndex(const int32_t node_number) {
  if (node_number <= 0) {
    std::cerr << "ERROR: ConvertFromNodeNumberToNodeIndex(): Invalid node_number = " << node_number << std::endl;
    throw 1;
  }
  return node_number - 1;
}

int32_t ConvertFromNodeIndexToNodeNumber(const int32_t node_index) {
  int32_t number;
  try {
    if (node_index == kTop) {
      number = -1;
    } else if (node_index == kInvalid) {
      number = -1;
    } else if (Node::IsInvalidNodeIndex(node_index)) {
      std::cerr << "ERROR: ConvertFromNodeIndexToNodeNumber(): Invalid node_index = " << node_index << std::endl;
      throw 1;
    } else {
      number = node_index + 1;
    }
  } catch (...) {
    std::cerr << "ERROR: ConvertFromNodeIndexToNodeNumber()" << std::endl;
    throw;
  }
  return number;
}

}  // namespace ALDS1_7_D
