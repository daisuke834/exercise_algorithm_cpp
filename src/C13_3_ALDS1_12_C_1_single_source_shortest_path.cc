/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-3. 重み付きグラフ(Weighted Graph)、単一始点最短経路(Single Source Shortest Path)。
 * ダイクストラのアルゴリズム (Dijkstra's algorithm)の、優先度キューによる改善版。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C13_3_ALDS1_12_C_1_single_source_shortest_path.h"

#include <iostream>
#include <string>

namespace ALDS1_12_C_1 {

void CallDijkstraAlgorithm(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  DijkstraAlgorithm* single_source_shortest_path = new DijkstraAlgorithm();
  try {
    int32_t number_of_vertices;
    input_stream >> number_of_vertices;
    single_source_shortest_path->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_vertices; ++i) {
      int32_t vertex_from, number_of_edges_from_this;
      input_stream >> vertex_from >> number_of_edges_from_this;
      for (int32_t i = 0; i < number_of_edges_from_this; ++i) {
        int32_t vertex_to, weight;
        input_stream >> vertex_to >> weight;
        single_source_shortest_path->AddWeight(vertex_from, vertex_to, weight);
      }
    }
    single_source_shortest_path->CalculateShortestPaths();
    single_source_shortest_path->Print();
  } catch (...) {
    std::cerr << "ERROR: CallDijkstraAlgorithm()" << std::endl;
    throw;
  }
  delete single_source_shortest_path;
}

// ****************************************************

DijkstraAlgorithm::DijkstraAlgorithm() noexcept : number_of_vertices_(0) {}

DijkstraAlgorithm::~DijkstraAlgorithm() noexcept {}

void DijkstraAlgorithm::CalculateShortestPaths() {
  try {
    QueueVertexAsRoot(kRootVertex);
    for (int32_t i = 0; i < kMaxLoop; ++i) {
      if (priority_queue_.empty()) {
        break;
      }
      const int32_t next_vertex_to_add = FindNextVertexToAdd();
      if (InvalidVertexIndex(next_vertex_to_add)) {
        // DO NOTHING
      } else {
        AddVertexToTree(next_vertex_to_add);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CalculateSumOfWeightsOfDijkstraAlgorithm()" << std::endl;
    throw;
  }
}

void DijkstraAlgorithm::Print() const noexcept {
  for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
    std::cout << vertex_index << " " << vertices_[vertex_index].distance_from_root << std::endl;
  }
}

void DijkstraAlgorithm::AddVertexToTree(const int32_t vertex_index_to_add) {
  if (InvalidVertexIndex(vertex_index_to_add)) {
    std::cerr << "ERROR: AddVertexToTree(): Invalid arg: vertex_index_to_add = " << vertex_index_to_add << std::endl;
    throw 1;
  }
  Vertex& vertex_to_add = vertices_[vertex_index_to_add];
  vertex_to_add.status = VertexStatus::kAdded;

  UpdateExternalVertices(vertex_index_to_add);
}

void DijkstraAlgorithm::UpdateExternalVertices(const int32_t vertex_index_added) {
  if (InvalidVertexIndex(vertex_index_added)) {
    std::cerr << "ERROR: UpdateExternalVertices(): Invalid arg: vertex_index_added = " << vertex_index_added
              << std::endl;
    throw 1;
  }
  try {
    for (const Neighbour& neighbour : neighbours_[vertex_index_added]) {
      CheckAndUpdateExternalVertex(vertex_index_added, neighbour.vertex_neighbour);
    }
  } catch (...) {
    std::cerr << "ERROR: UpdateExternalVertices()" << std::endl;
    throw;
  }
}

void DijkstraAlgorithm::CheckAndUpdateExternalVertex(const int32_t vertex_index_added,
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
    if (IsExternalVertex(vertex_index_to_update)) {
      if (CanBeUpdatedToSmallerDistance(vertex_index_added, vertex_index_to_update)) {
        UpdateCandidateByAddedVertex(vertex_index_added, vertex_index_to_update);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CheckAndUpdateExternalVertex()" << std::endl;
    throw;
  }
}

bool DijkstraAlgorithm::CanBeUpdatedToSmallerDistance(const int32_t vertex_index_added,
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
    try {
      const int32_t new_distance =
          vertices_[vertex_index_added].distance_from_root + GetWeight(vertex_index_added, vertex_index_to_update);
      can_be_updated_to_smaller = (new_distance < vertices_[vertex_index_to_update].distance_from_root);
    } catch (...) {
      std::cerr << "ERROR: CanBeUpdatedToSmallerDistance()" << std::endl;
      throw;
    }
  }
  return can_be_updated_to_smaller;
}

void DijkstraAlgorithm::UpdateCandidateByAddedVertex(const int32_t vertex_index_added,
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
    try {
      Vertex& vertex_to_update = vertices_[vertex_index_to_update];
      const int32_t new_distance =
          vertices_[vertex_index_added].distance_from_root + GetWeight(vertex_index_added, vertex_index_to_update);
      vertex_to_update.distance_from_root = new_distance;
      vertex_to_update.parent = vertex_index_added;
      vertex_to_update.status = VertexStatus::kCandidate;
      std::pair<int32_t, int32_t> pair_added = std::make_pair(-new_distance, vertex_index_to_update);
      priority_queue_.push(pair_added);
    } catch (...) {
      std::cerr << "ERROR: UpdateCandidateByAddedVertex()" << std::endl;
      throw;
    }
  }
}

bool DijkstraAlgorithm::IsExternalVertex(const int32_t vertex_index) const {
  if (InvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: IsExternalVertex(): Invalid arg: vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  return (vertices_[vertex_index].status != VertexStatus::kAdded);
}

bool DijkstraAlgorithm::IsTreeComponent(const int32_t vertex_index) const {
  if (InvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: IsTreeComponent(): Invalid arg: vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  return (vertices_[vertex_index].status == VertexStatus::kAdded);
}

int32_t DijkstraAlgorithm::FindNextVertexToAdd() {
  int32_t next_vertex_to_add = kInvalidVertex;
  try {
    std::pair<int32_t, int32_t> next = priority_queue_.top();
    priority_queue_.pop();
    const int32_t weight = -next.first;
    if (weight <= vertices_[next.second].distance_from_root) {
      next_vertex_to_add = next.second;
    }
  } catch (...) {
    std::cerr << "ERROR: FindNextVertexToAdd()" << std::endl;
    throw;
  }
  return next_vertex_to_add;
}

void DijkstraAlgorithm::QueueVertexAsRoot(const int32_t first_vertex_to_start) {
  if (InvalidVertexIndex(first_vertex_to_start)) {
    std::cerr << "ERROR: QueueVertexAsRoot(): Invalid arg: first_vertex_to_start = " << first_vertex_to_start
              << std::endl;
    throw 1;
  }
  const int32_t distance = 0;
  vertices_[first_vertex_to_start].distance_from_root = distance;
  try {
    std::pair<int32_t, int32_t> pair_added = std::make_pair(-distance, first_vertex_to_start);
    priority_queue_.push(pair_added);
  } catch (...) {
    std::cerr << "ERROR: QueueVertexAsRoot()" << std::endl;
    throw;
  }
}

void DijkstraAlgorithm::SetNumberOfVertices(const int32_t number_of_vertices) {
  number_of_vertices_ = number_of_vertices;
}

void DijkstraAlgorithm::AddWeight(const int32_t vertex_1, const int32_t vertex_2, const int32_t weight) {
  if (InvalidVertexIndex(vertex_1)) {
    std::cerr << "ERROR: AddWeight(): Invalid arg: vertex_1 = " << vertex_1 << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_2)) {
    std::cerr << "ERROR: AddWeight(): Invalid arg: vertex_2 = " << vertex_2 << std::endl;
    throw 1;
  } else {
    try {
      if (weight >= 0) {
        Neighbour neighbour;
        neighbour.vertex_neighbour = vertex_2;
        neighbour.weight = weight;
        neighbours_[vertex_1].push_back(neighbour);
      }
    } catch (...) {
      std::cerr << "ERROR: AddWeight()" << std::endl;
      throw;
    }
  }
}

int32_t DijkstraAlgorithm::GetWeight(const int32_t vertex_from, const int32_t vertex_to) const {
  int32_t weight = kInvalidWeight;
  if (InvalidVertexIndex(vertex_from)) {
    std::cerr << "ERROR: GetWeight(): Invalid arg: vertex_from = " << vertex_from << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_to)) {
    std::cerr << "ERROR: GetWeight(): Invalid arg: vertex_to = " << vertex_to << std::endl;
    throw 1;
  } else {
    for (const Neighbour& neighbour : neighbours_[vertex_from]) {
      if (neighbour.vertex_neighbour == vertex_to) {
        weight = neighbour.weight;
        break;
      }
    }
  }
  return weight;
}

bool DijkstraAlgorithm::InvalidVertexIndex(const int32_t vertex_index) const noexcept {
  return ((vertex_index < 0) || (vertex_index >= number_of_vertices_));
}

// **********************************************************************

}  // namespace ALDS1_12_C_1
