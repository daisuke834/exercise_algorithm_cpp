/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-3. グラフ(Graph)、深さ優先探索(Depth First Search, DFS)。
 * 各頂点について全ての頂点との隣接関係を調べているので、ノード数が|V|の時、計算量はO(|V|^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C12_3_ALDS1_11_B_1_DEPTH_FIRST_SEARCH_H_
#define SRC_C12_3_ALDS1_11_B_1_DEPTH_FIRST_SEARCH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_11_B_1 {

constexpr int32_t kMaxVertexNumber = 100;
constexpr int32_t kDoesNotExist = -1;
constexpr int32_t kMaxStackDepth = 200;
constexpr int32_t kMaxLoopCount = 1000000;
constexpr int32_t kFirstExploreTargetIndex = 0;

void CallDepthFirstSearch(std::istream &input_stream);

class TimeStamp {
 public:
  TimeStamp() noexcept;
  ~TimeStamp() noexcept;

  void Next();
  int32_t Get() const;
  void Set(const int32_t time);
  void Reset() noexcept;
  bool IsInvalid() const noexcept;
  bool IsValid() const noexcept;

 private:
  TimeStamp(const TimeStamp &obj) = delete;
  TimeStamp &operator=(const TimeStamp &obj) = delete;
  TimeStamp(TimeStamp &&obj) = delete;
  TimeStamp &operator=(TimeStamp &&obj) = delete;

 private:
  int32_t time_;
};

class Stack {
 public:
  Stack() noexcept;
  ~Stack() noexcept;
  void Main(std::istream &input_stream) noexcept;
  void LoadAndCompute(std::istream &input_stream);
  void Push(const int32_t x);
  int32_t Pop();
  bool IsEmpty() const noexcept;
  bool IsFull() const noexcept;

 private:
  void PopAndPrint() noexcept;

 private:
  Stack(const Stack &obj) = delete;
  Stack &operator=(const Stack &rhs) = delete;
  Stack(Stack &&obj) = delete;
  Stack &operator=(Stack &&rhs) = delete;

 private:
  int32_t top_position_;
  int32_t values_[kMaxStackDepth];
};

enum class VertexStatus : int32_t { kNotExplored = 0, kExplored, kCompleted };

class DepthFirstSearch {
 public:
  DepthFirstSearch() noexcept;
  ~DepthFirstSearch() noexcept;

  void AddVertex(const int32_t vertex);
  void MapDirection(const int32_t vertex_number_from, const int32_t vertex_number_to);
  void ExploreAllVertices();
  void Print() const;
  void Reset() noexcept;

 private:
  void ExploreOneVertex(const int32_t vertex_index);
  void CompleteOneVertex(const int32_t vertex_index);
  int32_t PickNextVertex() noexcept;
  void PushFutureVertexToExplore(const int32_t vertex_index) noexcept;
  int32_t GetUnexploredVertex() const;
  bool NoMoreUnexploredVertex() const;
  bool AllVerticesAreNotCompleted() const;
  bool IsInvalidVertexIndex(const int32_t index) const noexcept;
  static bool IsInvalidVertexNumber(const int32_t vertex_number) noexcept;
  static int32_t ConvertFromVertexNumberToIndex(const int32_t node_number);
  int32_t ConvertFromIndexToVertexNumber(const int32_t index) const;
  bool IsMapped(const int32_t index_from, const int32_t index_to) const;
  bool WasExplored(const int32_t vertex_index) const;
  bool NotExplored(const int32_t vertex_index) const;
  bool NotCompleted(const int32_t vertex_index) const;
  bool DoesNotExist(const int32_t vertex_index) const;
  VertexStatus GetVertexStatus(const int32_t vertex_index) const;

  DepthFirstSearch(const DepthFirstSearch &obj) = delete;
  DepthFirstSearch &operator=(const DepthFirstSearch &obj) = delete;
  DepthFirstSearch(DepthFirstSearch &&obj) = delete;
  DepthFirstSearch &operator=(DepthFirstSearch &&obj) = delete;

 private:
  TimeStamp time_;
  int32_t size_;
  bool adjacency_matrix_[kMaxVertexNumber][kMaxVertexNumber];
  TimeStamp explored_time_[kMaxVertexNumber];
  TimeStamp completion_time_[kMaxVertexNumber];
  Stack todo_;

 private:
  FRIEND_TEST(Test_ALDS1_11_B_1, ExploreAllVertices_1);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_11_B_1, ExploreAllVertices_2);  // Should be removed from production code
};

}  // namespace ALDS1_11_B_1

#endif  // SRC_C12_3_ALDS1_11_B_1_DEPTH_FIRST_SEARCH_H_
