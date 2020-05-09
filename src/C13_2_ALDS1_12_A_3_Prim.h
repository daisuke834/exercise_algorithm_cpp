/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-2. 重み付きグラフ(Weighted Graph)、最小全域木(Minimum Spanning Tree, MST)。
 * プリム法 (Prim's algorithm)と優先度付きキューによる実装。計算量はO((V+E)*log(V))。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C13_2_ALDS1_12_A_3_PRIM_H_
#define SRC_C13_2_ALDS1_12_A_3_PRIM_H_

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace ALDS1_12_A_3 {

constexpr int32_t kMaxNumberOfVertices = 100;
constexpr int32_t kInvalidIndex = -1;

void CallPrimAlgorithm(std::istream &input_stream);

struct Edge {
  int32_t to{kInvalidIndex};
  int32_t weight{INT32_MAX};
};

struct Vertex {
  bool assigned_to_tree{false};
  std::vector<Edge> neighbours;
};

class PrimAlgorithm {
 public:
  PrimAlgorithm() noexcept;
  ~PrimAlgorithm() noexcept;
  void SetNumberOfVertices(const int32_t number_of_vertices) noexcept;
  void AddVertex(const int32_t from, const int32_t to, const int32_t weight) noexcept;
  void BuildMinimumSpanningTree(const int32_t start_vertex_index) noexcept;
  int32_t GetSumOfWeightsOfMst() const noexcept;

 private:
  void AddToTree(const int32_t child, const int32_t weight) noexcept;

 private:
  int32_t number_of_vertices_;
  int32_t sum_of_weights_;
  Vertex vertices_[kMaxNumberOfVertices];
  using Pair = std::pair<int32_t, int32_t>;
  std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> priority_queue_;
};

}  // namespace ALDS1_12_A_3

#endif  // SRC_C13_2_ALDS1_12_A_3_PRIM_H_
