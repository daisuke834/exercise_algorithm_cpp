/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder DISCO presents ディスカバリーチャンネル コードコンテスト2020 予選
 * C. Strawberry Cakes.
 */

#include "src/D_ddcc2020_qual_C_1_strawberry_cakes.h"

#include <string>
#include <vector>

namespace D_ddcc2020_qual_C_1 {

int CallMain(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t H, W, K;
  input_stream >> H >> W >> K;
  std::vector<std::vector<int64_t>> strawberry(H, std::vector<int64_t>(W, false));
  std::vector<bool> filled_row(H, false);
  std::vector<std::vector<int64_t>> result(H, std::vector<int64_t>(W, INT64_MIN));
  for (int64_t row = 0; row < H; ++row) {
    std::string s;
    input_stream >> s;
    int64_t count_per_row = 0;
    for (int64_t column = 0; column < W; ++column) {
      const char ch = s.c_str()[column];
      if (ch == '#') {
        strawberry[row][column] = true;
        ++count_per_row;
        filled_row[row] = true;
      }
    }
  }

  int64_t last_filled_row = H - 1;
  while (last_filled_row >= 0) {
    if (filled_row[last_filled_row]) {
      break;
    }
    --last_filled_row;
  }

  int64_t start_row = 0;
  int64_t index = 1;
  while (true) {
    int64_t end_row = start_row;
    while (!filled_row[end_row]) {
      ++end_row;
      if (end_row == H - 1) {
        break;
      }
    }
    if (end_row == last_filled_row) {
      end_row = H - 1;
    }

    int64_t last_filled_col = W - 1;
    while (last_filled_col >= 0) {
      int64_t count = 0;
      for (int64_t row = start_row; row <= end_row; ++row) {
        if (strawberry[row][last_filled_col]) ++count;
      }
      if (count > 0) {
        break;
      }
      --last_filled_col;
    }

    int64_t start_col = 0;
    int64_t end_col;
    while (true) {
      end_col = start_col;
      while (end_col < W) {
        int64_t count = 0;
        for (int64_t r = start_row; r <= end_row; ++r) {
          if (strawberry[r][end_col]) {
            ++count;
          }
        }
        if (count > 0) {
          break;
        }
        ++end_col;
      }
      if (end_col == last_filled_col) {
        end_col = W - 1;
      }

      for (int64_t row = start_row; row <= end_row; ++row) {
        for (int64_t col = start_col; col <= end_col; ++col) {
          result[row][col] = index;
        }
      }
      ++index;

      if (end_col == W - 1) {
        break;
      }
      start_col = end_col + 1;
    }

    if (end_row == H - 1) {
      break;
    }
    start_row = end_row + 1;
  }

  for (int64_t row = 0; row < H; ++row) {
    for (int64_t column = 0; column < W; ++column) {
      if (column != 0) {
        std::cout << " ";
      }
      std::cout << result[row][column];
    }
    std::cout << std::endl;
  }

  return 0;
}

}  // namespace D_ddcc2020_qual_C_1
