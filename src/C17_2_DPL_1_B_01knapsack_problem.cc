/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-2. 動的計画法(Dynamic Programming, DP)、0-1ナップザック問題(Knapsack Problem)。
 * 計算量はO(number_of_items*capacity_of_knapsack)、外部メモリはO(kMaxNumberOfItems*kMaxCapacity)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C17_2_DPL_1_B_01knapsack_problem.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace DPL_1_B {

void Call01KnapsackProblem(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  KnapsackProblem* knapsack = new KnapsackProblem();
  try {
    int32_t number_of_items, capacity_of_knapsack;
    input_stream >> number_of_items >> capacity_of_knapsack;
    for (int32_t i = 0; i < number_of_items; ++i) {
      int32_t value, weight;
      input_stream >> value >> weight;
      knapsack->AddItem(value, weight);
    }
    std::cout << knapsack->FindMaxValue(capacity_of_knapsack) << std::endl;
  } catch (...) {
    std::cerr << "ERROR: Call01KnapsackProblem()" << std::endl;
    delete knapsack;
    throw;
  }
  delete knapsack;
}

// ****************************************************
KnapsackProblem::KnapsackProblem() noexcept : number_of_items_(0) {}

KnapsackProblem::~KnapsackProblem() noexcept {}

void KnapsackProblem::AddItem(const int32_t value, const int32_t weight) {
  if (number_of_items_ >= kMaxNumberOfItems) {
    std::cerr << "ERROR: AddItem(): number_of_items_ exceeded a limit = " << kMaxNumberOfItems << std::endl;
  }
  const int32_t index_stored = number_of_items_;
  items_[index_stored].value = value;
  items_[index_stored].weight = weight;
  ++number_of_items_;
}

int32_t KnapsackProblem::FindMaxValue(const int32_t capacity_of_knapsack) {
  for (int32_t tail_of_used_item = 0; tail_of_used_item < number_of_items_; ++tail_of_used_item) {
    for (int32_t capacity = 0; capacity <= capacity_of_knapsack; ++capacity) {
      lookup_values_[tail_of_used_item][capacity] = 0;
    }
  }

  for (int32_t tail_of_used_item = 0; tail_of_used_item < number_of_items_; ++tail_of_used_item) {
    for (int32_t capacity = 1; capacity <= capacity_of_knapsack; ++capacity) {
      const int32_t remaining_capacity_if_use = capacity - items_[tail_of_used_item].weight;
      const int32_t value_if_used_this_item =
          (remaining_capacity_if_use >= 0)
              ? GetMaxValue(tail_of_used_item - 1, remaining_capacity_if_use) + items_[tail_of_used_item].value
              : 0;
      const int32_t value_if_not_used_this_item = GetMaxValue(tail_of_used_item - 1, capacity);
      lookup_values_[tail_of_used_item][capacity] = std::max(value_if_used_this_item, value_if_not_used_this_item);
    }
  }

  return lookup_values_[number_of_items_ - 1][capacity_of_knapsack];
}

int32_t KnapsackProblem::GetMaxValue(const int32_t tail_of_used_item, const int32_t capacity) const noexcept {
  int32_t value;
  if (tail_of_used_item < 0) {
    value = 0;
  } else if (capacity <= 0) {
    value = 0;
  } else {
    value = lookup_values_[tail_of_used_item][capacity];
  }
  return value;
}

}  // namespace DPL_1_B
