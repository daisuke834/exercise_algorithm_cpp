/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 単一始点最短経路(Single Source Shortest Path)。
 * ダイクストラのアルゴリズム (Dijkstra's algorithm)の、優先度キューによる実装。
 * 計算量はO(E*log(V))
 */

#include "src/B_GRL_1_A_Dijkstra.h"

namespace GRL_1_A {

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

// ****************************************************

DijkstraAlgorithm::DijkstraAlgorithm() noexcept : number_of_vertices_(0) {}

DijkstraAlgorithm::~DijkstraAlgorithm() noexcept {}

void DijkstraAlgorithm::SetNumberOfVertices(const int32_t number_of_vertices) noexcept {
  number_of_vertices_ = number_of_vertices;
}

void DijkstraAlgorithm::AddWeight(const int32_t vertex_from, const int32_t vertex_to, const int32_t weight) noexcept {
  Edge cedge;
  cedge.connected_to = vertex_to;
  cedge.weight = weight;
  vertices_[vertex_from].edges_from_this_vertex.push_back(cedge);
}

void DijkstraAlgorithm::CalculateShortestPaths(const int32_t start_vertex_index) noexcept {
  vertices_[start_vertex_index].distance = 0;
  priority_queue_.push(Pair(vertices_[start_vertex_index].distance, start_vertex_index));
  while (priority_queue_.size() > 0) {
    const int32_t shortest_index = priority_queue_.top().second;
    const int32_t shortest_distance = priority_queue_.top().first;
    vertices_[shortest_index].distance_is_fixed = true;
    priority_queue_.pop();

    for (Edge &edge : vertices_[shortest_index].edges_from_this_vertex) {
      const int32_t neighbour_index = edge.connected_to;
      if (!vertices_[neighbour_index].distance_is_fixed) {
        const int32_t relative_distance = edge.weight;
        const int32_t distance_via_this_edge = shortest_distance + relative_distance;
        if (distance_via_this_edge < vertices_[neighbour_index].distance) {
          vertices_[neighbour_index].distance = distance_via_this_edge;
          priority_queue_.push(Pair(vertices_[neighbour_index].distance, neighbour_index));
        }
      }
    }
  }
}

void DijkstraAlgorithm::Print() noexcept {
  for (int32_t index = 0; index < number_of_vertices_; ++index) {
    if (vertices_[index].distance == INT32_MAX) {
      std::cout << "INF" << std::endl;
    } else {
      std::cout << vertices_[index].distance << std::endl;
    }
  }
}

// **********************************************************************

}  // namespace GRL_1_A
