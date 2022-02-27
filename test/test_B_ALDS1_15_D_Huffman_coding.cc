/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_15_D. 貪欲アルゴリズム、ハフマン符号(Huffman coding)。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/B_ALDS1_15_D_Huffman_coding.h"

namespace ALDS1_15_D {

class Test_ALDS1_15_D : public ::testing::Test {
 protected:
  HuffmanCoding* huffman_coding_;
  virtual void SetUp() { huffman_coding_ = new HuffmanCoding(); }
  virtual void TearDown() { delete huffman_coding_; }
};

TEST_F(Test_ALDS1_15_D, CallHuffmanCoding_1) {
  std::ostringstream answer;
  answer << "6" << std::endl;

  std::ostringstream input_stream;
  input_stream << "abca" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallHuffmanCoding(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_15_D, CallHuffmanCoding_2) {
  std::ostringstream answer;
  answer << "41" << std::endl;

  std::ostringstream input_stream;
  input_stream << "aaabbcccdeeeffg" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallHuffmanCoding(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_15_D, CallHuffmanCoding_3) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "z" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallHuffmanCoding(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_15_D
