/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-3. 動的計画法(Dynamic Programming, DP)、最長増加部分列(Longest Increasing Subsequence, LIS)。
 * LUTは常に昇順になっているので、上方から検索することで平均計算量はO(n*log(n))。最悪計算量はO(n^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C17_3_DPL_1_D_2_longest_increasing_subsequence.h"
#include <iostream>
#include <string>

namespace DPL_1_D_2 {

void CallLongestIncreasingSubsequence(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  LongestIncreasingSubsequence *longest_increasing_subsequence = new LongestIncreasingSubsequence();
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
  }
  const int32_t index_stored = length_;
  values_[index_stored] = value;
  ++length_;
}

int32_t LongestIncreasingSubsequence::FindLengthOfLis() {
  try {
    ResetLookUpTable();
    for (int32_t current_right_end = 0; current_right_end < length_; ++current_right_end) {
      UpdateLisLength(current_right_end);
    }
  } catch (...) {
    std::cerr << "ERROR: FindLengthOfLis()" << std::endl;
    throw;
  }
  return length_of_lis_;
}

void LongestIncreasingSubsequence::UpdateLisLength(const int32_t right_end) {
  try {
    for (int32_t lis_length_mapped_from = length_of_lis_ + 1; lis_length_mapped_from >= 1; --lis_length_mapped_from) {
      const bool mapping_was_updated = UpdateMappingAndLisLength(lis_length_mapped_from, right_end);
      if (mapping_was_updated) {
        break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: UpdateLisLength()" << std::endl;
    throw;
  }
}

bool LongestIncreasingSubsequence::UpdateMappingAndLisLength(const int32_t lis_length_mapped_from,
                                                             const int32_t right_end) {
  bool mapping_was_updated = false;
  try {
    if (MappingShouldBeUpdated(lis_length_mapped_from, right_end)) {
      look_up_index_having_lis_length_of_[lis_length_mapped_from] = right_end;
      mapping_was_updated = true;
      if (lis_length_mapped_from > length_of_lis_) {
        length_of_lis_ = lis_length_mapped_from;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: UpdateMappingAndLisLength()" << std::endl;
    throw;
  }
  return mapping_was_updated;
}

bool LongestIncreasingSubsequence::MappingShouldBeUpdated(const int32_t lis_length_mapped_from,
                                                          const int32_t right_end) const {
  bool mapping_should_be_updated;
  try {
    if (lis_length_mapped_from == 0) {
      std::cerr << "ERROR: MappingShouldBeUpdated(): Invalid arg lis_length_mapped_from=" << lis_length_mapped_from
                << std::endl;
      throw 1;
    } else if (lis_length_mapped_from == 1) {
      mapping_should_be_updated = RightendIsSmallerThanAssignedValue(right_end, lis_length_mapped_from);
    } else {
      mapping_should_be_updated = false;
      if (CanAssignValidNextLeft(lis_length_mapped_from, right_end)) {
        mapping_should_be_updated = (IndexIsNotMappedYetToThisLength(lis_length_mapped_from) ||
                                     RightendIsSmallerThanAssignedValue(right_end, lis_length_mapped_from));
      }
    }
  } catch (...) {
    std::cerr << "ERROR: MappingShouldBeUpdated()" << std::endl;
    throw;
  }
  return mapping_should_be_updated;
}

bool LongestIncreasingSubsequence::RightendIsSmallerThanAssignedValue(const int32_t right_end,
                                                                      const int32_t lis_length_mapped_from) const {
  bool smaller_value_is_assigned;
  try {
    const int32_t index_already_having_this_length = LoadIndexHavingLisLengthOf(lis_length_mapped_from);
    smaller_value_is_assigned = (values_[right_end] < values_[index_already_having_this_length]);
  } catch (...) {
    std::cerr << "ERROR: RightendIsSmallerThanAssignedValue()" << std::endl;
    throw;
  }
  return smaller_value_is_assigned;
}

bool LongestIncreasingSubsequence::IndexIsNotMappedYetToThisLength(const int32_t lis_length_mapped_from) const {
  bool index_is_not_mapped;
  try {
    const int32_t index_already_having_this_length = LoadIndexHavingLisLengthOf(lis_length_mapped_from);
    index_is_not_mapped = IsInvalidIndex(index_already_having_this_length);
  } catch (...) {
    std::cerr << "ERROR: IndexIsNotMappedYetToThisLength()" << std::endl;
    throw;
  }
  return index_is_not_mapped;
}

bool LongestIncreasingSubsequence::CanAssignValidNextLeft(const int32_t lis_length_mapped_from,
                                                          const int32_t right_end) const {
  bool can_assign_valid_next_left;
  try {
    const int32_t candidate_next_left = LoadIndexHavingLisLengthOf(lis_length_mapped_from - 1);
    can_assign_valid_next_left =
        IsValidIndex(candidate_next_left) && (values_[candidate_next_left] < values_[right_end]);
  } catch (...) {
    std::cerr << "ERROR: CanAssignValidNextLeft()" << std::endl;
    throw;
  }
  return can_assign_valid_next_left;
}

int32_t LongestIncreasingSubsequence::LoadIndexHavingLisLengthOf(const int32_t lis_length) const {
  if ((lis_length < 1) || (lis_length > length_)) {
    std::cerr << "ERROR: LoadIndexHavingLisLengthOf(): Invalid lis_length=" << lis_length << std::endl;
    throw 1;
  }
  return look_up_index_having_lis_length_of_[lis_length];
}

void LongestIncreasingSubsequence::ResetLookUpTable() noexcept {
  length_of_lis_ = 1;
  for (int32_t lis_length = 0; lis_length <= length_; ++lis_length) {
    look_up_index_having_lis_length_of_[lis_length] = kDoesNotExist;
  }
  look_up_index_having_lis_length_of_[1] = 0;
}

bool LongestIncreasingSubsequence::IsValidIndex(const int32_t index) const noexcept {
  return ((index >= 0) && (index < length_));
}

bool LongestIncreasingSubsequence::IsInvalidIndex(const int32_t index) const noexcept {
  return !IsValidIndex(index);
}

}  // namespace DPL_1_D_2
