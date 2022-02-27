/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-5. 最小全域木(Minimum Spanning Tree, MST)問題。
 * クラスカル法 (Kruskal's algorithm)とUnion Find Treeによる実装。計算量はO((E)*log(E))。
 */

#ifndef SRC_C15_5_GRL_2_A_2_MST_KRUSKAL_H_
#define SRC_C15_5_GRL_2_A_2_MST_KRUSKAL_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>

namespace GRL_2_A_2 {

constexpr int32_t kMaxNumberOfVertices = 10000;
constexpr int32_t kMaxNumberOfEdges = 100000;
constexpr int32_t kInvalidIndex = -1;

void CallKruskalAlgorithm(std::istream& input_stream);

struct Edge {
  int32_t weight{INT32_MAX};
  int32_t vertex_index_1{kInvalidIndex};
  int32_t vertex_index_2{kInvalidIndex};
};

struct Vertex {
  int32_t parent_union_find{kInvalidIndex};
};

class KruskalAlgorithm {
 public:
  KruskalAlgorithm() noexcept;
  ~KruskalAlgorithm() noexcept;
  void SetNumberOfVertices(const int32_t number_of_vertices) noexcept;
  void AddEdge(const int32_t vertex_index_1, const int32_t vertex_index_2, const int32_t weight) noexcept;
  void BuildMinimumSpanningTree() noexcept;
  int32_t GetSumOfWeightsOfMst() const noexcept;

 private:
  int32_t GetRootVertexIndex(const int32_t vertex_index) noexcept;

 private:
  int32_t number_of_vertices_;
  int32_t number_of_edges_;
  int32_t sum_of_weights_;
  Edge edges_[kMaxNumberOfEdges];
  Vertex vertices_[kMaxNumberOfVertices];
};

bool LessThan(const Edge& lhs, const Edge& rhs) noexcept;

}  // namespace GRL_2_A_2

#endif  // SRC_C15_5_GRL_2_A_2_MST_KRUSKAL_H_
