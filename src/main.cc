/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/C18_3_NTL_1_B_Power.h"

using NTL_1_B::CallCalculatePower;

int main() {
  try {
    CallCalculatePower(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
