/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-7. 高等的整列、最小コストソート(Minimum Cost Sort)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C07_7_ALDS1_6_D_MINIMUM_COST_SORT_H_
#define SRC_C07_7_ALDS1_6_D_MINIMUM_COST_SORT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_6_D {

constexpr int32_t kMaxArraySize = 1000;
constexpr int32_t kMaxValue = 10000;

void CallMinimumCostSort(std::istream &input_stream);

class MinimumCostSort {
 public:
  MinimumCostSort() noexcept;
  ~MinimumCostSort() noexcept;
  void AddData(const int32_t value);
  void ResetData() noexcept;
  void Sort();
  int32_t CalculateMinimumCost();
  void GenerateMapping();
  int32_t CalculateMinimumCostOfLoop(const int32_t index_start);

 private:
  MinimumCostSort(const MinimumCostSort &obj) = delete;
  MinimumCostSort &operator=(const MinimumCostSort &rhs) = delete;
  MinimumCostSort(MinimumCostSort &&obj) = delete;
  MinimumCostSort &operator=(MinimumCostSort &&rhs) = delete;

  int32_t CalculateCost(const int32_t end_index);
  static int32_t MinimumCostUsingMinimumInLoop(const int32_t sum_of_weights_in_loop,
                                               const int32_t number_of_nodes_in_loop,
                                               const int32_t minimum_value_in_loop) noexcept;
  int32_t MinimumCostUsingSharedMinimum(const int32_t sum_of_weights_in_loop, const int32_t number_of_nodes_in_loop,
                                        const int32_t minimum_value_in_loop) const noexcept;

  void ComputeMergeSort(const int32_t left_end, const int32_t right_end);
  void MergeLeftAndRight(const int32_t left_end, const int32_t center, const int32_t right_end);
  int32_t GetCenterIndex(const int32_t left_end, const int32_t right_end) const;

 private:
  int32_t size_;
  int32_t smallest_value_;
  int32_t sorted_values_[kMaxArraySize];
  int32_t input_values_[kMaxArraySize];
  bool evaluated_[kMaxArraySize];
  int32_t next_index_[kMaxValue + 1];

  int32_t left_values_[kMaxArraySize / 2 + 1];   //< 作業領域
  int32_t right_values_[kMaxArraySize / 2 + 1];  //< 作業領域

 private:
  FRIEND_TEST(Test_ALDS1_6_D, AddData);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_6_D, Sort_1);   // Should be removed from production code
};

}  // namespace ALDS1_6_D

#endif  // SRC_C07_7_ALDS1_6_D_MINIMUM_COST_SORT_H_
