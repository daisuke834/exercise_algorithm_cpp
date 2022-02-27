/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 176-D. Wizard in Maze.
 * Dijkstraによる解法.
 */

#include "176_D_2_grid_Dijkstra.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace D_ABC_176_D_2 {

using Pair = std::pair<int64_t, int64_t>;
constexpr int64_t kInf = INT64_MAX / 2L;

int CallMain(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t H, W;
  input_stream >> H >> W;
  int64_t start_r, start_c;
  input_stream >> start_r >> start_c;
  start_r--, start_c--;
  int64_t goal_r, goal_c;
  input_stream >> goal_r >> goal_c;
  goal_r--, goal_c--;

  std::vector<std::vector<bool>> is_open(H, std::vector<bool>(W, false));
  for (int64_t r = 0; r < H; ++r) {
    std::string s;
    input_stream >> s;
    for (int64_t c = 0; c < W; ++c) {
      if (s[c] == '.') {
        is_open[r][c] = true;
      }
    }
  }

  using QQ = std::pair<int64_t, Pair>;
  std::priority_queue<QQ> q;
  std::vector<std::vector<int64_t>> distances(H, std::vector<int64_t>(W, kInf));
  std::vector<std::vector<bool>> visited(H, std::vector<bool>(W, false));

  auto Update = [&](const Pair target) -> void {
    if (visited[target.first][target.second]) {
      return;
    }
    visited[target.first][target.second] = true;
    for (int64_t d_row = -2; d_row <= 2; ++d_row) {
      const int64_t n_row = target.first + d_row;
      for (int64_t d_col = -2; d_col <= 2; ++d_col) {
        const int64_t n_col = target.second + d_col;
        const int64_t step = std::abs(d_row) + std::abs(d_col);
        int64_t d;
        if (step == 0) {
          d = -1;
        } else if (step == 1) {
          d = 0;
        } else {
          d = 1;
        }
        if (d >= 0 && n_row >= 0 && n_row < H && n_col >= 0 && n_col < W && is_open[n_row][n_col]) {
          const int64_t next_distance = distances[target.first][target.second] + d;
          if (next_distance < distances[n_row][n_col]) {
            distances[n_row][n_col] = next_distance;
            q.emplace(QQ(-next_distance, Pair(n_row, n_col)));
          }
        }
      }
    }
  };

  distances[start_r][start_c] = 0;
  q.emplace(QQ(0, Pair(start_r, start_c)));
  while (!q.empty()) {
    const Pair next = q.top().second;
    q.pop();
    Update(next);
  }

  if (distances[goal_r][goal_c] == kInf) {
    std::cout << -1 << std::endl;
  } else {
    std::cout << distances[goal_r][goal_c] << std::endl;
  }
  return 0;
}

}  // namespace D_ABC_176_D_2
