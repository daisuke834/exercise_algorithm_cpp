/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Practical Algorithm Skill Test (PAST) 003-J. 回転寿司.
 */

#include "src/D_PAST_003_J_1_upper_bound.h"
#include <algorithm>
#include <functional>
#include <vector>

namespace PAST_003_J_1 {

int CallMain(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t N, M;
  input_stream >> N >> M;
  std::vector<int64_t> B(N, 0);
  for (int64_t i = 0; i < M; ++i) {
    int64_t a;
    input_stream >> a;
    auto itr = std::upper_bound(B.begin(), B.end(), a, std::greater<int>());
    if (itr != B.end()) {
      *itr = a;
    }
    int64_t person = static_cast<int64_t>(itr - B.begin()) + 1;
    if (person <= N) {
      std::cout << person << std::endl;
    } else {
      std::cout << -1 << std::endl;
    }
  }

  return 0;
}

}  // namespace PAST_003_J_1
