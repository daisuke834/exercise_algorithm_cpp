/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 176-D. Wizard in Maze.
 * double-ended queue (Deque, 二重終端キュー)による解法.
 */

#include "176_D_1_grid_deque.h"

#include <deque>
#include <string>
#include <utility>
#include <vector>

namespace D_ABC_176_D_1 {

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

  // BFS preparation
  std::deque<Pair> q;
  std::vector<std::vector<int64_t>> distances(H, std::vector<int64_t>(W, kInf));
  auto UpdateFront = [&](const Pair target, const int64_t distance) -> void {
    if (distance < distances[target.first][target.second]) {
      distances[target.first][target.second] = distance;
      q.emplace_front(target);
    }
  };
  auto UpdateBack = [&](const Pair target, const int64_t distance) -> void {
    if (distance < distances[target.first][target.second]) {
      distances[target.first][target.second] = distance;
      q.emplace_back(target);
    }
  };

  // BFS
  UpdateFront(Pair(start_r, start_c), 0);
  while (!q.empty()) {
    const Pair target = q.front();
    q.pop_front();
    for (int64_t next_row = target.first - 2; next_row <= target.first + 2; ++next_row) {
      for (int64_t next_col = target.second - 2; next_col <= target.second + 2; ++next_col) {
        if (next_row >= 0 && next_row < H && next_col >= 0 && next_col < W && is_open[next_row][next_col]) {
          const int64_t mdist = abs(next_col - target.second) + abs(next_row - target.first);
          if (mdist == 0) {
            // DO NOTHING
          } else if (mdist <= 1) {
            UpdateFront(Pair(next_row, next_col), distances[target.first][target.second]);
          } else {
            UpdateBack(Pair(next_row, next_col), distances[target.first][target.second] + 1);
          }
        }
      }
    }
  }

  if (distances[goal_r][goal_c] == kInf) {
    std::cout << -1 << std::endl;
  } else {
    std::cout << distances[goal_r][goal_c] << std::endl;
  }
  return 0;
}

}  // namespace D_ABC_176_D_1
