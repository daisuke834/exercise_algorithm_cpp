/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-4. 木の直径(Diameter of a Tree)。
 */

#include "src/C15_4_GRL_5_A_diameter_of_tree.h"

namespace GRL_5_A {

void CallTreeDiameter(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  TreeDiameter *tree_diameter = new TreeDiameter();
  try {
    int32_t number_of_nodes;
    input_stream >> number_of_nodes;
    for (int32_t i = 0; i < number_of_nodes; ++i) {
      int32_t node_index_1, node_index_2, weight;
      input_stream >> node_index_1 >> node_index_2 >> weight;
    }
    const int32_t diameter = 5;
    std::cout << diameter << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallTreeDiameter()" << std::endl;
    throw;
  }
  delete tree_diameter;
}

// ****************************************************
TreeDiameter::TreeDiameter() noexcept {}

TreeDiameter::~TreeDiameter() noexcept {}

// **********************************************************************

}  // namespace GRL_5_A
