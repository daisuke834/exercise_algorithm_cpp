/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 単一始点最短経路(Single Source Shortest Path)。
 * ダイクストラのアルゴリズム (Dijkstra's algorithm)の、優先度キューによる実装。
 * 計算量はO(E*log(V))
 */

#include "src/B_GRL_1_A_2_Dijkstra.h"

namespace GRL_1_A_2 {

void CallDijkstraAlgorithm(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  DijkstraAlgorithm *single_source_shortest_path = new DijkstraAlgorithm();
  try {
    int32_t number_of_vertices, number_of_edges, vertex_start;
    input_stream >> number_of_vertices >> number_of_edges >> vertex_start;
    single_source_shortest_path->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_edges; ++i) {
      int32_t vertex_from, vertex_to, weight;
      input_stream >> vertex_from >> vertex_to >> weight;
      single_source_shortest_path->AddWeight(vertex_from, vertex_to, weight);
    }
    single_source_shortest_path->CalculateShortestPaths(vertex_start);
    single_source_shortest_path->Print();
  } catch (...) {
    std::cerr << "ERROR: CallDijkstraAlgorithm()" << std::endl;
    throw;
  }
  delete single_source_shortest_path;
}

}  // namespace GRL_1_A_2
