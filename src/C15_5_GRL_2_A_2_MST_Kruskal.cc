/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-5. 最小全域木(Minimum Spanning Tree, MST)問題。
 * クラスカル法 (Kruskal's algorithm)とUnion Find Treeによる実装。計算量はO((E)*log(E))。
 */

#include "src/C15_5_GRL_2_A_2_MST_Kruskal.h"

namespace GRL_2_A_2 {

void CallKruskalAlgorithm(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  KruskalAlgorithm* minimum_spanning_tree = new KruskalAlgorithm();
  try {
    int32_t number_of_vertices, number_of_edges;
    input_stream >> number_of_vertices >> number_of_edges;
    minimum_spanning_tree->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_edges; ++i) {
      int32_t vertex_index_1, vertex_index_2, weight;
      input_stream >> vertex_index_1 >> vertex_index_2 >> weight;
      minimum_spanning_tree->AddEdge(vertex_index_1, vertex_index_2, weight);
    }
    minimum_spanning_tree->BuildMinimumSpanningTree();
    const int32_t sum_of_weights = minimum_spanning_tree->GetSumOfWeightsOfMst();
    std::cout << sum_of_weights << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallKruskalAlgorithm()" << std::endl;
    throw;
  }
  delete minimum_spanning_tree;
}

// ****************************************************
KruskalAlgorithm::KruskalAlgorithm() noexcept : number_of_vertices_(0), number_of_edges_(0), sum_of_weights_(0) {}

KruskalAlgorithm::~KruskalAlgorithm() noexcept {}

void KruskalAlgorithm::SetNumberOfVertices(const int32_t number_of_vertices) noexcept {
  number_of_vertices_ = number_of_vertices;
  for (int32_t index_vertex = 0; index_vertex < number_of_vertices; ++index_vertex) {
    vertices_[index_vertex].parent_union_find = index_vertex;
  }
}

void KruskalAlgorithm::AddEdge(const int32_t vertex_index_1, const int32_t vertex_index_2,
                               const int32_t weight) noexcept {
  const int32_t index_edge_stored = number_of_edges_;
  ++number_of_edges_;
  edges_[index_edge_stored].vertex_index_1 = vertex_index_1;
  edges_[index_edge_stored].vertex_index_2 = vertex_index_2;
  edges_[index_edge_stored].weight = weight;
}

void KruskalAlgorithm::BuildMinimumSpanningTree() noexcept {
  std::sort(edges_, &edges_[number_of_edges_], LessThan);
  for (int32_t index_edge = 0; index_edge < number_of_edges_; ++index_edge) {
    const int32_t c_vertex_index_1 = edges_[index_edge].vertex_index_1;
    const int32_t c_vertex_index_2 = edges_[index_edge].vertex_index_2;
    const int32_t root_of_1 = GetRootVertexIndex(c_vertex_index_1);
    const int32_t root_of_2 = GetRootVertexIndex(c_vertex_index_2);
    if (root_of_1 != root_of_2) {
      vertices_[root_of_2].parent_union_find = root_of_1;
      sum_of_weights_ += edges_[index_edge].weight;
    }
  }
}

int32_t KruskalAlgorithm::GetSumOfWeightsOfMst() const noexcept { return sum_of_weights_; }

int32_t KruskalAlgorithm::GetRootVertexIndex(const int32_t vertex_index) noexcept {
  int32_t c_index = vertex_index;
  while (vertices_[c_index].parent_union_find != c_index) {
    c_index = vertices_[c_index].parent_union_find;
  }
  const int32_t root_index = c_index;
  vertices_[vertex_index].parent_union_find = root_index;
  return root_index;
}

bool LessThan(const Edge& lhs, const Edge& rhs) noexcept { return (lhs.weight < rhs.weight); }

// **********************************************************************

}  // namespace GRL_2_A_2
