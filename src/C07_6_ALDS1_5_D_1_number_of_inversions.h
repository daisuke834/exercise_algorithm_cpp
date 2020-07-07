/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-6. 高等的整列、反転数(The Number of Inversions)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C07_6_ALDS1_5_D_1_NUMBER_OF_INVERSIONS_H_
#define SRC_C07_6_ALDS1_5_D_1_NUMBER_OF_INVERSIONS_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_5_D_1 {

constexpr int32_t kMaxArraySize = 200000;

void CallNumberOfInversions(std::istream &input_stream);

class NumberOfInversions {
 public:
  NumberOfInversions() noexcept;
  ~NumberOfInversions() noexcept;
  void AddData(const int32_t value);
  void ResetData() noexcept;
  void CalculateNumberOfInversions() noexcept;
  int64_t GetNumberOfInversions() const noexcept;
  void Print() const noexcept;

 private:
  NumberOfInversions(const NumberOfInversions &obj) = delete;
  NumberOfInversions &operator=(const NumberOfInversions &rhs) = delete;
  NumberOfInversions(NumberOfInversions &&obj) = delete;
  NumberOfInversions &operator=(NumberOfInversions &&rhs) = delete;

  void ComputeMergeSort(const int32_t left_end, const int32_t right_end);
  void MergeLeftAndRight(const int32_t left_end, const int32_t center, const int32_t right_end);
  int32_t GetCenterIndex(const int32_t left_end, const int32_t right_end) const;

 private:
  int32_t size_;
  int32_t values_[kMaxArraySize];
  int64_t number_of_inversions_;
  int32_t left_values_[kMaxArraySize / 2 + 1];   //< 作業領域
  int32_t right_values_[kMaxArraySize / 2 + 1];  //< 作業領域

 private:
  FRIEND_TEST(Test_ALDS1_5_D_1, AddData);                         // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_5_D_1, CalculateNumberOfInversions_10);  // Should be removed from production code
};

}  // namespace ALDS1_5_D_1

#endif  // SRC_C07_6_ALDS1_5_D_1_NUMBER_OF_INVERSIONS_H_
