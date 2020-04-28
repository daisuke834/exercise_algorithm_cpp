/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Quick Sortのスクラッチ実装
 * 最悪計算時間=O(N^2), 平均計算時間=O(N*log(N)), 追加作業記憶領域=O(1). Stableでないsort.
 * 最悪計算時間は、pivotの選び方に依存。
 */

#include "src/B_quick_sort.h"
#include <iostream>

namespace my_quick_sort {

void CallQuickSort(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  QuickSort *quick_sort = new QuickSort();
  try {
    for (int32_t i = 0; i < KMaxLoopCount; ++i) {
      int32_t value;
      input_stream >> value;
      if (input_stream.eof()) {
        break;
      }
      quick_sort->AddElement(value);
    }
    quick_sort->Sort();
    quick_sort->PrintElements();
  } catch (...) {
    std::cerr << "ERROR: CallHoge()" << std::endl;
    // DO NOT THROW EXCEPTION
  }
  delete quick_sort;
}

QuickSort::QuickSort() noexcept : number_of_elements_(0) {}

QuickSort::~QuickSort() noexcept {}

void QuickSort::AddElement(int32_t value) {
  if (number_of_elements_ >= kMaxNumberOfElements) {
    std::cerr << "ERROR: AddElement(): number of elements exceeded a limit = " << kMaxNumberOfElements << std::endl;
    throw 1;
  }
  const int32_t index_store = number_of_elements_;
  ++number_of_elements_;
  elements_[index_store].value = value;
}

void QuickSort::PrintElements() const noexcept {
  for (int32_t index = 0; index < number_of_elements_; ++index) {
    std::cout << elements_[index].value << std::endl;
  }
}

void QuickSort::Sort() {
  try {
    ComputeQuickSort(0, number_of_elements_ - 1);
  } catch (...) {
    std::cerr << "ERROR: Sort()" << std::endl;
    throw;
  }
}

void QuickSort::ComputeQuickSort(const int32_t start, const int32_t end) {
  try {
    if (start < end) {
      const int32_t index_pivot = ComputePartition(start, end);
      ComputeQuickSort(start, index_pivot - 1);
      ComputeQuickSort(index_pivot + 1, end);
    }
  } catch (...) {
    std::cerr << "ERROR: ComputeQuickSort()" << std::endl;
    throw;
  }
}

int32_t QuickSort::ComputePartition(const int32_t start, const int32_t end) {
  int32_t index_pivot;
  if (IndexOutOfRange(start)) {
    std::cerr << "ERROR: ComputePartition(): Out of range: start = " << start << std::endl;
    throw 1;
  } else if (IndexOutOfRange(end)) {
    std::cerr << "ERROR: ComputePartition(): Out of range: end = " << end << std::endl;
    throw 1;
  } else {
    try {
      const int32_t value_pivot = elements_[end].value;
      int32_t index_store = start;
      for (int32_t index_compare = start; index_compare < end; ++index_compare) {
        if (elements_[index_compare].value <= value_pivot) {
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

void QuickSort::Swap(const int32_t index_1, const int32_t index_2) {
  if ((IndexOutOfRange(index_1)) || (IndexOutOfRange(index_2))) {
    std::cerr << "ERROR: Swap(): Out of range: index_1=" << index_1 << ", index_2=" << index_2 << std::endl;
    throw 1;
  } else {
    const Element temp = elements_[index_2];
    elements_[index_2] = elements_[index_1];
    elements_[index_1] = temp;
  }
}

bool QuickSort::IndexOutOfRange(const int32_t index) const noexcept {
  return ((index) < 0 || (index >= number_of_elements_));
}

}  // namespace my_quick_sort
