/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-5. 最小全域木(Minimum Spanning Tree, MST)問題。
 * クラスカル法 (Kruskal's algorithm)とUnion Find Treeによる実装。計算量はO((E)*log(E))。
 */

#include "src/C15_5_GRL_2_A_2_MST_Kruskal.h"

namespace GRL_2_A_2 {

void CallKruskalAlgorithm(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  KruskalAlgorithm *minimum_spanning_tree = new KruskalAlgorithm();
  try {
    int32_t number_of_vertices, number_of_edges;
    input_stream >> number_of_vertices >> number_of_edges;
    minimum_spanning_tree->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_edges; ++i) {
      int32_t vertex_index_1, vertex_index_2, weight;
      input_stream >> vertex_index_1 >> vertex_index_2 >> weight;
      minimum_spanning_tree->AddEdge(vertex_index_1, vertex_index_2, weight);
      minimum_spanning_tree->AddEdge(vertex_index_2, vertex_index_1, weight);
    }
    constexpr int32_t kStartVertex = 0;
    minimum_spanning_tree->BuildMinimumSpanningTree(kStartVertex);
    const int32_t sum_of_weights = minimum_spanning_tree->GetSumOfWeightsOfMst();
    std::cout << sum_of_weights << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallKruskalAlgorithm()" << std::endl;
    throw;
  }
  delete minimum_spanning_tree;
}

// ****************************************************
KruskalAlgorithm::KruskalAlgorithm() noexcept : number_of_vertices_(0), sum_of_weights_(0) {}

KruskalAlgorithm::~KruskalAlgorithm() noexcept {}

void KruskalAlgorithm::SetNumberOfVertices(const int32_t number_of_vertices) noexcept {
  number_of_vertices_ = number_of_vertices;
}

void KruskalAlgorithm::AddEdge(const int32_t from, const int32_t to, const int32_t weight) noexcept {
}

void KruskalAlgorithm::BuildMinimumSpanningTree(const int32_t start_vertex_index) noexcept {
}

int32_t KruskalAlgorithm::GetSumOfWeightsOfMst() const noexcept {
  return sum_of_weights_;
}

// **********************************************************************

}  // namespace GRL_2_A_2
