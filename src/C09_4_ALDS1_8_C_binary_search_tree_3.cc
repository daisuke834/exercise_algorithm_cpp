/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part9-4. 二分探索木(Binary Search Tree)、削除(Delete)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C09_4_ALDS1_8_C_binary_search_tree_3.h"
#include <iostream>
#include <string>

namespace ALDS1_8_C {

void CallBinarySearchTree(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  BinarySearchTree *binary_search_tree = new BinarySearchTree();
  try {
    int32_t number_of_instructions;
    input_stream >> number_of_instructions;
    for (int32_t index_instruction = 0; index_instruction < number_of_instructions; ++index_instruction) {
      std::string instruction_str;
      input_stream >> instruction_str;
      const InstructionType instruction = JudgeInstructionType(instruction_str);
      switch (instruction) {
        case InstructionType::kInsert:
          int32_t insert_key;
          input_stream >> insert_key;
          binary_search_tree->Insert(insert_key);
          break;
        case InstructionType::kPrint:
          binary_search_tree->Print();
          break;
        case InstructionType::kFind:
          int32_t find_key;
          input_stream >> find_key;
          int32_t found_index;
          found_index = binary_search_tree->Find(find_key);
          PrintFindResult(found_index);
          break;
        case InstructionType::kDelete:
          int32_t delete_key;
          input_stream >> delete_key;
          binary_search_tree->Delete(delete_key);
          break;
        default:
          std::cerr << "ERROR: CallDictionary(): Invalid instruction type." << std::endl;
          break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CallBinarySearchTree()" << std::endl;
    binary_search_tree->Debug();
    throw;
  }
  delete binary_search_tree;
}

void PrintFindResult(const int32_t found_index) {
  if (BinarySearchTree::NotFound(found_index)) {
    std::cout << "no" << std::endl;
  } else {
    std::cout << "yes" << std::endl;
  }
}

// ****************************************************

InstructionType JudgeInstructionType(const std::string &str) {
  InstructionType instruction_type;
  if (str == "insert") {
    instruction_type = InstructionType::kInsert;
  } else if (str == "print") {
    instruction_type = InstructionType::kPrint;
  } else if (str == "find") {
    instruction_type = InstructionType::kFind;
  } else if (str == "delete") {
    instruction_type = InstructionType::kDelete;
  } else {
    std::cerr << "ERROR: JudgeInstructionType(): Invalid input data. " << str << std::endl;
    throw 1;
  }
  return instruction_type;
}

// ****************************************************

BinarySearchTree::BinarySearchTree() noexcept : root_(kInvalid), size_(0) {}
BinarySearchTree::~BinarySearchTree() noexcept {}

void BinarySearchTree::Insert(const int32_t key) {
  const int32_t index = AllocateNode(key);

  if (Node::IsInvalidNodeIndex(root_)) {
    SetTopNode(index);
  } else {
    InsertToChild(index, root_);
  }
}

void BinarySearchTree::InsertToChild(const int32_t inserted_index, const int32_t parent_index) {
  try {
    const Node &parent_node = nodes_[parent_index];
    const int32_t key = nodes_[inserted_index].GetKey();
    if (key < parent_node.GetKey()) {
      const int32_t next_parent = parent_node.GetChildLeft();
      if (Node::IsInvalidNodeIndex(next_parent)) {
        MapLeftChild(parent_index, inserted_index);
      } else {
        InsertToChild(inserted_index, next_parent);
      }
    } else {
      const int32_t next_parent = parent_node.GetChildRight();
      if (Node::IsInvalidNodeIndex(next_parent)) {
        MapRightChild(parent_index, inserted_index);
      } else {
        InsertToChild(inserted_index, next_parent);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: InsertToChild()" << std::endl;
    throw;
  }
}

int32_t BinarySearchTree::Find(const int32_t key) const {
  int32_t found_index;
  try {
    if (Node::IsInvalidNodeIndex(root_)) {
      found_index = kInvalid;
    } else {
      found_index = FindRecursively(key, root_);
    }
  } catch (...) {
    std::cerr << "ERROR: Find(): key = " << key << std::endl;
    throw 1;
  }
  return found_index;
}

int32_t BinarySearchTree::FindRecursively(const int32_t key, const int32_t find_at) const {
  if (Node::IsInvalidNodeIndex(find_at)) {
    std::cerr << "ERROR: MapLeftChild(): Invalid arg: find_at = " << find_at << std::endl;
    throw 1;
  }
  int32_t found_index = kInvalid;
  try {
    if (nodes_[find_at].GetKey() == key) {
      found_index = find_at;
    } else {
      int32_t find_next;
      if (key < nodes_[find_at].GetKey()) {
        find_next = nodes_[find_at].GetChildLeft();
      } else {
        find_next = nodes_[find_at].GetChildRight();
      }
      if (Node::IsValidNodeIndex(find_next)) {
        found_index = FindRecursively(key, find_next);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: FindRecursively(): key = " << key << ", find_at = " << find_at << std::endl;
    throw 1;
  }
  return found_index;
}

bool BinarySearchTree::NotFound(const int32_t found_index) {
  return Node::IsInvalidNodeIndex(found_index);
}

int32_t BinarySearchTree::AllocateNode(const int32_t key) {
  if (size_ >= kMaxNumberOfNodes) {
    std::cerr << "ERROR: AllocateNode(): Data size exceeded a limit = " << kMaxNumberOfNodes << std::endl;
    throw 1;
  }
  const int32_t node_index = size_;
  nodes_[node_index].Activate();
  nodes_[node_index].SetKey(key);
  size_++;
  return node_index;
}

void BinarySearchTree::MapLeftChild(const int32_t parent_index, const int32_t left_child_index) {
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

void BinarySearchTree::MapRightChild(const int32_t parent_index, const int32_t right_child_index) {
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

void BinarySearchTree::Delete(const int32_t key) {
  try {
    const int32_t index_to_be_deleted = Find(key);
    if (NotFound(index_to_be_deleted)) {
      std::cerr << "ERROR: Delete(): Key not found: key = " << key << std::endl;
      throw 1;
    }
    DeleteByIndex(index_to_be_deleted);
  } catch (...) {
    std::cerr << "ERROR: Delete(): key = " << key << std::endl;
    throw;
  }
}

void BinarySearchTree::DeleteByIndex(const int32_t index_to_be_deleted) {
  try {
    if (NotFound(index_to_be_deleted)) {
      std::cerr << "ERROR: DeleteByIndex(): Invalid arg: index_to_be_deleted = " << index_to_be_deleted << std::endl;
      throw 1;
    }
    Node &node_to_be_deleted = nodes_[index_to_be_deleted];
    const int32_t parent_index = node_to_be_deleted.GetParent();
    if (node_to_be_deleted.DoesNotHaveAnyChildren()) {
      UnmapChildFromParent(parent_index, index_to_be_deleted);
      node_to_be_deleted.Reset();
    } else if ((Node::IsValidNodeIndex(node_to_be_deleted.GetChildLeft())) &&
               (Node::IsValidNodeIndex(node_to_be_deleted.GetChildRight()))) {
      const int32_t next_node_inorder = GetNextNodeIndexInorder(root_, index_to_be_deleted);
      const int32_t copied_key = nodes_[next_node_inorder].GetKey();
      nodes_[index_to_be_deleted].SetKey(copied_key);
      DeleteByIndex(next_node_inorder);
    } else if (Node::IsValidNodeIndex(node_to_be_deleted.GetChildLeft())) {
      BypassParentAndChild(parent_index, index_to_be_deleted, node_to_be_deleted.GetChildLeft());
      node_to_be_deleted.Reset();
    } else if (Node::IsValidNodeIndex(node_to_be_deleted.GetChildRight())) {
      BypassParentAndChild(parent_index, index_to_be_deleted, node_to_be_deleted.GetChildRight());
      node_to_be_deleted.Reset();
    } else {
      std::cerr << "ERROR: Delete(): Invalid condition." << std::endl;
      throw 1;
    }
  } catch (...) {
    std::cerr << "ERROR: DeleteByIndex(): index_to_be_deleted = " << index_to_be_deleted << std::endl;
    throw;
  }
}

void BinarySearchTree::UnmapChildFromParent(const int32_t parent_index, const int32_t child_index) {
  try {
    Node &parent = nodes_[parent_index];
    if ((parent_index == kTop || root_ == child_index)) {
      root_ = kInvalid;
    } else if (parent.GetChildLeft() == child_index) {
      parent.ResetChildLeft();
    } else if (parent.GetChildRight() == child_index) {
      parent.ResetChildRight();
    } else {
      std::cerr << "ERROR: UnmapChild(): No child to be deleted. parent = " << parent_index
                << ", child = " << child_index << std::endl;
      throw 1;
    }
  } catch (...) {
    std::cerr << "ERROR: UnmapChild(): parent = " << parent_index << ", child = " << child_index << std::endl;
    throw;
  }
}

void BinarySearchTree::BypassParentAndChild(const int32_t parent_index, const int32_t current_child_index,
                                            const int32_t new_child_index) {
  if (Node::IsInvalidNodeIndex(parent_index)) {
    std::cerr << "ERROR: BypassParentAndChild(): Invalid arg parent_index = " << parent_index << std::endl;
    throw 1;
  } else if (Node::IsInvalidNodeIndex(current_child_index)) {
    std::cerr << "ERROR: BypassParentAndChild(): Invalid arg current_child_index = " << current_child_index
              << std::endl;
    throw 1;
  } else if (Node::IsInvalidNodeIndex(new_child_index)) {
    std::cerr << "ERROR: BypassParentAndChild(): Invalid arg new_child_index = " << new_child_index << std::endl;
    throw 1;
  } else {
    try {
      if (IsLeftChild(parent_index, current_child_index)) {
        MapLeftChild(parent_index, new_child_index);
      } else if (IsRightChild(parent_index, current_child_index)) {
        MapRightChild(parent_index, new_child_index);
      } else {
        std::cerr << "ERROR: BypassParentAndChild() Not a valid child: parent = " << parent_index
                  << ", current_child_index = " << current_child_index << ", new_child_index = " << new_child_index
                  << std::endl;
        throw 1;
      }
    } catch (...) {
      std::cerr << "ERROR: BypassParentAndChild(): parent = " << parent_index
                << ", current_child_index = " << current_child_index << ", new_child_index = " << new_child_index
                << std::endl;
      throw;
    }
  }
}

bool BinarySearchTree::IsLeftChild(const int32_t parent_index, const int32_t child_index) const {
  bool is_left_child = false;
  if (Node::IsInvalidNodeIndex(parent_index)) {
    std::cerr << "ERROR: IsLeftChild(): Invalid arg parent_index = " << parent_index << std::endl;
    throw 1;
  } else if (Node::IsInvalidNodeIndex(child_index)) {
    std::cerr << "ERROR: IsLeftChild(): Invalid arg child_index = " << child_index << std::endl;
    throw 1;
  } else {
    try {
      const Node &parent = nodes_[parent_index];
      if (Node::IsValidNodeIndex(parent.GetChildLeft())) {
        if (parent.GetChildLeft() == child_index) {
          is_left_child = true;
        }
      }
    } catch (...) {
      std::cerr << "ERROR: IsLeftChild(): parent = " << parent_index << ", child = " << child_index << std::endl;
      throw;
    }
  }
  return is_left_child;
}

bool BinarySearchTree::IsRightChild(const int32_t parent_index, const int32_t child_index) const {
  bool is_right_child = false;
  if (Node::IsInvalidNodeIndex(parent_index)) {
    std::cerr << "ERROR: IsRightChild(): Invalid arg parent_index = " << parent_index << std::endl;
    throw 1;
  } else if (Node::IsInvalidNodeIndex(child_index)) {
    std::cerr << "ERROR: IsRightChild(): Invalid arg child_index = " << child_index << std::endl;
    throw 1;
  } else {
    try {
      const Node &parent = nodes_[parent_index];
      if (Node::IsValidNodeIndex(parent.GetChildRight())) {
        if (parent.GetChildRight() == child_index) {
          is_right_child = true;
        }
      }
    } catch (...) {
      std::cerr << "ERROR: IsRightChild(): parent = " << parent_index << ", child = " << child_index << std::endl;
      throw;
    }
  }
  return is_right_child;
}

void BinarySearchTree::Print() const {
  try {
    WalkInorder(root_);
    std::cout << std::endl;
    WalkPreorder(root_);
    std::cout << std::endl;
  } catch (...) {
    std::cerr << "ERROR: Print()" << std::endl;
    throw;
  }
}

void BinarySearchTree::WalkPreorder(const int32_t node_index) const {
  // Preorder Tree Walk (先行順巡回)
  if (Node::IsInvalidNodeIndex(node_index)) {
    std::cerr << "ERROR: WalkPreorder(): Invalid arg node_index = " << node_index << std::endl;
    throw 1;
  }
  try {
    std::cout << " " << nodes_[node_index].GetKey();

    const int32_t left_child = nodes_[node_index].GetChildLeft();
    if (Node::IsValidNodeIndex(left_child)) {
      WalkPreorder(left_child);
    }

    const int32_t right_child = nodes_[node_index].GetChildRight();
    if (Node::IsValidNodeIndex(right_child)) {
      WalkPreorder(right_child);
    }
  } catch (...) {
    std::cerr << "ERROR: WalkPreorder()" << std::endl;
    throw 1;
  }
}

void BinarySearchTree::WalkInorder(const int32_t node_index) const {
  // Inorder Tree Walk (中間順巡回)
  if (Node::IsInvalidNodeIndex(node_index)) {
    std::cerr << "ERROR: WalkInorder(): Invalid arg node_index = " << node_index << std::endl;
    throw 1;
  }
  try {
    const int32_t left_child = nodes_[node_index].GetChildLeft();
    if (Node::IsValidNodeIndex(left_child)) {
      WalkInorder(left_child);
    }

    std::cout << " " << nodes_[node_index].GetKey();

    const int32_t right_child = nodes_[node_index].GetChildRight();
    if (Node::IsValidNodeIndex(right_child)) {
      WalkInorder(right_child);
    }
  } catch (...) {
    std::cerr << "ERROR: WalkInorder()" << std::endl;
    throw 1;
  }
}

int32_t BinarySearchTree::GetNextNodeIndexInorder(const int32_t walk_from, const int32_t target_node) {
  int32_t found_next_node = kInvalid;
  static bool target_was_found_in_order;
  // Inorder Tree Walk (中間順巡回)
  if (Node::IsInvalidNodeIndex(walk_from)) {
    std::cerr << "ERROR: GetNextNodeIndexInorder(): Invalid arg walk_from = " << walk_from << std::endl;
    throw 1;
  } else if (Node::IsInvalidNodeIndex(target_node)) {
    std::cerr << "ERROR: GetNextNodeIndexInorder(): Invalid arg target_node = " << target_node << std::endl;
    throw 1;
  } else {
    try {
      if (walk_from == root_) {
        target_was_found_in_order = false;
      }
      const int32_t left_child = nodes_[walk_from].GetChildLeft();
      if (Node::IsValidNodeIndex(left_child)) {
        found_next_node = GetNextNodeIndexInorder(left_child, target_node);
      }

      if (target_was_found_in_order && Node::IsInvalidNodeIndex(found_next_node)) {
        found_next_node = walk_from;
      } else if (walk_from == target_node) {
        target_was_found_in_order = true;
      } else {
        // DO NOTHING
      }
      if (Node::IsInvalidNodeIndex(found_next_node)) {
        const int32_t right_child = nodes_[walk_from].GetChildRight();
        if (Node::IsValidNodeIndex(right_child)) {
          found_next_node = GetNextNodeIndexInorder(right_child, target_node);
        }
      }
    } catch (...) {
      std::cerr << "ERROR: GetNextNodeIndexInorder()" << std::endl;
      throw 1;
    }
  }
  return found_next_node;
}

int32_t BinarySearchTree::GetSibling(const int32_t index) const {
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

int32_t BinarySearchTree::CalculateDepth(const int32_t index_node) const {
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

int32_t BinarySearchTree::CalculateHeight(const int32_t index_node) const {
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

void BinarySearchTree::SetTopNode(const int32_t top_node_index) {
  try {
    nodes_[top_node_index].SetParent(kTop);
    root_ = top_node_index;
  } catch (...) {
    std::cerr << "ERROR: SetTopNode()" << std::endl;
    throw;
  }
}

void BinarySearchTree::Debug() const {
  const char node_type_str[][20] = {"internal node", "leaf", "root"};
  try {
    std::cerr << "Number of nodes = " << size_ << std::endl;
    std::cerr << "Root = " << root_ << std::endl;
    for (int32_t current_node_index = 0; current_node_index < size_; ++current_node_index) {
      const Node &cnode = nodes_[current_node_index];
      std::cerr << "node " << current_node_index << ": ";
      std::cerr << "key = " << nodes_[current_node_index].GetKey() << ", ";
      std::cerr << "parent = " << cnode.GetParent() << ", ";
      std::cerr << "sibling = " << GetSibling(current_node_index) << ", ";
      std::cerr << "degree = " << cnode.GetDegree() << ", ";
      std::cerr << "depth = " << CalculateDepth(current_node_index) << ", ";
      std::cerr << "height = " << CalculateHeight(current_node_index) << ", ";
      std::cerr << node_type_str[static_cast<int32_t>(cnode.GetNodeType())] << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: Debug()" << std::endl;
    throw;
  }
}

// ****************************************************
Node::Node() noexcept : is_valid_(false), parent_(kInvalid), child_left_(kInvalid), child_right_(kInvalid), key_(0) {}

Node::~Node() noexcept {}

Node::Node(const Node &obj) noexcept
    : is_valid_(obj.is_valid_),
      parent_(obj.parent_),
      child_left_(obj.child_left_),
      child_right_(obj.child_right_),
      key_(obj.key_) {}

Node &Node::operator=(const Node &rhs) noexcept {
  if (this != &rhs) {
    this->is_valid_ = rhs.is_valid_;
    this->parent_ = rhs.parent_;
    this->child_left_ = rhs.child_left_;
    this->child_right_ = rhs.child_right_;
    this->key_ = rhs.key_;
  }
  return *this;
}

Node::Node(Node &&obj) noexcept
    : is_valid_(obj.is_valid_),
      parent_(obj.parent_),
      child_left_(obj.child_left_),
      child_right_(obj.child_right_),
      key_(obj.key_) {
  obj.Reset();
}

Node &Node::operator=(Node &&rhs) noexcept {
  if (this != &rhs) {
    this->is_valid_ = rhs.is_valid_;
    this->parent_ = rhs.parent_;
    this->child_left_ = rhs.child_left_;
    this->child_right_ = rhs.child_right_;
    this->key_ = rhs.key_;
    rhs.Reset();  // 無効化
  }
  return *this;
}

void Node::Reset() noexcept {
  this->is_valid_ = false;
  this->parent_ = kInvalid;
  this->child_left_ = kInvalid;
  this->child_right_ = kInvalid;
  this->key_ = 0;
}

void Node::Activate() noexcept {
  is_valid_ = true;
}

bool Node::IsValid() const noexcept {
  return is_valid_;
}

void Node::SetKey(const int32_t key) {
  if (!IsValid()) {
    std::cerr << "ERROR: SetKey(): Not valid node." << std::endl;
    throw 1;
  }
  key_ = key;
}

int32_t Node::GetKey() const {
  if (!IsValid()) {
    std::cerr << "ERROR: GetKey(): Not valid node." << std::endl;
    throw 1;
  }
  return key_;
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

void Node::ResetChildLeft() noexcept {
  child_left_ = kInvalid;
}

void Node::ResetChildRight() noexcept {
  child_right_ = kInvalid;
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

}  // namespace ALDS1_8_C
