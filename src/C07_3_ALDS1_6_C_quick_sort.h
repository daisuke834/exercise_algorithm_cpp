/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-3. 高等的整列、クイックソート(Quick Sort)。
 * 最悪計算時間=O(N^2), 平均計算時間=O(N*log(N)), 追加作業記憶領域=O(1). Stableでないsort.
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C07_3_ALDS1_6_C_QUICK_SORT_H_
#define SRC_C07_3_ALDS1_6_C_QUICK_SORT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_6_C {

constexpr int32_t kMaxArraySize = 100000;
constexpr char kInvalidSymbol = -1;
constexpr int32_t kInvalidNumber = -1;

void CallQuickSort(std::istream &input_stream);

struct Card {
  char symbol{kInvalidSymbol};
  int32_t number{kInvalidNumber};
};

class QuickSort {
 public:
  QuickSort() noexcept;
  ~QuickSort() noexcept;
  void AddCard(const std::string &symbol, const int32_t number);
  void ResetData() noexcept;
  Card GetCard(const int32_t index);
  void Sort();
  void Print() const noexcept;
  bool IsStable(const Card cards_[kMaxArraySize]) const noexcept;

 private:
  QuickSort(const QuickSort &obj) = delete;
  QuickSort &operator=(const QuickSort &rhs) = delete;
  QuickSort(QuickSort &&obj) = delete;
  QuickSort &operator=(QuickSort &&rhs) = delete;

  void ComputeQuickSort(const int32_t start, const int32_t end);
  int32_t ComputePartition(const int32_t start, const int32_t end);
  void Swap(const int32_t index_1, const int32_t index_2);

  bool IndexOutOfRange(const int32_t index) const noexcept;

 private:
  int32_t size_;
  Card cards_[kMaxArraySize];

 private:
  FRIEND_TEST(Test_ALDS1_6_C, AddCard);             // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_6_C, Swap);                // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_6_C, ComputePartition_1);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_6_C, ComputePartition_2);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_6_C, ComputePartition_3);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_6_C, ComputePartition_4);  // Should be removed from production code
};

bool IsSameCard(const Card &a, const Card &b) noexcept;
bool IsSameValue(const Card &a, const Card &b) noexcept;
Card ConvertCard(const std::string &symbol, const int32_t number);

}  // namespace ALDS1_6_C

#endif  // SRC_C07_3_ALDS1_6_C_QUICK_SORT_H_
