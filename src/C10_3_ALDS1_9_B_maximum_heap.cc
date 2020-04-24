/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part10-3. ヒープ、最大ヒープ(Maximum Heap)。
 * 高さHの完全二分木に対し、BuildMaxHeapの計算量はO(H) = H * sum_k(k/2~k)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C10_3_ALDS1_9_B_maximum_heap.h"
#include <iostream>
#include <string>

namespace ALDS1_9_B {

void CallMaximumHeap(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  MaximumHeap *maximum_heap = new MaximumHeap();
  try {
    int32_t number_of_nodes;
    input_stream >> number_of_nodes;
    for (int32_t i = 0; i < number_of_nodes; ++i) {
      int32_t key;
      input_stream >> key;
      maximum_heap->Add(key);
    }
    maximum_heap->BuildMaxHeap();
    maximum_heap->Print();
  } catch (...) {
    std::cerr << "ERROR: CallMaximumHeap()" << std::endl;
    // maximum_heap->Debug();
    throw;
  }
  delete maximum_heap;
}

// ****************************************************

MaximumHeap::MaximumHeap() noexcept : size_(0) {}
MaximumHeap::~MaximumHeap() noexcept {}

void MaximumHeap::Add(const int32_t key) {
  if (size_ >= kMaxNumberOfNodes) {
    std::cerr << "ERROR: Add(): Data size exceeded a limit = " << kMaxNumberOfNodes << std::endl;
    throw 1;
  }
  const int32_t store_index = size_;
  ++size_;
  SetKeyByIndex(store_index, key);
}

void MaximumHeap::SetKeyByIndex(const int32_t index, const int32_t key) {
  if (IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: Set(): Invalid arg: index = " << index << std::endl;
    throw 1;
  }
  nodes_[index].key = key;
  nodes_[index].is_valid = true;
}

int32_t MaximumHeap::GetKeyByIndex(const int32_t index) const {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: Set(): Invalid arg: index = " << index << std::endl;
    throw 1;
  }
  return nodes_[index].key;
}

void MaximumHeap::Print() const {
  try {
    for (int32_t index = 0; index < size_; ++index) {
      std::cout << " " << GetKeyByIndex(index);
    }
    std::cout << std::endl;
  } catch (...) {
    std::cerr << "ERROR: Debug()" << std::endl;
    throw 1;
  }
}

void MaximumHeap::Debug() const {
  try {
    for (int32_t index = 0; (index < size_) && (index < 20); ++index) {
      std::cerr << "node " << ConvertFromIndexToNodeNumber(index);
      std::cerr << ": key = " << GetKeyByIndex(index) << ", ";
      const int32_t parent_index = GetIndexParent(index);
      if (IsValidNodeIndex(parent_index)) {
        std::cerr << "parent key = " << GetKeyByIndex(parent_index) << ", ";
      }
      const int32_t child_left_index = GetIndexChildLeft(index);
      if (IsValidNodeIndex(child_left_index)) {
        std::cerr << "left key = " << GetKeyByIndex(child_left_index) << ", ";
      }
      const int32_t child_right_index = GetIndexChildRight(index);
      if (IsValidNodeIndex(child_right_index)) {
        std::cerr << "right key = " << GetKeyByIndex(child_right_index) << ", ";
      }
      std::cerr << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: Debug()" << std::endl;
    throw 1;
  }
}

void MaximumHeap::BuildMaxHeap() {
  try {
    for (int32_t node_number = size_ / 2; node_number >= 1; --node_number) {
      const int32_t index = ConvertFromNodeNumberToIndex(node_number);
      MaxHeapify(index);
    }
  } catch (...) {
    std::cerr << "ERROR: BuildMaxHeap()" << std::endl;
    throw 1;
  }
}

void MaximumHeap::MaxHeapify(const int32_t index) {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: MaxHeapify(): Invalid node: index = " << index << std::endl;
    throw 1;
  }
  try {
    const int32_t index_largest_value = GetIndexHavingLargestValueFromTargetAndChildren(index);
    if (index != index_largest_value) {
      Swap(index, index_largest_value);
      MaxHeapify(index_largest_value);
    }
  } catch (...) {
    std::cerr << "ERROR: MaxHeapify()" << std::endl;
    throw;
  }
}

void MaximumHeap::Swap(const int32_t index_a, const int32_t index_b) {
  if (IsInvalidNode(index_a)) {
    std::cerr << "ERROR: Swap(): Invalid node: index_a = " << index_a << std::endl;
    throw 1;
  } else if (IsInvalidNode(index_b)) {
    std::cerr << "ERROR: Swap(): Invalid node: index_b = " << index_b << std::endl;
    throw 1;
  } else {
    try {
      const int32_t temp_key = GetKeyByIndex(index_b);
      SetKeyByIndex(index_b, GetKeyByIndex(index_a));
      SetKeyByIndex(index_a, temp_key);
    } catch (...) {
      std::cerr << "ERROR: Swap()" << std::endl;
      throw;
    }
  }
}

