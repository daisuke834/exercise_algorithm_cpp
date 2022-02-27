/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-3. 動的計画法(Dynamic Programming, DP)、最長増加部分列(Longest Increasing Subsequence, LIS)。
 * 二重ループ構造になっているので、計算量はO(n^2)。外部記憶はO(n)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C17_3_DPL_1_D_1_longest_increasing_subsequence.h"

#include <iostream>
#include <string>

namespace DPL_1_D_1 {

void CallLongestIncreasingSubsequence(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  LongestIncreasingSubsequence* longest_increasing_subsequence = new LongestIncreasingSubsequence();
  try {
    int32_t length;
    input_stream >> length;
    for (int32_t i = 0; i < length; ++i) {
      int32_t value;
      input_stream >> value;
      longest_increasing_subsequence->AppendValue(value);
    }
    std::cout << longest_increasing_subsequence->FindLengthOfLis() << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallLongestIncreasingSubsequence()" << std::endl;
    delete longest_increasing_subsequence;
    throw;
  }
  delete longest_increasing_subsequence;
}

// ****************************************************
LongestIncreasingSubsequence::LongestIncreasingSubsequence() noexcept : length_(0) {}

LongestIncreasingSubsequence::~LongestIncreasingSubsequence() noexcept {}

void LongestIncreasingSubsequence::AppendValue(const int32_t value) {
  if (length_ >= kMaxLength) {
    std::cerr << "ERROR: AppendValue(): length_ exceeded a limit = " << kMaxLength << std::endl;
  }
  const int32_t index_stored = length_;
  values_[index_stored] = value;
  ++length_;
}

int32_t LongestIncreasingSubsequence::FindLengthOfLis() {
  int32_t length_of_lis = 0;
  for (int32_t current_right_end = 0; current_right_end < length_; ++current_right_end) {
    int32_t next_left = -1;
    for (int32_t candidate_next_left = -1; candidate_next_left < current_right_end; ++candidate_next_left) {
      const int32_t lis_length_of_candidate_next_left = ReadLengthOfLis(candidate_next_left);
      if (values_[candidate_next_left] < values_[current_right_end] &&
          lis_length_of_candidate_next_left > ReadLengthOfLis(next_left)) {
        next_left = candidate_next_left;
      }
    }
    look_up_lis_length_of_this_right_edge_[current_right_end] = ReadLengthOfLis(next_left) + 1;
    if (length_of_lis < look_up_lis_length_of_this_right_edge_[current_right_end]) {
      length_of_lis = look_up_lis_length_of_this_right_edge_[current_right_end];
    }
  }
  return length_of_lis;
}

int32_t LongestIncreasingSubsequence::ReadLengthOfLis(const int32_t index_right_end) const noexcept {
  return ((index_right_end >= 0) ? look_up_lis_length_of_this_right_edge_[index_right_end] : 0);
}

}  // namespace DPL_1_D_1
