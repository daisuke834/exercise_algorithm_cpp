/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-1. 高度なグラフアルゴリズム、全点対間最短経路(All Pairs Shortest Path, APSP)。
 * ワーシャルフロイドのアルゴリズム(Warshall-Floyd's algorithm)。計算量=O(|V|^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C15_1_GRL_1_all_pairs_shortest_path.h"
#include <algorithm>
#include <iostream>
#include <string>

namespace GRL_1 {

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

WarshallFloyd::WarshallFloyd() noexcept : number_of_vertices_(0) {}

WarshallFloyd::~WarshallFloyd() noexcept {}

void WarshallFloyd::SetNumberOfVertices(const int32_t number_of_vertices) {
  if (number_of_vertices > kMaxNumberOfVertices) {
    std::cerr << "ERROR: SetNumberOfVertices(): Invalid arg: number_of_vertices=" << number_of_vertices << std::endl;
    throw 1;
  }
  number_of_vertices_ = number_of_vertices;
  for (int32_t i = 0; i < number_of_vertices; ++i) {
    for (int32_t j = 0; j < number_of_vertices; ++j) {
      if (i == j) {
        shortest_distances_[i][j] = 0;
      } else {
        shortest_distances_[i][j] = INT32_MAX;
      }
    }
  }
}

void WarshallFloyd::AddWeight(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight) {
  if (InvalidVertexIndex(vertex_1)) {
    std::cerr << "ERROR: AddWeight(): Invalid arg: vertex_1 = " << vertex_1 << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_2)) {
    std::cerr << "ERROR: AddWeight(): Invalid arg: vertex_2 = " << vertex_2 << std::endl;
    throw 1;
  } else {
    shortest_distances_[vertex_1][vertex_2] = weight;
  }
}

void WarshallFloyd::CalculateDistancesOfAllPairsShortestPath() noexcept {
  for (int32_t via = 0; via < number_of_vertices_; ++via) {
    for (int32_t from = 0; from < number_of_vertices_; ++from) {
      for (int32_t to = 0; to < number_of_vertices_; ++to) {
        const int32_t distance_candidate = DistanceViaVertex(from, to, via);
        shortest_distances_[from][to] = std::min(shortest_distances_[from][to], distance_candidate);
      }
    }
  }
}

int32_t WarshallFloyd::DistanceViaVertex(const int32_t from, const int32_t to, const int32_t via) const {
  if (InvalidVertexIndex(from)) {
    std::cerr << "ERROR: DistanceViaVertex(): Invalid arg: from = " << from << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(to)) {
    std::cerr << "ERROR: DistanceViaVertex(): Invalid arg: to = " << to << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(via)) {
    std::cerr << "ERROR: DistanceViaVertex(): Invalid arg: via = " << via << std::endl;
    throw 1;
  } else {
    // DO NOTHING
  }
  int32_t distance;
  if (shortest_distances_[from][via] == INT32_MAX) {
    distance = INT32_MAX;
  } else if (shortest_distances_[via][to] == INT32_MAX) {
    distance = INT32_MAX;
  } else {
    // 初期値(INT32_MAX)以外の加算についてはオーバーフロー対策していないので注意。
    distance = shortest_distances_[from][via] + shortest_distances_[via][to];
  }
  return distance;
}

bool WarshallFloyd::InvalidVertexIndex(const int32_t vertex_index) const noexcept {
  return ((vertex_index < 0) || (vertex_index >= number_of_vertices_));
}

void WarshallFloyd::Print() const noexcept {
  if (NegativeCycleExists()) {
    std::cout << "NEGATIVE CYCLE" << std::endl;
  } else {
    PrintShortestDistances();
  }
}

void WarshallFloyd::PrintShortestDistances() const noexcept {
  for (int32_t from = 0; from < number_of_vertices_; ++from) {
    for (int32_t to = 0; to < number_of_vertices_; ++to) {
      if (to != 0) {
        std::cout << " ";
      }
      const int32_t shortest_distance = shortest_distances_[from][to];
      if (shortest_distance == INT32_MAX) {
        std::cout << "INF";
      } else {
        std::cout << shortest_distances_[from][to];
      }
    }
    std::cout << std::endl;
  }
}

void WarshallFloyd::Debug() const noexcept {
  std::cerr << "*****************************" << std::endl;
  for (int32_t from = 0; from < number_of_vertices_; ++from) {
    for (int32_t to = 0; to < number_of_vertices_; ++to) {
      if (to != 0) {
        std::cerr << " ";
      }
      const int32_t shortest_distance = shortest_distances_[from][to];
      if (shortest_distance == INT32_MAX) {
        std::cerr << "INF";
      } else {
        std::cerr << shortest_distances_[from][to];
      }
    }
    std::cerr << std::endl;
  }
}

bool WarshallFloyd::NegativeCycleExists() const noexcept {
  bool negative_cycle_exists = false;
  for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
    if (shortest_distances_[vertex_index][vertex_index] < 0) {
      negative_cycle_exists = true;
      break;
    }
  }
  return negative_cycle_exists;
}

// **********************************************************************

}  // namespace GRL_1
