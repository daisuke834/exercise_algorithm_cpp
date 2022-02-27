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

void CallHuffmanCoding(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  HuffmanCoding* huffman_coding = new HuffmanCoding();
  try {
    std::string text;
    input_stream >> text;
    huffman_coding->GenerateHuffmanCode(text);
    const std::string encoded_result = huffman_coding->Encode(text);
    std::cout << encoded_result.length() << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallHuffmanCoding()" << std::endl;
    throw;
  }
  delete huffman_coding;
}

HuffmanCoding::HuffmanCoding() noexcept
    : text_length_(0), number_of_leaves_(0), number_of_nodes_(0), top_index_(kInvalidIndex) {}
HuffmanCoding::~HuffmanCoding() noexcept {}

void HuffmanCoding::GenerateHuffmanCode(const std::string& text) noexcept {
  SetText(text);
  GenerateHistogram();
  BuildHuffmanTree();
}

void HuffmanCoding::SetText(const std::string& text) noexcept {
  strncpy(text_, text.c_str(), text.length());
  text_length_ = static_cast<int32_t>(text.length());
}

void HuffmanCoding::GenerateHistogram() noexcept {
  for (int32_t index_text = 0; index_text < text_length_; ++index_text) {
    const int32_t ch = static_cast<int32_t>(text_[index_text]);
    ++char_info_[ch].count;
  }

  number_of_leaves_ = 0;
  for (int32_t ch = 0; ch < kNumberOfCharTypes; ++ch) {
    if (char_info_[ch].count > 0) {
      const int32_t index_node = number_of_leaves_;
      ++number_of_leaves_;
      nodes_[index_node].ch_value = ch;
      char_info_[ch].node_index = index_node;
      queue_.push(Pair(char_info_[ch].count, index_node));
    }
  }
  number_of_nodes_ = number_of_leaves_;
}

void HuffmanCoding::BuildHuffmanTree() noexcept {
  while (queue_.size() >= 2) {
    const int32_t index_added_node = number_of_nodes_;
    ++number_of_nodes_;

    const int32_t left = queue_.top().second;
    const int32_t left_count = queue_.top().first;
    queue_.pop();
    const int32_t right = queue_.top().second;
    const int32_t right_count = queue_.top().first;
    queue_.pop();
    nodes_[index_added_node].left = left;
    nodes_[index_added_node].right = right;
    nodes_[left].parent = index_added_node;
    nodes_[right].parent = index_added_node;

    const int32_t merged_count = left_count + right_count;
    queue_.push(Pair(merged_count, index_added_node));
  }
  top_index_ = queue_.top().second;
}

std::string HuffmanCoding::Encode(const std::string text) const noexcept {
  std::string encoded_result = "";
  for (int32_t index = 0; index < static_cast<int32_t>(text.length()); ++index) {
    const char ch = text.c_str()[index];
    encoded_result += Encode(ch);
  }
  return encoded_result;
}

std::string HuffmanCoding::Encode(const char ch) const noexcept {
  constexpr int32_t kMaxLoop = 300000;
  int32_t current_node_index = char_info_[static_cast<int32_t>(ch)].node_index;
  std::string encoded_result = "";
  for (int32_t i = 0; i < kMaxLoop; ++i) {
    const int32_t parent_index = nodes_[current_node_index].parent;
    if (parent_index == kInvalidIndex) {
      break;
    } else {
      if (nodes_[parent_index].left == current_node_index) {
        encoded_result = std::string("0") + encoded_result;
      } else {
        encoded_result = std::string("1") + encoded_result;
      }
    }
    current_node_index = nodes_[current_node_index].parent;
  }
  if (encoded_result == "") {
    encoded_result = "0";
  }
  return encoded_result;
}

void HuffmanCoding::Debug() const noexcept {
  for (int32_t i = 0; i < number_of_nodes_; ++i) {
    const Node& cnode = nodes_[i];
    std::cerr << i << ", count=" << char_info_[cnode.ch_value].count << ", value=" << cnode.ch_value
              << ", parent=" << cnode.parent << ", left=" << cnode.left << ", right=" << cnode.right << std::endl;
  }
}

// ****************************************************

}  // namespace ALDS1_15_D
