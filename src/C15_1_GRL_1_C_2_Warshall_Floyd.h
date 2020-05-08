/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-1. 高度なグラフアルゴリズム、全点対間最短経路(All Pairs Shortest Path, APSP)。
 * ワーシャルフロイドのアルゴリズム(Warshall-Floyd's algorithm)。計算量=O(|V|^3)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C15_1_GRL_1_C_2_WARSHALL_FLOYD_H_
#define SRC_C15_1_GRL_1_C_2_WARSHALL_FLOYD_H_

#include <cstdint>
#include <iostream>
#include <string>

namespace GRL_1_C_2 {

// ****************************************************

void CallWarshallFloyd(std::istream &input_stream);

// ****************************************************

class WarshallFloyd {
 public:
  WarshallFloyd() noexcept;
  ~WarshallFloyd() noexcept;

 private:
 private:

};

}  // namespace GRL_1_C_2

#endif  // SRC_C15_1_GRL_1_C_2_WARSHALL_FLOYD_H_
