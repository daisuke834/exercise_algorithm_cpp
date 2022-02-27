/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode 202. Happy Number. HashSetを用いた解法
 */

#ifndef SRC_B_LC_202_HAPPY_NUMBER_H_
#define SRC_B_LC_202_HAPPY_NUMBER_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>

namespace LC_202 {

void CallHappyNumber(std::istream& input_stream) noexcept;

bool IsHappy(const int32_t n) noexcept;

int32_t SumOfSquaresOfEachDigit(const int32_t n) noexcept;

}  // namespace LC_202

#endif  // SRC_B_LC_202_HAPPY_NUMBER_H_
