/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/C15_5_GRL_2_A_2_MST_Kruskal.h"

using GRL_2_A_2::CallKruskalAlgorithm;

int main() {
  try {
    CallKruskalAlgorithm(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
