/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-1. 高等的整列、マージソート(Merge Sort)。
 * 最悪計算時間=O(N*log(N)), 平均計算時間=O(N*log(N)), 追加作業記憶領域=O(N). Stableなsort.
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C07_1_ALDS1_5_B_MERGE_SORT_H_
#define SRC_C07_1_ALDS1_5_B_MERGE_SORT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_5_B {

constexpr int32_t kMaxArraySize = 500000;

void CallMergeSort(std::istream &input_stream);

class MergeSort {
 public:
  MergeSort() noexcept;
  ~MergeSort() noexcept;
  void AddData(const int32_t value);
  void ResetData() noexcept;
  void Sort();
  void Print() const noexcept;
  int32_t GetValue(const int32_t index) const;

 private:
  MergeSort(const MergeSort &obj) = delete;
  MergeSort &operator=(const MergeSort &rhs) = delete;
  MergeSort(MergeSort &&obj) = delete;
  MergeSort &operator=(MergeSort &&rhs) = delete;

  void ComputeMergeSort(const int32_t left_end, const int32_t right_end);
  void MergeLeftAndRight(const int32_t left_end, const int32_t center, const int32_t right_end);
  int32_t GetCenterIndex(const int32_t left_end, const int32_t right_end) const;

 private:
  int32_t size_;
  int32_t comparison_count_;  //< デバッグ用
  int32_t values_[kMaxArraySize];
  int32_t left_values_[kMaxArraySize / 2 + 1];   //< 作業領域
  int32_t right_values_[kMaxArraySize / 2 + 1];  //< 作業領域

 private:
  FRIEND_TEST(Test_ALDS1_5_B, AddData);            // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_5_B, GetCenterIndex);     // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_5_B, MergeLeftAndRight);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_5_B, ComputeMergeSort);   // Should be removed from production code
};

}  // namespace ALDS1_5_B

#endif  // SRC_C07_1_ALDS1_5_B_MERGE_SORT_H_
