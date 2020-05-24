/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Grand Contest 044-A. Pay To Win.
 */

#include "src/D_AGC_044_A_pay_to_win.h"
#include <algorithm>

namespace AGC_044_A {

Solution::Solution(const int64_t N, const int64_t A, const int64_t B, const int64_t C, const int64_t D)
    : N_(N), A_(A), B_(B), C_(C), D_(D), array_max_(2 * N) {
  min_coins_ = std::vector<int64_t>(array_max_ + 1, INT64_MAX);
  min_coins_[0] = 0;
}

int64_t Solution::Calculate() {
  for (int64_t score = 1LL; score <= array_max_; ++score) {
    min_coins_[score] = std::min(min_coins_[score - 1LL] + D_, min_coins_[score]);
    if (score % 2LL == 0LL) {
      min_coins_[score] = std::min(min_coins_[score / 2LL] + A_, min_coins_[score]);
    }
    if (score % 3LL == 0LL) {
      min_coins_[score] = std::min(min_coins_[score / 3LL] + B_, min_coins_[score]);
    }
    if (score % 5LL == 0LL) {
      min_coins_[score] = std::min(min_coins_[score / 5LL] + C_, min_coins_[score]);
    }
    for (int64_t temp_score = score - 1; temp_score >= 1LL; --temp_score) {
      const int64_t temp_coins = min_coins_[temp_score + 1LL] + D_;
      if (temp_coins < min_coins_[temp_score]) {
        min_coins_[temp_score] = temp_coins;
      } else {
        break;
      }
    }
  }
  return min_coins_[N_];
}

}  // namespace AGC_044_A
