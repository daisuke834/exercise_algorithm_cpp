/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/C15_2_GRL_4_B_3_topological_sort_dfs.h"

using GRL_4_B_3::CallTopologicalSort;

int main() {
  try {
    CallTopologicalSort(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
