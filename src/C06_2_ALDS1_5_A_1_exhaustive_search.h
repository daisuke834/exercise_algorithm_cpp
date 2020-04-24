/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-2. 再帰・分割統治法、全探索(Exhaustive Search)。動的メモリを使ったバージョン。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C06_2_ALDS1_5_A_1_EXHAUSTIVE_SEARCH_H_
#define SRC_C06_2_ALDS1_5_A_1_EXHAUSTIVE_SEARCH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <list>
#include <string>

namespace ALDS1_5_A_1 {

void CallExhaustiveSearch(std::istream &input_stream);

constexpr int32_t kMaxNumberOfSources = 20;
constexpr int32_t kMaxNumberOfTargets = 200;

struct Sources {
  int32_t size{0};
  int32_t values[kMaxNumberOfSources];
};

struct Targets {
  int32_t size{0};
  int32_t values[kMaxNumberOfTargets];
};

class ExhaustiveSearch {
 public:
  ExhaustiveSearch() noexcept;
  ~ExhaustiveSearch() noexcept;
  void AddOneSource(const int32_t source);
  void AddOneTarget(const int32_t target);
  void Check();

 private:
  ExhaustiveSearch(const ExhaustiveSearch &obj) = delete;
  ExhaustiveSearch &operator=(const ExhaustiveSearch &rhs) = delete;
  ExhaustiveSearch(ExhaustiveSearch &&obj) = delete;
  ExhaustiveSearch &operator=(ExhaustiveSearch &&rhs) = delete;

  static bool CanBeCreated(const int32_t target, const std::list<int32_t> &sources);

 private:
  std::list<int32_t> sources_;
  Targets targets_;

 private:
  FRIEND_TEST(Test_ALDS1_5_A_1, AddOneSource);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_5_A_1, AddOneTarget);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_5_A_1, CanBeCreated);  // Should be removed from production code
};

}  // namespace ALDS1_5_A_1

#endif  // SRC_C06_2_ALDS1_5_A_1_EXHAUSTIVE_SEARCH_H_
