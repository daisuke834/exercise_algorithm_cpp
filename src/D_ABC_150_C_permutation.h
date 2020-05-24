/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 150-C.
 */

#ifndef SRC_D_ABC_150_C_DIJKSTRA_H_
#define SRC_D_ABC_150_C_DIJKSTRA_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace ABC_150_C {

constexpr int64_t kMaxNumberOfTowns = 200000L;
constexpr int64_t kMaxLog = 60L;  // > log2(K)

void CallPermutation(std::istream &input_stream) noexcept;

}  // namespace ABC_150_C

#endif  // SRC_D_ABC_150_C_DIJKSTRA_H_
