/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part1. 準備編。Cubic。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C1_5_2_cubic.h"
#include <iostream>
namespace C1P5P2 {
int32_t Cubic(const int32_t x) noexcept {
  return x * x * x;
}

void MyMain(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  int32_t x;
  input_stream >> x;
  const int32_t result = Cubic(x);
  std::cout << result << std::endl;
}

}  // namespace C1P5P2
