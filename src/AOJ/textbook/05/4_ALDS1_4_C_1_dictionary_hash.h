/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-4. 探索、ハッシュ法。ハッシュ衝突の無いように実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C05_4_ALDS1_4_C_1_DICTIONARY_HASH_H_
#define SRC_C05_4_ALDS1_4_C_1_DICTIONARY_HASH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_4_C_1 {

constexpr int32_t kMaxKeyLength = 12;
constexpr int32_t kHashTableSize = 22369620;
constexpr int8_t kInvalid = 0;
constexpr int8_t kValid = 1;

void CallDictionary(std::istream& input_stream) noexcept;

enum class InstructionType : int32_t { kInsert = 0, kFind, kInvalid };

enum DecodedValue : int32_t { kA = 0, kC, kG, kT, kBase };

InstructionType JudgeInstructionType(const std::string& str);

class Dictionary {
 public:
  Dictionary() noexcept;
  ~Dictionary() noexcept;
  void Insert(const std::string& key);
  int8_t Get(const std::string& key) const;
  bool WasFound(const std::string& key) const;

 private:
  Dictionary(const Dictionary& obj) = delete;
  Dictionary& operator=(const Dictionary& rhs) = delete;
  Dictionary(Dictionary&& obj) = delete;
  Dictionary& operator=(Dictionary&& rhs) = delete;

  static int32_t GetHash(const std::string& key);
  static int32_t DecodeOneChar(const char c);
  static int32_t GetDigitOffset(const int32_t digit_size);

 private:
  int8_t hash_table_[kHashTableSize];

 private:
  FRIEND_TEST(Test_ALDS1_4_C_1, kHashTableSize);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_4_C_1, DecodeOneChar);   // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_4_C_1, GetDigitOffset);  // Should be removed from production code
};
}  // namespace ALDS1_4_C_1

#endif  // SRC_C05_4_ALDS1_4_C_1_DICTIONARY_HASH_H_
