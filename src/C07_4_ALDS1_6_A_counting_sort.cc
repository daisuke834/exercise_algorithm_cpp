/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-4. 高等的整列、計数ソート(Counting Sort)。
 * 最悪計算時間=O(n+k), 平均計算時間=O(n+k), 追加作業記憶領域=O(n+k). Stable sort.
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C07_4_ALDS1_6_A_counting_sort.h"
#include <iostream>
#include <string>

namespace ALDS1_6_A {

void CallCountingSort(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  CountingSort *counting_sort = new CountingSort();
  try {
    int32_t count;
    input_stream >> count;
    for (int32_t index = 0; index < count; ++index) {
      int32_t cvalue;
      input_stream >> cvalue;
      counting_sort->AddData(cvalue);
    }
    counting_sort->Sort();
    counting_sort->Print();
  } catch (...) {
    std::cerr << "ERROR: CallCountingSort()" << std::endl;
    throw;
  }
  delete counting_sort;
}

// ****************************************************

CountingSort::CountingSort() noexcept : size_(0), input_values_{}, output_values_{} {
  for (int32_t &ccount : counts_) {
    ccount = 0;
  }
}
CountingSort::~CountingSort() noexcept {}

void CountingSort::AddData(const int32_t value) {
  if (size_ >= kMaxArraySize) {
    std::cerr << "ERROR: AddData(): Data size exceeded a limit = " << kMaxArraySize << std::endl;
    throw 1;
  }
  input_values_[size_] = value;
  size_++;
}

void CountingSort::Sort() {
  try {
    ComputeCounts();
    ComputeCumulativeCounts();
    ComputeSortedOutput();
  } catch (...) {
    std::cerr << "ERROR: Sort()" << std::endl;
    throw;
  }
}

void CountingSort::Print() const noexcept {
  for (int32_t index = 0; index < size_; ++index) {
    if (index != 0) {
      std::cout << " ";
    }
    std::cout << output_values_[index];
  }
  std::cout << std::endl;
}

void CountingSort::ResetData() noexcept {
  size_ = 0;
}

void CountingSort::ComputeCounts(void) noexcept {
  for (int32_t index_input = 0; index_input < size_; ++index_input) {
    ++counts_[input_values_[index_input]];
  }
}

void CountingSort::ComputeCumulativeCounts(void) noexcept {
  for (int32_t index_count = 1; index_count <= kMaxIntegerValue; ++index_count) {
    counts_[index_count] += counts_[index_count - 1];
  }
}

void CountingSort::ComputeSortedOutput(void) noexcept {
  for (int32_t index_input = size_ - 1; index_input >= 0; --index_input) {
    const int32_t current_input_value = input_values_[index_input];
    output_values_[counts_[current_input_value] - 1] = current_input_value;
    --counts_[current_input_value];
  }
}

}  // namespace ALDS1_6_A
