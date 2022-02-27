/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-4. 探索、ハッシュ法。オープンアドレス法による実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C05_4_ALDS1_4_C_2_DICTIONARY_HASH_H_
#define SRC_C05_4_ALDS1_4_C_2_DICTIONARY_HASH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_4_C_2 {

constexpr int32_t kMaxKeyLength = 12;
constexpr int64_t kHashTableSize = 1046527;  //!< Prime number
constexpr int8_t kInvalid = 0;
constexpr int8_t kValid = 1;
constexpr int64_t kMaxIterationHash = 1046527;

void CallDictionary(std::istream& input_stream) noexcept;

enum class InstructionType : int32_t { kInsert = 0, kFind, kInvalid };

enum DecodedValue : int64_t { kNone = 0, kA, kC, kG, kT, kBase };

InstructionType JudgeInstructionType(const std::string& str);

class Key {
 public:
  Key() noexcept;
  explicit Key(const char* const key) noexcept;
  explicit Key(const std::string key) noexcept;
  ~Key() noexcept;
  Key(const Key& obj) noexcept;
  Key& operator=(const Key& rhs) noexcept;
  Key(Key&& obj) noexcept;
  Key& operator=(Key&& rhs) noexcept;
  bool Equals(const Key& obj) const noexcept;
  std::string GetKey() const noexcept;
  bool IsValid() const noexcept;
  bool IsInvalid() const noexcept;

 private:
  void Reset() noexcept;

 private:
  char key_string_[kMaxKeyLength + 1];
};

class Dictionary {
 public:
  Dictionary() noexcept;
  ~Dictionary() noexcept;
  void Insert(const std::string& key);
  bool WasFound(const std::string& key) const;

 private:
  Dictionary(const Dictionary& obj) = delete;
  Dictionary& operator=(const Dictionary& obj) = delete;
  Dictionary(Dictionary&& obj) = delete;
  Dictionary& operator=(Dictionary&& obj) = delete;

  static int64_t GetDecodedKey(const std::string& key);
  static int64_t CalculateHash(const int64_t decoded_key, const int64_t index_iteration);
  static int64_t DecodeOneChar(const char c);
  static int64_t Hash1(const int64_t decoded_key);
  static int64_t Hash2(const int64_t decoded_key);

 private:
  Key hash_table_[kHashTableSize];

 private:
  FRIEND_TEST(Test_ALDS1_4_C_2, kHashTableSize);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_4_C_2, DecodeOneChar);   // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_4_C_2, GetDigitOffset);  // Should be removed from production code
};
}  // namespace ALDS1_4_C_2

#endif  // SRC_C05_4_ALDS1_4_C_2_DICTIONARY_HASH_H_
