/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-2. 重み付きグラフ(Weighted Graph)、最小全域木(Minimum Spanning Tree, MST)。
 * プリム法 (Prim's algorithm)による実装。計算量はO(|V|^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C13_2_ALDS1_12_A_3_Prim.h"
#include <iostream>
#include <string>

namespace ALDS1_12_A_3 {

void CallPrimAlgorithm(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  PrimAlgorithm *minimum_spanning_tree = new PrimAlgorithm();
  try {
    int32_t number_of_vertices;
    input_stream >> number_of_vertices;
    minimum_spanning_tree->SetNumberOfVertices(number_of_vertices);
    for (int32_t vertex_from = 0; vertex_from < number_of_vertices; ++vertex_from) {
      for (int32_t vertex_to = 0; vertex_to < number_of_vertices; ++vertex_to) {
        int32_t weight;
        input_stream >> weight;
        minimum_spanning_tree->AddWeight(vertex_from, vertex_to, weight);
      }
    }
    const int32_t sum_of_weights = minimum_spanning_tree->CalculateSumOfWeightsOfPrimAlgorithm();
    std::cout << sum_of_weights << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallPrimAlgorithm()" << std::endl;
    throw;
  }
  delete minimum_spanning_tree;
}

// ****************************************************

// **********************************************************************

}  // namespace ALDS1_12_A_3
