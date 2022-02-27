/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 単一始点最短経路(Single Source Shortest Path)。
 * ベルマン–フォード法(Bellman-Ford algorithm)による実装。
 */

#ifndef SRC_C13_3_GRL_1_B_BELLMAN_FORD_H_
#define SRC_C13_3_GRL_1_B_BELLMAN_FORD_H_

#include <cstdint>
#include <iostream>
#include <string>

namespace GRL_1_B {

constexpr int32_t kMaxNumberOfVertices = 1000;
constexpr int32_t kMaxNumberOfEdges = 2000;
constexpr int32_t kInvalidIndex = -1;

// ****************************************************

void CallBellmanFordAlgorithm(std::istream& input_stream);

// ****************************************************

struct Edge {
  int32_t from{kInvalidIndex};
  int32_t to{kInvalidIndex};
  int32_t weight{INT32_MAX};
};
struct Vertex {
  int32_t distance{INT32_MAX};
};

class BellmanFordAlgorithm {
 public:
  BellmanFordAlgorithm() noexcept;
  ~BellmanFordAlgorithm() noexcept;
  void SetNumberOfVertices(const int32_t number_of_vertices) noexcept;
  void AddWeight(const int32_t vertex_from, const int32_t vertex_to, const int32_t weight) noexcept;
  void CalculateShortestPaths(const int32_t start_vertex_index) noexcept;
  void Print() noexcept;

 private:
  int32_t number_of_vertices_;
  int32_t number_of_edges_;
  bool negative_cycle_;
  Vertex vertices_[kMaxNumberOfVertices];
  Edge edges_[kMaxNumberOfEdges];
};

}  // namespace GRL_1_B

#endif  // SRC_C13_3_GRL_1_B_BELLMAN_FORD_H_
