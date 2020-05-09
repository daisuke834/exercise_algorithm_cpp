/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-4. 木の直径(Diameter of a Tree)。
 */

#ifndef SRC_C15_5_GRL_5_A_MST_PRIM_H_
#define SRC_C15_5_GRL_5_A_MST_PRIM_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace GRL_5_A {

constexpr int32_t kMaxNumberOfNodes = 100000;
constexpr int32_t kInvalidIndex = -1;

void CallTreeDiameter(std::istream &input_stream);

struct Edge {
  int32_t neighbour{kInvalidIndex};
  int32_t weight{INT32_MAX};
};

struct Node {
  bool discovered{false};
  std::vector<Edge> edges;
};

using Pair = std::pair<int32_t, int32_t>;

class TreeDiameter {
 public:
  TreeDiameter() noexcept;
  ~TreeDiameter() noexcept;
  void SetNumberOfNodes(const int32_t number_of_nodes) noexcept;
  void AddEdge(const int32_t node_index_1, const int32_t node_index_2, const int32_t weight) noexcept;
  int32_t CalculateDiameter() noexcept;

 private:
  Pair FindFarthestNode(const int32_t node_index) noexcept;
  Pair Dfs(const Pair &distance_to_node) noexcept;
  void ResetDiscoveredFlags() noexcept;

 private:
  int32_t number_of_nodes_;
  Node nodes_[kMaxNumberOfNodes];
};

}  // namespace GRL_5_A

#endif  // SRC_C15_5_GRL_5_A_MST_PRIM_H_
