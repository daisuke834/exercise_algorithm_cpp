/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 202. Happy Number. HashSetを用いた解法
 */

#include "202_happy_number_hashset.h"

namespace LC_202 {

void CallHappyNumber(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  int32_t n;
  input_stream >> n;
  if (IsHappy(n)) {
    std::cout << "Is happy." << std::endl;
  } else {
    std::cout << "Is not happy." << std::endl;
  }
}

bool IsHappy(const int32_t n) noexcept {
  std::unordered_map<int32_t, bool> was_checked;
  bool is_happy = false;
  int32_t c_value = n;
  while (true) {
    const int32_t sum = SumOfSquaresOfEachDigit(c_value);
    if (sum == 1) {
      is_happy = true;
      break;
    } else if (was_checked.find(sum) != was_checked.end()) {
      is_happy = false;
      break;
    }
    was_checked[sum] = true;
    c_value = sum;
  }
  return is_happy;
}

int32_t SumOfSquaresOfEachDigit(const int32_t n) noexcept {
  int32_t cvalue = n;
  int32_t sum = 0;
  while (cvalue > 0) {
    const int32_t c_digit_value = cvalue % 10;
    sum += c_digit_value * c_digit_value;
    cvalue /= 10;
  }
  return sum;
}

// **********************************************************************

}  // namespace LC_202
