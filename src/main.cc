/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/C15_4_GRL_5_A_diameter_of_tree.h"

using GRL_5_A::CallTreeDiameter;

int main() {
  try {
    CallTreeDiameter(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
