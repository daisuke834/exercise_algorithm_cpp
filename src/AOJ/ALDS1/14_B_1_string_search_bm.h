/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_14_B. 文字列検索、BM文字列検索アルゴリズム（Boyer-Moore String Search Algorithm）。
 */

#ifndef SRC_B_ALDS1_14_B_1_STRING_SEARCH_BM_H_
#define SRC_B_ALDS1_14_B_1_STRING_SEARCH_BM_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_14_B_1 {

constexpr int32_t kMaxPatternLength = 10000;
constexpr int32_t kNotFound = -1;
constexpr int32_t kMaxLoop = 2000000;

void CallStringSearch(std::istream& input_stream);

void NaiveStringSearch(const std::string& text, const std::string& pattern);

class BoyerMoore {
 public:
  BoyerMoore() noexcept;
  ~BoyerMoore() noexcept;
  void SetPattern(const std::string& pattern) noexcept;
  void Search(const std::string& text_str) const noexcept;

 private:
  BoyerMoore(const BoyerMoore& obj) = delete;
  BoyerMoore& operator=(const BoyerMoore& rhs) = delete;
  BoyerMoore(BoyerMoore&& obj) = delete;
  BoyerMoore& operator=(BoyerMoore&& rhs) = delete;

 private:
  int32_t pattern_length_;
  char pattern_[kMaxPatternLength + 1];
  int32_t offsets_from_right_[256];

 private:
  FRIEND_TEST(Test_ALDS1_14_B_1, SetPattern);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_14_B_1, Search_1);    // Should be removed from production code
};

}  // namespace ALDS1_14_B_1

#endif  // SRC_B_ALDS1_14_B_1_STRING_SEARCH_BM_H_
