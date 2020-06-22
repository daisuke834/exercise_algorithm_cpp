/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 153-E. Crested Ibis vs Monster.
 */

#include "src/D_ABC_153_E_knapsack_monster.h"
#include <algorithm>
#include <vector>

namespace ABC_153_E {

constexpr int64_t kInf = INT64_MAX / 2L;

int CallMain(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t H, N;
  input_stream >> H >> N;
  std::vector<int64_t> total_mp(H + 1, kInf);
  total_mp[0] = 0;
  for (int64_t i = 0; i < N; ++i) {
    int64_t damage, mp;
    input_stream >> damage >> mp;
    for (int64_t d = 0; d < H; ++d) {
      const int64_t next_daname = std::min(H, d + damage);
      total_mp[next_daname] = std::min(total_mp[next_daname], total_mp[d] + mp);
    }
  }
  std::cout << total_mp[H] << std::endl;

  return 0;
}

}  // namespace ABC_153_E
