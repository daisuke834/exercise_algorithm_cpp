/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/C13_2_ALDS1_12_A_3_Prim.h"

using ALDS1_12_A_3::CallPrimAlgorithm;

int main() {
  try {
    CallPrimAlgorithm(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
