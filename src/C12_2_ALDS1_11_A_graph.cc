/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-2. グラフ(Graph)、グラフの表現。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C12_2_ALDS1_11_A_graph.h"

#include <iostream>
#include <string>

namespace ALDS1_11_A {

void CallGraph(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  Graph* graph = new Graph();
  try {
    int32_t number_of_vertices;
    input_stream >> number_of_vertices;
    for (int32_t i = 0; i < number_of_vertices; ++i) {
      int32_t vertex_number, out_degree;
      input_stream >> vertex_number >> out_degree;
      graph->AddVertex(vertex_number);
      for (int32_t j = 0; j < out_degree; ++j) {
        int32_t tail_vertex;
        input_stream >> tail_vertex;
        graph->MapDirection(vertex_number, tail_vertex);
      }
    }
    graph->Print();
  } catch (...) {
    std::cerr << "ERROR: CallGraph()" << std::endl;
    throw;
  }
  delete graph;
}

// ****************************************************

Graph::Graph() noexcept : size_(0) { Reset(); }
Graph::~Graph() noexcept {}

void Graph::AddVertex(const int32_t vertex_number) {
  if (IsInvalidVertexNumber(vertex_number)) {
    std::cerr << "ERROR: AddVertex(): Invalid arg vertex_number = " << vertex_number << std::endl;
    throw 1;
  }
  size_ = (vertex_number > size_) ? vertex_number : size_;
}

void Graph::MapDirection(const int32_t vertex_number_from, const int32_t vertex_number_to) {
  if (IsInvalidVertexNumber(vertex_number_from)) {
    std::cerr << "ERROR: AddVertex(): Invalid arg vertex_number_from = " << vertex_number_from << std::endl;
    throw 1;
  } else if (IsInvalidVertexNumber(vertex_number_to)) {
    std::cerr << "ERROR: AddVertex(): Invalid arg vertex_number_to = " << vertex_number_to << std::endl;
    throw 1;
  } else {
    try {
      int32_t index_from = ConvertFromVertexNumberToIndex(vertex_number_from);
      int32_t index_to = ConvertFromVertexNumberToIndex(vertex_number_to);
      adjacency_matrix_[index_from][index_to] = 1;
    } catch (...) {
      std::cerr << "ERROR: MapDirection()" << std::endl;
      throw;
    }
  }
}

void Graph::Print() const noexcept {
  for (int32_t i = 0; i < size_; ++i) {
    for (int32_t j = 0; j < size_; ++j) {
      if (j != 0) {
        std::cout << " ";
      }
      std::cout << adjacency_matrix_[i][j];
      if (j == size_ - 1) {
        std::cout << std::endl;
      }
    }
  }
}

void Graph::Reset() noexcept {
  for (auto& row : adjacency_matrix_) {
    for (auto& element : row) {
      element = 0;
    }
  }
}

bool Graph::IsInvalidVertexNumber(const int32_t vertex_number) noexcept {
  return ((vertex_number < 1) || (vertex_number > kMaxVertexNumber));
}

bool Graph::IsInvalidVertexIndex(const int32_t index) noexcept { return ((index < 0) || (index >= kMaxVertexNumber)); }

int32_t Graph::ConvertFromVertexNumberToIndex(const int32_t vertex_number) {
  const int32_t index = vertex_number - 1;
  if (IsInvalidVertexIndex(index)) {
    std::cerr << "ERROR: ConvertFromVertexNumberToIndex(): Invalid vertex: index = " << index
              << ", vertex_number=" << vertex_number << std::endl;
    throw 1;
  }
  return index;
}

int32_t Graph::ConvertFromIndexToVertexNumber(const int32_t index) {
  if (IsInvalidVertexIndex(index)) {
    std::cerr << "ERROR: ConvertFromIndexToVertexNumber(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  return index + 1;
}

}  // namespace ALDS1_11_A