int32_t MaximumHeap::GetIndexHavingLargestValueFromTargetAndChildren(const int32_t index_current) const {
  if (IsInvalidNode(index_current)) {
    std::cerr << "ERROR: GetIndexHavingLargestValueFromTargetAndChildren(): Invalid node: index_current = "
              << index_current << std::endl;
    throw 1;
  }
  int32_t index_largest_value = index_current;
  try {
    const int32_t index_child_left = GetIndexChildLeft(index_current);
    if (IsValidNode(index_child_left)) {
      if (GetKeyByIndex(index_child_left) > GetKeyByIndex(index_largest_value)) {
        index_largest_value = index_child_left;
      }
    }

    const int32_t index_child_right = GetIndexChildRight(index_current);
    if (IsValidNode(index_child_right)) {
      if (GetKeyByIndex(index_child_right) > GetKeyByIndex(index_largest_value)) {
        index_largest_value = index_child_right;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: GetIndexHavingLargestValueFromTargetAndChildren()" << std::endl;
    throw;
  }
  return index_largest_value;
}

int32_t MaximumHeap::GetIndexParent(const int32_t index) const {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: GetIndexParent(): Invalid node: index = " << index << std::endl;
    throw 1;
  }
  const int32_t node_number = ConvertFromIndexToNodeNumber(index);
  const int32_t parent = node_number / 2;
  const int32_t parent_index = ((parent == 0) ? kTopIndex : ConvertFromNodeNumberToIndex(parent));
  return parent_index;
}

int32_t MaximumHeap::GetIndexChildLeft(const int32_t index) const {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: GetIndexChildLeft(): Invalid arg: index = " << index << std::endl;
    throw 1;
  }
  int32_t left_index = kInvalidIndex;
  try {
    const int32_t node_number = ConvertFromIndexToNodeNumber(index);
    const int32_t left = node_number * 2;
    if (IsValidNodeNodeNumber(left)) {
      left_index = ConvertFromNodeNumberToIndex(left);
      if (IsInvalidNode(left_index)) {
        left_index = kInvalidIndex;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: GetIndexChildLeft(): index=" << index << ", left_index=" << left_index << std::endl;
    throw 1;
  }
  return left_index;
}

int32_t MaximumHeap::GetIndexChildRight(const int32_t index) const {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: GetIndexChildRight(): Invalid arg: index = " << index << std::endl;
    throw 1;
  }
  int32_t right_index = kInvalidIndex;
  try {
    const int32_t node_number = ConvertFromIndexToNodeNumber(index);
    const int32_t right = node_number * 2 + 1;
    if (IsValidNodeNodeNumber(right)) {
      right_index = ConvertFromNodeNumberToIndex(right);
      if (IsInvalidNode(right_index)) {
        right_index = kInvalidIndex;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: GetIndexChildRight(): index=" << index << ", right_index=" << right_index << std::endl;
    throw 1;
  }
  return right_index;
}

bool MaximumHeap::IsInvalidNode(const int32_t index) const noexcept {
  return !IsValidNode(index);
}

bool MaximumHeap::IsValidNode(const int32_t index) const noexcept {
  const bool is_valid = IsValidNodeIndex(index) ? nodes_[index].is_valid : false;
  return is_valid;
}

bool MaximumHeap::IsInvalidNodeIndex(const int32_t index) noexcept {
  return ((index < 0) || (index >= kMaxNumberOfNodes));
}

bool MaximumHeap::IsValidNodeIndex(const int32_t index) noexcept {
  return !IsInvalidNodeIndex(index);
}

bool MaximumHeap::IsInvalidNodeNumber(const int32_t node_number) noexcept {
  return ((node_number < 1) || (node_number > kMaxNumberOfNodes));
}

bool MaximumHeap::IsValidNodeNodeNumber(const int32_t node_number) noexcept {
  return !IsInvalidNodeNumber(node_number);
}

int32_t MaximumHeap::ConvertFromNodeNumberToIndex(const int32_t node_number) {
  const int32_t index = node_number - 1;
  if (IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: ConvertFromNodeNumberToIndex(): Invalid node: index = " << index
              << ", node_number=" << node_number << std::endl;
    throw 1;
  }
  return index;
}

int32_t MaximumHeap::ConvertFromIndexToNodeNumber(const int32_t index) {
  if (IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: ConvertFromIndexToNodeNumber(): Invalid node: index = " << index << std::endl;
    throw 1;
  }
  return index + 1;
}

int32_t MaximumHeap::GetSize() const noexcept {
  return size_;
}

void MaximumHeap::Reset() noexcept {
  size_ = 0;
}

}  // namespace ALDS1_9_B
