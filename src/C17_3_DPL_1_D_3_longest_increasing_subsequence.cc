/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-3. 動的計画法(Dynamic Programming, DP)、最長増加部分列(Longest Increasing Subsequence, LIS)。
 * LUTは常に昇順になっており、二分探索により検索するので、最悪計算量はO(n*log(n))。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C17_3_DPL_1_D_3_longest_increasing_subsequence.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace DPL_1_D_3 {

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
LongestIncreasingSubsequence::LongestIncreasingSubsequence() noexcept : length_(0), length_of_lis_(1) {}

LongestIncreasingSubsequence::~LongestIncreasingSubsequence() noexcept {}

void LongestIncreasingSubsequence::AppendValue(const int32_t value) {
  if (length_ >= kMaxLength) {
    std::cerr << "ERROR: AppendValue(): length_ exceeded a limit = " << kMaxLength << std::endl;
    throw 1;
  }
  const int32_t index_stored = length_;
  values_[index_stored] = value;
  ++length_;
}

int32_t LongestIncreasingSubsequence::FindLengthOfLis() noexcept {
  int32_t c_lis_length = 1;
  try {
    look_up_value_at_right_end_of_[c_lis_length] = values_[0];
    for (int32_t current_right_end = 0; current_right_end < length_; ++current_right_end) {
      int32_t current_value = values_[current_right_end];
      if (look_up_value_at_right_end_of_[c_lis_length] < current_value) {
        look_up_value_at_right_end_of_[c_lis_length + 1] = current_value;
        c_lis_length++;
      } else {
        int32_t* start = look_up_value_at_right_end_of_ + 1;
        int32_t* end = look_up_value_at_right_end_of_ + 1 + c_lis_length;
        *std::lower_bound(start, end, current_value) = current_value;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: FindLengthOfLis()" << std::endl;
    throw;
  }
  return c_lis_length;
}

}  // namespace DPL_1_D_3
