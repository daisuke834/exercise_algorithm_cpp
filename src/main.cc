/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/B_GRL_1_B_Bellman_Ford.h"

using GRL_1_B::CallBellmanFordAlgorithm;

int main() {
  try {
    CallBellmanFordAlgorithm(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
