/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-2. 高度なグラフアルゴリズム、トポロジカルソート(Topological Sort)。
 * 深さ優先探索(DFS)で、再帰を用いる実装。計算量はO(|V|+|E|)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C15_2_GRL_4_B_3_TOPOLOGICAL_SORT_DFS_H_
#define SRC_C15_2_GRL_4_B_3_TOPOLOGICAL_SORT_DFS_H_

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace GRL_4_B_3 {

void CallTopologicalSort(std::istream &input_stream);

}  // namespace GRL_4_B_3

#endif  // SRC_C15_2_GRL_4_B_3_TOPOLOGICAL_SORT_DFS_H_
