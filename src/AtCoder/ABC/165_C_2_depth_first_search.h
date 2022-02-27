/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 165-C. Depth First Search (DFS).
 * StackによるDFSの実装。
 */

#ifndef SRC_D_ABC_165_C_2_DEPTH_FIRST_SEARCH_H_
#define SRC_D_ABC_165_C_2_DEPTH_FIRST_SEARCH_H_

#include <cstdint>
#include <iostream>
#include <string>

namespace ABC_165_2 {

constexpr int32_t kMaxArraySize = 10;
constexpr int32_t kMinArrayValue = 1;
constexpr int32_t kMaxArrayValue = 10;
constexpr int32_t kMaxNumberOfConditions = 50;

void CallDepthFirstSearch(std::istream& input_stream) noexcept;

struct Condition {
  int32_t size{0};
  int32_t a[kMaxNumberOfConditions];
  int32_t b[kMaxNumberOfConditions];
  int32_t c[kMaxNumberOfConditions];
  int64_t score[kMaxNumberOfConditions];
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
  void ConfigureArray(const int32_t size, const int32_t max_value);
  void AddCondition(const int32_t a, const int32_t b, const int32_t c, const int64_t score);
  int64_t SearchMaxScore();

 private:
  void DoDepthFirstSearch(const int32_t target_index);
  int64_t CalculateScore() const;
  bool IsOkay(const int32_t index_condition) const;

 private:
  Condition condition_;
  Array array_;
};

}  // namespace ABC_165_2

#endif  // SRC_D_ABC_165_C_2_DEPTH_FIRST_SEARCH_H_
