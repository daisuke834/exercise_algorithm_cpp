/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include "src/hoge.h"

using hoge::Hoge;

int main() {
  try {
    // Hoge(std::cin);
    Hoge();
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
