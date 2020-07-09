/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 各種ユーティリティー
 */

#ifndef SRC_SEGMENT_TREE_H_
#define SRC_SEGMENT_TREE_H_

#include <cstdint>
#include <functional>
#include <vector>

namespace utils {

class SegmentTree {
 public:
  explicit SegmentTree(const int64_t array_size, const int64_t init_value,
                       std::function<int64_t(const int64_t a, const int64_t b)> &&Reduce)
      : init_value_(init_value), Reduce_(std::move(Reduce)) {
    array_size_ = 1;
    while (array_size_ < array_size) {
      array_size_ *= 2;
    }
    node_size_ = array_size_ * 2 - 1;
    nodes_ = std::vector<int64_t>(node_size_, init_value_);
  };

  explicit SegmentTree(const std::vector<int64_t> &array, const int64_t init_value,
                       std::function<int64_t(const int64_t a, const int64_t b)> &&Reduce)
      : init_value_(init_value), Reduce_(std::move(Reduce)) {
    nodes_ = array;
    const int64_t array_size = static_cast<int64_t>(array.size());
    array_size_ = 1;
    while (array_size_ < array_size) {
      array_size_ *= 2;
    }
    node_size_ = array_size_ * 2 - 1;
    nodes_.resize(node_size_, init_value_);
  };

  void Update(const int64_t array_index, const int64_t value, const bool overwrite = false) {
    int64_t node_index = LeafNodeIndex(array_index);
    if (overwrite) {
      nodes_[node_index] = value;
    } else {
      nodes_[node_index] = Reduce_(nodes_[node_index], value);
    }
    while (node_index > 0) {
      node_index = Parent(node_index);
      nodes_[node_index] = Reduce_(nodes_[ChildLeft(node_index)], nodes_[ChildRight(node_index)]);
    }
  };

  int64_t Find(const int64_t start, const int64_t end) {
    // [start, end)
    const int64_t result = Query(start, end, 0, 0, array_size_);
    return result;
  };

 private:
  SegmentTree() = delete;
  int64_t LeafNodeIndex(const int64_t array_index) const {
    return array_size_ + array_index - 1L;
  };

  static int64_t Parent(const int64_t node_index) {
    return (node_index - 1L) / 2L;
  };

  static int64_t ChildLeft(const int64_t node_index) {
    return (node_index * 2 + 1);
  };

  static int64_t ChildRight(const int64_t node_index) {
    return (node_index * 2 + 2);
  };

  int64_t Query(const int64_t start, const int64_t end, const int64_t node_index, const int64_t start_of_node,
                const int64_t end_of_node) const {
    if (end_of_node <= start || end <= start_of_node) {
      return init_value_;
    } else if (start <= start_of_node && end_of_node <= end) {
      return nodes_[node_index];
    }
    const int64_t middle = (start_of_node + end_of_node) / 2;
    const int64_t value_left = Query(start, end, ChildLeft(node_index), start_of_node, middle);
    const int64_t value_right = Query(start, end, ChildRight(node_index), middle, end_of_node);
    return Reduce_(value_left, value_right);
  };

 private:
  int64_t array_size_;
  int64_t node_size_;
  const int64_t init_value_;
  std::function<int64_t(const int64_t a, const int64_t b)> Reduce_;
  std::vector<int64_t> nodes_;
};

}  // namespace utils
#endif  // SRC_SEGMENT_TREE_H_
