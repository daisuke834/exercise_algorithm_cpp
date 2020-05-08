/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-2. 重み付きグラフ(Weighted Graph)、最小全域木(Minimum Spanning Tree, MST)。
 * プリム法 (Prim's algorithm)による実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C13_2_ALDS1_12_A_3_MINIMUM_SPANNING_TREE_H_
#define SRC_C13_2_ALDS1_12_A_3_MINIMUM_SPANNING_TREE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_12_A_3 {

void CallPrimAlgorithm(std::istream &input_stream);

}  // namespace ALDS1_12_A_3

#endif  // SRC_C13_2_ALDS1_12_A_3_MINIMUM_SPANNING_TREE_H_
