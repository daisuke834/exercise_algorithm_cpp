/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-1. 動的計画法(Dynamic Programming, DP)、コイン問題(Coin Changing Problem)。
 * ループ構造(非再帰計算)による実装。計算量はO(m*n)、外部記憶はO(n)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "1_DPL_1_A_2_coin_changing_problem.h"

#include <iostream>
#include <string>

namespace DPL_1_A_2 {

void CallCoinChangingProblem(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  CoinChangingProblem* coin_chainging_problem = new CoinChangingProblem();
  try {
    int32_t amount_of_payment, number_of_coin_types;
    input_stream >> amount_of_payment >> number_of_coin_types;
    for (int32_t i = 0; i < number_of_coin_types; ++i) {
      int32_t coin_value;
      input_stream >> coin_value;
      coin_chainging_problem->AddCoinValue(coin_value);
    }
    std::cout << coin_chainging_problem->FindNumberOfMinimumNumberOfCoins(amount_of_payment) << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallCoinChangingProblem()" << std::endl;
    delete coin_chainging_problem;
    throw;
  }
  delete coin_chainging_problem;
}

// ****************************************************
CoinChangingProblem::CoinChangingProblem() noexcept : number_of_coin_types_(0) {}

CoinChangingProblem::~CoinChangingProblem() noexcept {}

void CoinChangingProblem::AddCoinValue(const int32_t coin_value) {
  if (number_of_coin_types_ >= kMaxNumberOfCoinTypes) {
    std::cerr << "ERROR: AddCoinValue(): number_of_coin_types_ exceeded a limit = " << kMaxNumberOfCoinTypes
              << std::endl;
  }
  const int32_t index_stored = number_of_coin_types_;
  coin_values_[index_stored] = coin_value;
  ++number_of_coin_types_;
}

int32_t CoinChangingProblem::FindNumberOfMinimumNumberOfCoins(const int32_t amount_of_payment) noexcept {
  for (int32_t temp_amount = 1; temp_amount <= amount_of_payment; ++temp_amount) {
    minimum_number_of_coins_[temp_amount] = INT32_MAX;
    for (int32_t index_coin = 0; index_coin < number_of_coin_types_; ++index_coin) {
      const int32_t remaining_amount = temp_amount - coin_values_[index_coin];
      if (remaining_amount == 0) {
        minimum_number_of_coins_[temp_amount] = 1;
      } else if (remaining_amount > 0) {
        const int32_t number_of_coins_of_remaining_amount = minimum_number_of_coins_[remaining_amount];
        const int32_t candidate_of_minimum_number_of_coins = number_of_coins_of_remaining_amount + 1;
        if (candidate_of_minimum_number_of_coins < minimum_number_of_coins_[temp_amount]) {
          minimum_number_of_coins_[temp_amount] = candidate_of_minimum_number_of_coins;
        }
      }
    }
  }
  return minimum_number_of_coins_[amount_of_payment];
}

}  // namespace DPL_1_A_2
