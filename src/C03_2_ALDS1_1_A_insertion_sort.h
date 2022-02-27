/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-2. 初等的整列、挿入ソート。
 * 時間計算量(time complexity): 最悪計算時間=O(N^2), 最良計算時間=O(N), 平均計算時間=O(N^2)
 * 領域計算量(space complexity): O(N), 外部にO(1)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C03_2_ALDS1_1_A_INSERTION_SORT_H_
#define SRC_C03_2_ALDS1_1_A_INSERTION_SORT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>

namespace ALDS1_1_A {

constexpr int32_t kMaxArraySize = 100;

class InsertionSort {
 public:
  InsertionSort() noexcept;
  ~InsertionSort() noexcept;
  void Main(std::istream& input_stream) noexcept;

 private:
  void Sort() noexcept;
  void SwapAndInsert(const int32_t index_source) noexcept;
  bool ShouldSwap(const int32_t index_compare, const int32_t cvalue) noexcept;
  int32_t SwapAndGetInsertPoint(const int32_t index_compare) noexcept;
  void Insert(const int32_t index_insert_target, const int32_t cvalue) noexcept;
  void Load(std::istream& input_stream);
  void Print() const noexcept;

 private:
  InsertionSort(const InsertionSort& obj) = delete;
  InsertionSort& operator=(const InsertionSort& rhs) = delete;
  InsertionSort(InsertionSort&& obj) = delete;
  InsertionSort& operator=(InsertionSort&& rhs) = delete;

 private:
  int32_t count_;
  int32_t values_[kMaxArraySize];

 private:
  FRIEND_TEST(Test_ALDS1_1_A, LoadData_abnormal);  // Should be removed from production code
};

}  // namespace ALDS1_1_A
#endif  // SRC_C03_2_ALDS1_1_A_INSERTION_SORT_H_
