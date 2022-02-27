/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_14_B. 文字列検索、Rolling Hash。
 * 平均計算量=O(n)。ただしhash-hitした場合に、誤検出抑制のためにテキストマッチングを再度行なっており、
 * 全パターンでマッチする場合など、worstではO(n^2)になる。
 * ハッシュ衝突による誤検出を許容前提できる場合には、テキストマッチングをコメントアウトする。
 */

#include "14_B_2_string_search_rolling_hash.h"

#include <cstring>
#include <iostream>
#include <string>

namespace ALDS1_14_B_2 {

void CallStringSearch(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  RollingHash* rolling_hash = new RollingHash();
  try {
    std::string text, pattern;
    input_stream >> text >> pattern;
    rolling_hash->SetPattern(pattern);
    rolling_hash->Search(text);
  } catch (...) {
    std::cerr << "ERROR: CallStringSearch()" << std::endl;
    throw;
  }
  delete rolling_hash;
}

RollingHash::RollingHash() noexcept : pattern_length_(0), pattern_hash_(0) {}
RollingHash::~RollingHash() noexcept {}

void RollingHash::SetPattern(const std::string& pattern) noexcept {
  strncpy(pattern_, pattern.c_str(), pattern.length());
  pattern_length_ = static_cast<int32_t>(pattern.length());

  base_powered_[0] = 1;
  for (int32_t pow = 1; pow <= pattern_length_; ++pow) {
    base_powered_[pow] = (base_powered_[pow - 1] * kBase) % kPrime;
  }
  CalculateHashOfPattern();
}

void RollingHash::Search(const std::string& text_str) noexcept {
  const char* const text = text_str.c_str();
  const int32_t length_text = static_cast<int32_t>(text_str.length());
  text_hash_[0] = 0;
  // end = 末尾の右隣
  for (int32_t end = 1; end <= length_text; ++end) {
    text_hash_[end] = (DecodeCharacter(text[end - 1]) + text_hash_[end - 1] * kBase) % kPrime;

    const int32_t start = end - pattern_length_;
    if (start >= 0) {
      const int64_t sub_text_hash =
          (kPrime + text_hash_[end] - ((text_hash_[start] * CalculateBasePower(end - start)) % kPrime)) % kPrime;
      if (sub_text_hash == pattern_hash_) {
        bool does_match = true;
        // worstではO(n^2)になるので、TLEになる場合には、ハッシュ衝突による誤検出を許容前提で、テキストマッチングをコメントアウトする。
        for (int32_t index = 0; index < pattern_length_; ++index) {
          if (text[start + index] != pattern_[index]) {
            does_match = false;
            break;
          }
        }
        if (does_match) {
          printf("%d\n", start);
        }
      }
    }
  }
}

void RollingHash::CalculateHashOfPattern() {
  int64_t hash = 0;
  for (int32_t index = 0; index < pattern_length_; ++index) {
    const int64_t decoded_character = DecodeCharacter(pattern_[index]);
    hash = (decoded_character + hash * kBase) % kPrime;
  }
  pattern_hash_ = hash;
}

int64_t RollingHash::DecodeCharacter(const char ch) {
  int64_t decoded_number;
  constexpr int64_t kOffsetNumber = 0;
  constexpr int64_t kOffsetLowercase = kOffsetNumber + static_cast<int64_t>('9' - '0' + 1);
  constexpr int64_t kOffsetUppercase = kOffsetLowercase + static_cast<int64_t>('z' - 'a' + 1);
  if ((ch >= 'a') && (ch <= 'z')) {
    decoded_number = static_cast<int64_t>(ch - 'a') + kOffsetLowercase;
  } else if ((ch >= 'A') && (ch <= 'Z')) {
    decoded_number = static_cast<int64_t>(ch - 'A') + kOffsetUppercase;
  } else if ((ch >= '0') && (ch <= '9')) {
    decoded_number = static_cast<int64_t>(ch - '0') + kOffsetNumber;
  } else {
    std::cerr << "ERROR: DecodeCharacter(): Invalid arg ch=" << ch << std::endl;
    throw 1;
  }
  return decoded_number;
}

int64_t RollingHash::CalculateBasePower(const int64_t pow) const noexcept { return base_powered_[pow]; }

// ****************************************************

}  // namespace ALDS1_14_B_2
