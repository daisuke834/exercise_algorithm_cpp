/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-3. 重み付きグラフ(Weighted Graph)、単一始点最短経路(Single Source Shortest Path)。
 * ダイクストラのアルゴリズム (Dijkstra's algorithm)による実装。計算量はO(|V|^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C13_3_ALDS1_12_B_1_SINGLE_SOURCE_SHORTEST_PATH_H_
#define SRC_C13_3_ALDS1_12_B_1_SINGLE_SOURCE_SHORTEST_PATH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_12_B_1 {

constexpr int32_t kMaxNumberOfVertices = 100;
constexpr int32_t kMaxWeight = 2000;
constexpr int32_t kMaxLoop = 2000000;
constexpr int32_t kInvalidWeight = INT32_MAX;
constexpr int32_t kInvalidVertex = -1;
constexpr int32_t kRootVertex = 0;

// ****************************************************

void CallDijkstraAlgorithm(std::istream &input_stream);

// ****************************************************

enum class VertexStatus { kUnchecked = 0, kCandidate, kAdded };

struct Vertex {
  VertexStatus status{VertexStatus::kUnchecked};
  int32_t distance_from_root{INT32_MAX};
  int32_t parent{kInvalidVertex};
};

class DijkstraAlgorithm {
 public:
  DijkstraAlgorithm() noexcept;
  ~DijkstraAlgorithm() noexcept;

  void SetNumberOfVertices(const int32_t number_of_vertices);
  void AddWeight(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight);
  void CalculateShortestPaths();
  void Print() const noexcept;

 private:
  int32_t FindNextVertexToAdd() const noexcept;
  void UpdateExternalVertices(const int32_t vertex_index_added);
  void CheckAndUpdateExternalVertex(const int32_t vertex_index_added, const int32_t vertex_index_to_update);
  void UpdateCandidateByAddedVertex(const int32_t vertex_index_added, const int32_t vertex_index_to_update);
  bool CanBeUpdatedToSmallerDistance(const int32_t vertex_index_added, const int32_t vertex_index_to_update) const;
  void AddVertexToTree(const int32_t vertex_index_to_add);
  void QueueVertexAsRoot(const int32_t first_vertex_to_start);
  void AppendWeightToEdgeArray(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight);
  bool CanAppendWeightToEdgeArray(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight) const noexcept;
  bool CanBeMapped(const int32_t vertex_1, const int32_t vertex_2) const;
  bool IsExternalVertex(const int32_t vertex_index) const;
  bool IsTreeComponent(const int32_t vertex_index) const;
  bool InvalidVertexIndex(const int32_t vertex_index) const noexcept;

  DijkstraAlgorithm(const DijkstraAlgorithm &obj) = delete;
  DijkstraAlgorithm &operator=(const DijkstraAlgorithm &obj) = delete;
  DijkstraAlgorithm(DijkstraAlgorithm &&obj) = delete;
  DijkstraAlgorithm &operator=(DijkstraAlgorithm &&obj) = delete;

 private:
  int32_t number_of_vertices_;
  Vertex vertices_[kMaxNumberOfVertices];
  int32_t adjacency_matrix_[kMaxNumberOfVertices][kMaxNumberOfVertices];

 private:
  FRIEND_TEST(Test_ALDS1_12_B_1, Constructor);          // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_12_B_1, AddWeight_1);          // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_12_B_1, AddWeight_2);          // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_12_B_1, FindNextVertexToAdd);  // Should be removed from production code
};

}  // namespace ALDS1_12_B_1

#endif  // SRC_C13_3_ALDS1_12_B_1_SINGLE_SOURCE_SHORTEST_PATH_H_
