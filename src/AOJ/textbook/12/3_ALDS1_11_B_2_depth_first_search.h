/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-3. グラフ(Graph)、深さ優先探索(Depth First Search, DFS)。
 * 隣接行列表現(Adjacency matrices)による管理。
 * 各頂点について全ての頂点との隣接関係を調べているので、ノード数が|V|の時、計算量はO(|V|^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C12_3_ALDS1_11_B_2_DEPTH_FIRST_SEARCH_H_
#define SRC_C12_3_ALDS1_11_B_2_DEPTH_FIRST_SEARCH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_11_B_2 {

constexpr int32_t kMaxVertexNumber = 100;
constexpr int32_t kDoesNotExist = -1;
constexpr int32_t kMaxStackDepth = 200;
constexpr int32_t kMaxLoopCount = 1000000;
constexpr int32_t kFirstExploreTargetIndex = 0;
constexpr int32_t kInvalidTime = -1;

void CallDepthFirstSearch(std::istream& input_stream);

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
  void Reset() noexcept;
  int32_t GetNextTailCheck() noexcept;

 private:
  Vertex(const Vertex& obj) = delete;
  Vertex& operator=(const Vertex& obj) = delete;
  Vertex(Vertex&& obj) = delete;
  Vertex& operator=(Vertex&& obj) = delete;

 private:
  VertexStatus status_;
  int32_t discovered_time_;
  int32_t completion_time_;
  int32_t next_check_;
};

class Stack {
 public:
  Stack() noexcept;
  ~Stack() noexcept;
  void Main(std::istream& input_stream) noexcept;
  void LoadAndCompute(std::istream& input_stream);
  void Push(const int32_t x);
  void Pop();
  int32_t GetTop();
  bool IsEmpty() const noexcept;
  bool IsFull() const noexcept;

 private:
  void PopAndPrint() noexcept;

 private:
  Stack(const Stack& obj) = delete;
  Stack& operator=(const Stack& rhs) = delete;
  Stack(Stack&& obj) = delete;
  Stack& operator=(Stack&& rhs) = delete;

 private:
  int32_t top_position_;
  int32_t values_[kMaxStackDepth];
};

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
  bool IsMapped(const int32_t index_from, const int32_t index_to) const;
  bool DoesNotExist(const int32_t vertex_index) const;

  DepthFirstSearch(const DepthFirstSearch& obj) = delete;
  DepthFirstSearch& operator=(const DepthFirstSearch& obj) = delete;
  DepthFirstSearch(DepthFirstSearch&& obj) = delete;
  DepthFirstSearch& operator=(DepthFirstSearch&& obj) = delete;

 private:
  int32_t time_;
  int32_t number_of_vertices_;
  bool adjacency_matrix_[kMaxVertexNumber][kMaxVertexNumber];
  Vertex vertices_[kMaxVertexNumber];
  Stack todo_;

 private:
  FRIEND_TEST(Test_ALDS1_11_B_2, ExploreAllVertices_1);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_11_B_2, ExploreAllVertices_2);  // Should be removed from production code
};

}  // namespace ALDS1_11_B_2

#endif  // SRC_C12_3_ALDS1_11_B_2_DEPTH_FIRST_SEARCH_H_
