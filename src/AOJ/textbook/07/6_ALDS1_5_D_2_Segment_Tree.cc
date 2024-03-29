/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-6. 高等的整列、反転数, 転倒数(The Number of Inversions)。
 * Segment Tree.
 */

#include "6_ALDS1_5_D_2_Segment_Tree.h"

#include <iostream>
#include <map>
#include <string>

namespace ALDS1_5_D_2 {

void CallMain(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int32_t N;
  input_stream >> N;
  std::vector<int64_t> A(N);
  std::map<int64_t, int64_t> value_to_rank;
  for (int32_t j = 0; j < N; ++j) {
    input_stream >> A[j];
    if (value_to_rank.find(A[j]) == value_to_rank.end()) {
      value_to_rank[A[j]] = -1;
    }
  }
  int64_t rank = 0;
  for (auto& m : value_to_rank) {
    m.second = rank;
    ++rank;
  }

  int64_t result = 0;
  SegmentTree st(value_to_rank.size(), 0);
  for (int32_t j = 0; j < N; ++j) {
    const int64_t smaller_or_equel = st.Find(0, value_to_rank[A[j]] + 1);
    result += j - smaller_or_equel;
    st.Add(value_to_rank[A[j]], 1);
  }
  std::cout << result << std::endl;
}

SegmentTree::SegmentTree(const int64_t array_size, const int64_t init_value) : init_value_(init_value) {
  array_size_ = 1;
  while (array_size_ < array_size) {
    array_size_ *= 2;
  }
  node_size_ = array_size_ * 2 - 1;
  nodes_ = std::vector<int64_t>(node_size_, init_value_);
}

SegmentTree::SegmentTree(const std::vector<int64_t>& array, const int64_t init_value) : init_value_(init_value) {
  nodes_ = array;
  const int64_t array_size = static_cast<int64_t>(array.size());
  array_size_ = 1;
  while (array_size_ < array_size) {
    array_size_ *= 2;
  }
  node_size_ = array_size_ * 2 - 1;
  nodes_.resize(node_size_, init_value_);
}

void SegmentTree::Add(const int64_t array_index, const int64_t value) {
  int64_t node_index = LeafNodeIndex(array_index);
  nodes_[node_index] += value;
  while (node_index > 0) {
    node_index = Parent(node_index);
    nodes_[node_index] += value;
  }
}

int64_t SegmentTree::Find(const int64_t start, const int64_t end) {
  // [start, end)
  const int64_t result = Query(start, end, 0, 0, array_size_);
  return result;
}

int64_t SegmentTree::Query(const int64_t start, const int64_t end, const int64_t node_index,
                           const int64_t start_of_node, const int64_t end_of_node) const {
  if (end_of_node <= start || end <= start_of_node) {
    return init_value_;
  } else if (start <= start_of_node && end_of_node <= end) {
    return nodes_[node_index];
  }
  const int64_t middle = (start_of_node + end_of_node) / 2;
  const int64_t value_left = Query(start, end, ChildLeft(node_index), start_of_node, middle);
  const int64_t value_right = Query(start, end, ChildRight(node_index), middle, end_of_node);
  return value_left + value_right;
}

int64_t SegmentTree::LeafNodeIndex(const int64_t array_index) const { return array_size_ + array_index - 1L; }

int64_t SegmentTree::Parent(const int64_t node_index) { return (node_index - 1L) / 2L; }

int64_t SegmentTree::ChildLeft(const int64_t node_index) { return (node_index * 2 + 1); }

int64_t SegmentTree::ChildRight(const int64_t node_index) { return (node_index * 2 + 2); }

}  // namespace ALDS1_5_D_2
