/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-4. 初等的整列、選択ソート。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 * @brief Summary
 */

#include "src/C03_4_ALDS1_2_B_selection_sort.h"

#include <iostream>
namespace ALDS1_2_B {

SelectionSort::SelectionSort() noexcept : count_(0), values_{-1}, swapped_count_{0} {}

SelectionSort::~SelectionSort() noexcept {}

void SelectionSort::Main(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  try {
    Load(input_stream);
    Sort();
    Print();
  } catch (...) {
    std::cerr << "ERROR: Main()" << std::endl;
  }
}

void SelectionSort::Sort() noexcept {
  for (int32_t index_unsorted_top = 0; index_unsorted_top < count_; ++index_unsorted_top) {
    const int32_t index_minimum = FindMinimumIndex(index_unsorted_top);
    if (index_unsorted_top != index_minimum) {
      Swap(index_unsorted_top, index_minimum);
    }
  }
}

int32_t SelectionSort::FindMinimumIndex(int32_t index_unsorted_top) const noexcept {
  int32_t index_minimum = index_unsorted_top;
  for (int32_t index_scan = index_unsorted_top; index_scan < count_; ++index_scan) {
    if (values_[index_scan] < values_[index_minimum]) {
      index_minimum = index_scan;
    }
  }
  return index_minimum;
}

void SelectionSort::Swap(const int32_t index_unsorted_top, const int32_t index_minimum) noexcept {
  const int32_t value_top = values_[index_unsorted_top];
  values_[index_unsorted_top] = values_[index_minimum];
  values_[index_minimum] = value_top;
  ++swapped_count_;
}

void SelectionSort::Load(std::istream& input_stream) {
  input_stream >> count_;
  if (count_ > kMaxArraySize) {
    std::cout << "kMaxArraySize is too small for the number of data count." << std::endl;
    throw 1;
  }
  for (int32_t index = 0; index < count_; ++index) {
    input_stream >> values_[index];
  }
}

void SelectionSort::Print() const noexcept {
  for (int32_t index = 0; index < count_; ++index) {
    if (index != 0) {
      std::cout << " ";
    }
    std::cout << values_[index];
  }
  std::cout << std::endl;
  std::cout << swapped_count_ << std::endl;
}

}  // namespace ALDS1_2_B
