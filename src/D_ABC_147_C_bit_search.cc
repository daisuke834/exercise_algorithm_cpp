/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 147-C. ビット全探索.
 */

#include "src/D_ABC_147_C_bit_search.h"

#include <algorithm>
#include <bitset>
#include <string>
#include <utility>
#include <vector>

namespace D_ABC_147_C {

int CallMain(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t N;
  input_stream >> N;
  std::vector<std::vector<std::pair<int64_t, bool>>> A(N, std::vector<std::pair<int64_t, bool>>());
  for (int64_t i = 0; i < N; ++i) {
    int64_t a;
    input_stream >> a;
    for (int64_t j = 0; j < a; ++j) {
      int64_t person, y;
      input_stream >> person >> y;
      A[i].push_back(std::pair<int64_t, bool>(person - 1, (y == 1)));
    }
  }
  int64_t result = 0;
  for (int32_t b = 0; b < (1 << N); ++b) {
    const std::bitset<15> bs(b);
    bool is_okay = true;
    for (int64_t person = 0; person < N; ++person) {
      if (bs[person]) {
        for (const auto p : A[person]) {
          if (bs[p.first] != p.second) {
            is_okay = false;
            break;
          }
        }
      }
      if (!is_okay) {
        break;
      }
    }
    if (is_okay) {
      result = std::max(result, static_cast<int64_t>(bs.count()));
      // cerr << bs << endl;
    }
  }
  std::cout << result << std::endl;

  return 0;
}

}  // namespace D_ABC_147_C
