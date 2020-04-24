/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/C16_12_CGL_4_A_convex_hull.h"

using CGL_4_A::CallConvexHull;

int main(int argc, char *argv[]) {
  try {
    CallConvexHull(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
