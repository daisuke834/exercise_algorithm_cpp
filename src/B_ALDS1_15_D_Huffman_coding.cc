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
    std::string text;
    input_stream >> text;
    huffman_coding->GenerateHuffmanCode(text);
    const std::string encoded_result = huffman_coding->Encode(text);
    std::cout << encoded_result.length() << std::endl;
    huffman_coding->Debug();
  } catch (...) {
    std::cerr << "ERROR: CallHuffmanCoding()" << std::endl;
    throw;
  }
  delete huffman_coding;
}

HuffmanCoding::HuffmanCoding() noexcept : text_length_(0), number_of_leaves_(0), number_of_nodes_(0) {
  for (int32_t &index : node_index_lookup_) {
    index = kInvalidIndex;
  }
}
HuffmanCoding::~HuffmanCoding() noexcept {}

void HuffmanCoding::GenerateHuffmanCode(const std::string &text) noexcept {
  SetText(text);
  GenerateHistogram();
  BuildHuffmanTree();
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
  for (int32_t index = 0; index < kNumberOfCharTypes; ++index) {
    if (nodes_[index].count == INT32_MAX) {
      number_of_leaves_ = index;
      break;
    }
    node_index_lookup_[nodes_[index].value] = index;
  }
  number_of_nodes_ = number_of_leaves_;
}

bool Node1IsLessThanNode2(const Node &node1, const Node &node2) noexcept {
  return (node1.count < node2.count);
}

void HuffmanCoding::BuildHuffmanTree() noexcept {
  int32_t top_index = 0;
  for (int32_t index_selected_leaf = 1; index_selected_leaf < number_of_leaves_; ++number_of_leaves_) {
    const int32_t node_to_be_stored = number_of_nodes_;
    ++number_of_nodes_;
    nodes_[top_index].parent = node_to_be_stored;
    nodes_[index_selected_leaf].parent = node_to_be_stored;
    nodes_[node_to_be_stored].count = nodes_[top_index].count + nodes_[index_selected_leaf].count;
    if (nodes_[top_index].count > nodes_[index_selected_leaf].count) {
      nodes_[node_to_be_stored].left = top_index;
      nodes_[node_to_be_stored].right = index_selected_leaf;
    } else {
      nodes_[node_to_be_stored].left = index_selected_leaf;
      nodes_[node_to_be_stored].right = top_index;
    }
    top_index = node_to_be_stored;
  }
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
  int32_t current_node_index = node_index_lookup_[static_cast<int32_t>(ch)];
  std::string encoded_result = "";
  for (int32_t i = 0; i < kMaxLoop; ++i) {
    const int32_t parent_index = nodes_[current_node_index].parent;
    if (parent_index == kInvalidIndex) {
      break;
    } else {
      if (nodes_[parent_index].left == current_node_index) {
        encoded_result += "0";
      } else {
        encoded_result += "1";
      }
    }
    current_node_index = nodes_[current_node_index].parent;
  }
  return encoded_result;
}

void HuffmanCoding::Debug() const noexcept {
  for (int32_t i = 0; i < number_of_nodes_; ++i) {
    const Node &cnode = nodes_[i];
    std::cerr << i << ", value=" << cnode.value << ", parent" << cnode.parent << ", left=" << cnode.left
              << ", right=" << cnode.right << std::endl;
  }
}

// ****************************************************

}  // namespace ALDS1_15_D
