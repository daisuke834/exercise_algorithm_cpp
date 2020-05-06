/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_15_D. 貪欲アルゴリズム、ハフマン符号(Huffman coding)。
 */

#ifndef SRC_B_ALDS1_15_D_HUFFMAN_CODING_H_
#define SRC_B_ALDS1_15_D_HUFFMAN_CODING_H_

// #include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace ALDS1_15_D {

constexpr int32_t kMaxTextLength = 100000;
constexpr int32_t kInvalidIndex = -1;
constexpr int32_t kInvalidValue = -1;
constexpr int32_t kMaxNumberOfNodes = 100000;
constexpr int32_t kNumberOfCharTypes = 256 +1;

void CallHuffmanCoding(std::istream &input_stream);

struct Node {
  int32_t count{INT32_MAX};
  int32_t value{kInvalidValue};
  int32_t parent{kInvalidIndex};
  int32_t left{kInvalidIndex};
  int32_t right{kInvalidIndex};
};

bool Node1IsLessThanNode2(const Node& node1, const Node& node2) noexcept;

class HuffmanCoding {
 public:
  HuffmanCoding() noexcept;
  ~HuffmanCoding() noexcept;
  void BuildHuffmanTree(const std::string &text) noexcept;

 private:
  void SetText(const std::string &text) noexcept;
  void GenerateHistogram() noexcept;

  HuffmanCoding(const HuffmanCoding &obj) = delete;
  HuffmanCoding &operator=(const HuffmanCoding &rhs) = delete;
  HuffmanCoding(HuffmanCoding &&obj) = delete;
  HuffmanCoding &operator=(HuffmanCoding &&rhs) = delete;

 private:
  int32_t text_length_;
  int32_t number_of_leaves_;
  int32_t number_of_nodes_;
  char text_[kMaxTextLength + 1];
  Node nodes_[kMaxNumberOfNodes];


 private:
  // FRIEND_TEST(Test_ALDS1_15_D, dummy);    // Should be removed from production code
};

}  // namespace ALDS1_15_D

#endif  // SRC_B_ALDS1_15_D_HUFFMAN_CODING_H_
