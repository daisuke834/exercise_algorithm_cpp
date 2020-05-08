/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-1. 高度なグラフアルゴリズム、全点対間最短経路(All Pairs Shortest Path, APSP)。
 * ワーシャルフロイドのアルゴリズム(Warshall-Floyd's algorithm)。計算量=O(|V|^3)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C15_1_GRL_1_C_2_Warshall_Floyd.h"
#include <algorithm>
#include <iostream>
#include <string>

namespace GRL_1_C_2 {

void CallWarshallFloyd(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  WarshallFloyd *all_pairs_shortest_path = new WarshallFloyd();
  try {
    int32_t number_of_vertices, number_of_edges;
    input_stream >> number_of_vertices >> number_of_edges;
    all_pairs_shortest_path->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_edges; ++i) {
      int32_t vertex_index_1, vertex_index_2, weight;
      input_stream >> vertex_index_1 >> vertex_index_2 >> weight;
      all_pairs_shortest_path->AddWeight(vertex_index_1, vertex_index_2, weight);
    }
    all_pairs_shortest_path->CalculateDistancesOfAllPairsShortestPath();
    all_pairs_shortest_path->Print();
  } catch (...) {
    std::cerr << "ERROR: CallWarshallFloyd()" << std::endl;
    throw;
  }
  delete all_pairs_shortest_path;
}

// ****************************************************

WarshallFloyd::WarshallFloyd() noexcept {}

WarshallFloyd::~WarshallFloyd() noexcept {}


// **********************************************************************

}  // namespace GRL_1_C_2
