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

void CallDijkstraAlgorithm(std::istream& input_stream);

// ****************************************************

using Edge = std::pair<int32_t, int32_t>;
using DistanceAndVertexPair = std::pair<int32_t, int32_t>;

struct Vertex {
  bool explored_{false};
  int32_t distance{INT32_MAX};
  std::vector<Edge> edges_from_this;
};

class DijkstraAlgorithm {
 public:
  DijkstraAlgorithm() noexcept;
  ~DijkstraAlgorithm() noexcept;
  void SetNumberOfVertices(const int32_t number_of_vertices) noexcept;
  void AddEdge(const int32_t vertex_from, const int32_t vertex_to, const int32_t weight) noexcept;
  void CalculateShortestPaths(const int32_t vertex_start) noexcept;
  void Print() noexcept;

 private:
  int32_t number_of_vertices_;
  Vertex vertices_[kMaxNumberOfVertices];
  std::priority_queue<DistanceAndVertexPair, std::vector<DistanceAndVertexPair>, std::greater<DistanceAndVertexPair>>
      pqueue_;
};

}  // namespace GRL_1_A_2

#endif  // SRC_C13_3_GRL_1_A_2_DIIKSTRA_H_
