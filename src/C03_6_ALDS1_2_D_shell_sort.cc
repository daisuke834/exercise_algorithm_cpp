/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-6. 初等的整列、シェルソート。
 * 時間計算量(time complexity): 最悪計算時間=O(N^2), 最良計算時間=O(N*logN), 平均計算時間=O(N^1.25)
 * 領域計算量(space complexity): O(N), 外部にO(1)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C03_6_ALDS1_2_D_shell_sort.h"

#include <iostream>
namespace ALDS1_2_D {

ShellSort::ShellSort() noexcept : count_(0), swap_count_(0), number_of_gaps_(0), gaps_{-1}, values_{-1} {}

ShellSort::~ShellSort() noexcept {}

void ShellSort::Main(std::istream& input_stream) noexcept {
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

void ShellSort::Sort() noexcept {
  CalculateGaps();
  for (int32_t index = number_of_gaps_ - 1; index >= 0; --index) {
    InsertionSort(gaps_[index]);
  }
}

void ShellSort::CalculateGaps() noexcept {
  gaps_[0] = 1;
  for (number_of_gaps_ = 1; number_of_gaps_ <= 100; ++number_of_gaps_) {
    gaps_[number_of_gaps_] = 3 * gaps_[number_of_gaps_ - 1] + 1;
    if (gaps_[number_of_gaps_] > count_) {
      break;
    }
  }
}

void ShellSort::InsertionSort(const int32_t gap) noexcept {
  for (int32_t index_source = gap; index_source < count_; ++index_source) {
    SwapAndInsert(index_source, gap);
  }
}

void ShellSort::SwapAndInsert(const int32_t index_source, const int32_t gap) noexcept {
  int32_t cvalue = values_[index_source];
  int32_t index_insert_target = index_source;
  for (int32_t index_compare = index_source - gap; index_compare >= 0; index_compare -= gap) {
    if (ShouldSwap(index_compare, cvalue)) {
      index_insert_target = SwapAndGetInsertPoint(index_compare, gap);
    } else {
      break;
    }
  }
  Insert(index_insert_target, cvalue);
}

bool ShellSort::ShouldSwap(const int32_t index_compare, const int32_t cvalue) noexcept {
  return (values_[index_compare] > cvalue);
}

int32_t ShellSort::SwapAndGetInsertPoint(const int32_t index_compare, const int32_t gap) noexcept {
  values_[index_compare + gap] = values_[index_compare];
  const int32_t index_insert_target = index_compare;
  ++swap_count_;
  return index_insert_target;
}

void ShellSort::Insert(const int32_t index_insert_target, const int32_t cvalue) noexcept {
  values_[index_insert_target] = cvalue;
}

void ShellSort::Load(std::istream& input_stream) {
  input_stream >> count_;
  if (count_ > kMaxArraySize) {
    std::cout << "kMaxArraySize is too small for the number of data count." << std::endl;
    throw 1;
  }
  for (int32_t index = 0; index < count_; ++index) {
    input_stream >> values_[index];
  }
}

void ShellSort::Print() const noexcept {
  std::cout << number_of_gaps_ << std::endl;
  for (int32_t index = number_of_gaps_ - 1; index >= 0; --index) {
    if (index != number_of_gaps_ - 1) {
      std::cout << " ";
    }
    std::cout << gaps_[index];
  }
  std::cout << std::endl;
  std::cout << swap_count_ << std::endl;
  for (int32_t index = 0; index < count_; ++index) {
    std::cout << values_[index] << std::endl;
  }
}

}  // namespace ALDS1_2_D
