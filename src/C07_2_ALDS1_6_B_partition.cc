/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-2. 高等的整列、パーティション(Partition)。
 * 最悪計算量=O(N), 追加作業記憶領域=O(1)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C07_2_ALDS1_6_B_partition.h"
#include <iostream>
#include <string>

namespace ALDS1_6_B {

void CallPartition(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  Partition *partition = new Partition();
  try {
    int32_t count;
    input_stream >> count;
    for (int32_t index = 0; index < count; ++index) {
      int32_t cvalue;
      input_stream >> cvalue;
      partition->AddData(cvalue);
    }
    const int32_t index_pivot = partition->ComputePartition(0, count - 1);
    for (int32_t index = 0; index < count; ++index) {
      if (index != 0) {
        std::cout << " ";
      }
      if (index == index_pivot) {
        std::cout << "[" << partition->GetValue(index) << "]";
      } else {
        std::cout << partition->GetValue(index);
      }
    }
    std::cout << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallPartition()" << std::endl;
    throw;
  }
  delete partition;
}

// ****************************************************

Partition::Partition() noexcept : size_(0), values_{} {}
Partition::~Partition() noexcept {}

void Partition::AddData(const int32_t value) {
  if (size_ >= kMaxArraySize) {
    std::cerr << "ERROR: AddData(): Data size exceeded a limit = " << kMaxArraySize << std::endl;
    throw 1;
  }
  values_[size_] = value;
  size_++;
}

void Partition::ResetData() noexcept {
  size_ = 0;
}

int32_t Partition::GetValue(const int32_t index) {
  if (IndexOutOfRange(index)) {
    std::cerr << "ERROR: GetValue(): Out of range: index = " << index << std::endl;
    throw 1;
  }
  return values_[index];
}

int32_t Partition::ComputePartition(const int32_t start, const int32_t end) {
  int32_t index_pivot = -1;
  if (IndexOutOfRange(start)) {
    std::cerr << "ERROR: ComputePartition(): Out of range: start = " << start << std::endl;
    throw 1;
  } else if (IndexOutOfRange(end)) {
    std::cerr << "ERROR: ComputePartition(): Out of range: end = " << end << std::endl;
    throw 1;
  } else {
    try {
      // pivot_indexを外部から指定するようにすると、stable sortではなくなるため、endをpivotとして用いる。
      const int32_t value_pivot = values_[end];
      int32_t index_store = start;
      for (int32_t index_compare = start; index_compare < end; ++index_compare) {
        if (values_[index_compare] <= value_pivot) {
          Swap(index_compare, index_store);
          ++index_store;
        }
      }
      Swap(end, index_store);
      index_pivot = index_store;
    } catch (...) {
      std::cerr << "ERROR: ComputePartition()" << std::endl;
      throw;
    }
  }
  return index_pivot;
}

void Partition::Swap(const int32_t index_1, const int32_t index_2) {
  if (IndexOutOfRange(index_1)) {
    std::cerr << "ERROR: Swap(): Out of range: index_1 = " << index_1 << std::endl;
    throw 1;
  } else if (IndexOutOfRange(index_2)) {
    std::cerr << "ERROR: Swap(): Out of range: index_2 = " << index_2 << std::endl;
    throw 1;
  } else {
    const int32_t temp = values_[index_2];
    values_[index_2] = values_[index_1];
    values_[index_1] = temp;
  }
}

bool Partition::IndexOutOfRange(const int32_t index) const noexcept {
  return ((index) < 0 || (index >= size_));
}

}  // namespace ALDS1_6_B
