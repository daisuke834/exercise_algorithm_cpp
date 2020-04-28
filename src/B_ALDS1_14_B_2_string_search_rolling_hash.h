/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_14_B. 文字列検索、Rolling Hash。
 */

#ifndef SRC_B_ALDS1_14_B_2_STRING_SEARCH_ROLLING_HASH_H_
#define SRC_B_ALDS1_14_B_2_STRING_SEARCH_ROLLING_HASH_H_

// #include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_14_B_2 {

constexpr int32_t kMaxPatternLength = 10000;
constexpr int32_t kMaxTextLength = 1000000;
constexpr int64_t kBase = static_cast<int64_t>('9' - '0' + 1) + 2LL * static_cast<int64_t>('z' - 'a' + 1);
constexpr int64_t kPrime = 1000000007LL;

void CallStringSearch(std::istream &input_stream);

class RollingHash {
 public:
  RollingHash() noexcept;
  ~RollingHash() noexcept;
  void SetPattern(const std::string &pattern) noexcept;
  void Search(const std::string &text_str) noexcept;

 private:
  static int64_t DecodeCharacter(const char ch);
  void CalculateHashOfPattern();
  int64_t CalculateBasePower(const int64_t pow) const noexcept;

  RollingHash(const RollingHash &obj) = delete;
  RollingHash &operator=(const RollingHash &rhs) = delete;
  RollingHash(RollingHash &&obj) = delete;
  RollingHash &operator=(RollingHash &&rhs) = delete;

 private:
  int32_t pattern_length_;
  int64_t pattern_hash_;
  char pattern_[kMaxPatternLength + 1];
  int64_t text_hash_[kMaxTextLength + 1];
  int64_t base_powered_[kMaxPatternLength + 1];

 private:
  // FRIEND_TEST(Test_ALDS1_14_B_2, dummy);    // Should be removed from production code
};

}  // namespace ALDS1_14_B_2

#endif  // SRC_B_ALDS1_14_B_2_STRING_SEARCH_ROLLING_HASH_H_
