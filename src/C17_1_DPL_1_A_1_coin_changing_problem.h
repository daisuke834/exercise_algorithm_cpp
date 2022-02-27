/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-1. 動的計画法(Dynamic Programming, DP)、コイン問題(Coin Changing Problem)。
 * 再帰計算による実装。計算量はO(m*n)、外部記憶はO(n)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C17_1_DPL_1_A_1_COIN_CHANGING_PROBLEM_H_
#define SRC_C17_1_DPL_1_A_1_COIN_CHANGING_PROBLEM_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>

namespace DPL_1_A_1 {

constexpr int32_t kMaxNumberOfCoinTypes = 20;
constexpr int32_t kMaxAmountOfPayment = 50000;

void CallCoinChangingProblem(std::istream& input_stream);

struct LookUpMinimumNumberOfCoins {
  bool is_valid{false};
  int32_t minimum_number_of_coins{INT32_MAX};
};

class CoinChangingProblem {
 public:
  CoinChangingProblem() noexcept;
  ~CoinChangingProblem() noexcept;
  void AddCoinValue(const int32_t coin_value);
  int32_t FindNumberOfMinimumNumberOfCoins(const int32_t amount_of_payment) noexcept;

 private:
  CoinChangingProblem(const CoinChangingProblem& obj) = delete;
  CoinChangingProblem& operator=(const CoinChangingProblem& obj) = delete;
  CoinChangingProblem(CoinChangingProblem&& obj) = delete;
  CoinChangingProblem& operator=(CoinChangingProblem&& obj) = delete;

 private:
  int32_t number_of_coin_types_;
  int32_t coin_values_[kMaxNumberOfCoinTypes];
  LookUpMinimumNumberOfCoins look_up_table_[kMaxAmountOfPayment + 1];

 private:
  FRIEND_TEST(Test_DPL_1_A_1, dummy);  // Should be removed from production code
};

}  // namespace DPL_1_A_1

#endif  // SRC_C17_1_DPL_1_A_1_COIN_CHANGING_PROBLEM_H_
