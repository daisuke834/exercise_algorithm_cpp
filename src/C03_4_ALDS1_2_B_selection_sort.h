/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-4. 初等的整列、選択ソート。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C03_4_ALDS1_2_B_SELECTION_SORT_H_
#define SRC_C03_4_ALDS1_2_B_SELECTION_SORT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>

namespace ALDS1_2_B {

constexpr int32_t kMaxArraySize = 100;

class SelectionSort {
 public:
  SelectionSort() noexcept;
  ~SelectionSort() noexcept;
  void Main(std::istream& input_stream) noexcept;

 private:
  void Sort() noexcept;
  int32_t FindMinimumIndex(int32_t index_unsorted_top) const noexcept;
  void Swap(const int32_t index_unsorted_top, const int32_t index_minimum) noexcept;
  void Load(std::istream& input_stream);
  void Print() const noexcept;

 private:
  SelectionSort(const SelectionSort& obj) = delete;
  SelectionSort& operator=(const SelectionSort& rhs) = delete;
  SelectionSort(SelectionSort&& obj) = delete;
  SelectionSort& operator=(SelectionSort&& rhs) = delete;

 private:
  int32_t count_;
  int32_t values_[kMaxArraySize];
  int32_t swapped_count_;

 private:
  FRIEND_TEST(Test_ALDS1_2_B, LoadData_abnormal);  // Should be removed from production code
};

}  // namespace ALDS1_2_B
#endif  // SRC_C03_4_ALDS1_2_B_SELECTION_SORT_H_
