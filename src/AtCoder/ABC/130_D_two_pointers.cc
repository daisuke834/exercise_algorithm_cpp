/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 130-D. しゃくとり法(尺取り法, Two pointers).
 */

#include "130_D_two_pointers.h"

#include <algorithm>
#include <vector>

namespace ABC_130_D {

int CallMain(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t N, K;
  input_stream >> N >> K;
  std::vector<int64_t> A(N);
  for (int64_t i = 0; i < N; ++i) {
    input_stream >> A[i];
  }
  int64_t count = 0;
  int64_t temp_sum = 0;
  int64_t end = 0;
  for (int64_t start = 0; start < N; ++start) {
    while (end < N && temp_sum + A[end] < K) {
      temp_sum += A[end];
      ++end;
    }
    count += end - start;
    temp_sum -= A[start];
  }
  std::cout << ((N + 1) * N / 2 - count) << std::endl;

  return 0;
}

}  // namespace ABC_130_D
