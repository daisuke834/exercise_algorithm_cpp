/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 各種ユーティリティー
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace utils {

std::vector<std::string> SplitStringToVector(const std::string &text, const char delimiter);

std::vector<float> SplitStringToFloatVector(const std::string &text, const char delimiter);

std::vector<double> SplitStringToDoubleVector(const std::string &text, const char delimiter);

int64_t CalculatePower(const int64_t x, const int64_t n) noexcept;

bool IsPrime(const int64_t N);

std::vector<std::pair<int64_t, int64_t>> FactorizeIntoPrimeFactors(const int64_t N);

int64_t GreatestCommonDivisor(const int64_t a, const int64_t b);

int64_t LeastCommonMultiple(const int64_t a, const int64_t b);

int64_t GetNumberOfDigits(const int64_t N);

std::vector<bool> GeneratePrimeTable(int64_t max_value);

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
#endif  // SRC_UTILS_H_
