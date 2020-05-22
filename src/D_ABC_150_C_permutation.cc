/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest 150-C.
 */

#include "src/D_ABC_150_C_permutation.h"

namespace ABC_150_C {

void CallPermutation(std::istream &input_stream) noexcept {
  int32_t N;
  input_stream >> N;
  std::vector<int32_t> P(N, 0);
  std::vector<int32_t> Q(N, 0);
  for (int32_t i = 0; i < N; ++i) {
    input_stream >> P[i];
  }
  for (int32_t i = 0; i < N; ++i) {
    input_stream >> Q[i];
  }

  std::vector<int32_t> permutation(N);
  for (int32_t i = 0; i < N; ++i) {
    permutation[i] = i + 1;
  }
  std::map<std::vector<int32_t>, int32_t> order_map;
  int32_t order = 1;
  do {
    order_map[permutation] = order;
    ++order;
  } while (next_permutation(permutation.begin(), permutation.end()));

  std::cout << abs(order_map[P] - order_map[Q]) << std::endl;
}

}  // namespace ABC_150_C
