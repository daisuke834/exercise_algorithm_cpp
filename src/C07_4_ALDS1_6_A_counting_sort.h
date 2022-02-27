/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-4. 高等的整列、計数ソート(Counting Sort)。
 * 最悪計算時間=O(n+k), 平均計算時間=O(n+k), 追加作業記憶領域=O(n+k). Stable sort.
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C07_4_ALDS1_6_A_COUNTING_SORT_H_
#define SRC_C07_4_ALDS1_6_A_COUNTING_SORT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_6_A {

constexpr int32_t kMaxArraySize = 2000000;
constexpr int32_t kMaxIntegerValue = 10000;

void CallCountingSort(std::istream& input_stream);

class CountingSort {
 public:
  CountingSort() noexcept;
  ~CountingSort() noexcept;
  void AddData(const int32_t value);
  void ResetData() noexcept;
  void Sort();
  void Print() const noexcept;

 private:
  CountingSort(const CountingSort& obj) = delete;
  CountingSort& operator=(const CountingSort& rhs) = delete;
  CountingSort(CountingSort&& obj) = delete;
  CountingSort& operator=(CountingSort&& rhs) = delete;

  void ComputeCounts(void) noexcept;
  void ComputeCumulativeCounts(void) noexcept;
  void ComputeSortedOutput(void) noexcept;

 private:
  int32_t size_;
  int32_t input_values_[kMaxArraySize];
  int32_t counts_[kMaxIntegerValue + 1];
  int32_t output_values_[kMaxArraySize];

 private:
  FRIEND_TEST(Test_ALDS1_6_A, AddData);  // Should be removed from production code
};

}  // namespace ALDS1_6_A

#endif  // SRC_C07_4_ALDS1_6_A_COUNTING_SORT_H_
