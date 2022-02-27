/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-2. 探索、線形探索。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C05_2_ALDS1_4_A_LINEAR_SEARCH_H_
#define SRC_C05_2_ALDS1_4_A_LINEAR_SEARCH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_4_A {

void CallLinearSearch(std::istream& input_stream) noexcept;

constexpr int32_t kMaxNumberOfSources = 10000;
constexpr int32_t kMaxNumberOfTargets = 500;

struct Sources {
  int32_t size{0};
  int32_t values_[kMaxNumberOfSources];
};

struct Targets {
  int32_t size{0};
  int32_t values_[kMaxNumberOfTargets];
};

class LinearSearch {
 public:
  LinearSearch() noexcept;
  ~LinearSearch() noexcept;
  int32_t SearchTarget() const;
  void AddOneSource(const int32_t source);
  void AddOneTarget(const int32_t target);

 private:
  LinearSearch(const LinearSearch& obj) = delete;
  LinearSearch& operator=(const LinearSearch& rhs) = delete;
  LinearSearch(LinearSearch&& obj) = delete;
  LinearSearch& operator=(LinearSearch&& rhs) = delete;

  bool TargetIsIncludedInSource(const int32_t index_target) const;

 private:
  Sources sources_;
  Targets targets_;

 private:
  FRIEND_TEST(Test_ALDS1_4_A, SearchTarget_1);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_4_A, SearchTarget_2);  // Should be removed from production code
};
}  // namespace ALDS1_4_A

#endif  // SRC_C05_2_ALDS1_4_A_LINEAR_SEARCH_H_
