/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_15_D. 貪欲アルゴリズム、ハフマン符号(Huffman coding)。
 */

#include "src/B_ALDS1_15_D_Huffman_coding.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

namespace ALDS1_15_D {

void CallHuffmanCoding(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  HuffmanCoding *huffman_coding = new HuffmanCoding();
  try {
    std::string text, pattern;
    input_stream >> text;
    huffman_coding->BuildHuffmanTree(text);
  } catch (...) {
    std::cerr << "ERROR: CallHuffmanCoding()" << std::endl;
    throw;
  }
  delete huffman_coding;
}

HuffmanCoding::HuffmanCoding() noexcept : text_length_(0), number_of_leaves_(0), number_of_nodes_(0) {}
HuffmanCoding::~HuffmanCoding() noexcept {}

void HuffmanCoding::BuildHuffmanTree(const std::string &text) noexcept {
  SetText(text);
  GenerateHistogram();
}

void HuffmanCoding::SetText(const std::string &text) noexcept {
  strncpy(text_, text.c_str(), text.length());
  text_length_ = static_cast<int32_t>(text.length());
}

void HuffmanCoding::GenerateHistogram() noexcept {
  for (int32_t index = 0; index < text_length_; ++index) {
    const int32_t value = static_cast<int32_t>(text_[index]);
    if (nodes_[value].count == INT32_MAX) {
      nodes_[value].count = 1;
    } else {
      ++nodes_[value].count;
    }
    nodes_[value].value = value;
  }
  std::sort(nodes_, nodes_ + kNumberOfCharTypes, Node1IsLessThanNode2);
}

bool Node1IsLessThanNode2(const Node &node1, const Node &node2) noexcept {
  return (node1.count < node2.count);
}

// ****************************************************

}  // namespace ALDS1_15_D
