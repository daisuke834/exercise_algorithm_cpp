/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 有向グラフの閉路検査(Cycle Detection for a Directed Graph)。
 * 計算量はO(V)
 */

#include "src/B_GRL_4_A_cycle_detection.h"

namespace GRL_4_A {

void CallCycleDetection(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  CycleDetection* cycle_detection = new CycleDetection();
  try {
    int32_t number_of_vertices, number_of_edges;
    input_stream >> number_of_vertices >> number_of_edges;
    cycle_detection->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_edges; ++i) {
      int32_t vertex_from, vertex_to;
      input_stream >> vertex_from >> vertex_to;
      cycle_detection->AddEdge(vertex_from, vertex_to);
    }
    const bool have_cycle = cycle_detection->HaveCycle();
    if (have_cycle) {
      std::cout << "1" << std::endl;
    } else {
      std::cout << "0" << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: CallCycleDetection()" << std::endl;
    throw;
  }
  delete cycle_detection;
}

// ****************************************************

CycleDetection::CycleDetection() noexcept : number_of_vertices_(0), have_cycle_(false) {}

CycleDetection::~CycleDetection() noexcept {}

void CycleDetection::SetNumberOfVertices(const int32_t number_of_vertices) noexcept {
  number_of_vertices_ = number_of_vertices;
}

void CycleDetection::AddEdge(const int32_t vertex_from, const int32_t vertex_to) noexcept {
  vertices_[vertex_from].next.push_back(vertex_to);
}

bool CycleDetection::HaveCycle() noexcept {
  for (int32_t start_index = 0; start_index < number_of_vertices_; ++start_index) {
    if (!vertices_[start_index].completed_) {
      Dfs(start_index);
    }
  }
  return have_cycle_;
}

void CycleDetection::Dfs(const int32_t vertex_index) noexcept {
  if ((!vertices_[vertex_index].completed_) && (vertices_[vertex_index].discovered_)) {
    have_cycle_ = true;
  } else {
    vertices_[vertex_index].discovered_ = true;
    for (const int32_t next_index : vertices_[vertex_index].next) {
      if (!vertices_[vertex_index].completed_) {
        Dfs(next_index);
      }
    }
    vertices_[vertex_index].completed_ = true;
  }
}

// **********************************************************************

}  // namespace GRL_4_A
