/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 最大公約数(Greatest Common Divisor, GCD)
 */

#ifndef SRC_C18_2_ALDS1_1_B_1_GCD_H_
#define SRC_C18_2_ALDS1_1_B_1_GCD_H_

#include <cstdint>
#include <iostream>

namespace ALDS1_1_B_1 {

constexpr int32_t kMaxInputValue = 1000000000;

void CallCalculateGreatestCommonDivisor(std::istream& input_stream) noexcept;

int32_t CalculateGreatestCommonDivisor(const int32_t a, const int32_t b);

}  // namespace ALDS1_1_B_1
#endif  // SRC_C18_2_ALDS1_1_B_1_GCD_H_
