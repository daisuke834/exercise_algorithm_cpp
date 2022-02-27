/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-4. 探索、ハッシュ法。ハッシュ衝突の無いように実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "4_ALDS1_4_C_1_dictionary_hash.h"

#include <cmath>
#include <iostream>
#include <string>
namespace ALDS1_4_C_1 {

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

Dictionary::Dictionary() noexcept : hash_table_{} {}
Dictionary::~Dictionary() noexcept {}

void Dictionary::Insert(const std::string& key) {
  const int32_t hash = GetHash(key);
  if ((hash < 0) || (hash >= kHashTableSize)) {
    std::cerr << "ERROR: Insert(): Invalid hash value. " << hash << std::endl;
    throw 1;
  }
  hash_table_[hash] = kValid;
}

int8_t Dictionary::Get(const std::string& key) const {
  const int32_t hash = GetHash(key);
  if ((hash < 0) || (hash >= kHashTableSize)) {
    std::cerr << "ERROR: Get(): Invalid hash value. " << hash << std::endl;
    throw 1;
  }
  return hash_table_[hash];
}

bool Dictionary::WasFound(const std::string& key) const {
  try {
    const int8_t value = Get(key);
    return (value != kInvalid);
  } catch (...) {
    std::cerr << "ERROR: WasFound()" << std::endl;
    throw;
  }
}

int32_t Dictionary::GetHash(const std::string& key) {
  if ((key.size() <= 0) || (key.size() > kMaxKeyLength)) {
    std::cerr << "ERROR: GetHash(): Invalid input key. " << key << std::endl;
    throw 1;
  }

  int32_t relative_position = 0;
  int32_t val_exp = 1;
  for (int32_t digit = key.size() - 1; digit >= 0; --digit) {
    const int32_t cval = DecodeOneChar(key[digit]);
    relative_position += val_exp * cval;
    val_exp *= kBase;
  }
  const int32_t digit_offset = GetDigitOffset(key.size());
  const int32_t result = digit_offset + relative_position;
  return result;
}

int32_t Dictionary::DecodeOneChar(const char c) {
  int32_t value;
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

int32_t Dictionary::GetDigitOffset(const int32_t digit_size) {
  if ((digit_size <= 0) || (digit_size > kMaxKeyLength + 1)) {
    std::cerr << "ERROR: GetDigitOffset(): Invalid digit size. " << digit_size << std::endl;
    throw 1;
  }
  try {
    const int32_t offset = (std::pow(static_cast<int32_t>(kBase), digit_size) - kBase) / (kBase - 1);
    return offset;
  } catch (...) {
    std::cerr << "ERROR: GetDigitOffset()" << std::endl;
    throw;
  }
}

}  // namespace ALDS1_4_C_1
