/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 単一始点最短経路(Single Source Shortest Path)。
 * ベルマン–フォード法(Bellman-Ford algorithm)による実装。
 * 計算量はO(V*E)
 */

#include "1_B_Bellman_Ford.h"

namespace GRL_1_B {

void CallBellmanFordAlgorithm(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  BellmanFordAlgorithm* single_source_shortest_path = new BellmanFordAlgorithm();
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
    std::cerr << "ERROR: CallBellmanFordAlgorithm()" << std::endl;
    throw;
  }
  delete single_source_shortest_path;
}

// ****************************************************

BellmanFordAlgorithm::BellmanFordAlgorithm() noexcept
    : number_of_vertices_(0), number_of_edges_(0), negative_cycle_(false) {}

BellmanFordAlgorithm::~BellmanFordAlgorithm() noexcept {}

void BellmanFordAlgorithm::SetNumberOfVertices(const int32_t number_of_vertices) noexcept {
  number_of_vertices_ = number_of_vertices;
}

void BellmanFordAlgorithm::AddWeight(const int32_t vertex_from, const int32_t vertex_to,
                                     const int32_t weight) noexcept {
  const int32_t index_edge_store = number_of_edges_;
  ++number_of_edges_;
  edges_[index_edge_store].from = vertex_from;
  edges_[index_edge_store].to = vertex_to;
  edges_[index_edge_store].weight = weight;
}

void BellmanFordAlgorithm::CalculateShortestPaths(const int32_t start_vertex_index) noexcept {
  vertices_[start_vertex_index].distance = 0;
  bool updated;
  for (int32_t i = 0; i < kMaxNumberOfVertices; ++i) {
    updated = false;
    for (int32_t index_edge = 0; index_edge < number_of_edges_; ++index_edge) {
      const int32_t from = edges_[index_edge].from;
      const int32_t to = edges_[index_edge].to;
      const int32_t weight = edges_[index_edge].weight;
      if (vertices_[from].distance < INT32_MAX) {
        const int32_t distance_candidate = vertices_[from].distance + weight;
        if (distance_candidate < vertices_[to].distance) {
          vertices_[to].distance = distance_candidate;
          updated = true;
        }
      }
    }
    if (!updated) {
      break;
    }
  }
  if (updated) {
    negative_cycle_ = true;
  }
}

void BellmanFordAlgorithm::Print() noexcept {
  if (negative_cycle_) {
    std::cout << "NEGATIVE CYCLE" << std::endl;
  } else {
    for (int32_t index = 0; index < number_of_vertices_; ++index) {
      if (vertices_[index].distance == INT32_MAX) {
        std::cout << "INF" << std::endl;
      } else {
        std::cout << vertices_[index].distance << std::endl;
      }
    }
  }
}

// **********************************************************************

}  // namespace GRL_1_B
