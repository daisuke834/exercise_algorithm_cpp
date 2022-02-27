/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-2. グラフ(Graph)、グラフの表現。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C12_2_ALDS1_11_A_GRAPH_H_
#define SRC_C12_2_ALDS1_11_A_GRAPH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_11_A {

constexpr int32_t kMaxVertexNumber = 100;

void CallGraph(std::istream& input_stream);

class Graph {
 public:
  Graph() noexcept;
  ~Graph() noexcept;

  void AddVertex(const int32_t vertex);
  void MapDirection(const int32_t vertex_number_from, const int32_t vertex_number_to);
  void Print() const noexcept;
  void Reset() noexcept;

 private:
  Graph(const Graph& obj) = delete;
  Graph& operator=(const Graph& obj) = delete;
  Graph(Graph&& obj) = delete;
  Graph& operator=(Graph&& obj) = delete;

  static bool IsInvalidVertexIndex(const int32_t index) noexcept;
  static bool IsInvalidVertexNumber(const int32_t vertex_number) noexcept;
  static int32_t ConvertFromVertexNumberToIndex(const int32_t node_number);
  static int32_t ConvertFromIndexToVertexNumber(const int32_t index);

 private:
  int32_t size_;
  int32_t adjacency_matrix_[kMaxVertexNumber][kMaxVertexNumber];

 private:
  // FRIEND_TEST(Test_ALDS1_11_A, Add);  // Should be removed from production code
};

}  // namespace ALDS1_11_A

#endif  // SRC_C12_2_ALDS1_11_A_GRAPH_H_
