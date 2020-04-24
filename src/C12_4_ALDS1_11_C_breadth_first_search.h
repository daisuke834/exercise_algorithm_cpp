/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-4. グラフ(Graph)、幅優先探索(Breadth First Search, BFS)。
 * 各頂点について全ての頂点との隣接関係を調べているので、ノード数が|V|の時、計算量はO(|V|^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C12_4_ALDS1_11_C_BREADTH_FIRST_SEARCH_H_
#define SRC_C12_4_ALDS1_11_C_BREADTH_FIRST_SEARCH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_11_C {

constexpr int32_t kMaxVertexNumber = 100;
constexpr int32_t kDoesNotExist = -1;
constexpr int32_t kFirstExploreTargetIndex = 0;
constexpr int32_t kNotReached = -1;
constexpr int32_t kMaxDistance = 1000;
constexpr int32_t kMaxQueueSize = 10000;
constexpr int32_t kMaxLoop = 2000000;

void CallBreadthFirstSearch(std::istream &input_stream);

class Queue {
 public:
  Queue() noexcept;
  ~Queue() noexcept;
  void Enqueue(const int32_t index);
  int32_t Dequeue();
  bool IsEmpty() const noexcept;
  bool IsFull() const noexcept;

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

class BreadthFirstSearch {
 public:
  BreadthFirstSearch() noexcept;
  ~BreadthFirstSearch() noexcept;

  void AddVertex(const int32_t vertex);
  void MapDirection(const int32_t vertex_number_from, const int32_t vertex_number_to);
  void ExploreAllVertices();
  void Print() const;
  void Reset() noexcept;

 private:
  void SetStartingVertex(const int32_t starting_vertex_index);
  int32_t PickNextVertex();
  void ExploreOneVertex(const int32_t vertex_index);
  void PushFutureVertexToExplore(const int32_t vertex_index) noexcept;
  void SetDistance(const int32_t index, const int32_t distance);
  int32_t GetDistance(const int32_t index) const;
  void MarkAsExplored(const int32_t index);
  bool NotExplored(const int32_t index) const;
  bool AlreadyExplored(const int32_t index) const;
  bool IsInvalidVertexIndex(const int32_t index) const noexcept;
  static bool IsInvalidVertexNumber(const int32_t vertex_number) noexcept;
  static int32_t ConvertFromVertexNumberToIndex(const int32_t node_number);
  int32_t ConvertFromIndexToVertexNumber(const int32_t index) const;
  bool IsMapped(const int32_t index_from, const int32_t index_to) const;
  bool DoesNotExist(const int32_t vertex_index) const;
  bool DoesExist(const int32_t vertex_index) const;
  bool InvalidDistance(const int32_t index) const;

  BreadthFirstSearch(const BreadthFirstSearch &obj) = delete;
  BreadthFirstSearch &operator=(const BreadthFirstSearch &obj) = delete;
  BreadthFirstSearch(BreadthFirstSearch &&obj) = delete;
  BreadthFirstSearch &operator=(BreadthFirstSearch &&obj) = delete;

 private:
  int32_t size_;
  bool adjacency_matrix_[kMaxVertexNumber][kMaxVertexNumber];
  bool explored_[kMaxVertexNumber];
  int32_t distances_[kMaxVertexNumber];
  Queue todo_;

 private:
  // FRIEND_TEST(Test_ALDS1_11_C, aaa);  // Should be removed from production code
};

}  // namespace ALDS1_11_C

#endif  // SRC_C12_4_ALDS1_11_C_BREADTH_FIRST_SEARCH_H_
