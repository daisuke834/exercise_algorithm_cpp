/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/C15_1_GRL_1_C_2_Warshall_Floyd.h"

using GRL_1_C_2::CallWarshallFloyd;

int main() {
  try {
    CallWarshallFloyd(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
