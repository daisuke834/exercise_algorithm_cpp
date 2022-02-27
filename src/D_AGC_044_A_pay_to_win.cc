/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Grand Contest(AGC) 044-A. Pay To Win.
 */

#include "src/D_AGC_044_A_pay_to_win.h"

#include <algorithm>

namespace AGC_044_A {

Solution::Solution(const int64_t A, const int64_t B, const int64_t C, const int64_t D) noexcept {
  operations_[kDouble].coins = A;
  operations_[kDouble].ratio = 2;

  operations_[kTriple].coins = B;
  operations_[kTriple].ratio = 3;

  operations_[kQuintuple].coins = C;
  operations_[kQuintuple].ratio = 5;

  operations_[kIncrement].coins = D;

  operations_[kDecrement].coins = D;

  min_coins_[0] = 0;
  min_coins_[1] = operations_[kDecrement].coins;
}

int64_t Solution::CalculateMinimumAmountOfCoins(const int64_t goal) noexcept {
  if (min_coins_.count(goal) > 0) {
    return min_coins_[goal];
  }

  int64_t result = INT64_MAX;
  if (goal < result / operations_[kIncrement].coins) {
    result = goal * operations_[kIncrement].coins;
  }

  const OperationType next_operations[] = {kDouble, kTriple, kQuintuple};
  for (const OperationType next : next_operations) {
    const Operation& operation = operations_[next];
    if (goal % operation.ratio == 0) {
      int64_t temp_result = CalculateMinimumAmountOfCoins(goal / operation.ratio);
      if (temp_result != INT64_MAX) {
        temp_result += operation.coins;
        result = std::min(temp_result, result);
      }
    } else {
      const int64_t r = goal / operation.ratio;

      {  // Lower Bound
        const int64_t lower_bound = r * operation.ratio;
        int64_t temp_result = CalculateMinimumAmountOfCoins(lower_bound / operation.ratio);
        if (temp_result != INT64_MAX) {
          temp_result += operation.coins + (goal - lower_bound) * operations_[kIncrement].coins;
          result = std::min(temp_result, result);
        }
      }

      {  // Upper Bound
        const int64_t upper_bound = (r + 1LL) * operation.ratio;
        int64_t temp_result = CalculateMinimumAmountOfCoins(upper_bound / operation.ratio);
        if (temp_result != INT64_MAX) {
          temp_result += operation.coins + (upper_bound - goal) * operations_[kDecrement].coins;
          result = std::min(temp_result, result);
        }
      }
    }
  }
  min_coins_[goal] = result;
  return result;
}

}  // namespace AGC_044_A
