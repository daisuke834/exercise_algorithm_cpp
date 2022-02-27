/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-2. 高度なグラフアルゴリズム、トポロジカルソート(Topological Sort)。
 * 深さ優先探索(DFS)で、再帰を用いる実装。計算量はO(|V|+|E|)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "2_GRL_4_B_3_topological_sort_dfs.h"

#include <iostream>
#include <string>

namespace GRL_4_B_3 {

void CallTopologicalSort(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  TopologicalSort* topological_sort = new TopologicalSort();
  int32_t number_of_vertices, number_of_edges;
  input_stream >> number_of_vertices >> number_of_edges;
  topological_sort->ConfigureVertices(number_of_vertices);
  for (int32_t i = 0; i < number_of_edges; ++i) {
    int32_t vertex_from, vertex_to;
    input_stream >> vertex_from >> vertex_to;
    topological_sort->AddVertex(vertex_from, vertex_to);
  }
  topological_sort->Sort();
  topological_sort->Print();
  delete topological_sort;
}

TopologicalSort::TopologicalSort() : number_of_vertices_(0) {}

TopologicalSort::~TopologicalSort() {}

void TopologicalSort::ConfigureVertices(const int32_t number_of_vertices) { number_of_vertices_ = number_of_vertices; }

void TopologicalSort::AddVertex(const int32_t from_index, const int32_t to_index) {
  vertices_[from_index].next.push_back(to_index);
}

void TopologicalSort::Sort() {
  sorted_result_.clear();
  chain_.clear();

  while (true) {
    const int32_t start_index = GetUnexploredVertexIndex();
    if (start_index == kInvalidIndex) {
      break;
    }
    chain_.push_back(start_index);
    Dfs(chain_);
  }
}

int32_t TopologicalSort::GetUnexploredVertexIndex() const {
  int32_t unexplored = kInvalidIndex;
  for (int32_t i = 0; i < number_of_vertices_; ++i) {
    if (!vertices_[i].explored) {
      unexplored = i;
      break;
    }
  }
  return unexplored;
}

void TopologicalSort::Dfs(std::vector<int32_t> chain) {
  const int32_t target = chain.back();
  vertices_[target].explored = true;
  for (const int32_t next_index : vertices_[target].next) {
    if (vertices_[next_index].explored) {
      // DO NOTHING
    } else {
      chain.push_back(next_index);
      Dfs(chain);
      chain.pop_back();
    }
  }
  sorted_result_.push_front(target);
}

void TopologicalSort::Print() {
  for (std::list<int32_t>::iterator itr = sorted_result_.begin(); itr != sorted_result_.end(); ++itr) {
    std::cout << *itr << std::endl;
  }
}

}  // namespace GRL_4_B_3
