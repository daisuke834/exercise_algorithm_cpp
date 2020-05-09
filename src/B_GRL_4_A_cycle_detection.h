/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 有向グラフの閉路検査(Cycle Detection for a Directed Graph)。
 */

#ifndef SRC_B_GRL_4_A_CYCLE_DETECTION_H_
#define SRC_B_GRL_4_A_CYCLE_DETECTION_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace GRL_4_A {

constexpr int32_t kMaxNumberOfVertices = 100;

// ****************************************************

void CallCycleDetection(std::istream &input_stream);

// ****************************************************

struct Vertex {
  bool discovered_{false};
  bool completed_{false};
  std::vector<int32_t> next;
};

class CycleDetection {
 public:
  CycleDetection() noexcept;
  ~CycleDetection() noexcept;
  void SetNumberOfVertices(const int32_t number_of_vertices) noexcept;
  void AddEdge(const int32_t vertex_from, const int32_t vertex_to) noexcept;
  bool HaveCycle() noexcept;

 private:
  void Dfs(const int32_t vertex_index) noexcept;

 private:
  int32_t number_of_vertices_;
  bool have_cycle_;
  Vertex vertices_[kMaxNumberOfVertices];
};

}  // namespace GRL_4_A

#endif  // SRC_B_GRL_4_A_CYCLE_DETECTION_H_
