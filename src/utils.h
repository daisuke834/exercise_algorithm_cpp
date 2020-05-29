/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 各種ユーティリティー
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace utils {

std::vector<std::string> SplitStringToVector(const std::string &text, const char delimiter);

std::vector<float> SplitStringToFloatVector(const std::string &text, const char delimiter);

std::vector<double> SplitStringToDoubleVector(const std::string &text, const char delimiter);

int64_t CalculatePower(const int64_t x, const int64_t n) noexcept;

}  // namespace utils
#endif  // SRC_UTILS_H_
