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

  const OperationType next_operations[] = {kDouble, kTriple, kQuintuple};
  for (const OperationType next : next_operations) {
    const Operation &operation = operations_[next];
    if (goal % operation.ratio == 0) {
      int64_t temp_result = CalculateMinimumAmountOfCoins(goal / operation.ratio);
      if (temp_result != INT64_MAX) {
        temp_result += operation.coins;
        result = std::min(temp_result, result);
      }
    } else {
      const int64_t r = goal / operation.ratio;

      {
        const int64_t lower_bound = r * operation.ratio;
        int64_t temp_result_1 = CalculateMinimumAmountOfCoins(lower_bound / operation.ratio);
        if (temp_result_1 != INT64_MAX) {
          temp_result_1 += operation.coins + (goal - lower_bound) * operations_[kIncrement].coins;
          result = std::min(temp_result_1, result);
        }
      }

      {
        const int64_t upper_bound = (r + 1) * operation.ratio;
        int64_t temp_result_2 = CalculateMinimumAmountOfCoins(upper_bound / operation.ratio);
        if (temp_result_2 != INT64_MAX) {
          temp_result_2 += operation.coins + (upper_bound - goal) * operations_[kDecrement].coins;
          result = std::min(temp_result_2, result);
        }
      }
    }
  }
  min_coins_[goal] = result;
  return result;
}

}  // namespace AGC_044_A
