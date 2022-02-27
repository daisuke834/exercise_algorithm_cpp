/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-2. 初等的整列、挿入ソート。
 * 時間計算量(time complexity): 最悪計算時間=O(N^2), 最良計算時間=O(N), 平均計算時間=O(N^2)
 * 領域計算量(space complexity): O(N), 外部にO(1)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C03_2_ALDS1_1_A_insertion_sort.h"

#include <iostream>
namespace ALDS1_1_A {

InsertionSort::InsertionSort() noexcept : count_(0), values_{-1} {}

InsertionSort::~InsertionSort() noexcept {}

void InsertionSort::Main(std::istream& input_stream) noexcept {
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

void InsertionSort::Sort() noexcept {
  for (int32_t index_source = 1; index_source < count_; ++index_source) {
    Print();
    SwapAndInsert(index_source);
  }
}

void InsertionSort::SwapAndInsert(const int32_t index_source) noexcept {
  int32_t cvalue = values_[index_source];
  int32_t index_insert_target = index_source;
  for (int32_t index_compare = index_source - 1; index_compare >= 0; --index_compare) {
    if (ShouldSwap(index_compare, cvalue)) {
      index_insert_target = SwapAndGetInsertPoint(index_compare);
    } else {
      break;
    }
  }
  Insert(index_insert_target, cvalue);
}

bool InsertionSort::ShouldSwap(const int32_t index_compare, const int32_t cvalue) noexcept {
  return (values_[index_compare] > cvalue);
}

int32_t InsertionSort::SwapAndGetInsertPoint(const int32_t index_compare) noexcept {
  values_[index_compare + 1] = values_[index_compare];
  const int32_t index_insert_target = index_compare;
  return index_insert_target;
}

void InsertionSort::Insert(const int32_t index_insert_target, const int32_t cvalue) noexcept {
  values_[index_insert_target] = cvalue;
}

void InsertionSort::Load(std::istream& input_stream) {
  input_stream >> count_;
  if (count_ > kMaxArraySize) {
    std::cout << "kMaxArraySize is too small for the number of data count." << std::endl;
    throw 1;
  }
  for (int32_t index = 0; index < count_; ++index) {
    input_stream >> values_[index];
  }
}

void InsertionSort::Print() const noexcept {
  for (int32_t index = 0; index < count_; ++index) {
    if (index != 0) {
      std::cout << " ";
    }
    std::cout << values_[index];
  }
  std::cout << std::endl;
}

}  // namespace ALDS1_1_A
