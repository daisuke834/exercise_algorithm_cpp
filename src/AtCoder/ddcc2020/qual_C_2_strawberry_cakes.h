/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder DISCO presents ディスカバリーチャンネル コードコンテスト2020 予選
 * C. Strawberry Cakes. 再帰による実装。
 */

#ifndef SRC_D_DDCC2020_QUAL_C_2_STRAWBERRY_H_
#define SRC_D_DDCC2020_QUAL_C_2_STRAWBERRY_H_

#include <cstdint>
#include <iostream>
#include <vector>

namespace D_ddcc2020_qual_C_2 {

int CallMain(std::istream& input_stream);

using Pair = std::pair<int64_t, int64_t>;

class Strawberry {
 public:
  Strawberry(const int64_t H, const int64_t W);
  void IsStrawberry(const int64_t row, const int64_t column);
  void Search();
  void Print();

 private:
  int64_t SumOfCol(const int64_t column, const int64_t row_start, const int64_t row_end);
  int64_t SumOfRow(const int64_t row, const int64_t column_start, const int64_t column_end);
  void Dfs(const Pair& top_left, const Pair& bottom_right);

 private:
  int64_t H_;
  int64_t W_;
  int64_t index_;
  std::vector<std::vector<int64_t>> strawberry_;
  std::vector<std::vector<int64_t>> result_;
};

}  // namespace D_ddcc2020_qual_C_2

#endif  // SRC_D_DDCC2020_QUAL_C_2_STRAWBERRY_H_
