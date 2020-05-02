/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest 165. Depth First Search (DFS).
 */

#ifndef SRC_B_ABC_165_1_DEPTH_FIRST_SEARCH_H_
#define SRC_B_ABC_165_1_DEPTH_FIRST_SEARCH_H_

// #include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace ABC_165_1 {

constexpr int32_t kMaxArraySize = 10;
constexpr int32_t kMinArrayValue = 1;
constexpr int32_t kMaxArrayValue = 10;
constexpr int32_t kMaxNumberOfConditions = 10;

void CallDepthFirstSearch(std::istream &input_stream) noexcept;

struct Condition {
  int32_t size{0};
  int32_t a[kMaxNumberOfConditions];
  int32_t b[kMaxNumberOfConditions];
  int32_t c[kMaxNumberOfConditions];
  int32_t score[kMaxNumberOfConditions];
};

struct Array {
  int32_t size{0};
  int32_t max_value{0};
  int32_t values[kMaxArraySize];
};

class DepthFirstSearch {
 public:
  DepthFirstSearch() noexcept;
  ~DepthFirstSearch() noexcept;
  void AddCondition(const int32_t a, const int32_t b, const int32_t c, const int32_t score);
  void ConfigureArray(const int32_t size, const int32_t max_value);
  int32_t SearchMaxScore();

 private:
  void DoDepthFirstSearch(const int32_t target_index);
  bool IsOkay(const int32_t index_condition) const;

 private:
  int32_t max_score_;
  Condition condition_;
  Array array_;
};

}  // namespace ABC_165_1

#endif  // SRC_B_ABC_165_1_DEPTH_FIRST_SEARCH_H_
