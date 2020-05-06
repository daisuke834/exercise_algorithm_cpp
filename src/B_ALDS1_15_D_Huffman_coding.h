/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_15_D. 貪欲アルゴリズム、ハフマン符号(Huffman coding)。
 */

#ifndef SRC_B_ALDS1_15_D_HUFFMAN_CODING_H_
#define SRC_B_ALDS1_15_D_HUFFMAN_CODING_H_

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace ALDS1_15_D {

constexpr int32_t kMaxTextLength = 100000;
constexpr int32_t kInvalidIndex = -1;
constexpr int32_t kInvalidValue = -1;
constexpr int32_t kMaxNumberOfNodes = 100000;
constexpr int32_t kNumberOfCharTypes = 256;

void CallHuffmanCoding(std::istream &input_stream);

struct Node {
  int32_t ch_value{kInvalidValue};
  int32_t parent{kInvalidIndex};
  int32_t left{kInvalidIndex};
  int32_t right{kInvalidIndex};
};

bool Node1IsLessThanNode2(const Node &node1, const Node &node2) noexcept;

struct CharInfo {
  int32_t count{0};
  int32_t node_index{kInvalidIndex};
};

class HuffmanCoding {
 public:
  HuffmanCoding() noexcept;
  ~HuffmanCoding() noexcept;
  void GenerateHuffmanCode(const std::string &text) noexcept;
  std::string Encode(const std::string text) const noexcept;
  void Debug() const noexcept;

 private:
  void SetText(const std::string &text) noexcept;
  void GenerateHistogram() noexcept;
  void BuildHuffmanTree() noexcept;
  int32_t GetDepth() const noexcept;
  std::string Encode(const char ch) const noexcept;

  HuffmanCoding(const HuffmanCoding &obj) = delete;
  HuffmanCoding &operator=(const HuffmanCoding &rhs) = delete;
  HuffmanCoding(HuffmanCoding &&obj) = delete;
  HuffmanCoding &operator=(HuffmanCoding &&rhs) = delete;

 private:
  int32_t text_length_;
  int32_t number_of_leaves_;
  int32_t number_of_nodes_;
  int32_t top_index_;
  char text_[kMaxTextLength + 1];
  CharInfo char_info_[kNumberOfCharTypes];
  Node nodes_[kMaxNumberOfNodes];
  using Pair = std::pair<int32_t, int32_t>;
  std::priority_queue<int32_t, std::vector<Pair>, std::greater<Pair>> queue_;
};

}  // namespace ALDS1_15_D

#endif  // SRC_B_ALDS1_15_D_HUFFMAN_CODING_H_
