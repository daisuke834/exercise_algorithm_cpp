/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-2. 重み付きグラフ(Weighted Graph)、最小全域木(Minimum Spanning Tree, MST)。
 * クラスカル法 (Kruskal's algorithm)による実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C13_2_ALDS1_12_A_1_MST_KRUSKAL_H_
#define SRC_C13_2_ALDS1_12_A_1_MST_KRUSKAL_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace ALDS1_12_A_1 {

constexpr int32_t kMaxNumberOfVertices = 100;
constexpr int32_t kMaxWeight = 2000;
constexpr int32_t kInvalidVertex = -1;
constexpr int32_t kInvalidWeight = -1;
constexpr int32_t kMaxLoop = 2000000;
constexpr int32_t kMaxQueueSize = 100000;
constexpr int32_t kMaxNumberOfEdges = kMaxNumberOfVertices * kMaxNumberOfVertices;
constexpr int32_t kMaxSizeOfEdgeMappings = kMaxNumberOfEdges * 2;

// ****************************************************

void CallMinimumSpanningTree(std::istream &input_stream);

enum class EdgeStatus : int32_t { kNotChecked = 0, kSkipped, kSelected };

struct Edge {
  int32_t weight{kInvalidWeight};
  int32_t vertex_1{kInvalidVertex};
  int32_t vertex_2{kInvalidVertex};
  EdgeStatus status{EdgeStatus::kNotChecked};
};

// ****************************************************

class Queue {
 public:
  Queue() noexcept;
  ~Queue() noexcept;
  void Enqueue(const int32_t index);
  int32_t Dequeue();
  bool IsEmpty() const noexcept;
  bool IsFull() const noexcept;
  void Clear() noexcept;

 private:
  Queue(const Queue &obj) = delete;
  Queue &operator=(const Queue &rhs) = delete;
  Queue(Queue &&obj) = delete;
  Queue &operator=(Queue &&rhs) = delete;

  static int32_t GetNextPosition(const int32_t current_position) noexcept;

 private:
  int32_t depth_;
  int32_t head_;
  int32_t indices_[kMaxQueueSize];
};

// ****************************************************
class ConnectedComponents {
 public:
  ConnectedComponents() noexcept;
  ~ConnectedComponents() noexcept;

  void SetNumberOfVertices(const int32_t number_of_vertices);
  bool ConnectionExistsBetweenStartAndEnd(const int32_t vertex_start, const int32_t vertex_end);
  void AddMapping(const int32_t vertex_1, const int32_t vertex_2);
  void ResetAll() noexcept;

 private:
  void ExploreOneVertex(const int32_t vertex_index, const int32_t cluster_id);
  void MapEdge(const int32_t edge_index, const int32_t vertex_from, const int32_t vertex_to);
  int32_t GetNeighbour(const int32_t vertex_index, const int32_t relative_index) const;
  void PushFutureVertexToExplore(const int32_t vertex_index) noexcept;
  int32_t PickNextVertex();
  void MarkAsExplored(const int32_t index);
  bool NotExplored(const int32_t index) const;
  bool AlreadyExplored(const int32_t index) const;
  void MarkAsQueued(const int32_t index);
  bool NotQueued(const int32_t index) const;
  bool AlreadyQueued(const int32_t index) const;
  bool DoesNotExist(const int32_t vertex_index) const;
  bool DoesExist(const int32_t vertex_index) const;
  bool InvalidVertexIndex(const int32_t vertex_index) const noexcept;
  bool InvalidEdgeIndex(const int32_t edge_index) const noexcept;
  void Reset() noexcept;
  void ResetClusterMappings() noexcept;

  void SetClusterId(const int32_t vertex_index, const int32_t cluster_id);
  int32_t GetClusterId(const int32_t vertex_index) const;
  int32_t ClusterIdIsNotAllocated(const int32_t vertex_index) const;

  ConnectedComponents(const ConnectedComponents &obj) = delete;
  ConnectedComponents &operator=(const ConnectedComponents &obj) = delete;
  ConnectedComponents(ConnectedComponents &&obj) = delete;
  ConnectedComponents &operator=(ConnectedComponents &&obj) = delete;

 private:
  int32_t number_of_vertices_;
  int32_t number_of_edges_;
  Queue todo_;
  bool queued_[kMaxNumberOfVertices];
  bool explored_[kMaxNumberOfVertices];
  std::vector<int32_t> neighbours_[kMaxNumberOfVertices];
  int32_t cluster_mappings_[kMaxNumberOfVertices];

 private:
  FRIEND_TEST(Test_ALDS1_11_D_2, Mapping);                         // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_11_D_2, BuildGraph_sort);                 // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_11_D_2, BuildGraph_BuildMetaDataOfEdge);  // Should be removed from production code
};

// ****************************************************

class MinimumSpanningTree {
 public:
  MinimumSpanningTree() noexcept;
  ~MinimumSpanningTree() noexcept;

  void SetNumberOfVertices(const int32_t number_of_vertices);
  void AddWeight(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight);
  int32_t CalculateSumOfWeightsOfMinimumSpanningTree();

 private:
  void StoreWeightInAdjacencyMatrix(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight) noexcept;
  void AppendWeightToEdgeArray(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight);
  bool CanAppendWeightToEdgeArray(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight) const noexcept;
  bool InvalidVertexIndex(const int32_t vertex_index) const noexcept;
  bool WeightIsAlreadyStored(const int32_t vertex_1, const int32_t vertex_2) const noexcept;
  static bool ValidWeight(const int32_t weight) noexcept;
  bool InvalidEdgeIndex(const int32_t edge_index) const noexcept;
  int32_t GetSumOfWeights() const noexcept;

  void ComputeQuickSort(const int32_t start, const int32_t end);
  int32_t ComputePartition(const int32_t start, const int32_t end);
  void Swap(const int32_t index_1, const int32_t index_2);

  MinimumSpanningTree(const MinimumSpanningTree &obj) = delete;
  MinimumSpanningTree &operator=(const MinimumSpanningTree &obj) = delete;
  MinimumSpanningTree(MinimumSpanningTree &&obj) = delete;
  MinimumSpanningTree &operator=(MinimumSpanningTree &&obj) = delete;

 private:
  int32_t number_of_vertices_;
  int32_t number_of_edges_;
  int32_t adjacency_matrix_[kMaxNumberOfVertices][kMaxNumberOfVertices];
  Edge edges_[(kMaxNumberOfVertices * kMaxNumberOfVertices - kMaxNumberOfVertices) / 2];
  ConnectedComponents connected_components_;

 private:
  FRIEND_TEST(Test_ALDS1_12_A_1, AddWeight);                   // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_12_A_1, CanAppendWeightToEdgeArray);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_12_A_1, ComputeQuickSort);            // Should be removed from production code
};

}  // namespace ALDS1_12_A_1

#endif  // SRC_C13_2_ALDS1_12_A_1_MST_KRUSKAL_H_
