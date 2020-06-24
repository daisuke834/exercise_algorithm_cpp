/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Educational DP Contest. G - Longest Path.
 * https://atcoder.jp/contests/dp/tasks/dp_g
 */

#include "src/D_AtCoder_Educational_DP_G_LongestPath.h"
#include <algorithm>
#include <vector>

namespace AtCoder_Educational_DP_G {

int64_t N, M;
std::vector<std::vector<int64_t>> nexts;
std::vector<bool> visited;
std::vector<int64_t> length;

int64_t Dfs(const int64_t vertex) {
  if (visited[vertex]) {
    return length[vertex];
  }
  visited[vertex] = true;
  int64_t result = 0;
  for (const int64_t n : nexts[vertex]) {
    result = std::max(result, Dfs(n) + 1);
  }
  length[vertex] = result;
  return result;
}

void CallMain(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  input_stream >> N >> M;
  nexts = std::vector<std::vector<int64_t>>(N + 1);
  visited = std::vector<bool>(N + 1, false);
  length = std::vector<int64_t>(N + 1, 0);
  for (int64_t i = 0; i < M; ++i) {
    int64_t from, to;
    input_stream >> from >> to;
    nexts[from].emplace_back(to);
  }

  int64_t result = 0;
  for (int64_t v = 1; v <= N; ++v) {
    if (!visited[v]) {
      result = std::max(result, Dfs(v));
    }
  }

  std::cout << result << std::endl;
}

}  // namespace AtCoder_Educational_DP_G
