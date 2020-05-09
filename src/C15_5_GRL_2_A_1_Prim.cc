/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-5. 最小全域木(Minimum Spanning Tree, MST)問題。
 * プリム法 (Prim's algorithm)と優先度付きキューによる実装。計算量はO((V+E)*log(V))。
 */

#include "src/C15_5_GRL_2_A_1_Prim.h"

namespace GRL_2_A_1 {

void CallPrimAlgorithm(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  PrimAlgorithm *minimum_spanning_tree = new PrimAlgorithm();
  try {
    int32_t number_of_vertices, number_of_edges;
    input_stream >> number_of_vertices >> number_of_edges;
    minimum_spanning_tree->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_edges; ++i) {
      int32_t vertex_index_1, vertex_index_2, weight;
      input_stream >> vertex_index_1 >> vertex_index_2 >> weight;
      minimum_spanning_tree->AddVertex(vertex_index_1, vertex_index_2, weight);
      minimum_spanning_tree->AddVertex(vertex_index_2, vertex_index_1, weight);
    }
    constexpr int32_t kStartVertex = 0;
    minimum_spanning_tree->BuildMinimumSpanningTree(kStartVertex);
    const int32_t sum_of_weights = minimum_spanning_tree->GetSumOfWeightsOfMst();
    std::cout << sum_of_weights << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallPrimAlgorithm()" << std::endl;
    throw;
  }
  delete minimum_spanning_tree;
}

// ****************************************************
PrimAlgorithm::PrimAlgorithm() noexcept : number_of_vertices_(0), sum_of_weights_(0) {}

PrimAlgorithm::~PrimAlgorithm() noexcept {}

void PrimAlgorithm::SetNumberOfVertices(const int32_t number_of_vertices) noexcept {
  number_of_vertices_ = number_of_vertices;
}

void PrimAlgorithm::AddVertex(const int32_t from, const int32_t to, const int32_t weight) noexcept {
  Edge edge1;
  edge1.to = to;
  edge1.weight = weight;
  vertices_[from].neighbours.push_back(edge1);
}

void PrimAlgorithm::BuildMinimumSpanningTree(const int32_t start_vertex_index) noexcept {
  constexpr int32_t kZeroDistance = 0;
  priority_queue_.push(Pair(kZeroDistance, start_vertex_index));
  while (priority_queue_.size() > 0) {
    const int32_t c_distance = priority_queue_.top().first;
    const int32_t c_vertex_index = priority_queue_.top().second;
    priority_queue_.pop();
    if (!vertices_[c_vertex_index].assigned_to_tree) {
      AddToTree(c_vertex_index, c_distance);
      for (const Edge &c_edge : vertices_[c_vertex_index].neighbours) {
        const int32_t neighbour_index = c_edge.to;
        if (!vertices_[neighbour_index].assigned_to_tree) {
          priority_queue_.push(Pair(c_edge.weight, neighbour_index));
        }
      }
    }
  }
}

int32_t PrimAlgorithm::GetSumOfWeightsOfMst() const noexcept {
  return sum_of_weights_;
}

void PrimAlgorithm::AddToTree(const int32_t child, const int32_t weight) noexcept {
  vertices_[child].assigned_to_tree = true;
  sum_of_weights_ += weight;
}

// **********************************************************************

}  // namespace GRL_2_A_1
