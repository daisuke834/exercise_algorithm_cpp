/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-6. 高等的整列、反転数, 転倒数(The Number of Inversions)。
 * Segment Tree.
 */

#ifndef SRC_C07_6_ALDS1_5_D_2_SEGMENT_TREE_H_
#define SRC_C07_6_ALDS1_5_D_2_SEGMENT_TREE_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace ALDS1_5_D_2 {

void CallMain(std::istream& input_stream);

class SegmentTree {
 public:
  explicit SegmentTree(const int64_t array_size, const int64_t init_value);
  explicit SegmentTree(const std::vector<int64_t>& array, const int64_t init_value);
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
  const int64_t init_value_;
  std::vector<int64_t> nodes_;
};

}  // namespace ALDS1_5_D_2

#endif  // SRC_C07_6_ALDS1_5_D_2_SEGMENT_TREE_H_
