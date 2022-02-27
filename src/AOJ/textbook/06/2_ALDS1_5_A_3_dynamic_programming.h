/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-2. ALDS1_5_A_3を動的計画法(Dynamic Programming, DP)を用いて再実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C06_2_ALDS1_5_A_3_DYNAMIC_PROGRAMMING_H_
#define SRC_C06_2_ALDS1_5_A_3_DYNAMIC_PROGRAMMING_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_5_A_3 {

void CallDynamicProgramming(std::istream& input_stream);

constexpr int32_t kMaxNumberOfSources = 20;
constexpr int32_t kMaxNumberOfTargets = 200;
constexpr int32_t kMaxValue = 3000;
constexpr int32_t kMinValue = 1;

struct Sources {
  int32_t size{0};
  int32_t values[kMaxNumberOfSources];
};

struct Targets {
  int32_t size{0};
  int32_t values[kMaxNumberOfTargets];
};

struct LookUp {
  bool calculated{false};
  int32_t can_be_created{false};
};

class DynamicProgramming {
 public:
  DynamicProgramming() noexcept;
  ~DynamicProgramming() noexcept;
  void AddOneSource(const int32_t source);
  void AddOneTarget(const int32_t target);
  void Check();

 private:
  DynamicProgramming(const DynamicProgramming& obj) = delete;
  DynamicProgramming& operator=(const DynamicProgramming& rhs) = delete;
  DynamicProgramming(DynamicProgramming&& obj) = delete;
  DynamicProgramming& operator=(DynamicProgramming&& rhs) = delete;

  bool CanBeCreated(const int32_t target, const int32_t start_index_of_source);
  bool LoadCanBeCreated(const int32_t target, const int32_t start_index_of_source) const;
  void SetResult(const int32_t target, const int32_t start_index_of_source, const bool can_be_created);
  bool AlreadyCalculated(const int32_t target, const int32_t start_index_of_source) const;
  bool IsInvalidSourceIndex(const int32_t index) const noexcept;
  bool IsValidSourceIndex(const int32_t index) const noexcept;
  bool IsInvalidValue(const int32_t value) const noexcept;

 private:
  Sources sources_;
  Targets targets_;
  LookUp look_up_table_[kMaxValue + 1][kMaxNumberOfSources];

 private:
  FRIEND_TEST(Test_ALDS1_5_A_3, AddOneSource);    // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_5_A_3, AddOneTarget);    // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_5_A_3, CanBeCreated_1);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_5_A_3, CanBeCreated_2);  // Should be removed from production code
};

}  // namespace ALDS1_5_A_3

#endif  // SRC_C06_2_ALDS1_5_A_3_DYNAMIC_PROGRAMMING_H_
