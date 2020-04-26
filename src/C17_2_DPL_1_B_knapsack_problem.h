/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-2. 動的計画法(Dynamic Programming, DP)、0-1ナップザック問題(Knapsack Problem)。
 * 計算量はO(number_of_items*capacity_of_knapsack)、外部メモリはO(kMaxNumberOfItems*kMaxCapacity)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C17_2_DPL_1_B_KNAPSACK_PROBLEM_H_
#define SRC_C17_2_DPL_1_B_KNAPSACK_PROBLEM_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>

namespace DPL_1_B {

constexpr int32_t kMaxNumberOfItems = 100;
constexpr int32_t kMaxWeight = 1000;
constexpr int32_t kMaxCapacity = 10000;

void CallKnapsackProblem(std::istream &input_stream);

struct Item {
  int32_t value{0};
  int32_t weight{0};
};

class KnapsackProblem {
 public:
  KnapsackProblem() noexcept;
  ~KnapsackProblem() noexcept;
  void AddItem(const int32_t value, const int32_t weight);
  int32_t FindMaxValue(const int32_t capacity_of_knapsack);

 private:
  int32_t GetMaxValue(const int32_t tail_of_used_item, const int32_t capacity) const noexcept;

  KnapsackProblem(const KnapsackProblem &obj) = delete;
  KnapsackProblem &operator=(const KnapsackProblem &obj) = delete;
  KnapsackProblem(KnapsackProblem &&obj) = delete;
  KnapsackProblem &operator=(KnapsackProblem &&obj) = delete;

 private:
  int32_t number_of_items_;
  Item items_[kMaxNumberOfItems];
  int32_t lookup_values_[kMaxNumberOfItems][kMaxCapacity + 1];

 private:
  FRIEND_TEST(Test_DPL_1_B, dummy);  // Should be removed from production code
};

}  // namespace DPL_1_B

#endif  // SRC_C17_2_DPL_1_B_KNAPSACK_PROBLEM_H_
