/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-196-4. 1505. Minimum Possible Integer After at Most K Adjacent Swaps On Digits
 * https://leetcode.com/contest/weekly-contest-196/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/
 */

#ifndef SRC_B_LC_WEEKLY_196_4_SEGMENT_TREE_H_
#define SRC_B_LC_WEEKLY_196_4_SEGMENT_TREE_H_

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace LC_weekly_196_4 {

class Solution {
 public:
  std::string minInteger(std::string num, int k);
};

class SegmentTree {
 public:
  explicit SegmentTree(const int64_t array_size, const int64_t init_value,
                       std::function<int64_t(const int64_t a, const int64_t b)>&& Reduce);
  explicit SegmentTree(const std::vector<int64_t>& array, const int64_t init_value,
                       std::function<int64_t(const int64_t a, const int64_t b)>&& Reduce);
  void Update(const int64_t array_index, const int64_t value, const bool overwrite = false);
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
  std::function<int64_t(const int64_t a, const int64_t b)> Reduce_;
  std::vector<int64_t> nodes_;
};

}  // namespace LC_weekly_196_4

#endif  // SRC_B_LC_WEEKLY_196_4_SEGMENT_TREE_H_
