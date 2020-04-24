/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-4. 探索、ハッシュ法のテスト。ハッシュ衝突の無いように実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C05_4_ALDS1_4_C_1_dictionary_hash.h"

namespace ALDS1_4_C_1 {

class Test_ALDS1_4_C_1 : public ::testing::Test {
 protected:
  Dictionary *dictionary_;
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ALDS1_4_C_1, kHashTableSize) {
  const int32_t expected_max_number_of_hash_value = Dictionary::GetDigitOffset(kMaxKeyLength + 1);
  ASSERT_EQ(expected_max_number_of_hash_value, kHashTableSize);
}

TEST_F(Test_ALDS1_4_C_1, DataSize) {
  const int32_t data_size_in_KB = sizeof(Dictionary) / 1024;
  std::cout << "Table data dize in KB: " << data_size_in_KB << std::endl;
  ASSERT_GE(65536, data_size_in_KB);
}

TEST_F(Test_ALDS1_4_C_1, GetDigitOffset) {
  ASSERT_EQ(0, Dictionary::GetDigitOffset(1));
  ASSERT_EQ(4, Dictionary::GetDigitOffset(2));
  ASSERT_EQ(4 + 4 * 4, Dictionary::GetDigitOffset(3));
}

TEST_F(Test_ALDS1_4_C_1, NoData) {
  dictionary_ = new Dictionary();
  ASSERT_FALSE(dictionary_->WasFound("A"));
  ASSERT_FALSE(dictionary_->WasFound("C"));
  ASSERT_FALSE(dictionary_->WasFound("G"));
  ASSERT_FALSE(dictionary_->WasFound("T"));
  ASSERT_FALSE(dictionary_->WasFound("AAA"));
  ASSERT_FALSE(dictionary_->WasFound("AAAA"));
  ASSERT_FALSE(dictionary_->WasFound("AAAAAAAAAAAA"));
  ASSERT_ANY_THROW(dictionary_->WasFound("AAAAAAAAAAAAA"));
  ASSERT_ANY_THROW(dictionary_->WasFound("B"));
  delete dictionary_;
}

TEST_F(Test_ALDS1_4_C_1, WithData) {
  dictionary_ = new Dictionary();
  dictionary_->Insert("A");
  dictionary_->Insert("GGG");
  ASSERT_TRUE(dictionary_->WasFound("A"));
  ASSERT_FALSE(dictionary_->WasFound("C"));
  ASSERT_FALSE(dictionary_->WasFound("G"));
  ASSERT_FALSE(dictionary_->WasFound("T"));
  ASSERT_TRUE(dictionary_->WasFound("GGG"));
  ASSERT_FALSE(dictionary_->WasFound("AAA"));
  ASSERT_FALSE(dictionary_->WasFound("AAAA"));
  ASSERT_FALSE(dictionary_->WasFound("AAAAAAAAAAAA"));
  ASSERT_ANY_THROW(dictionary_->WasFound("AAAAAAAAAAAAA"));
  ASSERT_ANY_THROW(dictionary_->WasFound("B"));
  delete dictionary_;
}

TEST_F(Test_ALDS1_4_C_1, CallDictionary_1) {
  std::ostringstream answer;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "insert AAA" << std::endl;
  input_stream << "insert AAC" << std::endl;
  input_stream << "find AAA" << std::endl;
  input_stream << "find CCC" << std::endl;
  input_stream << "insert CCC" << std::endl;
  input_stream << "find CCC" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallDictionary(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_4_C_1, CallDictionary_2) {
  std::ostringstream answer;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;

  std::ostringstream input_stream;
  input_stream << "15" << std::endl;
  input_stream << "insert AAA" << std::endl;
  input_stream << "insert AAC" << std::endl;
  input_stream << "insert AGA" << std::endl;
  input_stream << "insert AGG" << std::endl;
  input_stream << "insert TTT" << std::endl;
  input_stream << "find AAA" << std::endl;
  input_stream << "find CCC" << std::endl;
  input_stream << "find CCC" << std::endl;
  input_stream << "insert CCC" << std::endl;
  input_stream << "find CCC" << std::endl;
  input_stream << "find CC" << std::endl;
  input_stream << "insert T" << std::endl;
  input_stream << "find TTT" << std::endl;
  input_stream << "find T" << std::endl;
  input_stream << "find A" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallDictionary(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_4_C_1, CallDictionary_3) {
  std::ostringstream answer;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;

  std::ostringstream input_stream;
  input_stream << "100" << std::endl;
  input_stream << "insert T" << std::endl;
  input_stream << "insert AAA" << std::endl;
  input_stream << "find T" << std::endl;
  input_stream << "insert CAC" << std::endl;
  input_stream << "find A" << std::endl;
  input_stream << "insert AA" << std::endl;
  input_stream << "insert CA" << std::endl;
  input_stream << "insert T" << std::endl;
  input_stream << "find TAA" << std::endl;
  input_stream << "find TCG" << std::endl;
  input_stream << "find C" << std::endl;
  input_stream << "insert TG" << std::endl;
  input_stream << "find C" << std::endl;
  input_stream << "insert G" << std::endl;
  input_stream << "find A" << std::endl;
  input_stream << "find AAC" << std::endl;
  input_stream << "insert TC" << std::endl;
  input_stream << "insert T" << std::endl;
  input_stream << "insert AA" << std::endl;
  input_stream << "find C" << std::endl;
  input_stream << "insert G" << std::endl;
  input_stream << "find CTG" << std::endl;
  input_stream << "find CT" << std::endl;
  input_stream << "insert TT" << std::endl;
  input_stream << "find AC" << std::endl;
  input_stream << "find TTG" << std::endl;
  input_stream << "find CG" << std::endl;
  input_stream << "find T" << std::endl;
  input_stream << "insert TT" << std::endl;
  input_stream << "find G" << std::endl;
  input_stream << "insert TCG" << std::endl;
  input_stream << "insert GGT" << std::endl;
  input_stream << "find AGC" << std::endl;
  input_stream << "find T" << std::endl;
  input_stream << "insert GCT" << std::endl;
  input_stream << "insert CA" << std::endl;
  input_stream << "insert TAG" << std::endl;
  input_stream << "find CG" << std::endl;
  input_stream << "find C" << std::endl;
  input_stream << "insert A" << std::endl;
  input_stream << "find TAT" << std::endl;
  input_stream << "find C" << std::endl;
  input_stream << "find CGG" << std::endl;
  input_stream << "insert G" << std::endl;
  input_stream << "find ACG" << std::endl;
  input_stream << "insert TGT" << std::endl;
  input_stream << "insert G" << std::endl;
  input_stream << "insert C" << std::endl;
  input_stream << "find AA" << std::endl;
  input_stream << "find T" << std::endl;
  input_stream << "insert CG" << std::endl;
  input_stream << "insert T" << std::endl;
  input_stream << "insert GC" << std::endl;
  input_stream << "find C" << std::endl;
  input_stream << "insert CT" << std::endl;
  input_stream << "find AT" << std::endl;
  input_stream << "find CTG" << std::endl;
  input_stream << "find G" << std::endl;
  input_stream << "find T" << std::endl;
  input_stream << "find G" << std::endl;
  input_stream << "insert A" << std::endl;
  input_stream << "find CT" << std::endl;
  input_stream << "find AGT" << std::endl;
  input_stream << "insert T" << std::endl;
  input_stream << "find AGG" << std::endl;
  input_stream << "find AGG" << std::endl;
  input_stream << "insert G" << std::endl;
  input_stream << "insert C" << std::endl;
  input_stream << "find AAT" << std::endl;
  input_stream << "insert CG" << std::endl;
  input_stream << "find A" << std::endl;
  input_stream << "insert AT" << std::endl;
  input_stream << "insert TAG" << std::endl;
  input_stream << "insert TA" << std::endl;
  input_stream << "find TT" << std::endl;
  input_stream << "find CG" << std::endl;
  input_stream << "find CC" << std::endl;
  input_stream << "find GTC" << std::endl;
  input_stream << "insert ACG" << std::endl;
  input_stream << "insert CC" << std::endl;
  input_stream << "insert G" << std::endl;
  input_stream << "find CTC" << std::endl;
  input_stream << "insert TCT" << std::endl;
  input_stream << "insert A" << std::endl;
  input_stream << "insert AG" << std::endl;
  input_stream << "insert CAA" << std::endl;
  input_stream << "find TT" << std::endl;
  input_stream << "insert G" << std::endl;
  input_stream << "find T" << std::endl;
  input_stream << "find ATA" << std::endl;
  input_stream << "insert G" << std::endl;
  input_stream << "insert GT" << std::endl;
  input_stream << "find G" << std::endl;
  input_stream << "find AAA" << std::endl;
  input_stream << "find GT" << std::endl;
  input_stream << "find AA" << std::endl;
  input_stream << "find A" << std::endl;
  input_stream << "insert TTA" << std::endl;
  input_stream << "find AAG" << std::endl;
  input_stream << "insert TT" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallDictionary(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_4_C_1
