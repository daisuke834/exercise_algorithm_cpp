/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-6. 初等的整列、シェルソート。Shell Sort it not a stable sort.
 * 時間計算量(time complexity): 最悪計算時間=O(N^2), 最良計算時間=O(N*logN), 平均計算時間=O(N^1.25)
 * 領域計算量(space complexity): O(N), 外部にO(1)
 * 正確な時間計算量を求める方法は、未解決問題。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C03_6_ALDS1_2_D_SHELL_SORT_H_
#define SRC_C03_6_ALDS1_2_D_SHELL_SORT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>

namespace ALDS1_2_D {

constexpr int32_t kMaxArraySize = 1000000;

class ShellSort {
 public:
  ShellSort() noexcept;
  ~ShellSort() noexcept;
  void Main(std::istream &input_stream) noexcept;

 private:
  void Sort() noexcept;
  void InsertionSort(const int32_t gap) noexcept;
  void SwapAndInsert(const int32_t index_source, const int32_t gap) noexcept;
  bool ShouldSwap(const int32_t index_compare, const int32_t cvalue) noexcept;
  int32_t SwapAndGetInsertPoint(const int32_t index_compare, const int32_t gap) noexcept;
  void Insert(const int32_t index_insert_target, const int32_t cvalue) noexcept;
  void Load(std::istream &input_stream);
  void Print() const noexcept;
  void CalculateGaps() noexcept;

 private:
  ShellSort(const ShellSort &obj) = delete;
  ShellSort &operator=(const ShellSort &rhs) = delete;
  ShellSort(ShellSort &&obj) = delete;
  ShellSort &operator=(ShellSort &&rhs) = delete;

 private:
  int32_t count_;
  int64_t swap_count_;
  int32_t number_of_gaps_;
  int32_t gaps_[100];
  int32_t values_[kMaxArraySize];

 private:
  FRIEND_TEST(Test_ALDS1_2_D, InsertionSort_gap_1);   // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_2_D, InsertionSort_gap_2a);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_2_D, InsertionSort_gap_2b);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_2_D, InsertionSort_gap_2c);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_2_D, InsertionSort_gap_2d);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_2_D, InsertionSort_gap_4a);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_2_D, InsertionSort_gap_4b);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_2_D, SwapAndInsert);         // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_2_D, ShellSort);             // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_2_D, CalculateGaps);         // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_2_D, LoadData_abnormal);     // Should be removed from production code
};

}  // namespace ALDS1_2_D
#endif  // SRC_C03_6_ALDS1_2_D_SHELL_SORT_H_
