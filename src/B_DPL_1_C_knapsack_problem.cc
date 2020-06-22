/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 動的計画法(Dynamic Programming, DP)、個別制限なしナップザック問題(Knapsack Problem)。
 */

#include "src/B_DPL_1_C_knapsack_problem.h"
#include <algorithm>
#include <vector>

namespace DPL_1_C {

void CallKnapsackProblem(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t N, W;
  input_stream >> N >> W;
  std::vector<int64_t> total_value(W + 1, 0);
  for (int64_t i = 0; i < N; ++i) {
    int64_t value, weight;
    input_stream >> value >> weight;
    for (int64_t w = 0; w < W; ++w) {
      const int64_t next_weight = w + weight;
      if (next_weight <= W) {
        total_value[next_weight] = std::max(total_value[next_weight], total_value[w] + value);
      }
    }
  }
  std::cout << total_value[W] << std::endl;
}

}  // namespace DPL_1_C
