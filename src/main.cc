/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/B_GRL_4_A_cycle_detection.h"

using GRL_4_A::CallCycleDetection;

int main() {
  try {
    CallCycleDetection(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
