/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-3. 動的計画法(Dynamic Programming, DP)、最長増加部分列(Longest Increasing Subsequence, LIS)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C17_3_DPL_1_D_1_LONGEST_INCREASING_SUBSEQUENCE_H_
#define SRC_C17_3_DPL_1_D_1_LONGEST_INCREASING_SUBSEQUENCE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>

namespace DPL_1_D_1 {

constexpr int32_t kMaxLength = 100000;

void CallLongestIncreasingSubsequence(std::istream &input_stream);

class LongestIncreasingSubsequence {
 public:
  LongestIncreasingSubsequence() noexcept;
  ~LongestIncreasingSubsequence() noexcept;
  void AppendValue(const int32_t value);
  int32_t FindLengthOfLis();

 private:
  int32_t ReadLengthOfLis(const int32_t index_right_end) const noexcept;

  LongestIncreasingSubsequence(const LongestIncreasingSubsequence &obj) = delete;
  LongestIncreasingSubsequence &operator=(const LongestIncreasingSubsequence &obj) = delete;
  LongestIncreasingSubsequence(LongestIncreasingSubsequence &&obj) = delete;
  LongestIncreasingSubsequence &operator=(LongestIncreasingSubsequence &&obj) = delete;

 private:
  int32_t length_;
  int32_t values_[kMaxLength];
  int32_t look_up_lis_length_of_this_right_edge_[kMaxLength];

 private:
  FRIEND_TEST(Test_DPL_1_D_1, FindLengthOfLis_1);  // Should be removed from production code
  FRIEND_TEST(Test_DPL_1_D_1, FindLengthOfLis_2);  // Should be removed from production code
};

}  // namespace DPL_1_D_1

#endif  // SRC_C17_3_DPL_1_D_1_LONGEST_INCREASING_SUBSEQUENCE_H_
