/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part11-3. 動的計画法(Dynamic Programming, DP)、最長共通部分列(Longest Common Subsequence, LCS)。
 * 文字列の長さをnとmとした時、計算時間=O(n*m), 追加作業記憶領域=O(n*m).
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "3_ALDS1_10_C_lcs.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

namespace ALDS1_10_C {

void CallLCS(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  LCS* lcs = new LCS();
  try {
    int32_t number_of_problems;
    input_stream >> number_of_problems;
    for (int32_t i = 0; i < number_of_problems; ++i) {
      std::string text_1, text_2;
      input_stream >> text_1 >> text_2;
      std::cout << lcs->CalculateLcs(text_1, text_2) << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: CallLCS()" << std::endl;
    throw;
  }
  delete lcs;
}

// ****************************************************

LCS::LCS() noexcept : size_a_(0), size_b_(0) {}

LCS::~LCS() noexcept {}

int32_t LCS::CalculateLcs(const std::string& a, const std::string& b) {
  Reset(a, b);
  const int32_t lcs = CalculageLcsRecursively(size_a_, size_b_);
  return lcs;
}

int32_t LCS::CalculageLcsRecursively(const int32_t length_a, const int32_t length_b) {
  int32_t lcs;
  if ((length_a == 0) || (length_b == 0)) {
    lcs = 0;
  } else if (IsInvalidLengthA(length_a)) {
    std::cerr << "ERROR: CalculageLcsRecursively(): length_a = " << length_a << std::endl;
    throw 1;
  } else if (IsInvalidLengthB(length_b)) {
    std::cerr << "ERROR: CalculageLcsRecursively(): length_b = " << length_b << std::endl;
    throw 1;
  } else if (IsAlreadyCalculated(length_a, length_b)) {
    lcs = GetCalculatedResult(length_a, length_b);
  } else {
    if (a_[length_a - 1] == b_[length_b - 1]) {
      lcs = CalculageLcsRecursively(length_a - 1, length_b - 1) + 1;
    } else {
      const int32_t lcs_1 = CalculageLcsRecursively(length_a - 1, length_b);
      const int32_t lcs_2 = CalculageLcsRecursively(length_a, length_b - 1);
      lcs = std::max(lcs_1, lcs_2);
    }
    StoreCalculatedResult(length_a, length_b, lcs);
  }
  return lcs;
}

void LCS::Reset(const std::string& a, const std::string& b) {
  try {
    strncpy(a_, a.c_str(), a.size());
    strncpy(b_, b.c_str(), b.size());
    size_a_ = static_cast<int32_t>(a.size());
    size_b_ = static_cast<int32_t>(b.size());
    for (int32_t length_a = 1; length_a <= size_a_; ++length_a) {
      for (int32_t length_b = 1; length_b <= size_b_; ++length_b) {
        ResetCalculatedResult(length_a, length_b);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: Reset():" << std::endl;
    throw;
  }
}

bool LCS::IsInvalidLengthA(const int32_t length_a) const noexcept { return ((length_a <= 0) || (length_a > size_a_)); }

bool LCS::IsInvalidLengthB(const int32_t length_b) const noexcept { return ((length_b <= 0) || (length_b > size_b_)); }

bool LCS::IsAlreadyCalculated(const int32_t length_a, const int32_t length_b) const {
  if (IsInvalidLengthA(length_a)) {
    std::cerr << "ERROR: IsAlreadyCalculated(): length_a = " << length_a << std::endl;
    throw 1;
  } else if (IsInvalidLengthB(length_b)) {
    std::cerr << "ERROR: IsAlreadyCalculated(): length_b = " << length_b << std::endl;
    throw 1;
  } else {
    // DO NOTHING
  }
  return look_up_table_[length_a - 1][length_b - 1].calculated;
}

int32_t LCS::GetCalculatedResult(const int32_t length_a, const int32_t length_b) const {
  if (IsInvalidLengthA(length_a)) {
    std::cerr << "ERROR: GetCalculatedResult(): length_a = " << length_a << std::endl;
    throw 1;
  } else if (IsInvalidLengthB(length_b)) {
    std::cerr << "ERROR: GetCalculatedResult(): length_b = " << length_b << std::endl;
    throw 1;
  } else {
    // DO NOTHING
  }
  return look_up_table_[length_a - 1][length_b - 1].lcs;
}

void LCS::StoreCalculatedResult(const int32_t length_a, const int32_t length_b, const int32_t lcs) {
  if (IsInvalidLengthA(length_a)) {
    std::cerr << "ERROR: StoreCalculatedResult(): length_a = " << length_a << std::endl;
    throw 1;
  } else if (IsInvalidLengthB(length_b)) {
    std::cerr << "ERROR: StoreCalculatedResult(): length_b = " << length_b << std::endl;
    throw 1;
  } else {
    // DO NOTHING
  }
  look_up_table_[length_a - 1][length_b - 1].lcs = lcs;
  look_up_table_[length_a - 1][length_b - 1].calculated = true;
}

void LCS::ResetCalculatedResult(const int32_t length_a, const int32_t length_b) {
  if (IsInvalidLengthA(length_a)) {
    std::cerr << "ERROR: ResetCalculatedResult(): length_a = " << length_a << std::endl;
    throw 1;
  } else if (IsInvalidLengthB(length_b)) {
    std::cerr << "ERROR: ResetCalculatedResult(): length_b = " << length_b << std::endl;
    throw 1;
  } else {
    // DO NOTHING
  }
  look_up_table_[length_a - 1][length_b - 1].calculated = false;
}

}  // namespace ALDS1_10_C
