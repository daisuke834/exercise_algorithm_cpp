/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-4. 木の直径(Diameter of a Tree)。
 */

#include "4_GRL_5_A_diameter_of_tree.h"

namespace GRL_5_A {

void CallTreeDiameter(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  TreeDiameter* tree_diameter = new TreeDiameter();
  try {
    int32_t number_of_nodes;
    input_stream >> number_of_nodes;
    tree_diameter->SetNumberOfNodes(number_of_nodes);
    for (int32_t i = 0; i < number_of_nodes; ++i) {
      int32_t node_index_1, node_index_2, weight;
      input_stream >> node_index_1 >> node_index_2 >> weight;
      tree_diameter->AddEdge(node_index_1, node_index_2, weight);
    }
    const int32_t diameter = tree_diameter->CalculateDiameter();
    std::cout << diameter << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallTreeDiameter()" << std::endl;
    throw;
  }
  delete tree_diameter;
}

// ****************************************************
TreeDiameter::TreeDiameter() noexcept : number_of_nodes_(0) {}

TreeDiameter::~TreeDiameter() noexcept {}

void TreeDiameter::SetNumberOfNodes(const int32_t number_of_nodes) noexcept { number_of_nodes_ = number_of_nodes; }

void TreeDiameter::AddEdge(const int32_t node_index_1, const int32_t node_index_2, const int32_t weight) noexcept {
  Edge edge1;
  edge1.weight = weight;
  edge1.neighbour = node_index_2;
  nodes_[node_index_1].edges.push_back(edge1);

  Edge edge2;
  edge2.weight = weight;
  edge2.neighbour = node_index_1;
  nodes_[node_index_2].edges.push_back(edge2);
}

int32_t TreeDiameter::CalculateDiameter() noexcept {
  constexpr int32_t kSomeNode = 0;
  const Pair firthest1 = FindFarthestNode(kSomeNode);
  const Pair firthest2 = FindFarthestNode(firthest1.second);
  const int32_t diameter = firthest2.first;
  return diameter;
}

Pair TreeDiameter::FindFarthestNode(const int32_t node_index) noexcept {
  ResetDiscoveredFlags();
  constexpr int32_t kInitDistance = 0;
  nodes_[node_index].discovered = true;
  const Pair farthest_distance_to_node = Dfs(Pair(kInitDistance, node_index));
  return farthest_distance_to_node;
}

Pair TreeDiameter::Dfs(const Pair& distance_to_node) noexcept {
  const int32_t c_distance = distance_to_node.first;
  const int32_t c_node_index = distance_to_node.second;
  Pair farthest_distance = Pair(c_distance, c_node_index);

  for (const Edge& c_edge : nodes_[c_node_index].edges) {
    const int32_t neighbour = c_edge.neighbour;
    if (!nodes_[neighbour].discovered) {
      nodes_[neighbour].discovered = true;
      const int32_t distance_to_neighbour = c_distance + c_edge.weight;
      const Pair temp_farthest_distance = Dfs(Pair(distance_to_neighbour, neighbour));
      if (temp_farthest_distance.first > farthest_distance.first) {
        farthest_distance = temp_farthest_distance;
      }
    }
  }
  return farthest_distance;
}

void TreeDiameter::ResetDiscoveredFlags() noexcept {
  for (int32_t i = 0; i < number_of_nodes_; ++i) {
    nodes_[i].discovered = false;
  }
}

// **********************************************************************

}  // namespace GRL_5_A
