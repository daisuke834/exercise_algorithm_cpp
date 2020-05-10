/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/D_ABC_167_D_1_teleporter_cycle.h"

using ABC_167_D_1::CallTeleporter;

int main() {
  try {
    CallTeleporter(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
