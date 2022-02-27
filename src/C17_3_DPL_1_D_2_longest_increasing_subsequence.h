/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-3. 動的計画法(Dynamic Programming, DP)、最長増加部分列(Longest Increasing Subsequence, LIS)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C17_3_DPL_1_D_2_LONGEST_INCREASING_SUBSEQUENCE_H_
#define SRC_C17_3_DPL_1_D_2_LONGEST_INCREASING_SUBSEQUENCE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>

namespace DPL_1_D_2 {

constexpr int32_t kMaxLength = 100000;
constexpr int32_t kDoesNotExist = -1;

void CallLongestIncreasingSubsequence(std::istream& input_stream);

class LongestIncreasingSubsequence {
 public:
  LongestIncreasingSubsequence() noexcept;
  ~LongestIncreasingSubsequence() noexcept;
  void AppendValue(const int32_t value);
  int32_t FindLengthOfLis();

 private:
  void UpdateLisLength(const int32_t right_end);
  bool UpdateMappingAndLisLength(const int32_t lis_length_mapped_from, const int32_t right_end);
  bool MappingShouldBeUpdated(const int32_t lis_length_mapped_from, const int32_t right_end) const;
  bool CanAssignValidNextLeft(const int32_t lis_length_mapped_from, const int32_t right_end) const;
  bool IndexIsNotMappedYetToThisLength(const int32_t lis_length_mapped_from) const;
  bool RightendIsSmallerThanAssignedValue(const int32_t right_end, const int32_t lis_length_mapped_from) const;
  int32_t GetLengthOfLis() const noexcept;
  int32_t LoadIndexHavingLisLengthOf(const int32_t lis_length) const;
  void ResetLookUpTable() noexcept;
  bool IsValidIndex(const int32_t index) const noexcept;
  bool IsInvalidIndex(const int32_t index) const noexcept;

  LongestIncreasingSubsequence(const LongestIncreasingSubsequence& obj) = delete;
  LongestIncreasingSubsequence& operator=(const LongestIncreasingSubsequence& obj) = delete;
  LongestIncreasingSubsequence(LongestIncreasingSubsequence&& obj) = delete;
  LongestIncreasingSubsequence& operator=(LongestIncreasingSubsequence&& obj) = delete;

 private:
  int32_t length_;
  int32_t length_of_lis_;
  int32_t values_[kMaxLength];
  int32_t look_up_index_having_lis_length_of_[kMaxLength + 1];

 private:
  FRIEND_TEST(Test_DPL_1_D_2, FindLengthOfLis_1);  // Should be removed from production code
};

}  // namespace DPL_1_D_2

#endif  // SRC_C17_3_DPL_1_D_2_LONGEST_INCREASING_SUBSEQUENCE_H_
