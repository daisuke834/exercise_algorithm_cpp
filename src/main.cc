/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <iostream>
#include "src/C17_3_DPL_1_D_3_longest_increasing_subsequence.h"

using DPL_1_D_3::CallLongestIncreasingSubsequence;

int main() {
  try {
    CallLongestIncreasingSubsequence(std::cin);
  } catch (...) {
    std::cerr << "ERROR: main()" << std::endl;
  }
  return 0;
}
