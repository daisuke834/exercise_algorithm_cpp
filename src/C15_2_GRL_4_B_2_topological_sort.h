/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-2. 高度なグラフアルゴリズム、トポロジカルソート(Topological Sort)。
 * 幅優先探索(BFS)で、かつ再帰を用いない実装。計算量はO(|V|+|E|)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C15_2_GRL_4_B_2_TOPOLOGICAL_SORT_H_
#define SRC_C15_2_GRL_4_B_2_TOPOLOGICAL_SORT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace GRL_4_B_2 {

constexpr int32_t kMaxNumberOfVertices = 10000;
constexpr int32_t kMaxNumberOfEdges = 100000;
constexpr int32_t kDoesNotExist = -1;
constexpr int32_t kMaxLoopCount = 1000000;
constexpr int32_t kFirstExploreTargetIndex = 0;

void CallTopologicalSort(std::istream& input_stream);

enum class VertexStatus : int32_t { kInit = 0, kCompleted };

class Vertex {
 public:
  Vertex() noexcept;
  ~Vertex() noexcept;
  void Completed();
  VertexStatus GetStatus() const noexcept;
  void AddTail(const int32_t tail_index) noexcept;
  void IncrementRemainingIndegree();
  void DecrementRemainingIndegree();
  bool RemainingIndegreeIsZero() const noexcept;
  int32_t GetNextTailIndex() noexcept;

 private:
  int32_t GetNumberOfTails() const noexcept;

  Vertex(const Vertex& obj) = delete;
  Vertex& operator=(const Vertex& obj) = delete;
  Vertex(Vertex&& obj) = delete;
  Vertex& operator=(Vertex&& obj) = delete;

 private:
  VertexStatus status_;
  int32_t next_check_;
  int32_t remaining_indegree_;
  std::vector<int32_t> tails_;
};

class TopologicalSort {
 public:
  TopologicalSort() noexcept;
  ~TopologicalSort() noexcept;

  void SetNumberOfVertices(const int32_t number_of_vertices);
  void MapDirection(const int32_t vertex_index_from, const int32_t vertex_index_to);
  void GenerateSortedList();
  void Print();
  void Reset() noexcept;

 private:
  void ExploreOneVertex(const int32_t vertex_index);
  int32_t PickNextVertex();
  void CompleteOneVertex(const int32_t vertex_index);
  int32_t PickUnexploredIndependentVertex();
  int32_t FindUnexploredIndependentVertex() const;
  bool NoMoreUnexploredIndependentVertex() const;
  bool AllVerticesAreNotCompleted() const;
  bool IsInvalidVertexIndex(const int32_t index) const noexcept;
  bool DoesNotExist(const int32_t vertex_index) const;

  TopologicalSort(const TopologicalSort& obj) = delete;
  TopologicalSort& operator=(const TopologicalSort& obj) = delete;
  TopologicalSort(TopologicalSort&& obj) = delete;
  TopologicalSort& operator=(TopologicalSort&& obj) = delete;

 private:
  int32_t number_of_vertices_;
  Vertex vertices_[kMaxNumberOfVertices];
  std::queue<int32_t> todo_;
  std::vector<int32_t> sorted_;

 private:
  FRIEND_TEST(Test_GRL_4_B_2, dummy);  // Should be removed from production code
};

}  // namespace GRL_4_B_2

#endif  // SRC_C15_2_GRL_4_B_2_TOPOLOGICAL_SORT_H_
