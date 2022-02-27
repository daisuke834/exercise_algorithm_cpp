/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-196-4. 1505. Minimum Possible Integer After at Most K Adjacent Swaps On Digits
 * https://leetcode.com/contest/weekly-contest-196/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/
 */

#include "src/B_LC_weekly_196_4_segment_tree.h"

#include <queue>

namespace LC_weekly_196_4 {

std::string Solution::minInteger(std::string num, int k) {
  const int64_t L = static_cast<int64_t>(num.size());
  std::queue<int64_t> queues[10];
  for (int64_t index = 0; index < L; ++index) {
    const char ch = num[index];
    queues[ch - '0'].emplace(index);
  }

  auto Add = [](const int64_t a, const int64_t b) -> int64_t { return (a + b); };
  SegmentTree st(L, 0, Add);

  std::string result;
  for (int64_t digit = 0; digit < L; ++digit) {
    for (int64_t v = 0; v < 10; ++v) {
      if (queues[v].empty()) {
        continue;
      }
      const int64_t index = queues[v].front();
      const int64_t move = index - st.Find(0, index);
      if (move <= k) {
        k -= move;
        queues[v].pop();
        st.Update(index, 1);
        result.push_back('0' + static_cast<char>(v));
        break;
      }
    }
  }
  return result;
}

SegmentTree::SegmentTree(const int64_t array_size, const int64_t init_value,
                         std::function<int64_t(const int64_t a, const int64_t b)>&& Reduce)
    : init_value_(init_value), Reduce_(std::move(Reduce)) {
  array_size_ = 1;
  while (array_size_ < array_size) {
    array_size_ *= 2;
  }
  node_size_ = array_size_ * 2 - 1;
  nodes_ = std::vector<int64_t>(node_size_, init_value_);
}

SegmentTree::SegmentTree(const std::vector<int64_t>& array, const int64_t init_value,
                         std::function<int64_t(const int64_t a, const int64_t b)>&& Reduce)
    : init_value_(init_value), Reduce_(std::move(Reduce)) {
  nodes_ = array;
  const int64_t array_size = static_cast<int64_t>(array.size());
  array_size_ = 1;
  while (array_size_ < array_size) {
    array_size_ *= 2;
  }
  node_size_ = array_size_ * 2 - 1;
  nodes_.resize(node_size_, init_value_);
}

void SegmentTree::Update(const int64_t array_index, const int64_t value, const bool overwrite) {
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
  return Reduce_(value_left, value_right);
}

int64_t SegmentTree::LeafNodeIndex(const int64_t array_index) const { return array_size_ + array_index - 1L; }

int64_t SegmentTree::Parent(const int64_t node_index) { return (node_index - 1L) / 2L; }

int64_t SegmentTree::ChildLeft(const int64_t node_index) { return (node_index * 2 + 1); }

int64_t SegmentTree::ChildRight(const int64_t node_index) { return (node_index * 2 + 2); }

}  // namespace LC_weekly_196_4
