/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-3. グラフ(Graph)、深さ優先探索(Depth First Search, DFS)。
 * 隣接リスト表現(Adjacency list)による管理。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C12_3_ALDS1_11_B_3_DEPTH_FIRST_SEARCH_H_
#define SRC_C12_3_ALDS1_11_B_3_DEPTH_FIRST_SEARCH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace ALDS1_11_B_3 {

constexpr int32_t kMaxVertexNumber = 100;
constexpr int32_t kDoesNotExist = -1;
constexpr int32_t kMaxStackDepth = 200;
constexpr int32_t kMaxLoopCount = 1000000;
constexpr int32_t kFirstExploreTargetIndex = 0;
constexpr int32_t kInvalidTime = -1;

void CallDepthFirstSearch(std::istream &input_stream);

enum class VertexStatus : int32_t { kInit = 0, kDiscovered, kCompleted };

class Vertex {
 public:
  Vertex() noexcept;
  ~Vertex() noexcept;
  void Discovered(const int32_t time);
  void Completed(const int32_t time);
  VertexStatus GetStatus() const noexcept;
  int32_t GetDiscoveredTime() const noexcept;
  int32_t GetCompletionTime() const noexcept;
  void AddTail(const int32_t tail_index) noexcept;
  int32_t GetNextTailIndex() noexcept;

 private:
  int32_t GetNumberOfTails() const noexcept;

  Vertex(const Vertex &obj) = delete;
  Vertex &operator=(const Vertex &obj) = delete;
  Vertex(Vertex &&obj) = delete;
  Vertex &operator=(Vertex &&obj) = delete;

 private:
  VertexStatus status_;
  int32_t discovered_time_;
  int32_t completion_time_;
  int32_t next_check_;
  std::vector<int32_t> tails_;
};

class DepthFirstSearch {
 public:
  DepthFirstSearch() noexcept;
  ~DepthFirstSearch() noexcept;

  void AddVertex(const int32_t vertex);
  void MapDirection(const int32_t vertex_number_from, const int32_t vertex_number_to);
  void ExploreAllVertices();
  void Print() const;

 private:
  void ExploreOneVertex(const int32_t vertex_index);
  int32_t PickNextVertex();
  void DiscoverOneVertex(const int32_t vertex_index);
  void CompleteOneVertex(const int32_t vertex_index);
  int32_t PickUnexploredVertex();
  int32_t FindUnexploredVertex() const;
  bool NoMoreUnexploredVertex() const;
  bool AllVerticesAreNotCompleted() const;
  bool IsInvalidVertexIndex(const int32_t index) const noexcept;
  static bool IsInvalidVertexNumber(const int32_t vertex_number) noexcept;
  static int32_t ConvertFromVertexNumberToIndex(const int32_t node_number);
  int32_t ConvertFromIndexToVertexNumber(const int32_t index) const;
  bool DoesNotExist(const int32_t vertex_index) const;

  DepthFirstSearch(const DepthFirstSearch &obj) = delete;
  DepthFirstSearch &operator=(const DepthFirstSearch &obj) = delete;
  DepthFirstSearch(DepthFirstSearch &&obj) = delete;
  DepthFirstSearch &operator=(DepthFirstSearch &&obj) = delete;

 private:
  int32_t time_;
  int32_t number_of_vertices_;
  Vertex vertices_[kMaxVertexNumber];
  std::stack<int32_t> todo_;

 private:
  FRIEND_TEST(Test_ALDS1_11_B_3, ExploreAllVertices_1);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_11_B_3, ExploreAllVertices_2);  // Should be removed from production code
};

}  // namespace ALDS1_11_B_3

#endif  // SRC_C12_3_ALDS1_11_B_3_DEPTH_FIRST_SEARCH_H_
