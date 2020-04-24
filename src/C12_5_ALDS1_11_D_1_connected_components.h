/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-5. グラフ(Graph)、連結成分(Connected Components)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C12_5_ALDS1_11_D_1_CONNECTED_COMPONENTS_H_
#define SRC_C12_5_ALDS1_11_D_1_CONNECTED_COMPONENTS_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_11_D_1 {

constexpr int32_t kMaxNumberOfVertices = 100000;
constexpr int32_t kMaxNumberOfEdges = 100000;
constexpr int32_t kMaxSizeOfEdgeMappings = kMaxNumberOfEdges * 2;
constexpr int32_t kMaxNumberOfQuestions = 10000;
constexpr int32_t kDoesNotExist = -1;
constexpr int32_t kMaxLoop = 2000000;
constexpr int32_t kMaxQueueSize = 100000;

void CallConnectedComponents(std::istream &input_stream);

struct Edge {
  int32_t from{-1};
  int32_t to{-1};
};

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
  void BuildGraph();
  void PrintEdges() const;

 private:
  void ExploreOneVertex(const int32_t vertex_index, const int32_t cluster_id);
  void MapEdge(const int32_t edge_index, const int32_t vertex_from, const int32_t vertex_to);
  int32_t GetNumberOfNeighbours(const int32_t vertex_index) const;
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

  void ComputeQuickSort(const int32_t start, const int32_t end);
  int32_t ComputePartition(const int32_t start, const int32_t end);
  void Swap(const int32_t index_1, const int32_t index_2);

  void BuildMetaDataOfEdge() noexcept;
  void ResetMetaDataOfEdge() noexcept;

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
  Edge edges_[kMaxSizeOfEdgeMappings];
  int32_t edge_offset_of_each_vertex_[kMaxNumberOfVertices];
  int32_t number_of_neighbours_of_each_vertex_[kMaxNumberOfVertices];
  int32_t cluster_mappings_[kMaxNumberOfVertices];

 private:
  FRIEND_TEST(Test_ALDS1_11_D_1, Mapping);                         // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_11_D_1, BuildGraph_sort);                 // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_11_D_1, BuildGraph_BuildMetaDataOfEdge);  // Should be removed from production code
};

}  // namespace ALDS1_11_D_1

#endif  // SRC_C12_5_ALDS1_11_D_1_CONNECTED_COMPONENTS_H_
