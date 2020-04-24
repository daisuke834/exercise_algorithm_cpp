/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_14_B. 文字列検索、BM文字列検索アルゴリズム（Boyer-Moore String Search Algorithm）。
 */

#include "src/B_ALDS1_14_B_1_bm_string_search.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

namespace ALDS1_14_B_1 {

void CallStringSearch(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  BoyerMoore *boyer_moore = new BoyerMoore();
  try {
    std::string text, pattern;
    input_stream >> text >> pattern;
    boyer_moore->SetPattern(pattern);
    boyer_moore->Search(text);
  } catch (...) {
    std::cerr << "ERROR: CallStringSearch()" << std::endl;
    throw;
  }
  delete boyer_moore;
}

BoyerMoore::BoyerMoore() noexcept : pattern_length_(0) {}
BoyerMoore::~BoyerMoore() noexcept {}

void BoyerMoore::SetPattern(const std::string &pattern) noexcept {
  strncpy(pattern_, pattern.c_str(), pattern.length());
  pattern_length_ = static_cast<int32_t>(pattern.length());

  for (int32_t &offset : offsets_from_right_) {
    offset = pattern_length_;
  }
  for (int32_t index_pattern = 0; index_pattern < pattern_length_; ++index_pattern) {
    offsets_from_right_[static_cast<int32_t>(pattern_[index_pattern])] = pattern_length_ - index_pattern - 1;
  }
}

void BoyerMoore::Search(const std::string &text_str) const noexcept {
  const char *const text = text_str.c_str();
  const int32_t length_text = static_cast<int32_t>(text_str.length());
  int32_t index_text = pattern_length_ - 1;
  while (index_text < length_text) {
    int32_t index_pattern = pattern_length_ - 1;
    while (text[index_text] == pattern_[index_pattern]) {
      if (index_pattern == 0) {
        printf("%d\n", index_text);
        break;
      } else {
        --index_text;
        --index_pattern;
      }
    }
    index_text +=
        std::max(pattern_length_ - index_pattern, offsets_from_right_[static_cast<int32_t>(text[index_text])]);
  }
}

// ****************************************************

}  // namespace ALDS1_14_B_1
