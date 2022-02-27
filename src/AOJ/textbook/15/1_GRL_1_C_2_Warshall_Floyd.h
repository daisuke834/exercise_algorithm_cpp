/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-1. 高度なグラフアルゴリズム、全点対間最短経路(All Pairs Shortest Path, APSP)。
 * ワーシャルフロイドのアルゴリズム(Warshall-Floyd's algorithm)。計算量=O(|V|^3)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C15_1_GRL_1_C_2_WARSHALL_FLOYD_H_
#define SRC_C15_1_GRL_1_C_2_WARSHALL_FLOYD_H_

#include <cstdint>
#include <iostream>
#include <string>

namespace GRL_1_C_2 {

// ****************************************************
constexpr int32_t kMaxNumberOfVertices = 100;
constexpr int32_t kInvalidVertexIndex = -1;

void CallWarshallFloyd(std::istream& input_stream);

// ****************************************************

class WarshallFloyd {
 public:
  WarshallFloyd() noexcept;
  ~WarshallFloyd() noexcept;
  void SetNumberOfVertices(const int32_t number_of_vertices) noexcept;
  void AddEdge(const int32_t vertex_from_index, const int32_t vertex_to_index, const int32_t weight) noexcept;
  void CalculateWarshallFloyd() noexcept;
  void Print() const noexcept;

 private:
  int32_t number_of_vertices_;
  int32_t distances_[kMaxNumberOfVertices][kMaxNumberOfVertices];
};

}  // namespace GRL_1_C_2

#endif  // SRC_C15_1_GRL_1_C_2_WARSHALL_FLOYD_H_
