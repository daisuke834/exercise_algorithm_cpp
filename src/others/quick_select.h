/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Quick Selectのスクラッチ実装
 * 最悪計算時間=O(N^2), 平均計算時間=O(N), 追加作業記憶領域=O(1). Stableでないsort.
 * 最悪計算時間は、pivotの選び方に依存。
 */

#ifndef SRC_OTHERS_QUICK_SELECT_H_
#define SRC_OTHERS_QUICK_SELECT_H_

// #include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace my_quick_select {

constexpr int32_t kMaxNumberOfElements = 100000;
constexpr int32_t kMaxLoopCount = 2000000;

struct Element {
  int32_t value{INT32_MAX};
};

void CallQuickSelect(std::istream& input_stream) noexcept;

class QuickSelect {
 public:
  QuickSelect() noexcept;
  ~QuickSelect() noexcept;
  void AddElement(int32_t value);
  void PrintSelectedElements() const noexcept;
  void Select(const int32_t ordinal_number);

 private:
  void ComputeQuickSelect(const int32_t start, const int32_t end);
  int32_t ComputePartition(const int32_t start, const int32_t end);
  void Swap(const int32_t index_1, const int32_t index_2);
  bool IndexOutOfRange(const int32_t index) const noexcept;

  QuickSelect(const QuickSelect& obj) = delete;
  QuickSelect& operator=(const QuickSelect& rhs) = delete;
  QuickSelect(QuickSelect&& obj) = delete;
  QuickSelect& operator=(QuickSelect&& rhs) = delete;

 private:
  int32_t number_of_elements_;
  int32_t ordinal_index_;  // 0-base
  Element elements_[kMaxNumberOfElements];

  //  private:
  //   FRIEND_TEST(QuickSelectTest, Test_1);  // Should be removed from production code
};

}  // namespace my_quick_select

#endif  // SRC_OTHERS_QUICK_SELECT_H_
