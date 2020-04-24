/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-3. 高度なグラフアルゴリズム、関節点(Articulation Point)。
 * 深さ優先探索(DFS)で、かつ再帰を用いない実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C15_3_GRL_3_A_ARTICULATION_POINT_H_
#define SRC_C15_3_GRL_3_A_ARTICULATION_POINT_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace GRL_3_A {

constexpr int32_t kMaxNumberOfVertices = 100000;
constexpr int32_t kMaxNumberOfEdges = 100000;
constexpr int32_t kDoesNotExist = -1;
constexpr int32_t kMaxLoopCount = 1000000;
constexpr int32_t kFirstExploreTargetIndex = 0;
constexpr int32_t kRoot = -2;

void CallArticulationPoint(std::istream &input_stream);

enum class VertexStatus : int32_t { kInit = 0, kDiscovered, kCompleted };

class Vertex {
 public:
  Vertex() noexcept;
  ~Vertex() noexcept;
  void Discovered(const int32_t preorder_number, const int32_t parent_index);
  void AddChild(const int32_t child_index);
  std::vector<int32_t> GetChildren() const noexcept;
  void Completed();
  VertexStatus GetStatus() const noexcept;
  void AddTail(const int32_t tail_index) noexcept;
  int32_t GetNextTailIndex() noexcept;

  int32_t GetParentIndex() const noexcept;
  int32_t GetPreorderNumber() const noexcept;
  void UpdateLowestScore(const int32_t lowest_score) noexcept;
  int32_t GetLowestScore() const noexcept;

 private:
  int32_t GetNumberOfTails() const noexcept;

  Vertex(const Vertex &obj) = delete;
  Vertex &operator=(const Vertex &obj) = delete;
  Vertex(Vertex &&obj) = delete;
  Vertex &operator=(Vertex &&obj) = delete;

 private:
  VertexStatus status_;
  int32_t parent_index_;
  int32_t preorder_number_;
  int32_t lowest_score_;
  int32_t next_check_;
  std::vector<int32_t> tails_;
  std::vector<int32_t> children_;
};

class ArticulationPoint {
 public:
  ArticulationPoint() noexcept;
  ~ArticulationPoint() noexcept;

  void SetNumberOfVertices(const int32_t number_of_vertices);
  void MapDirection(const int32_t vertex_index_from, const int32_t vertex_index_to);
  void ExploreAllVertices();
  void PrintArticulationPoints();
  void Reset() noexcept;

 private:
  void ExploreOneVertex(const int32_t vertex_index);
  bool IsArticulationPoint(const int32_t vertex_index) const;
  int32_t PickNextVertex();
  void DiscoverOneVertex(const int32_t discovered_index, const int32_t parent_index);
  void CompleteOneVertex(const int32_t vertex_index);
  int32_t FindUnexploredVertex() const;
  bool NoMoreUnexploredVertex() const;
  bool AllVerticesAreNotCompleted() const;
  bool IsInvalidVertexIndex(const int32_t index) const noexcept;
  bool DoesNotExist(const int32_t vertex_index) const;

  ArticulationPoint(const ArticulationPoint &obj) = delete;
  ArticulationPoint &operator=(const ArticulationPoint &obj) = delete;
  ArticulationPoint(ArticulationPoint &&obj) = delete;
  ArticulationPoint &operator=(ArticulationPoint &&obj) = delete;

 private:
  int32_t number_of_vertices_;
  int32_t preorder_number_;
  Vertex vertices_[kMaxNumberOfVertices];
  std::stack<int32_t> todo_;

 private:
  FRIEND_TEST(Test_GRL_3_A, dummy);  // Should be removed from production code
};

}  // namespace GRL_3_A

#endif  // SRC_C15_3_GRL_3_A_ARTICULATION_POINT_H_
