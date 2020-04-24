/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part10-4. ヒープ、優先度付きキュー(Priority Queue)。
 * 要素数nの優先度付き付きキューに対し、InsertおよびExtractの計算量はそれぞれO(H)=O(log(n))。(H=木の高さ)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C10_4_ALDS1_9_C_priority_queue.h"
#include <iostream>
#include <string>

namespace ALDS1_9_C {

void CallPriorityQueue(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  PriorityQueue *priority_queue = new PriorityQueue();
  try {
    bool loop_end = false;
    constexpr int32_t kMaxNumberOfInstructions = 3000000;
    for (int32_t index_instruction = 0; index_instruction < kMaxNumberOfInstructions; ++index_instruction) {
      std::string instruction_str;
      input_stream >> instruction_str;
      const InstructionType instruction = JudgeInstructionType(instruction_str);
      switch (instruction) {
        case InstructionType::kInsert:
          int32_t insert_key;
          input_stream >> insert_key;
          priority_queue->Insert(insert_key);
          break;
        case InstructionType::kExtract:
          std::cout << priority_queue->Extract() << std::endl;
          break;
        case InstructionType::kEnd:
          loop_end = true;
          break;
        default:
          std::cerr << "ERROR: CallDictionary(): Invalid instruction type." << std::endl;
          break;
      }
      if (loop_end) {
        break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CallPriorityQueue()" << std::endl;
    // priority_queue->Debug();
    throw;
  }
  delete priority_queue;
}
// ****************************************************

InstructionType JudgeInstructionType(const std::string &str) {
  InstructionType instruction_type;
  if (str == "insert") {
    instruction_type = InstructionType::kInsert;
  } else if (str == "extract") {
    instruction_type = InstructionType::kExtract;
  } else if (str == "end") {
    instruction_type = InstructionType::kEnd;
  } else {
    std::cerr << "ERROR: JudgeInstructionType(): Invalid input data. " << str << std::endl;
    throw 1;
  }
  return instruction_type;
}

// ****************************************************

PriorityQueue::PriorityQueue() noexcept : size_(0) {}
PriorityQueue::~PriorityQueue() noexcept {}

void PriorityQueue::Insert(const int32_t key) {
  try {
    Add(key);
    const int32_t index_added_tail = size_ - 1;
    SwapIfLargerThanParent(index_added_tail);
  } catch (...) {
    std::cerr << "ERROR: Insert()" << std::endl;
    throw;
  }
}

void PriorityQueue::SwapIfLargerThanParent(const int32_t index) {
  if (IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: SwapIfLargerThanParent(): Invalid arg: index = " << index << std::endl;
    throw 1;
  }
  try {
    const int32_t index_parent = GetIndexParent(index);
    if (IsValidNode(index_parent)) {
      if (GetKeyByIndex(index) > GetKeyByIndex(index_parent)) {
        Swap(index, index_parent);
        SwapIfLargerThanParent(index_parent);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: SwapIfLargerThanParent()" << std::endl;
    throw;
  }
}

int32_t PriorityQueue::Extract() {
  int32_t extracted_key;
  try {
    extracted_key = GetKeyByIndex(0);
    RemoveTop();
  } catch (...) {
    std::cerr << "ERROR: Extract()" << std::endl;
    throw;
  }
  return extracted_key;
}

void PriorityQueue::RemoveTop() {
  if (size_ <= 0) {
    std::cerr << "ERROR: InvalidateTop(): Invalid size_=" << size_ << std::endl;
    throw 1;
  } else {
    try {
      const int32_t index_tail = size_ - 1;
      SetKeyByIndex(0, GetKeyByIndex(index_tail));
      nodes_[index_tail].is_valid = false;
      --size_;
      if (size_ > 0) {
        MaxHeapify(0);
      }
    } catch (...) {
      std::cerr << "ERROR: InvalidateTop()" << std::endl;
      throw;
    }
  }
}

void PriorityQueue::Add(const int32_t key) {
  if (size_ >= kMaxNumberOfNodes) {
    std::cerr << "ERROR: Add(): Data size exceeded a limit = " << kMaxNumberOfNodes << std::endl;
    throw 1;
  }
  const int32_t store_index = size_;
  ++size_;
  SetKeyByIndex(store_index, key);
}

void PriorityQueue::SetKeyByIndex(const int32_t index, const int32_t key) {
  if (IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: Set(): Invalid arg: index = " << index << std::endl;
    throw 1;
  }
  nodes_[index].key = key;
  nodes_[index].is_valid = true;
}

int32_t PriorityQueue::GetKeyByIndex(const int32_t index) const {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: Set(): Invalid arg: index = " << index << std::endl;
    throw 1;
  }
  return nodes_[index].key;
}

void PriorityQueue::Print() const {
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

void PriorityQueue::Debug() const {
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
    throw;
  }
}

void PriorityQueue::BuildMaxHeap() {
  try {
    for (int32_t node_number = size_ / 2; node_number >= 1; --node_number) {
      const int32_t index = ConvertFromNodeNumberToIndex(node_number);
      MaxHeapify(index);
    }
  } catch (...) {
    std::cerr << "ERROR: BuildMaxHeap()" << std::endl;
    throw;
  }
}

void PriorityQueue::MaxHeapify(const int32_t index) {
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

void PriorityQueue::Swap(const int32_t index_a, const int32_t index_b) {
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

int32_t PriorityQueue::GetIndexHavingLargestValueFromTargetAndChildren(const int32_t index_current) const {
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

int32_t PriorityQueue::GetIndexParent(const int32_t index) const {
  if (IsInvalidNode(index)) {
    std::cerr << "ERROR: GetIndexParent(): Invalid node: index = " << index << std::endl;
    throw 1;
  }
  const int32_t node_number = ConvertFromIndexToNodeNumber(index);
  const int32_t parent = node_number / 2;
  const int32_t parent_index = ((parent == 0) ? kTopIndex : ConvertFromNodeNumberToIndex(parent));
  return parent_index;
}

int32_t PriorityQueue::GetIndexChildLeft(const int32_t index) const {
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

int32_t PriorityQueue::GetIndexChildRight(const int32_t index) const {
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

bool PriorityQueue::IsInvalidNode(const int32_t index) const noexcept {
  return !IsValidNode(index);
}

bool PriorityQueue::IsValidNode(const int32_t index) const noexcept {
  const bool is_valid = IsValidNodeIndex(index) ? nodes_[index].is_valid : false;
  return is_valid;
}

bool PriorityQueue::IsInvalidNodeIndex(const int32_t index) noexcept {
  return ((index < 0) || (index >= kMaxNumberOfNodes));
}

bool PriorityQueue::IsValidNodeIndex(const int32_t index) noexcept {
  return !IsInvalidNodeIndex(index);
}

bool PriorityQueue::IsInvalidNodeNumber(const int32_t node_number) noexcept {
  return ((node_number < 1) || (node_number > kMaxNumberOfNodes));
}

bool PriorityQueue::IsValidNodeNodeNumber(const int32_t node_number) noexcept {
  return !IsInvalidNodeNumber(node_number);
}

int32_t PriorityQueue::ConvertFromNodeNumberToIndex(const int32_t node_number) {
  const int32_t index = node_number - 1;
  if (IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: ConvertFromNodeNumberToIndex(): Invalid node: index = " << index
              << ", node_number=" << node_number << std::endl;
    throw 1;
  }
  return index;
}

int32_t PriorityQueue::ConvertFromIndexToNodeNumber(const int32_t index) {
  if (IsInvalidNodeIndex(index)) {
    std::cerr << "ERROR: ConvertFromIndexToNodeNumber(): Invalid node: index = " << index << std::endl;
    throw 1;
  }
  return index + 1;
}

int32_t PriorityQueue::GetSize() const noexcept {
  return size_;
}

void PriorityQueue::Reset() noexcept {
  size_ = 0;
}

}  // namespace ALDS1_9_C
