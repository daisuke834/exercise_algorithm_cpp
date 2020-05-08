/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-2. 高度なグラフアルゴリズム、トポロジカルソート(Topological Sort)。
 * 深さ優先探索(DFS)で、再帰を用いる実装。計算量はO(|V|+|E|)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C15_2_GRL_4_B_3_TOPOLOGICAL_SORT_DFS_H_
#define SRC_C15_2_GRL_4_B_3_TOPOLOGICAL_SORT_DFS_H_

#include <cstdint>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>

namespace GRL_4_B_3 {

constexpr int32_t kMaxNumberOfVertices = 10000;
constexpr int32_t kInvalidIndex = -1;

void CallTopologicalSort(std::istream &input_stream);

struct Vertex {
  bool explored{false};
  std::vector<int32_t> next;
};

class TopologicalSort {
 public:
  TopologicalSort();
  ~TopologicalSort();
  void ConfigureVertices(const int32_t number_of_vertices);
  void AddVertex(const int32_t from_index, const int32_t to_index);
  void Sort();
  void Print();

 private:
  void Dfs(std::vector<int32_t> chain);
  int32_t GetUnexploredVertexIndex() const;

 private:
  int32_t number_of_vertices_;
  Vertex vertices_[kMaxNumberOfVertices];
  std::vector<int32_t> chain_;
  std::list<int32_t> sorted_result_;
};

}  // namespace GRL_4_B_3

#endif  // SRC_C15_2_GRL_4_B_3_TOPOLOGICAL_SORT_DFS_H_
