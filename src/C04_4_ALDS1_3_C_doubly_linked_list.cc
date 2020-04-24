/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-4. データ構造、双方向連結リスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C04_4_ALDS1_3_C_doubly_linked_list.h"
#include <algorithm>
#include <iostream>
#include <string>
namespace ALDS1_3_C {

void CallDoublyLinkedList(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  int32_t number_of_operations;
  input_stream >> number_of_operations;
  DoublyLinkedList *linked_list = new DoublyLinkedList();
  try {
    for (int32_t operation_index = 0; operation_index < number_of_operations; ++operation_index) {
      std::string operation_name;
      int32_t key;
      input_stream >> operation_name;
      if (operation_name == "insert") {
        input_stream >> key;
        linked_list->Insert(Key(key));
      } else if (operation_name == "delete") {
        input_stream >> key;
        linked_list->Delete(Key(key));
      } else if (operation_name == "deleteFirst") {
        linked_list->DeleteFirst();
      } else if (operation_name == "deleteLast") {
        linked_list->DeleteLast();
      } else {
        std::cout << "Invalid operation name" << std::endl;
        throw 1;
      }
    }
    linked_list->Print();
  } catch (...) {
    std::cerr << "ERROR: CallDoublyLinkedList()" << std::endl;
    throw;
  }
  delete linked_list;
}

Key::Key() noexcept : key_(INT16_MAX) {}

Key::Key(const int32_t key) noexcept : key_(key) {}

Key::~Key() noexcept {}

Key::Key(const Key &obj) noexcept : key_(obj.key_) {}

Key &Key::operator=(const Key &rhs) noexcept {
  if (this != &rhs) {
    this->key_ = rhs.key_;
  }
  return *this;
}

Key::Key(Key &&obj) noexcept : key_(obj.key_) {
  obj.key_ = INT16_MAX;  // 無効化
}

Key &Key::operator=(Key &&rhs) noexcept {
  if (this != &rhs) {
    this->key_ = rhs.key_;
    rhs.key_ = INT16_MAX;  // 無効化
  }
  return *this;
}

int32_t Key::GetKey() const noexcept {
  return key_;
}

bool Key::Equals(const Key &obj) const noexcept {
  return (IsValid() && (GetKey() == obj.GetKey()));
}

bool Key::IsValid() const noexcept {
  return (key_ != INT32_MAX);
}

// ****************************************************
Node::Node() noexcept : next_(kInvalidIndex), previous_(kInvalidIndex) {}
Node::~Node() noexcept {}

void Node::SetKey(const Key &key) noexcept {
  key_ = key;
}

void Node::UpdateNext(int32_t next) noexcept {
  next_ = next;
}

void Node::UpdatePrevious(int32_t previous) noexcept {
  previous_ = previous;
}

bool Node::IsValid() const noexcept {
  return (next_ != kInvalidIndex) && (previous_ != kInvalidIndex);
}

Key Node::GetKey() const noexcept {
  return key_;
}

bool Node::HasKey(const Key &key) const noexcept {
  return (IsValid() && key_.Equals(key));
}

int32_t Node::GetNext() const noexcept {
  return next_;
}
int32_t Node::GetPrevious() const noexcept {
  return previous_;
}

// ****************************************************

DoublyLinkedList::DoublyLinkedList() noexcept : top_(kInvalidIndex), tail_(kInvalidIndex) {}

DoublyLinkedList::~DoublyLinkedList() noexcept {}

void DoublyLinkedList::Insert(const Key &key) {
  if (!key.IsValid()) {
    std::cerr << "ERROR: Insert(): Invalid key arg" << std::endl;
    throw 1;
  }
  try {
    const int32_t index_stored = FindInvalidNode();
    nodes_[index_stored].SetKey(key);
    nodes_[index_stored].UpdatePrevious(kTopIndex);
    if (top_ == kInvalidIndex) {
      nodes_[index_stored].UpdateNext(kTailIndex);
      tail_ = index_stored;
    } else {
      const int32_t old_top = top_;
      nodes_[index_stored].UpdateNext(old_top);
      nodes_[old_top].UpdatePrevious(index_stored);
    }
    top_ = index_stored;
  } catch (...) {
    std::cerr << "ERROR: Insert()" << std::endl;
    throw;
  }
}

void DoublyLinkedList::Delete(const Key &key) {
  if (!key.IsValid()) {
    std::cerr << "ERROR: Insert(): Invalid key arg" << std::endl;
    throw 1;
  }
  try {
    const int32_t index_delete = Search(key);
    const int32_t right = nodes_[index_delete].GetNext();
    const int32_t left = nodes_[index_delete].GetPrevious();
    if ((index_delete == top_) && (index_delete == tail_)) {
      // 左右が存在しない
      top_ = kInvalidIndex;
      tail_ = kInvalidIndex;
    } else if (index_delete == top_) {
      // 右は存在するが、左が存在しない
      top_ = right;
      nodes_[right].UpdatePrevious(kTopIndex);
    } else if (index_delete == tail_) {
      // 左は存在するが、右が存在しない
      nodes_[left].UpdateNext(kTailIndex);
      tail_ = left;
    } else {
      // 左右共に存在する
      nodes_[left].UpdateNext(right);
      nodes_[right].UpdatePrevious(left);
    }
    nodes_[index_delete].UpdatePrevious(kInvalidIndex);
    nodes_[index_delete].UpdateNext(kInvalidIndex);
  } catch (...) {
    // DO NOTHING
  }
}

void DoublyLinkedList::DeleteFirst() {
  try {
    const int32_t index_delete = top_;
    if (index_delete == tail_) {
      // 左右が存在しない
      top_ = kInvalidIndex;
      tail_ = kInvalidIndex;
    } else {
      // 右は存在するが、左が存在しない
      const int32_t right = nodes_[index_delete].GetNext();
      top_ = right;
      nodes_[right].UpdatePrevious(kTopIndex);
    }
    nodes_[index_delete].UpdatePrevious(kInvalidIndex);
    nodes_[index_delete].UpdateNext(kInvalidIndex);
  } catch (...) {
    std::cerr << "ERROR: DeleteFirst()" << std::endl;
    throw;
  }
}
void DoublyLinkedList::DeleteLast() {
  try {
    const int32_t index_delete = tail_;
    if (index_delete == top_) {
      // 左右が存在しない
      top_ = kInvalidIndex;
      tail_ = kInvalidIndex;
    } else {
      // 左は存在するが、右が存在しない
      const int32_t left = nodes_[index_delete].GetPrevious();
      nodes_[left].UpdateNext(kTailIndex);
      tail_ = left;
    }
    nodes_[index_delete].UpdatePrevious(kInvalidIndex);
    nodes_[index_delete].UpdateNext(kInvalidIndex);
  } catch (...) {
    std::cerr << "ERROR: DeleteLast()" << std::endl;
    throw;
  }
}

int32_t DoublyLinkedList::FindInvalidNode() {
  int32_t found_index = -1;
  // for (int32_t index = 0; index < kMaxNumberOfNodes; ++index) {  // Memory efficient, but flow
  for (int32_t index = std::max(0, top_); index < kMaxNumberOfNodes; ++index) {  // Fast, but memory inefficient
    if (!nodes_[index].IsValid()) {
      found_index = index;
      break;
    }
  }
  if (found_index < 0) {
    std::cerr << "ERROR: FindInvalidNode(): not found." << std::endl;
    throw 1;
  }
  return found_index;
}

int32_t DoublyLinkedList::Search(const Key &key) {
  int32_t found_index = -1;
  int32_t current_index = top_;
  for (int32_t count = 1; count <= kMaxNumberOfNodes; ++count) {
    if ((current_index == kTailIndex) || (current_index == kInvalidIndex)) {
      break;
    } else if (nodes_[current_index].HasKey(key)) {
      found_index = current_index;
      break;
    } else {
      current_index = nodes_[current_index].GetNext();
    }
  }
  if (found_index < 0) {
    // DO NOT PRINT MESSAGE
    throw 1;
  }
  return found_index;
}

void DoublyLinkedList::Print() const {
  int32_t current_index = top_;
  for (int32_t count = 1; count <= kMaxNumberOfNodes; ++count) {
    if ((current_index == kTailIndex) || (current_index == kInvalidIndex)) {
      break;
    } else {
      std::cout << nodes_[current_index].GetKey().GetKey();
      if (nodes_[current_index].GetNext() == kTailIndex) {
        std::cout << std::endl;
      } else {
        std::cout << " ";
      }
      current_index = nodes_[current_index].GetNext();
    }
  }
}

}  // namespace ALDS1_3_C
