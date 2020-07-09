/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 各種ユーティリティー
 */

#ifndef SRC_UNION_FIND_H_
#define SRC_UNION_FIND_H_

#include <cstdint>
#include <iostream>
#include <vector>

namespace utils {

class UnionFind {
 public:
  explicit UnionFind(const int32_t n) : parents_(n, -1) {}
  UnionFind() = delete;

  bool IsRoot(const int32_t x) const {
    return (parents_[x] < 0);
  }

  int32_t FindRoot(const int32_t x) {
    if (IsRoot(x)) {
      return x;
    }
    parents_[x] = FindRoot(parents_[x]);
    return parents_[x];
  }

  bool Unite(const int32_t x, const int32_t y) {
    int32_t root_1 = FindRoot(x);
    int32_t root_2 = FindRoot(y);
    if (root_1 == root_2) {
      return false;
    }
    if (parents_[root_1] > parents_[root_2]) {
      std::swap(root_1, root_2);
    }
    parents_[root_1] += parents_[root_2];
    parents_[root_2] = root_1;
    return true;
  }

  bool IsSame(const int32_t x, const int32_t y) {
    return FindRoot(x) == FindRoot(y);
  }

  int32_t Size(const int32_t x) {
    return -1 * parents_[FindRoot(x)];
  }

 private:
  std::vector<int32_t> parents_;
};

}  // namespace utils
#endif  // SRC_UNION_FIND_H_
