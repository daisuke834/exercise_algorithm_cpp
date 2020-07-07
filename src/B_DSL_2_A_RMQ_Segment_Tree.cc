/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AOJ DSL_2_A Range Minimum Query問題(RMQ)。セグメント木(Segment Tree)。
 * https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A
 */

#include "src/B_DSL_2_A_RMQ_Segment_Tree.h"
#include <algorithm>

namespace DSL_2_A {

void CallMain(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t N, Q;
  input_stream >> N >> Q;
  constexpr int64_t kInf = (1L << 31L) - 1;
  SegmentTree st(N, kInf);
  enum Query : int64_t { kUpdate = 0, kFind };
  for (int64_t q = 0; q < Q; ++q) {
    int64_t command;
    input_stream >> command;
    if (command == kUpdate) {
      int64_t index, value;
      input_stream >> index >> value;
      st.Update(index, value);
    } else {
      int64_t start, end_m1;
      input_stream >> start >> end_m1;
      std::cout << st.Find(start, end_m1 + 1) << std::endl;
    }
  }
}

SegmentTree::SegmentTree(const int64_t array_size, const int64_t init_value) : init_value_(init_value) {
  array_size_ = 1;
  while (array_size_ < array_size) {
    array_size_ *= 2;
  }
  node_size_ = array_size_ * 2 - 1;
  nodes_ = std::vector<int64_t>(node_size_, init_value_);
}

SegmentTree::SegmentTree(const std::vector<int64_t> &array, const int64_t init_value) : init_value_(init_value) {
  nodes_ = array;
  const int64_t array_size = static_cast<int64_t>(array.size());
  array_size_ = 1;
  while (array_size_ < array_size) {
    array_size_ *= 2;
  }
  node_size_ = array_size_ * 2 - 1;
  nodes_.resize(node_size_, init_value_);
}

void SegmentTree::Update(const int64_t array_index, const int64_t value) {
  int64_t node_index = LeafNodeIndex(array_index);
  nodes_[node_index] = value;
  while (node_index > 0) {
    node_index = Parent(node_index);
    nodes_[node_index] = std::min(nodes_[ChildLeft(node_index)], nodes_[ChildRight(node_index)]);
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
  return std::min(value_left, value_right);
}

int64_t SegmentTree::LeafNodeIndex(const int64_t array_index) const {
  return array_size_ + array_index - 1L;
}

int64_t SegmentTree::Parent(const int64_t node_index) {
  return (node_index - 1L) / 2L;
}

int64_t SegmentTree::ChildLeft(const int64_t node_index) {
  return (node_index * 2 + 1);
}

int64_t SegmentTree::ChildRight(const int64_t node_index) {
  return (node_index * 2 + 2);
}

}  // namespace DSL_2_A
