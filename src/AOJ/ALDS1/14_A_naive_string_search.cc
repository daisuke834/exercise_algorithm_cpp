/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_14_A. 文字列検索(String Search)、Naive String Search。計算量はO(N*M)。
 */

#include "14_A_naive_string_search.h"

#include <iostream>
#include <string>

namespace ALDS1_14_A {

void CallNaiveStringSearch(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  try {
    std::string text, pattern;
    input_stream >> text >> pattern;
    NaiveStringSearch(text, pattern);
  } catch (...) {
    std::cerr << "ERROR: CallNaiveStringSearch()" << std::endl;
    throw;
  }
}

void NaiveStringSearch(const std::string& text, const std::string& pattern) {
  try {
    int32_t length_text = static_cast<int32_t>(text.length());
    int32_t length_pattern = static_cast<int32_t>(pattern.length());
    for (int32_t start_text = 0; start_text < length_text; ++start_text) {
      const int32_t length_substr = length_text - start_text;
      if (length_substr < length_pattern) {
        break;
      }
      bool match = true;
      for (int32_t offset = 0; offset < length_pattern; ++offset) {
        if (text.c_str()[start_text + offset] != pattern.c_str()[offset]) {
          match = false;
          break;
        }
      }
      if (match) {
        std::cout << start_text << std::endl;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: NaiveStringSearch()" << std::endl;
    throw;
  }
}

// ****************************************************

}  // namespace ALDS1_14_A
