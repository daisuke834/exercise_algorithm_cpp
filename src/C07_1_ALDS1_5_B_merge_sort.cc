/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-1. 高等的整列、マージソート(Merge Sort)。
 * 最悪計算時間=O(N*log(N)), 平均計算時間=O(N*log(N)), 追加作業記憶領域=O(N). Stableなsort.
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C07_1_ALDS1_5_B_merge_sort.h"
#include <iostream>
#include <string>

namespace ALDS1_5_B {

void CallMergeSort(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  MergeSort *merge_sort = new MergeSort();
  try {
    int32_t count;
    input_stream >> count;
    for (int32_t index = 0; index < count; ++index) {
      int32_t cvalue;
      input_stream >> cvalue;
      merge_sort->AddData(cvalue);
    }
    merge_sort->Sort();
    merge_sort->Print();
  } catch (...) {
    std::cerr << "ERROR: CallMergeSort()" << std::endl;
    throw;
  }
  delete merge_sort;
}

// ****************************************************

MergeSort::MergeSort() noexcept : size_(0), comparison_count_(0), values_{}, left_values_{}, right_values_{} {}
MergeSort::~MergeSort() noexcept {}

void MergeSort::AddData(const int32_t value) {
  if (size_ >= kMaxArraySize) {
    std::cerr << "ERROR: AddData(): Data size exceeded a limit = " << kMaxArraySize << std::endl;
    throw 1;
  }
  values_[size_] = value;
  size_++;
}

void MergeSort::Sort() {
  try {
    ComputeMergeSort(0, size_);
  } catch (...) {
    std::cerr << "ERROR: Sort()" << std::endl;
    throw;
  }
}

void MergeSort::Print() const noexcept {
  for (int32_t index = 0; index < size_; ++index) {
    if (index != 0) {
      std::cout << " ";
    }
    std::cout << values_[index];
  }
  std::cout << std::endl;
  std::cout << comparison_count_ << std::endl;
}

void MergeSort::ComputeMergeSort(const int32_t left_end, const int32_t right_end) {
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

void MergeSort::MergeLeftAndRight(const int32_t left_end, const int32_t center, const int32_t right_end) {
  // endは右端indexの右一つ隣のindex (無効領域の先頭)left_end(有効) < center(有効) < right_end(無効)
  if (((left_end < 0) || (right_end > size_) || (center <= left_end) || (right_end <= center))) {
    std::cerr << "ERROR: MergeLeftAndRight: invalid args. left_end=" << left_end << ", center=" << center
              << ", right_end=" << right_end << std::endl;
    throw 1;
  }
  const int32_t left_size = center - left_end;
  const int32_t right_size = right_end - center;
  if (left_size > kMaxArraySize / 2) {
    std::cerr << "ERROR: MergeLeftAndRight: Invalid left_size. left_size=" << left_size << std::endl;
    throw 1;
  } else if (right_size > kMaxArraySize / 2) {
    std::cerr << "ERROR: MergeLeftAndRight: Invalid right_size. right_size=" << right_size << std::endl;
    throw 1;
  }
  try {
    for (int32_t index_left = 0; index_left < left_size; ++index_left) {
      left_values_[index_left] = values_[left_end + index_left];
    }
    left_values_[left_size] = INT32_MAX;
    for (int32_t index_right = 0; index_right < right_size; ++index_right) {
      right_values_[index_right] = values_[center + index_right];
    }
    right_values_[right_size] = INT32_MAX;

    int32_t index_left = 0;
    int32_t index_right = 0;
    for (int32_t index_target = left_end; index_target < right_end; ++index_target) {
      if (left_values_[index_left] <= right_values_[index_right]) {
        values_[index_target] = left_values_[index_left];
        ++index_left;
      } else {
        values_[index_target] = right_values_[index_right];
        ++index_right;
      }
      ++comparison_count_;
    }
  } catch (...) {
    std::cerr << "ERROR: MergeLeftAndRight()" << std::endl;
    throw;
  }
}

int32_t MergeSort::GetCenterIndex(const int32_t left_end, const int32_t right_end) const {
  // endは右端indexの右一つ隣のindex (無効領域の先頭)left_end(有効) < center(有効) < right_end(無効)
  if ((right_end <= left_end + 1) || ((left_end < 0) || (right_end > size_))) {
    std::cerr << "ERROR: GetCenterIndex: invalid args. left_end=" << left_end << ", right_end=" << right_end
              << std::endl;
    throw 1;
  }
  return (left_end + right_end) / 2;
}

void MergeSort::ResetData() noexcept {
  size_ = 0;
}

int32_t MergeSort::GetValue(const int32_t index) const {
  if ((index < 0) || (index >= size_)) {
    std::cerr << "ERROR: GetValue: invalid args. index=" << index << std::endl;
    throw 1;
  }
  return values_[index];
}

}  // namespace ALDS1_5_B
