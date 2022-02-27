/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 最大公約数(Greatest Common Divisor, GCD)
 */

#include "2_ALDS1_1_B_1_GCD.h"

#include <algorithm>
#include <iostream>

namespace ALDS1_1_B_1 {

void CallCalculateGreatestCommonDivisor(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  int32_t a;
  int32_t b;
  input_stream >> a >> b;
  int32_t result = CalculateGreatestCommonDivisor(a, b);
  std::cout << result << std::endl;
}

int32_t CalculateGreatestCommonDivisor(const int32_t a, const int32_t b) {
  int32_t result = -1;
  if ((a < 0) || (a > kMaxInputValue)) {
    std::cerr << "ERROR: CalculateGreatestCommonDivisor(): a is out of range: " << a << std::endl;
    throw 1;
  } else if ((b < 0) || (b > kMaxInputValue)) {
    std::cerr << "ERROR: CalculateGreatestCommonDivisor(): b is out of range: " << b << std::endl;
    throw 1;
  } else if (a == 0) {
    result = b;
  } else if (b == 0) {
    result = a;
  } else {
    const int32_t new_a = std::min(a, b);
    const int32_t new_b = std::max(a, b) - new_a;
    result = CalculateGreatestCommonDivisor(new_a, new_b);
  }
  return result;
}

}  // namespace ALDS1_1_B_1
