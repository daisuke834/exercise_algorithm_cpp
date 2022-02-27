/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-4. 探索、ハッシュ法。オープンアドレス法による実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C05_4_ALDS1_4_C_2_dictionary_hash.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
namespace ALDS1_4_C_2 {

void CallDictionary(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  Dictionary* dictionary = new Dictionary();
  try {
    int32_t number_of_instructions;
    input_stream >> number_of_instructions;
    for (int32_t index_instruction = 0; index_instruction < number_of_instructions; ++index_instruction) {
      std::string instruction_str;
      input_stream >> instruction_str;
      const InstructionType instruction = JudgeInstructionType(instruction_str);
      std::string key;
      input_stream >> key;
      switch (instruction) {
        case InstructionType::kInsert:
          dictionary->Insert(key);
          break;
        case InstructionType::kFind:
          if (dictionary->WasFound(key)) {
            std::cout << "yes" << std::endl;
          } else {
            std::cout << "no" << std::endl;
          }
          break;
        case InstructionType::kInvalid:
          std::cerr << "ERROR: CallDictionary(): Invalid instruction type." << std::endl;
          break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CallDictionary()" << std::endl;
  }
  delete dictionary;
}

InstructionType JudgeInstructionType(const std::string& str) {
  InstructionType instruction_type;
  if (str == "insert") {
    instruction_type = InstructionType::kInsert;
  } else if (str == "find") {
    instruction_type = InstructionType::kFind;
  } else {
    std::cerr << "ERROR: JudgeInstructionType(): Invalid input data. " << str << std::endl;
    throw 1;
  }
  return instruction_type;
}

// ****************************************************

Key::Key() noexcept { Reset(); }

Key::Key(const char* const key) noexcept { strncpy(key_string_, key, kMaxKeyLength); }

Key::Key(const std::string key) noexcept { strncpy(key_string_, key.c_str(), kMaxKeyLength); }

Key::~Key() noexcept {}

Key::Key(const Key& obj) noexcept { strncpy(this->key_string_, obj.key_string_, kMaxKeyLength); }

Key& Key::operator=(const Key& rhs) noexcept {
  if (this != &rhs) {
    strncpy(this->key_string_, rhs.key_string_, kMaxKeyLength);
  }
  return *this;
}

Key::Key(Key&& obj) noexcept {
  strncpy(this->key_string_, obj.key_string_, kMaxKeyLength);
  obj.Reset();
}

Key& Key::operator=(Key&& rhs) noexcept {
  if (this != &rhs) {
    strncpy(this->key_string_, rhs.key_string_, kMaxKeyLength);
    rhs.Reset();  // 無効化
  }
  return *this;
}

std::string Key::GetKey() const noexcept { return std::string(key_string_); }

bool Key::Equals(const Key& obj) const noexcept { return (IsValid() && (strcmp(key_string_, obj.key_string_) == 0)); }

bool Key::IsValid() const noexcept { return (strlen(key_string_) != 0); }

bool Key::IsInvalid() const noexcept { return (strlen(key_string_) == 0); }

void Key::Reset() noexcept {
  for (char& c : key_string_) {
    c = '\0';
  }
}

// ****************************************************

Dictionary::Dictionary() noexcept {}
Dictionary::~Dictionary() noexcept {}

void Dictionary::Insert(const std::string& key) {
  try {
    const int64_t decoded_key = GetDecodedKey(key);
    for (int64_t index_iteration = 0; index_iteration < kMaxIterationHash; ++index_iteration) {
      const int64_t hash_value = CalculateHash(decoded_key, index_iteration);

      if ((hash_value < 0) || (hash_value >= kHashTableSize)) {
        std::cerr << "ERROR: Insert(): Invalid hash value. " << hash_value << std::endl;
        throw 1;
      }
      if (hash_table_[hash_value].Equals(Key(key))) {
        // Key overwrapping
        break;
      } else if (hash_table_[hash_value].IsInvalid()) {
        hash_table_[hash_value] = Key(key);
        break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: Insert()" << std::endl;
    throw;
  }
}

bool Dictionary::WasFound(const std::string& key) const {
  bool was_found = false;
  try {
    const int64_t decoded_key = GetDecodedKey(key);
    for (int64_t index_iteration = 0; index_iteration < kMaxIterationHash; ++index_iteration) {
      const int64_t hash_value = CalculateHash(decoded_key, index_iteration);

      if ((hash_value < 0) || (hash_value >= kHashTableSize)) {
        std::cerr << "ERROR: WasFound(): Invalid hash value. " << hash_value << std::endl;
        throw 1;
      }
      const Key current_key = hash_table_[hash_value];
      if (current_key.Equals(Key(key))) {
        was_found = true;
        break;
      } else if (current_key.IsInvalid()) {
        was_found = false;
        break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: WasFound()" << std::endl;
    throw;
  }
  return was_found;
}

int64_t Dictionary::CalculateHash(const int64_t decoded_key, const int64_t index_iteration) {
  const int64_t hash_value = (Hash1(decoded_key) + index_iteration * Hash2(decoded_key)) % kHashTableSize;
  return hash_value;
}

int64_t Dictionary::GetDecodedKey(const std::string& key) {
  if ((key.size() <= 0) || (key.size() > kMaxKeyLength)) {
    std::cerr << "ERROR: GetHash(): Invalid input key. " << key << std::endl;
    throw 1;
  }
  int64_t decoded_key = 0;
  int64_t val_exp = 1;
  for (int64_t digit = static_cast<int64_t>(key.size()) - 1; digit >= 0; --digit) {
    const int64_t cval = DecodeOneChar(key[digit]);
    decoded_key += val_exp * cval;
    val_exp *= kBase;
  }
  return decoded_key;
}

int64_t Dictionary::Hash1(const int64_t decoded_key) { return (decoded_key % kHashTableSize); }

int64_t Dictionary::Hash2(const int64_t decoded_key) { return (1 + (decoded_key % (kHashTableSize - 1))); }

int64_t Dictionary::DecodeOneChar(const char c) {
  int64_t value;
  switch (c) {
    case 'A':
      value = kA;
      break;
    case 'C':
      value = kC;
      break;
    case 'G':
      value = kG;
      break;
    case 'T':
      value = kT;
      break;
    default:
      std::cerr << "ERROR: DecodeOneChar(): Invalid input char. " << c << std::endl;
      throw 1;
      break;
  }
  return value;
}

}  // namespace ALDS1_4_C_2
