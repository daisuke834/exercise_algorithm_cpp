/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-3. 重み付きグラフ(Weighted Graph)、単一始点最短経路(Single Source Shortest Path)。
 * ダイクストラのアルゴリズム (Dijkstra's algorithm)の、優先度キューによる改善版。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C13_3_ALDS1_12_C_2_DIIKSTRA_H_
#define SRC_C13_3_ALDS1_12_C_2_DIIKSTRA_H_

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace ALDS1_12_C_2 {

constexpr int32_t kMaxNumberOfVertices = 10000;
constexpr int32_t kInvalidIndex = -1;

// ****************************************************

void CallDijkstraAlgorithm(std::istream& input_stream);

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
 private:
  int32_t number_of_vertices_;
  Vertex vertices_[kMaxNumberOfVertices];
  using Pair = std::pair<int32_t, int32_t>;
  std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> priority_queue_;
};

}  // namespace ALDS1_12_C_2

#endif  // SRC_C13_3_ALDS1_12_C_2_DIIKSTRA_H_
