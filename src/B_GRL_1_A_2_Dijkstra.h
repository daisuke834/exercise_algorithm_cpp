/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 単一始点最短経路(Single Source Shortest Path)。
 * ダイクストラのアルゴリズム (Dijkstra's algorithm)の、優先度キューによる実装。
 */

#ifndef SRC_C13_3_GRL_1_A_2_DIIKSTRA_H_
#define SRC_C13_3_GRL_1_A_2_DIIKSTRA_H_

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace GRL_1_A_2 {

constexpr int32_t kMaxNumberOfVertices = 100000;
constexpr int32_t kInvalidIndex = -1;

// ****************************************************

void CallDijkstraAlgorithm(std::istream &input_stream);

// ****************************************************

class DijkstraAlgorithm {};

}  // namespace GRL_1_A_2

#endif  // SRC_C13_3_GRL_1_A_2_DIIKSTRA_H_
