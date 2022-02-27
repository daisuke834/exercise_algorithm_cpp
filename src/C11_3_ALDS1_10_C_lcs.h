/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part11-3. 動的計画法(Dynamic Programming, DP)、最長共通部分列(Longest Common Subsequence, LCS)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C11_3_ALDS1_10_C_LCS_H_
#define SRC_C11_3_ALDS1_10_C_LCS_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_10_C {

constexpr int32_t kMaxNumberOfString = 1000;
constexpr int32_t kNotFound = -1;

void CallLCS(std::istream& input_stream);

struct LookUp {
  bool calculated{false};
  int32_t lcs{0};
};

class LCS {
 public:
  LCS() noexcept;
  ~LCS() noexcept;

  int32_t CalculateLcs(const std::string& a, const std::string& b);

 private:
  int32_t CalculageLcsRecursively(const int32_t length_a, const int32_t length_b);
  void Reset(const std::string& a, const std::string& b);
  bool IsInvalidLengthA(const int32_t length_a) const noexcept;
  bool IsInvalidLengthB(const int32_t length_b) const noexcept;
  bool IsAlreadyCalculated(const int32_t length_a, const int32_t length_b) const;
  int32_t GetCalculatedResult(const int32_t length_a, const int32_t length_b) const;
  void StoreCalculatedResult(const int32_t length_a, const int32_t length_b, const int32_t lcs);
  void ResetCalculatedResult(const int32_t length_a, const int32_t length_b);

  LCS(const LCS& obj) = delete;
  LCS& operator=(const LCS& obj) = delete;
  LCS(LCS&& obj) = delete;
  LCS& operator=(LCS&& obj) = delete;

 private:
  int32_t size_a_;
  int32_t size_b_;
  char a_[kMaxNumberOfString + 1];
  char b_[kMaxNumberOfString + 1];
  LookUp look_up_table_[kMaxNumberOfString][kMaxNumberOfString];

 private:
  // FRIEND_TEST(Test_ALDS1_10_C, ConcatLookups);   // Should be removed from production code
};

}  // namespace ALDS1_10_C

#endif  // SRC_C11_3_ALDS1_10_C_LCS_H_
