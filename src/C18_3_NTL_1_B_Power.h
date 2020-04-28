/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 整数論、べき乗。
 */

#ifndef SRC_C18_3_NTL_1_B_POWER_H_
#define SRC_C18_3_NTL_1_B_POWER_H_

#include <cstdint>
#include <iostream>

namespace NTL_1_B {

constexpr int64_t kPrime = 1000000007LL;

void CallCalculatePower(std::istream &input_stream) noexcept;

int64_t CalculatePower(const int64_t x, const int64_t n) noexcept;

}  // namespace NTL_1_B
#endif  // SRC_C18_3_NTL_1_B_POWER_H_
