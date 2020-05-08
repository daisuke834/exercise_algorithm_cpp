/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-1. 高度なグラフアルゴリズム、全点対間最短経路(All Pairs Shortest Path, APSP)。
 * ワーシャルフロイドのアルゴリズム(Warshall-Floyd's algorithm)。計算量=O(|V|^3)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C15_1_GRL_1_C_1_ALL_PAIRS_SHORTEST_PATH_H_
#define SRC_C15_1_GRL_1_C_1_ALL_PAIRS_SHORTEST_PATH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace GRL_1_C_1 {

constexpr int32_t kMaxNumberOfVertices = 100;
constexpr int32_t kMaxNumberOfEdges = 9900;

// ****************************************************

void CallWarshallFloyd(std::istream &input_stream);

// ****************************************************

class WarshallFloyd {
 public:
  WarshallFloyd() noexcept;
  ~WarshallFloyd() noexcept;
  void SetNumberOfVertices(const int32_t number_of_vertices);
  void AddWeight(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight);
  void CalculateDistancesOfAllPairsShortestPath() noexcept;
  void Print() const noexcept;
  void Debug() const noexcept;

 private:
  int32_t DistanceViaVertex(const int32_t from, const int32_t to, const int32_t via) const;
  void PrintShortestDistances() const noexcept;
  bool InvalidVertexIndex(const int32_t vertex_index) const noexcept;
  bool NegativeCycleExists() const noexcept;

  WarshallFloyd(const WarshallFloyd &obj) = delete;
  WarshallFloyd &operator=(const WarshallFloyd &obj) = delete;
  WarshallFloyd(WarshallFloyd &&obj) = delete;
  WarshallFloyd &operator=(WarshallFloyd &&obj) = delete;

 private:
  int32_t number_of_vertices_;
  int32_t shortest_distances_[kMaxNumberOfVertices][kMaxNumberOfVertices];

 private:
  FRIEND_TEST(Test_GRL_1_C_1, AddWeight);  // Should be removed from production code
};

}  // namespace GRL_1_C_1

#endif  // SRC_C15_1_GRL_1_C_1_ALL_PAIRS_SHORTEST_PATH_H_
