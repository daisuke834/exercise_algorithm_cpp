/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/C15_5_GRL_2_A_1_MST_Prim.h"

using GRL_2_A_1::CallPrimAlgorithm;

int main() {
  try {
    CallPrimAlgorithm(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
