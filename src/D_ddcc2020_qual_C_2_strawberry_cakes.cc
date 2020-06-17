/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder DISCO presents ディスカバリーチャンネル コードコンテスト2020 予選
 * C. Strawberry Cakes.
 */

#include "src/D_ddcc2020_qual_C_2_strawberry_cakes.h"
#include <string>

namespace D_ddcc2020_qual_C_2 {

int CallMain(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t H, W, K;
  input_stream >> H >> W >> K;
  Strawberry strawberry(H, W);
  for (int64_t row = 0; row < H; ++row) {
    std::string s;
    input_stream >> s;
    for (int64_t column = 0; column < W; ++column) {
      const char ch = s.c_str()[column];
      if (ch == '#') {
        strawberry.IsStrawberry(row, column);
      }
    }
  }
  strawberry.Search();
  strawberry.Print();

  return 0;
}

Strawberry::Strawberry(const int64_t H, const int64_t W) : H_(H), W_(W), index_(1) {
  strawberry_ = std::vector<std::vector<int64_t>>(H, std::vector<int64_t>(W, false));
  result_ = std::vector<std::vector<int64_t>>(H, std::vector<int64_t>(W, INT64_MIN));
}

void Strawberry::IsStrawberry(const int64_t row, const int64_t column) {
  strawberry_[row][column] = true;
}

void Strawberry::Search() {
  Dfs(Pair(0, 0), Pair(H_ - 1, W_ - 1));
}

int64_t Strawberry::SumOfCol(const int64_t column, const int64_t row_start, const int64_t row_end) {
  int64_t count = 0;
  for (int64_t row = row_start; row <= row_end; ++row) {
    if (strawberry_[row][column]) {
      ++count;
    }
  }
  return count;
}

int64_t Strawberry::SumOfRow(const int64_t row, const int64_t column_start, const int64_t column_end) {
  int64_t count = 0;
  for (int64_t column = column_start; column <= column_end; ++column) {
    if (strawberry_[row][column]) {
      ++count;
    }
  }
  return count;
}

void Strawberry::Dfs(const Pair &top_left, const Pair &bottom_right) {
  int64_t number_of_filled_rows = 0;
  int64_t total_count = 0;
  int64_t last_filled_row = -1;
  // cerr << top_left.first << ", " << top_left.second << " :: " << bottom_right.first << ", " << bottom_right.second
  //      << endl;
  for (int64_t row = top_left.first; row <= bottom_right.first; ++row) {
    const int64_t count = SumOfRow(row, top_left.second, bottom_right.second);
    if (count > 0) {
      ++number_of_filled_rows;
      total_count += count;
      last_filled_row = row;
    }
  }
  if (total_count == 0) {
    std::cerr << "ERROR: " << __LINE__ << std::endl;
    throw 1;
  } else if (total_count == 1) {
    for (int64_t row = top_left.first; row <= bottom_right.first; ++row) {
      for (int64_t column = top_left.second; column <= bottom_right.second; ++column) {
        result_[row][column] = index_;
      }
    }
    ++index_;
  } else if (number_of_filled_rows >= 2) {
    Dfs(top_left, Pair(last_filled_row - 1, bottom_right.second));
    Dfs(Pair(last_filled_row, top_left.second), bottom_right);
  } else {
    int64_t number_of_filled_columns = 0;
    int64_t last_filled_column = -1;
    for (int64_t column = top_left.second; column <= bottom_right.second; ++column) {
      const int64_t count = SumOfCol(column, top_left.first, bottom_right.first);
      if (count > 0) {
        ++number_of_filled_columns;
        last_filled_column = column;
      }
    }
    Dfs(top_left, Pair(bottom_right.first, last_filled_column - 1));
    Dfs(Pair(top_left.first, last_filled_column), bottom_right);
  }
}

void Strawberry::Print() {
  for (int64_t row = 0; row < H_; ++row) {
    for (int64_t column = 0; column < W_; ++column) {
      if (column != 0) {
        std::cout << " ";
      }
      std::cout << result_[row][column];
    }
    std::cout << std::endl;
  }
}

}  // namespace D_ddcc2020_qual_C_2
