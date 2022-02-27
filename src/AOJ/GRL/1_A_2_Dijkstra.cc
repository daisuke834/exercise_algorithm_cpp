/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 単一始点最短経路(Single Source Shortest Path)。
 * ダイクストラのアルゴリズム (Dijkstra's algorithm)の、優先度キューによる実装。
 * 計算量はO(E*log(V))
 */

#include "1_A_2_Dijkstra.h"

namespace GRL_1_A_2 {

void CallDijkstraAlgorithm(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  DijkstraAlgorithm* single_source_shortest_path = new DijkstraAlgorithm();
  try {
    int32_t number_of_vertices, number_of_edges, vertex_start;
    input_stream >> number_of_vertices >> number_of_edges >> vertex_start;
    single_source_shortest_path->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_edges; ++i) {
      int32_t vertex_from, vertex_to, weight;
      input_stream >> vertex_from >> vertex_to >> weight;
      single_source_shortest_path->AddEdge(vertex_from, vertex_to, weight);
    }
    single_source_shortest_path->CalculateShortestPaths(vertex_start);
    single_source_shortest_path->Print();
  } catch (...) {
    std::cerr << "ERROR: CallDijkstraAlgorithm()" << std::endl;
    throw;
  }
  delete single_source_shortest_path;
}

DijkstraAlgorithm::DijkstraAlgorithm() noexcept : number_of_vertices_(0) {}

DijkstraAlgorithm::~DijkstraAlgorithm() noexcept {}

void DijkstraAlgorithm::SetNumberOfVertices(const int32_t number_of_vertices) noexcept {
  number_of_vertices_ = number_of_vertices;
}

void DijkstraAlgorithm::AddEdge(const int32_t vertex_from, const int32_t vertex_to, const int32_t weight) noexcept {
  vertices_[vertex_from].edges_from_this.push_back(Edge(weight, vertex_to));
}

void DijkstraAlgorithm::CalculateShortestPaths(const int32_t vertex_start) noexcept {
  constexpr int32_t kInitDistance = 0;
  vertices_[vertex_start].distance = kInitDistance;
  pqueue_.push(DistanceAndVertexPair(kInitDistance, vertex_start));
  while (pqueue_.size() > 0) {
    const DistanceAndVertexPair distance_and_vertex = pqueue_.top();
    pqueue_.pop();
    const int32_t target_distance = distance_and_vertex.first;
    const int32_t target_index = distance_and_vertex.second;
    vertices_[target_index].explored_ = true;
    for (const Edge& c_edge : vertices_[target_index].edges_from_this) {
      const int32_t to = c_edge.second;
      if (!vertices_[to].explored_) {
        const int32_t weight = c_edge.first;
        const int32_t temp_distance = (target_distance != INT32_MAX) ? target_distance + weight : INT32_MAX;
        if (temp_distance < vertices_[to].distance) {
          vertices_[to].distance = temp_distance;
          pqueue_.push(DistanceAndVertexPair(temp_distance, to));
        }
      }
    }
  }
}

void DijkstraAlgorithm::Print() noexcept {
  for (int32_t index_vertex = 0; index_vertex < number_of_vertices_; ++index_vertex) {
    const int32_t distance = vertices_[index_vertex].distance;
    if (distance == INT32_MAX) {
      std::cout << "INF" << std::endl;
    } else {
      std::cout << distance << std::endl;
    }
  }
}

}  // namespace GRL_1_A_2
