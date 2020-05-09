/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief 有向グラフの閉路検査(Cycle Detection for a Directed Graph)。
 */

#ifndef SRC_B_GRL_4_A_CYCLE_DETECTION_H_
#define SRC_B_GRL_4_A_CYCLE_DETECTION_H_

#include <cstdint>
#include <iostream>
#include <string>

namespace GRL_4_A {

// ****************************************************

void CallCycleDetection(std::istream &input_stream);

// ****************************************************

class CycleDetection {
 public:
  CycleDetection() noexcept;
  ~CycleDetection() noexcept;
  void SetNumberOfVertices(const int32_t number_of_vertices) noexcept;
  void AddEdge(const int32_t vertex_from, const int32_t vertex_to) noexcept;
  bool HaveCycle() const noexcept;

 private:
  int32_t number_of_vertices_;
};

}  // namespace GRL_4_A

#endif  // SRC_B_GRL_4_A_CYCLE_DETECTION_H_
