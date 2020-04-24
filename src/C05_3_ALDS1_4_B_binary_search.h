/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-3. 探索、二分探索。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C05_3_ALDS1_4_B_BINARY_SEARCH_H_
#define SRC_C05_3_ALDS1_4_B_BINARY_SEARCH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_4_B {

void CallBinarySearch(std::istream &input_stream) noexcept;

constexpr int32_t kMaxNumberOfSources = 100000;
constexpr int32_t kMaxNumberOfTargets = 50000;

struct Sources {
  int32_t size{0};
  int32_t values[kMaxNumberOfSources];
};

struct Targets {
  int32_t size{0};
  int32_t values[kMaxNumberOfTargets];
};

enum class TargetPosition : int32_t { kLeftSide = 0, kCenter, kRightSide };

class BinarySearch {
 public:
  BinarySearch() noexcept;
  ~BinarySearch() noexcept;
  int32_t SearchTarget() const;
  void AddOneSource(const int32_t source);
  void AddOneTarget(const int32_t target);

 private:
  BinarySearch(const BinarySearch &obj) = delete;
  BinarySearch &operator=(const BinarySearch &rhs) = delete;
  BinarySearch(BinarySearch &&obj) = delete;
  BinarySearch &operator=(BinarySearch &&rhs) = delete;

  bool TargetIsIncludedInSource(const int32_t index_target) const;
  int32_t GetCenterIndex(const int32_t start, const int32_t end) const;
  TargetPosition GetTargetPosition(const int32_t target_value, const int32_t index_center) const;

 private:
  Sources sources_;
  Targets targets_;

 private:
  FRIEND_TEST(Test_ALDS1_4_B, SearchTarget_1);     // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_4_B, SearchTarget_2);     // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_4_B, GetCenterIndex);     // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_4_B, GetTargetPosition);  // Should be removed from production code
};
}  // namespace ALDS1_4_B

#endif  // SRC_C05_3_ALDS1_4_B_BINARY_SEARCH_H_
