/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-5. 初等的整列、安定なソート。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C03_5_ALDS1_2_C_STABLE_SORT_H_
#define SRC_C03_5_ALDS1_2_C_STABLE_SORT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>

namespace ALDS1_2_C {

constexpr int32_t kMaxArraySize = 100;

struct Card {
  char suit;
  int32_t value;
};

struct CardGroup {
  int32_t count_;
  Card card_[kMaxArraySize];
};

class BubbleSort {
 public:
  BubbleSort() noexcept;
  ~BubbleSort() noexcept;
  void Sort() noexcept;
  void Print() const noexcept;
  void Load(const CardGroup &card_group) noexcept;
  bool IsStable(const CardGroup &card_group) const noexcept;

 private:
  bool ShouldSwap(const int32_t index_target) noexcept;
  void SwapWithLeftNext(const int32_t index_target) noexcept;

 private:
  BubbleSort(const BubbleSort &obj) = delete;
  BubbleSort &operator=(const BubbleSort &rhs) = delete;
  BubbleSort(BubbleSort &&obj) = delete;
  BubbleSort &operator=(BubbleSort &&rhs) = delete;

 private:
  CardGroup card_group_;
};

class SelectionSort {
 public:
  SelectionSort() noexcept;
  ~SelectionSort() noexcept;
  void Sort() noexcept;
  void Print() const noexcept;
  void Load(const CardGroup &card_group) noexcept;
  bool IsStable(const CardGroup &card_group_compare) const noexcept;

 private:
  int32_t FindMinimumIndex(int32_t index_unsorted_top) const noexcept;
  void Swap(const int32_t index_unsorted_top, const int32_t index_minimum) noexcept;

 private:
  SelectionSort(const SelectionSort &obj) = delete;
  SelectionSort &operator=(const SelectionSort &obj) = delete;
  SelectionSort(SelectionSort &&obj) = delete;
  SelectionSort &operator=(SelectionSort &&obj) = delete;

 private:
  CardGroup card_group_;
};

class StableSort {
 public:
  StableSort() noexcept;
  ~StableSort() noexcept;
  void Main(std::istream &input_stream) noexcept;

 private:
  void Sort() noexcept;
  void Print() const noexcept;
  void Load(std::istream &input_stream);

 private:
  StableSort(const StableSort &obj) = delete;
  StableSort &operator=(const StableSort &obj) = delete;
  StableSort(StableSort &&obj) = delete;
  StableSort &operator=(StableSort &&obj) = delete;

 private:
  CardGroup card_group_;
  BubbleSort bubble_sort_;
  SelectionSort selection_sort_;

 private:
  FRIEND_TEST(Test_ALDS1_2_C, LoadData_abnormal);  // Should be removed from production code
};

bool IsSameCard(const Card &a, const Card &b) noexcept;
bool IsSameValue(const Card &a, const Card &b) noexcept;

}  // namespace ALDS1_2_C
#endif  // SRC_C03_5_ALDS1_2_C_STABLE_SORT_H_
