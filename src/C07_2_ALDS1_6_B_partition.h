/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-2. 高等的整列、パーティション(Partition)。
 * 最悪計算量=O(N), 追加作業記憶領域=O(1)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C07_2_ALDS1_6_B_PARTITION_H_
#define SRC_C07_2_ALDS1_6_B_PARTITION_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_6_B {

constexpr int32_t kMaxArraySize = 100000;

void CallPartition(std::istream& input_stream);

class Partition {
 public:
  Partition() noexcept;
  ~Partition() noexcept;
  void AddData(const int32_t value);
  void ResetData() noexcept;
  int32_t ComputePartition(const int32_t start, const int32_t end);
  int32_t GetValue(const int32_t index);

 private:
  Partition(const Partition& obj) = delete;
  Partition& operator=(const Partition& rhs) = delete;
  Partition(Partition&& obj) = delete;
  Partition& operator=(Partition&& rhs) = delete;

  void Swap(const int32_t index_1, const int32_t index_2);
  bool IndexOutOfRange(const int32_t index) const noexcept;

 private:
  int32_t size_;
  int32_t values_[kMaxArraySize];

 private:
  FRIEND_TEST(Test_ALDS1_6_B, AddData);             // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_6_B, Swap);                // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_6_B, ComputePartition_1);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_6_B, ComputePartition_2);  // Should be removed from production code
};

}  // namespace ALDS1_6_B

#endif  // SRC_C07_2_ALDS1_6_B_PARTITION_H_
