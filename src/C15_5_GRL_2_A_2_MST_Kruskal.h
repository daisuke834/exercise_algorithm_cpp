/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-5. 最小全域木(Minimum Spanning Tree, MST)問題。
 * クラスカル法 (Kruskal's algorithm)とUnion Find Treeによる実装。計算量はO((E)*log(E))。
 */

#ifndef SRC_C15_5_GRL_2_A_2_MST_KRUSKAL_H_
#define SRC_C15_5_GRL_2_A_2_MST_KRUSKAL_H_

#include <cstdint>
#include <iostream>
#include <string>

namespace GRL_2_A_2 {

constexpr int32_t kMaxNumberOfVertices = 10000;
constexpr int32_t kInvalidIndex = -1;

void CallKruskalAlgorithm(std::istream &input_stream);

class KruskalAlgorithm {
 public:
  KruskalAlgorithm() noexcept;
  ~KruskalAlgorithm() noexcept;
  void SetNumberOfVertices(const int32_t number_of_vertices) noexcept;
  void AddEdge(const int32_t v, const int32_t to, const int32_t weight) noexcept;
  void BuildMinimumSpanningTree(const int32_t start_vertex_index) noexcept;
  int32_t GetSumOfWeightsOfMst() const noexcept;

 private:
  int32_t number_of_vertices_;
  int32_t sum_of_weights_;
};

}  // namespace GRL_2_A_2

#endif  // SRC_C15_5_GRL_2_A_2_MST_KRUSKAL_H_
