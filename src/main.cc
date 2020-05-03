/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/D_ABC_165_1_depth_first_search.h"

using NTL_1_B::CallCalculatePower;

int main() {
  try {
    CallDepthFirstSearch(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
