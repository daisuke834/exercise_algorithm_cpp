/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AOJ DSL_2_B Range Sum Query問題(RSQ)。セグメント木(Segment Tree)。
 * https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B
 */

#ifndef SRC_B_DSL_2_B_SEGMENT_TREE_H_
#define SRC_B_DSL_2_B_SEGMENT_TREE_H_

#include <cstdint>
#include <iostream>
#include <vector>

namespace DSL_2_B {

void CallMain(std::istream &input_stream);

class SegmentTree {
 public:
  SegmentTree(const int64_t array_size, const int64_t init_value);
  SegmentTree(const std::vector<int64_t> array, const int64_t init_value);
  void Add(const int64_t array_index, const int64_t value);
  int64_t Find(const int64_t start, const int64_t end);  // [start, end)

 private:
  SegmentTree() = delete;
  int64_t LeafNodeIndex(const int64_t array_index) const;
  static int64_t Parent(const int64_t node_index);
  static int64_t ChildLeft(const int64_t node_index);
  static int64_t ChildRight(const int64_t node_index);
  int64_t Query(const int64_t start, const int64_t end, const int64_t node_index, const int64_t start_of_node,
                const int64_t end_of_node) const;

 private:
  int64_t array_size_;
  int64_t node_size_;
  int64_t init_value_;
  std::vector<int64_t> nodes_;
};

}  // namespace DSL_2_B

#endif  // SRC_B_DSL_2_B_SEGMENT_TREE_H_
