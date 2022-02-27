/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-2. 重み付きグラフ(Weighted Graph)、最小全域木(Minimum Spanning Tree, MST)。
 * プリム法 (Prim's algorithm)による実装。計算量はO(|V|^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "2_ALDS1_12_A_2_MST_Prim.h"

#include <iostream>
#include <string>

namespace ALDS1_12_A_2 {

void CallMinimumSpanningTree(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  MinimumSpanningTree* minimum_spanning_tree = new MinimumSpanningTree();
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
    const int32_t sum_of_weights = minimum_spanning_tree->CalculateSumOfWeightsOfMinimumSpanningTree();
    std::cout << sum_of_weights << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallMinimumSpanningTree()" << std::endl;
    throw;
  }
  delete minimum_spanning_tree;
}

// ****************************************************

MinimumSpanningTree::MinimumSpanningTree() noexcept : number_of_vertices_(0) {
  for (auto& row : adjacency_matrix_) {
    for (int32_t& element : row) {
      element = kInvalidWeight;
    }
  }
}

MinimumSpanningTree::~MinimumSpanningTree() noexcept {}

int32_t MinimumSpanningTree::CalculateSumOfWeightsOfMinimumSpanningTree() {
  try {
    QueueVertexAsRoot(kRootVertex);
    for (int32_t i = 0; i < kMaxLoop; ++i) {
      const int32_t next_vertex_to_add = FindNextVertexToAdd();
      if (InvalidVertexIndex(next_vertex_to_add)) {
        break;
      } else {
        AddVertexToTree(next_vertex_to_add);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CalculateSumOfWeightsOfMinimumSpanningTree()" << std::endl;
    throw;
  }
  const int32_t sum_of_weights = GetSumOfWeights();
  return sum_of_weights;
}

void MinimumSpanningTree::AddVertexToTree(const int32_t vertex_index_to_add) {
  if (InvalidVertexIndex(vertex_index_to_add)) {
    std::cerr << "ERROR: AddVertexToTree(): Invalid arg: vertex_index_to_add = " << vertex_index_to_add << std::endl;
    throw 1;
  }
  Vertex& vertex_to_add = vertices_[vertex_index_to_add];
  vertex_to_add.status = VertexStatus::kAdded;

  UpdateExternalVertices(vertex_index_to_add);
}

void MinimumSpanningTree::UpdateExternalVertices(const int32_t vertex_index_added) {
  if (InvalidVertexIndex(vertex_index_added)) {
    std::cerr << "ERROR: UpdateExternalVertices(): Invalid arg: vertex_index_added = " << vertex_index_added
              << std::endl;
    throw 1;
  }
  try {
    for (int32_t vertex_index_to_update = 0; vertex_index_to_update < number_of_vertices_; ++vertex_index_to_update) {
      CheckAndUpdateExternalVertex(vertex_index_added, vertex_index_to_update);
    }
  } catch (...) {
    std::cerr << "ERROR: UpdateExternalVertices()" << std::endl;
    throw;
  }
}

void MinimumSpanningTree::CheckAndUpdateExternalVertex(const int32_t vertex_index_added,
                                                       const int32_t vertex_index_to_update) {
  if (InvalidVertexIndex(vertex_index_added)) {
    std::cerr << "ERROR: CheckAndUpdateExternalVertex(): Invalid arg: vertex_index_added = " << vertex_index_added
              << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_index_to_update)) {
    std::cerr << "ERROR: CheckAndUpdateExternalVertex(): Invalid arg: vertex_index_to_update = "
              << vertex_index_to_update << std::endl;
    throw 1;
  } else {
    // DO NOTHING
  }
  try {
    if (IsExternalVertex(vertex_index_to_update) && CanBeMapped(vertex_index_added, vertex_index_to_update)) {
      if (CanBeUpdatedToSmallerDistance(vertex_index_added, vertex_index_to_update)) {
        UpdateCandidateByAddedVertex(vertex_index_added, vertex_index_to_update);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CheckAndUpdateExternalVertex()" << std::endl;
    throw;
  }
}

bool MinimumSpanningTree::CanBeUpdatedToSmallerDistance(const int32_t vertex_index_added,
                                                        const int32_t vertex_index_to_update) const {
  bool can_be_updated_to_smaller;
  if (InvalidVertexIndex(vertex_index_added)) {
    std::cerr << "ERROR: CanBeUpdatedToSmallerDistance(): Invalid arg: vertex_index_added = " << vertex_index_added
              << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_index_to_update)) {
    std::cerr << "ERROR: CanBeUpdatedToSmallerDistance(): Invalid arg: vertex_index_to_update = "
              << vertex_index_to_update << std::endl;
    throw 1;
  } else {
    can_be_updated_to_smaller = (adjacency_matrix_[vertex_index_added][vertex_index_to_update] <
                                 vertices_[vertex_index_to_update].minimum_distance_to_this);
  }
  return can_be_updated_to_smaller;
}

void MinimumSpanningTree::UpdateCandidateByAddedVertex(const int32_t vertex_index_added,
                                                       const int32_t vertex_index_to_update) {
  if (InvalidVertexIndex(vertex_index_added)) {
    std::cerr << "ERROR: UpdateCandidateByAddedVertex(): Invalid arg: vertex_index_added = " << vertex_index_added
              << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_index_to_update)) {
    std::cerr << "ERROR: UpdateCandidateByAddedVertex(): Invalid arg: vertex_index_to_update = "
              << vertex_index_to_update << std::endl;
    throw 1;
  } else {
    Vertex& vertex_to_update = vertices_[vertex_index_to_update];
    vertex_to_update.minimum_distance_to_this = adjacency_matrix_[vertex_index_added][vertex_index_to_update];
    vertex_to_update.parent = vertex_index_added;
    vertex_to_update.status = VertexStatus::kCandidate;
  }
}

bool MinimumSpanningTree::IsExternalVertex(const int32_t vertex_index) const {
  if (InvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: IsExternalVertex(): Invalid arg: vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  return (vertices_[vertex_index].status != VertexStatus::kAdded);
}

bool MinimumSpanningTree::IsTreeComponent(const int32_t vertex_index) const {
  if (InvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: IsTreeComponent(): Invalid arg: vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  return (vertices_[vertex_index].status == VertexStatus::kAdded);
}

bool MinimumSpanningTree::CanBeMapped(const int32_t vertex_1, const int32_t vertex_2) const {
  if (InvalidVertexIndex(vertex_1)) {
    std::cerr << "ERROR: CanBeMapped(): Invalid arg: vertex_1 = " << vertex_1 << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_2)) {
    std::cerr << "ERROR: CanBeMapped(): Invalid arg: vertex_2 = " << vertex_2 << std::endl;
    throw 1;
  } else {
    return (adjacency_matrix_[vertex_1][vertex_2] != INT32_MAX);
  }
}

int32_t MinimumSpanningTree::FindNextVertexToAdd() const noexcept {
  int32_t minimum_distance = INT32_MAX;
  int32_t next_vertex_to_add = kInvalidVertex;
  for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
    if (IsExternalVertex(vertex_index)) {
      const Vertex& current_vertex = vertices_[vertex_index];
      if (current_vertex.minimum_distance_to_this < minimum_distance) {
        next_vertex_to_add = vertex_index;
        minimum_distance = current_vertex.minimum_distance_to_this;
      }
    }
  }
  return next_vertex_to_add;
}

void MinimumSpanningTree::QueueVertexAsRoot(const int32_t first_vertex_to_start) {
  if (InvalidVertexIndex(first_vertex_to_start)) {
    std::cerr << "ERROR: QueueVertexAsRoot(): Invalid arg: first_vertex_to_start = " << first_vertex_to_start
              << std::endl;
    throw 1;
  }
  vertices_[first_vertex_to_start].minimum_distance_to_this = 0;
}

int32_t MinimumSpanningTree::GetSumOfWeights() const noexcept {
  int32_t sum_of_weights = 0;
  for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
    const Vertex& current_vertex = vertices_[vertex_index];
    if (IsTreeComponent(vertex_index)) {
      sum_of_weights += current_vertex.minimum_distance_to_this;
    }
  }
  return sum_of_weights;
}

void MinimumSpanningTree::SetNumberOfVertices(const int32_t number_of_vertices) {
  number_of_vertices_ = number_of_vertices;
}

void MinimumSpanningTree::AddWeight(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight) {
  if (InvalidVertexIndex(vertex_1)) {
    std::cerr << "ERROR: AddWeight(): Invalid arg: vertex_1 = " << vertex_1 << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_2)) {
    std::cerr << "ERROR: AddWeight(): Invalid arg: vertex_2 = " << vertex_2 << std::endl;
    throw 1;
  } else {
    try {
      adjacency_matrix_[vertex_1][vertex_2] = ((weight < 0) ? kInvalidWeight : weight);
    } catch (...) {
      std::cerr << "ERROR: AddWeight()" << std::endl;
      throw;
    }
  }
}

bool MinimumSpanningTree::InvalidVertexIndex(const int32_t vertex_index) const noexcept {
  return ((vertex_index < 0) || (vertex_index >= number_of_vertices_));
}

// **********************************************************************

}  // namespace ALDS1_12_A_2
