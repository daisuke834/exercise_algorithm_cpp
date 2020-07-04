/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Practical Algorithm Skill Test (PAST) 003-J. 回転寿司.
 */

#include "src/D_PAST_003_J_2_binary_search.h"
#include <algorithm>
#include <functional>
#include <vector>

namespace PAST_003_J_2 {

int CallMain(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t N, M;
  input_stream >> N >> M;

  std::vector<int64_t> eated(N, 0);

  auto BinarySearch = [&](const int64_t c_sushi) -> int64_t {
    auto IsOkay = [&](const int64_t index, const int64_t key) -> bool {
      const bool is_okay = (eated[index] < c_sushi);
      return is_okay;
    };

    int64_t end_of_NG = -1;
    int64_t beggining_of_OK = static_cast<int64_t>(eated.size());
    while (std::abs(beggining_of_OK - end_of_NG) > 1) {
      const int64_t middle = (beggining_of_OK + end_of_NG) / 2;
      if (IsOkay(middle, c_sushi)) {
        beggining_of_OK = middle;
      } else {
        end_of_NG = middle;
      }
    }
    return beggining_of_OK;
  };

  for (int64_t i = 0; i < M; ++i) {
    int64_t a;
    input_stream >> a;
    const int64_t index = BinarySearch(a);
    if (index >= N) {
      std::cout << -1 << std::endl;
    } else {
      std::cout << index + 1 << std::endl;
      eated[index] = a;
    }
  }

  return 0;
}

}  // namespace PAST_003_J_2
