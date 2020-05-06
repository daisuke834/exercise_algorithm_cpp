/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/B_ALDS1_15_D_Huffman_coding.h"

using ALDS1_15_D::CallHuffmanCoding;

int main() {
  try {
    CallHuffmanCoding(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
