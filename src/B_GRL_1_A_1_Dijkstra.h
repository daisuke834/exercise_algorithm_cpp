/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 単一始点最短経路(Single Source Shortest Path)。
 * ダイクストラのアルゴリズム (Dijkstra's algorithm)の、優先度キューによる実装。
 */

#ifndef SRC_C13_3_GRL_1_A_1_DIIKSTRA_H_
#define SRC_C13_3_GRL_1_A_1_DIIKSTRA_H_

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace GRL_1_A_1 {

constexpr int32_t kMaxNumberOfVertices = 100000;
constexpr int32_t kInvalidIndex = -1;

// ****************************************************

void CallDijkstraAlgorithm(std::istream &input_stream);

// ****************************************************

struct Edge {
  int32_t connected_to{kInvalidIndex};
  int32_t weight{INT32_MAX};
};
struct Vertex {
  int32_t distance{INT32_MAX};
  bool distance_is_fixed{false};
  std::vector<Edge> edges_from_this_vertex;
};

class DijkstraAlgorithm {
 public:
  DijkstraAlgorithm() noexcept;
  ~DijkstraAlgorithm() noexcept;
  void SetNumberOfVertices(const int32_t number_of_vertices) noexcept;
  void AddWeight(const int32_t vertex_from, const int32_t vertex_to, const int32_t weight) noexcept;
  void CalculateShortestPaths(const int32_t start_vertex_index) noexcept;
  void Print() noexcept;

 private:
  int32_t number_of_vertices_;
  Vertex vertices_[kMaxNumberOfVertices];
  using Pair = std::pair<int32_t, int32_t>;
  std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> priority_queue_;
};

}  // namespace GRL_1_A_1

#endif  // SRC_C13_3_GRL_1_A_1_DIIKSTRA_H_
