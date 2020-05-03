/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/D_ABC_165_2_depth_first_search.h"

using ABC_165_2::CallDepthFirstSearch;

int main() {
  try {
    CallDepthFirstSearch(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
