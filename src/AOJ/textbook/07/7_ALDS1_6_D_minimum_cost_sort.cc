/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-7. 高等的整列、最小コストソート(Minimum Cost Sort)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "7_ALDS1_6_D_minimum_cost_sort.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace ALDS1_6_D {

void CallMinimumCostSort(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  MinimumCostSort* minimum_cost_sort = new MinimumCostSort();
  try {
    int32_t count;
    input_stream >> count;
    for (int32_t index = 0; index < count; ++index) {
      int32_t cvalue;
      input_stream >> cvalue;
      minimum_cost_sort->AddData(cvalue);
    }
    int32_t cost = minimum_cost_sort->CalculateMinimumCost();
    std::cout << cost << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallMinimumCostSort()" << std::endl;
    throw;
  }
  delete minimum_cost_sort;
}

// ****************************************************

MinimumCostSort::MinimumCostSort() noexcept
    : size_(0),
      smallest_value_(INT32_MAX),
      sorted_values_{},
      input_values_{},
      evaluated_{},
      next_index_{},
      left_values_{},
      right_values_{} {
  for (bool& e : evaluated_) {
    e = false;
  }
}
MinimumCostSort::~MinimumCostSort() noexcept {}

int32_t MinimumCostSort::CalculateMinimumCost() {
  int32_t total_cost = 0;
  try {
    Sort();
    GenerateMapping();
    for (int32_t index_start = 0; index_start < size_; ++index_start) {
      if (evaluated_[index_start]) {
        // DO NOTHING
      } else {
        total_cost += CalculateMinimumCostOfLoop(index_start);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CalculateMinimumCost()" << std::endl;
    throw;
  }
  return total_cost;
}

int32_t MinimumCostSort::CalculateMinimumCostOfLoop(const int32_t index_start) {
  if ((index_start < 0) || (index_start >= kMaxArraySize)) {
    std::cerr << "ERROR: CalculateMinimumCostOfLoop(): invalid arg index_start = " << index_start << std::endl;
    throw 1;
  }
  int32_t current_index = index_start;
  int32_t sum_of_weights_in_loop = 0;
  int32_t minimum_value_in_loop = INT32_MAX;
  int32_t number_of_nodes_in_loop = 0;
  for (int32_t i = 0; i < size_; ++i) {
    evaluated_[current_index] = true;
    ++number_of_nodes_in_loop;
    const int32_t cvalue = input_values_[current_index];
    minimum_value_in_loop = std::min(cvalue, minimum_value_in_loop);
    sum_of_weights_in_loop += cvalue;
    current_index = next_index_[cvalue];
    if ((current_index < 0) || (current_index >= kMaxArraySize)) {
      std::cerr << "ERROR: CalculateMinimumCostOfLoop(): invalid current_index = " << current_index << std::endl;
      throw 1;
    } else if (evaluated_[current_index]) {
      break;
    } else {
      // DO NOTHING
    }
  }
  const int32_t cost_of_loop =
      std::min(MinimumCostUsingMinimumInLoop(sum_of_weights_in_loop, number_of_nodes_in_loop, minimum_value_in_loop),
               MinimumCostUsingSharedMinimum(sum_of_weights_in_loop, number_of_nodes_in_loop, minimum_value_in_loop));
  return cost_of_loop;
}

int32_t MinimumCostSort::MinimumCostUsingMinimumInLoop(const int32_t sum_of_weights_in_loop,
                                                       const int32_t number_of_nodes_in_loop,
                                                       const int32_t minimum_value_in_loop) noexcept {
  const int32_t cost = sum_of_weights_in_loop + (number_of_nodes_in_loop - 2) * minimum_value_in_loop;
  return cost;
}

int32_t MinimumCostSort::MinimumCostUsingSharedMinimum(const int32_t sum_of_weights_in_loop,
                                                       const int32_t number_of_nodes_in_loop,
                                                       const int32_t minimum_value_in_loop) const noexcept {
  const int32_t cost = sum_of_weights_in_loop + minimum_value_in_loop + (number_of_nodes_in_loop + 1) * smallest_value_;
  return cost;
}

void MinimumCostSort::GenerateMapping() {
  for (int32_t index = 0; index < size_; ++index) {
    const int32_t value = sorted_values_[index];
    if ((value < 0) || (value > kMaxValue)) {
      std::cerr << "ERROR: GenerateMapping(): Invalid value = " << value << std::endl;
      throw 1;
    }
    next_index_[value] = index;
  }
}

void MinimumCostSort::AddData(const int32_t value) {
  if (size_ >= kMaxArraySize) {
    std::cerr << "ERROR: AddData(): Data size exceeded a limit = " << kMaxArraySize << std::endl;
    throw 1;
  }
  sorted_values_[size_] = value;
  input_values_[size_] = value;
  smallest_value_ = std::min(value, smallest_value_);
  size_++;
}

void MinimumCostSort::Sort() {
  try {
    ComputeMergeSort(0, size_);
  } catch (...) {
    std::cerr << "ERROR: Sort()" << std::endl;
    throw;
  }
}

void MinimumCostSort::ComputeMergeSort(const int32_t left_end, const int32_t right_end) {
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

void MinimumCostSort::MergeLeftAndRight(const int32_t left_end, const int32_t center, const int32_t right_end) {
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
      left_values_[index_left] = sorted_values_[left_end + index_left];
    }
    left_values_[left_size] = INT32_MAX;
    for (int32_t index_right = 0; index_right < right_size; ++index_right) {
      right_values_[index_right] = sorted_values_[center + index_right];
    }
    right_values_[right_size] = INT32_MAX;

    int32_t index_left = 0;
    int32_t index_right = 0;
    for (int32_t index_target = left_end; index_target < right_end; ++index_target) {
      if (left_values_[index_left] <= right_values_[index_right]) {
        sorted_values_[index_target] = left_values_[index_left];
        ++index_left;
      } else {
        sorted_values_[index_target] = right_values_[index_right];
        ++index_right;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: MergeLeftAndRight()" << std::endl;
    throw;
  }
}

int32_t MinimumCostSort::GetCenterIndex(const int32_t left_end, const int32_t right_end) const {
  // endは右端indexの右一つ隣のindex (無効領域の先頭)left_end(有効) < center(有効) < right_end(無効)
  if ((right_end <= left_end + 1) || ((left_end < 0) || (right_end > size_))) {
    std::cerr << "ERROR: GetCenterIndex: invalid args. left_end=" << left_end << ", right_end=" << right_end
              << std::endl;
    throw 1;
  }
  return (left_end + right_end) / 2;
}

void MinimumCostSort::ResetData() noexcept { size_ = 0; }

}  // namespace ALDS1_6_D
