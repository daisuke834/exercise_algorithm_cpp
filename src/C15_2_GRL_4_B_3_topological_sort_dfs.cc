/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-2. 高度なグラフアルゴリズム、トポロジカルソート(Topological Sort)。
 * 深さ優先探索(DFS)で、再帰を用いる実装。計算量はO(|V|+|E|)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C15_2_GRL_4_B_3_topological_sort_dfs.h"
#include <iostream>
#include <string>

namespace GRL_4_B_3 {

void CallTopologicalSort(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  int32_t number_of_vertices, number_of_edges;
  input_stream >> number_of_vertices >> number_of_edges;
}

}  // namespace GRL_4_B_3
