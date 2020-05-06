/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/B_GRL_1_A_Dijkstra.h"

using GRL_1_A::CallDijkstraAlgorithm;

int main() {
  try {
    CallDijkstraAlgorithm(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
