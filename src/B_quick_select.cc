/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Quick Selectのスクラッチ実装
 * 最悪計算時間=O(N^2), 平均計算時間=O(N), 追加作業記憶領域=O(1). Stableでないsort.
 * 最悪計算時間は、pivotの選び方に依存。
 */

#include "src/B_quick_select.h"

#include <iostream>

namespace my_quick_select {

void CallQuickSelect(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  QuickSelect* quick_select = new QuickSelect();
  try {
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      int32_t value;
      input_stream >> value;
      if (input_stream.eof()) {
        break;
      }
      quick_select->AddElement(value);
    }
    constexpr int32_t kOrdinalNumber = 3;
    quick_select->Select(kOrdinalNumber);
    quick_select->PrintSelectedElements();
  } catch (...) {
    std::cerr << "ERROR: CallHoge()" << std::endl;
    // DO NOT THROW EXCEPTION
  }
  delete quick_select;
}

QuickSelect::QuickSelect() noexcept : number_of_elements_(0) {}

QuickSelect::~QuickSelect() noexcept {}

void QuickSelect::AddElement(int32_t value) {
  if (number_of_elements_ >= kMaxNumberOfElements) {
    std::cerr << "ERROR: AddElement(): number of elements exceeded a limit = " << kMaxNumberOfElements << std::endl;
    throw 1;
  }
  const int32_t index_store = number_of_elements_;
  ++number_of_elements_;
  elements_[index_store].value = value;
}

void QuickSelect::PrintSelectedElements() const noexcept {
  for (int32_t index = 0; index <= ordinal_index_; ++index) {
    std::cout << elements_[index].value << std::endl;
  }
}

void QuickSelect::Select(const int32_t ordinal_number) {
  if ((ordinal_number <= 0) || (ordinal_number > number_of_elements_)) {
    std::cerr << "ERROR: Select(): Invalid arg ordinal_number=" << ordinal_number << std::endl;
  }
  ordinal_index_ = ordinal_number - 1;
  try {
    ComputeQuickSelect(0, number_of_elements_ - 1);
  } catch (...) {
    std::cerr << "ERROR: Sort()" << std::endl;
    throw;
  }
}

void QuickSelect::ComputeQuickSelect(const int32_t start, const int32_t end) {
  try {
    if (start < end) {
      const int32_t index_pivot = ComputePartition(start, end);
      if (ordinal_index_ == index_pivot) {
        // DO NOTHING
      } else if (ordinal_index_ < index_pivot) {
        ComputeQuickSelect(start, index_pivot - 1);
      } else {
        ComputeQuickSelect(index_pivot + 1, end);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: ComputeQuickSelect()" << std::endl;
    throw;
  }
}

int32_t QuickSelect::ComputePartition(const int32_t start, const int32_t end) {
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

void QuickSelect::Swap(const int32_t index_1, const int32_t index_2) {
  if ((IndexOutOfRange(index_1)) || (IndexOutOfRange(index_2))) {
    std::cerr << "ERROR: Swap(): Out of range: index_1=" << index_1 << ", index_2=" << index_2 << std::endl;
    throw 1;
  } else {
    const Element temp = elements_[index_2];
    elements_[index_2] = elements_[index_1];
    elements_[index_1] = temp;
  }
}

bool QuickSelect::IndexOutOfRange(const int32_t index) const noexcept {
  return ((index) < 0 || (index >= number_of_elements_));
}

}  // namespace my_quick_select
