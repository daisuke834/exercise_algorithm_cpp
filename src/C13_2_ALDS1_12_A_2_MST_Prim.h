/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-2. 重み付きグラフ(Weighted Graph)、最小全域木(Minimum Spanning Tree, MST)。
 * プリム法 (Prim's algorithm)による実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C13_2_ALDS1_12_A_2_MST_PRIM_H_
#define SRC_C13_2_ALDS1_12_A_2_MST_PRIM_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_12_A_2 {

constexpr int32_t kMaxNumberOfVertices = 100;
constexpr int32_t kMaxWeight = 2000;
constexpr int32_t kMaxLoop = 2000000;
constexpr int32_t kInvalidWeight = INT32_MAX;
constexpr int32_t kInvalidVertex = -1;
constexpr int32_t kRootVertex = 0;

// ****************************************************

void CallMinimumSpanningTree(std::istream& input_stream);

// ****************************************************

enum class VertexStatus { kUnchecked = 0, kCandidate, kAdded };

struct Vertex {
  VertexStatus status{VertexStatus::kUnchecked};
  int32_t minimum_distance_to_this{INT32_MAX};
  int32_t parent{kInvalidVertex};
};

class MinimumSpanningTree {
 public:
  MinimumSpanningTree() noexcept;
  ~MinimumSpanningTree() noexcept;

  void SetNumberOfVertices(const int32_t number_of_vertices);
  void AddWeight(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight);
  int32_t CalculateSumOfWeightsOfMinimumSpanningTree();

 private:
  int32_t FindNextVertexToAdd() const noexcept;
  void UpdateExternalVertices(const int32_t vertex_index_added);
  void CheckAndUpdateExternalVertex(const int32_t vertex_index_added, const int32_t vertex_index_to_update);
  void UpdateCandidateByAddedVertex(const int32_t vertex_index_added, const int32_t vertex_index_to_update);
  bool CanBeUpdatedToSmallerDistance(const int32_t vertex_index_added, const int32_t vertex_index_to_update) const;
  void AddVertexToTree(const int32_t vertex_index_to_add);
  void QueueVertexAsRoot(const int32_t first_vertex_to_start);
  void AppendWeightToEdgeArray(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight);
  int32_t GetSumOfWeights() const noexcept;
  bool CanAppendWeightToEdgeArray(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight) const noexcept;
  bool CanBeMapped(const int32_t vertex_1, const int32_t vertex_2) const;
  bool IsExternalVertex(const int32_t vertex_index) const;
  bool IsTreeComponent(const int32_t vertex_index) const;
  bool InvalidVertexIndex(const int32_t vertex_index) const noexcept;

  MinimumSpanningTree(const MinimumSpanningTree& obj) = delete;
  MinimumSpanningTree& operator=(const MinimumSpanningTree& obj) = delete;
  MinimumSpanningTree(MinimumSpanningTree&& obj) = delete;
  MinimumSpanningTree& operator=(MinimumSpanningTree&& obj) = delete;

 private:
  int32_t number_of_vertices_;
  Vertex vertices_[kMaxNumberOfVertices];
  int32_t adjacency_matrix_[kMaxNumberOfVertices][kMaxNumberOfVertices];

 private:
  FRIEND_TEST(Test_ALDS1_12_A_2, Constructor);          // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_12_A_2, AddWeight);            // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_12_A_2, FindNextVertexToAdd);  // Should be removed from production code
};

}  // namespace ALDS1_12_A_2

#endif  // SRC_C13_2_ALDS1_12_A_2_MST_PRIM_H_
