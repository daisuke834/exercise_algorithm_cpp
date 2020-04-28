/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Quick Sortのスクラッチ実装
 * 最悪計算時間=O(N^2), 平均計算時間=O(N*log(N)), 追加作業記憶領域=O(1). Stableでないsort.
 * 最悪計算時間は、pivotの選び方に依存。
 */

#ifndef SRC_B_QUICK_SORT_H_
#define SRC_B_QUICK_SORT_H_

// #include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace my_quick_sort {

constexpr int32_t kMaxNumberOfElements = 100000;
constexpr int32_t KMaxLoopCount = 2000000;

struct Element {
  int32_t value{INT32_MAX};
};

void CallQuickSort(std::istream &input_stream) noexcept;

class QuickSort {
 public:
  QuickSort() noexcept;
  ~QuickSort() noexcept;
  void AddElement(int32_t value);
  void PrintElements() const noexcept;
  void Sort();

 private:
  void ComputeQuickSort(const int32_t start, const int32_t end);
  int32_t ComputePartition(const int32_t start, const int32_t end);
  void Swap(const int32_t index_1, const int32_t index_2);
  bool IndexOutOfRange(const int32_t index) const noexcept;

  QuickSort(const QuickSort &obj) = delete;
  QuickSort &operator=(const QuickSort &rhs) = delete;
  QuickSort(QuickSort &&obj) = delete;
  QuickSort &operator=(QuickSort &&rhs) = delete;

 private:
  int32_t number_of_elements_;
  Element elements_[kMaxNumberOfElements];

  //  private:
  //   FRIEND_TEST(QuickSortTest, Test_1);  // Should be removed from production code
};

}  // namespace my_quick_sort

#endif  // SRC_B_QUICK_SORT_H_
