/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-3. 初等的整列、バブルソート。
 * 時間計算量(time complexity): 最悪計算時間=O(N^2), 最良計算時間=O(N), 平均計算時間=O(N^2)
 * 領域計算量(space complexity): 外部にO(1)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C03_3_ALDS1_2_A_BUBBLE_SORT_H_
#define SRC_C03_3_ALDS1_2_A_BUBBLE_SORT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>

namespace ALDS1_2_A {

constexpr int32_t kMaxArraySize = 100;

class BubbleSort {
 public:
  BubbleSort() noexcept;
  ~BubbleSort() noexcept;
  void Main(std::istream& input_stream) noexcept;

 private:
  void Sort() noexcept;
  bool ShouldSwap(const int32_t index_target) noexcept;
  void SwapWithLeftNext(const int32_t index_target) noexcept;
  void Load(std::istream& input_stream);
  void Print() const noexcept;

 private:
  BubbleSort(const BubbleSort& obj) = delete;
  BubbleSort& operator=(const BubbleSort& rhs) = delete;
  BubbleSort(BubbleSort&& obj) = delete;
  BubbleSort& operator=(BubbleSort&& rhs) = delete;

 private:
  int32_t count_;
  int32_t values_[kMaxArraySize];
  int32_t swapped_count_;

 private:
  FRIEND_TEST(Test_ALDS1_2_A, LoadData_abnormal);  // Should be removed from production code
};

}  // namespace ALDS1_2_A
#endif  // SRC_C03_3_ALDS1_2_A_BUBBLE_SORT_H_
