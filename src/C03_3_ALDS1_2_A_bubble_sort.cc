/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-3. 初等的整列、バブルソート。
 * 時間計算量(time complexity): 最悪計算時間=O(N^2), 最良計算時間=O(N), 平均計算時間=O(N^2)
 * 領域計算量(space complexity): 外部にO(1)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C03_3_ALDS1_2_A_bubble_sort.h"

#include <iostream>
namespace ALDS1_2_A {

BubbleSort::BubbleSort() noexcept : count_(0), values_{-1}, swapped_count_{0} {}

BubbleSort::~BubbleSort() noexcept {}

void BubbleSort::Main(std::istream& input_stream) noexcept {
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

void BubbleSort::Sort() noexcept {
  bool should_scan = true;
  int32_t index_unsorted_head = 0;
  while (should_scan) {
    should_scan = false;
    for (int32_t index_target = count_ - 1; index_target >= index_unsorted_head + 1; --index_target) {
      if (ShouldSwap(index_target)) {
        SwapWithLeftNext(index_target);
        should_scan = true;
      }
    }
    ++index_unsorted_head;
  }
}

bool BubbleSort::ShouldSwap(const int32_t index_target) noexcept {
  return (values_[index_target - 1] > values_[index_target]);
}

void BubbleSort::SwapWithLeftNext(const int32_t index_target) noexcept {
  const int32_t cvalue = values_[index_target];
  values_[index_target] = values_[index_target - 1];
  values_[index_target - 1] = cvalue;
  ++swapped_count_;
}

void BubbleSort::Load(std::istream& input_stream) {
  input_stream >> count_;
  if (count_ > kMaxArraySize) {
    std::cout << "kMaxArraySize is too small for the number of data count." << std::endl;
    throw 1;
  }
  for (int32_t index = 0; index < count_; ++index) {
    input_stream >> values_[index];
  }
}

void BubbleSort::Print() const noexcept {
  for (int32_t index = 0; index < count_; ++index) {
    if (index != 0) {
      std::cout << " ";
    }
    std::cout << values_[index];
  }
  std::cout << std::endl;
  std::cout << swapped_count_ << std::endl;
}

}  // namespace ALDS1_2_A
