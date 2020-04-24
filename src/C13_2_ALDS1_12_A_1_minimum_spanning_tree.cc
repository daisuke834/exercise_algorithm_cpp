/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-2. 重み付きグラフ(Weighted Graph)、最小全域木(Minimum Spanning Tree, MST)。
 * クラスカル法 (Kruskal's algorithm)による実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C13_2_ALDS1_12_A_1_minimum_spanning_tree.h"
#include <iostream>
#include <string>

namespace ALDS1_12_A_1 {

void CallMinimumSpanningTree(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  MinimumSpanningTree *minimum_spanning_tree = new MinimumSpanningTree();
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

MinimumSpanningTree::MinimumSpanningTree() noexcept : number_of_vertices_(0), number_of_edges_(0) {
  for (auto &row : adjacency_matrix_) {
    for (int32_t &element : row) {
      element = kInvalidWeight;
    }
  }
}

MinimumSpanningTree::~MinimumSpanningTree() noexcept {}

int32_t MinimumSpanningTree::CalculateSumOfWeightsOfMinimumSpanningTree() {
  try {
    ComputeQuickSort(0, number_of_edges_ - 1);

    connected_components_.SetNumberOfVertices(number_of_vertices_);
    for (int32_t edge_index = 0; edge_index < number_of_edges_; ++edge_index) {
      const int32_t vertex_start = edges_[edge_index].vertex_1;
      const int32_t vertex_end = edges_[edge_index].vertex_2;
      const bool connection_exists = connected_components_.ConnectionExistsBetweenStartAndEnd(vertex_start, vertex_end);
      if (connection_exists) {
        edges_[edge_index].status = EdgeStatus::kSkipped;
      } else {
        edges_[edge_index].status = EdgeStatus::kSelected;
        connected_components_.ResetAll();
        for (int32_t cedge = 0; cedge <= edge_index; ++cedge) {
          if (edges_[cedge].status == EdgeStatus::kSelected) {
            connected_components_.AddMapping(edges_[cedge].vertex_1, edges_[cedge].vertex_2);
          }
        }
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CalculateSumOfWeightsOfMinimumSpanningTree()" << std::endl;
    throw;
  }
  const int32_t sum_of_weights = GetSumOfWeights();
  return sum_of_weights;
}

int32_t MinimumSpanningTree::GetSumOfWeights() const noexcept {
  int32_t sum_of_weights = 0;
  for (int32_t edge_index = 0; edge_index < number_of_edges_; ++edge_index) {
    if (edges_[edge_index].status == EdgeStatus::kSelected) {
      sum_of_weights += edges_[edge_index].weight;
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
      if (CanAppendWeightToEdgeArray(vertex_1, vertex_2, weight)) {
        AppendWeightToEdgeArray(vertex_1, vertex_2, weight);
      }
      StoreWeightInAdjacencyMatrix(vertex_1, vertex_2, weight);
    } catch (...) {
      std::cerr << "ERROR: AddWeight()" << std::endl;
      throw;
    }
  }
}

bool MinimumSpanningTree::CanAppendWeightToEdgeArray(const int32_t vertex_1, const int32_t vertex_2,
                                                     const int32_t weight) const noexcept {
  const bool valid_weight = ValidWeight(weight);
  const bool not_stored_yet = (!WeightIsAlreadyStored(vertex_1, vertex_2));
  const bool not_diagonal = (vertex_1 != vertex_2);
  const bool can_append = valid_weight && not_stored_yet && not_diagonal;
  return can_append;
}

void MinimumSpanningTree::StoreWeightInAdjacencyMatrix(const int32_t vertex_1, const int32_t vertex_2,
                                                       const int32_t weight) noexcept {
  adjacency_matrix_[vertex_1][vertex_2] = weight;
  adjacency_matrix_[vertex_2][vertex_1] = weight;
}

void MinimumSpanningTree::AppendWeightToEdgeArray(const int32_t vertex_1, const int32_t vertex_2,
                                                  const int32_t weight) {
  if (InvalidVertexIndex(vertex_1)) {
    std::cerr << "ERROR: AppendWeightToEdgeArray(): Invalid arg: vertex_1 = " << vertex_1 << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_2)) {
    std::cerr << "ERROR: AppendWeightToEdgeArray(): Invalid arg: vertex_2 = " << vertex_2 << std::endl;
    throw 1;
  } else if (WeightIsAlreadyStored(vertex_1, vertex_2)) {
    std::cerr << "ERROR: AppendWeightToEdgeArray(): Weight is already stored. vertex_1=" << vertex_1
              << ", vertex_2=" << vertex_2 << std::endl;
    throw 1;
  } else if (vertex_1 == vertex_2) {
    std::cerr << "ERROR: AppendWeightToEdgeArray(): Weight shall not be set to: vertex_1=" << vertex_1
              << ", vertex_2=" << vertex_2 << std::endl;
    throw 1;
  }
  const int32_t edge_index_to_store = number_of_edges_;
  ++number_of_edges_;
  edges_[edge_index_to_store].weight = weight;
  edges_[edge_index_to_store].vertex_1 = vertex_1;
  edges_[edge_index_to_store].vertex_2 = vertex_2;
}

bool MinimumSpanningTree::WeightIsAlreadyStored(const int32_t vertex_1, const int32_t vertex_2) const noexcept {
  const bool stored_1 = ValidWeight(adjacency_matrix_[vertex_1][vertex_2]);
  const bool stored_2 = ValidWeight(adjacency_matrix_[vertex_2][vertex_1]);
  const bool stored = (stored_1 && stored_2);
  return stored;
}

bool MinimumSpanningTree::ValidWeight(const int32_t weight) noexcept {
  return ((weight >= 0) && (weight <= kMaxWeight));
}

bool MinimumSpanningTree::InvalidVertexIndex(const int32_t vertex_index) const noexcept {
  return ((vertex_index < 0) || (vertex_index >= number_of_vertices_));
}

bool MinimumSpanningTree::InvalidEdgeIndex(const int32_t edge_index) const noexcept {
  return ((edge_index < 0) || (edge_index >= number_of_edges_));
}

void MinimumSpanningTree::ComputeQuickSort(const int32_t start, const int32_t end) {
  try {
    if (start < end) {
      const int32_t index_pivot = ComputePartition(start, end);
      ComputeQuickSort(start, index_pivot - 1);
      ComputeQuickSort(index_pivot + 1, end);
    }
  } catch (...) {
    std::cerr << "ERROR: ComputeQuickSort()" << std::endl;
    throw;
  }
}

int32_t MinimumSpanningTree::ComputePartition(const int32_t start, const int32_t end) {
  int32_t index_pivot = -1;
  if (InvalidEdgeIndex(start)) {
    std::cerr << "ERROR: ComputePartition(): Out of range: start = " << start << std::endl;
    throw 1;
  } else if (InvalidEdgeIndex(end)) {
    std::cerr << "ERROR: ComputePartition(): Out of range: end = " << end << std::endl;
    throw 1;
  } else {
    try {
      const int32_t value_pivot = edges_[end].weight;
      int32_t index_store = start;
      for (int32_t index_compare = start; index_compare < end; ++index_compare) {
        if (edges_[index_compare].weight <= value_pivot) {
          Swap(index_compare, index_store);
          ++index_store;
        }
      }
      Swap(end, index_store);
      index_pivot = index_store;
    } catch (...) {
      std::cerr << "ERROR: ComputePartition()" << std::endl;
      throw;
    }
  }
  return index_pivot;
}

void MinimumSpanningTree::Swap(const int32_t index_1, const int32_t index_2) {
  if ((InvalidEdgeIndex(index_1)) || (InvalidEdgeIndex(index_2))) {
    std::cerr << "ERROR: Swap(): Out of range: index_1=" << index_1 << ", index_2=" << index_2 << std::endl;
    throw 1;
  } else {
    const Edge temp = edges_[index_2];
    edges_[index_2] = edges_[index_1];
    edges_[index_1] = temp;
  }
}

// **********************************************************************

Queue::Queue() noexcept {
  Clear();
}

Queue::~Queue() noexcept {}

void Queue::Clear() noexcept {
  depth_ = 0;
  head_ = 0;
}

bool Queue::IsEmpty() const noexcept {
  return (depth_ <= 0);
}

bool Queue::IsFull() const noexcept {
  return (depth_ >= kMaxQueueSize);
}

void Queue::Enqueue(const int32_t index) {
  if (IsFull()) {
    std::cerr << "ERROR: Enqueue(): queue is full. index = " << index << std::endl;
    throw 1;
  }
  const int32_t tail_position = (head_ + depth_) % kMaxQueueSize;
  indices_[tail_position] = index;
  ++depth_;
}

int32_t Queue::Dequeue() {
  if (IsEmpty()) {
    std::cerr << "ERROR: Dequeue(): queue is empty." << std::endl;
    throw 1;
  }
  int32_t value = indices_[head_];
  head_ = GetNextPosition(head_);
  --depth_;
  return value;
}

int32_t Queue::GetNextPosition(const int32_t current_position) noexcept {
  return ((current_position + 1) % kMaxQueueSize);
}
// **********************************************************************

ConnectedComponents::ConnectedComponents() noexcept : number_of_vertices_(0), number_of_edges_(0) {}

ConnectedComponents::~ConnectedComponents() noexcept {}

bool ConnectedComponents::ConnectionExistsBetweenStartAndEnd(const int32_t vertex_start, const int32_t vertex_end) {
  bool connected = false;
  try {
    if (ClusterIdIsNotAllocated(vertex_start) && ClusterIdIsNotAllocated(vertex_end)) {
      Reset();
      PushFutureVertexToExplore(vertex_start);
      for (int32_t i = 0; i <= kMaxLoop; ++i) {
        const int32_t vertex_index = PickNextVertex();
        if (DoesNotExist(vertex_index)) {
          break;
        }
        int32_t cluster_id = vertex_start;
        ExploreOneVertex(vertex_index, cluster_id);
        if (AlreadyExplored(vertex_end) || AlreadyQueued(vertex_end)) {
          connected = true;
          // break;
        }
      }
    } else {
      // One or both of start vertex and end vertex are allocated clusters
      if (ClusterIdIsNotAllocated(vertex_start)) {
        // Only start vertex
        connected = false;
      } else if (ClusterIdIsNotAllocated(vertex_end)) {
        // Only end vertex
        connected = false;
      } else {
        // Both of start vertex and end vertex
        const int32_t cluster_start = GetClusterId(vertex_start);
        const int32_t cluster_end = GetClusterId(vertex_end);
        connected = (cluster_start == cluster_end);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: ExploreAllVertices()" << std::endl;
    throw;
  }
  return connected;
}

void ConnectedComponents::ExploreOneVertex(const int32_t vertex_index, const int32_t cluster_id) {
  if (InvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: ExploreOneVertex(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  } else if (AlreadyExplored(vertex_index)) {
    std::cerr << "ERROR: ExploreOneVertex(): Already reached vertex_index = " << vertex_index << std::endl;
    throw 1;
  } else {
    // DO NOTHING
  }
  try {
    MarkAsExplored(vertex_index);
    SetClusterId(vertex_index, cluster_id);
    const int32_t number_of_neighbours = static_cast<int32_t>(neighbours_[vertex_index].size());
    for (int32_t relative_index = 0; relative_index < number_of_neighbours; ++relative_index) {
      const int32_t index_neighbour = GetNeighbour(vertex_index, relative_index);
      if (NotExplored(index_neighbour) && NotQueued(index_neighbour)) {
        PushFutureVertexToExplore(index_neighbour);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: ExploreOneVertex()" << std::endl;
    throw;
  }
}

void ConnectedComponents::SetNumberOfVertices(const int32_t number_of_vertices) {
  if (number_of_vertices_ <= 0) {
    number_of_vertices_ = number_of_vertices;
    Reset();
    ResetClusterMappings();
  } else {
    std::cerr << "ERROR: SetNumberOfVertices(): number_of_vertices_ is already set. number_of_vertices_ = "
              << number_of_vertices_ << std::endl;
    throw 1;
  }
}

void ConnectedComponents::AddMapping(const int32_t vertex_1, const int32_t vertex_2) {
  if (InvalidVertexIndex(vertex_1)) {
    std::cerr << "ERROR: AddMapping(): Invalid arg vertex_1 = " << vertex_1 << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_2)) {
    std::cerr << "ERROR: AddMapping(): Invalid arg vertex_2 = " << vertex_2 << std::endl;
    throw 1;
  } else if (number_of_edges_ + 2 > kMaxSizeOfEdgeMappings) {
    std::cerr << "ERROR: AddMapping(): Number of edges exceeded a limit = " << kMaxNumberOfEdges << std::endl;
    throw 1;
  } else {
    try {
      const int32_t edge_index_1 = number_of_edges_;
      const int32_t edge_index_2 = edge_index_1 + 1;
      number_of_edges_ += 2;
      MapEdge(edge_index_1, vertex_1, vertex_2);
      MapEdge(edge_index_2, vertex_2, vertex_1);
    } catch (...) {
      std::cerr << "ERROR: AddMapping()" << std::endl;
      throw;
    }
  }
}

void ConnectedComponents::MapEdge(const int32_t edge_index, const int32_t vertex_from, const int32_t vertex_to) {
  if (InvalidEdgeIndex(edge_index)) {
    std::cerr << "ERROR: MapEdge(): Invalid arg edge_index = " << edge_index << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_from)) {
    std::cerr << "ERROR: MapEdge(): Invalid arg vertex_from = " << vertex_from << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(vertex_to)) {
    std::cerr << "ERROR: MapEdge(): Invalid arg vertex_to = " << vertex_to << std::endl;
    throw 1;
  } else {
    neighbours_[vertex_from].push_back(vertex_to);
  }
}

int32_t ConnectedComponents::GetNeighbour(const int32_t vertex_index, const int32_t relative_index) const {
  int32_t neighbour_index;
  if (InvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: GetNeighbour(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  } else if (relative_index < 0) {
    std::cerr << "ERROR: GetNeighbour(): Invalid arg relative_index = " << relative_index << std::endl;
    throw 1;
  } else {
    try {
      const int32_t number_of_neighbours = static_cast<int32_t>(neighbours_[vertex_index].size());
      if (relative_index >= number_of_neighbours) {
        std::cerr << "ERROR: GetNeighbour(): Invalid arg relative_index = " << relative_index << std::endl;
        throw 1;
      }
      neighbour_index = neighbours_[vertex_index][relative_index];
    } catch (...) {
      std::cerr << "ERROR: GetNeighbour()" << std::endl;
      throw;
    }
  }
  return neighbour_index;
}

void ConnectedComponents::PushFutureVertexToExplore(const int32_t vertex_index) noexcept {
  try {
    if (NotExplored(vertex_index) && NotQueued(vertex_index)) {
      todo_.Enqueue(vertex_index);
      MarkAsQueued(vertex_index);
    }
  } catch (...) {
    std::cerr << "ERROR: PushFutureVertex()" << std::endl;
    throw;
  }
}

int32_t ConnectedComponents::PickNextVertex() {
  int32_t next_vertex_index = kInvalidVertex;
  try {
    for (int32_t i = 0; i < kMaxLoop; ++i) {
      if (todo_.IsEmpty()) {
        next_vertex_index = kInvalidVertex;
        break;
      }
      next_vertex_index = todo_.Dequeue();
      if (DoesExist(next_vertex_index)) {
        if (NotExplored(next_vertex_index)) {
          // Pick this one to explore
          break;
        } else {
          // DO NOTHING. Next pick-up
        }
      } else {
        std::cerr << "ERROR: PickNextVertex(): Non-existing index was dequeued. index = " << next_vertex_index
                  << std::endl;
        throw 1;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: PickNextVertex()" << std::endl;
    throw;
  }
  return next_vertex_index;
}

void ConnectedComponents::MarkAsExplored(const int32_t index) {
  if (InvalidVertexIndex(index)) {
    std::cerr << "ERROR: MarkAsExplored(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  explored_[index] = true;
}

bool ConnectedComponents::NotExplored(const int32_t index) const {
  if (InvalidVertexIndex(index)) {
    std::cerr << "ERROR: NotExplored(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  return !explored_[index];
}

bool ConnectedComponents::AlreadyExplored(const int32_t index) const {
  if (InvalidVertexIndex(index)) {
    std::cerr << "ERROR: AlreadyExplored(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  return explored_[index];
}

void ConnectedComponents::MarkAsQueued(const int32_t index) {
  if (InvalidVertexIndex(index)) {
    std::cerr << "ERROR: MarkAsQueued(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  queued_[index] = true;
}

bool ConnectedComponents::NotQueued(const int32_t index) const {
  if (InvalidVertexIndex(index)) {
    std::cerr << "ERROR: NotQueued(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  return !queued_[index];
}

bool ConnectedComponents::AlreadyQueued(const int32_t index) const {
  if (InvalidVertexIndex(index)) {
    std::cerr << "ERROR: NotQueued(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  return queued_[index];
}

bool ConnectedComponents::DoesNotExist(const int32_t vertex_index) const {
  bool does_not_exist;
  if (vertex_index == kInvalidVertex) {
    does_not_exist = true;
  } else if (InvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: DoesNotExist(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  } else {
    does_not_exist = false;
  }
  return does_not_exist;
}

bool ConnectedComponents::DoesExist(const int32_t vertex_index) const {
  bool does_exist;
  try {
    does_exist = !DoesNotExist(vertex_index);
  } catch (...) {
    std::cerr << "ERROR: DoesExist()" << std::endl;
    throw 1;
  }
  return does_exist;
}

bool ConnectedComponents::InvalidVertexIndex(const int32_t vertex_index) const noexcept {
  return ((vertex_index < 0) || (vertex_index >= number_of_vertices_));
}

bool ConnectedComponents::InvalidEdgeIndex(const int32_t edge_index) const noexcept {
  return ((edge_index < 0) || (edge_index >= number_of_edges_));
}

void ConnectedComponents::ResetAll() noexcept {
  Reset();
  ResetClusterMappings();
  for (auto &element : neighbours_) {
    element.clear();
  }
}

void ConnectedComponents::Reset() noexcept {
  for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
    explored_[vertex_index] = false;
    queued_[vertex_index] = false;
  }
  todo_.Clear();
}

void ConnectedComponents::ResetClusterMappings() noexcept {
  for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
    cluster_mappings_[vertex_index] = kInvalidVertex;
  }
}

void ConnectedComponents::SetClusterId(const int32_t vertex_index, const int32_t cluster_id) {
  if (InvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: SetClusterId(): Invalid arg: vertex_index = " << vertex_index << std::endl;
    throw 1;
  } else if (InvalidVertexIndex(cluster_id)) {
    std::cerr << "ERROR: SetClusterId(): Invalid arg: cluster_id = " << cluster_id << std::endl;
    throw 1;
  } else {
    cluster_mappings_[vertex_index] = cluster_id;
  }
}

int32_t ConnectedComponents::GetClusterId(const int32_t vertex_index) const {
  int32_t cluster_id;
  if (InvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: GetClusterId(): Invalid arg: vertex_index = " << vertex_index << std::endl;
    throw 1;
  } else if (ClusterIdIsNotAllocated(vertex_index)) {
    std::cerr << "ERROR: GetClusterId(): Invalid cluster_id = " << cluster_mappings_[vertex_index]
              << " at vertex = " << vertex_index << std::endl;
    throw 1;
  } else {
    cluster_id = cluster_mappings_[vertex_index];
  }
  return cluster_id;
}

int32_t ConnectedComponents::ClusterIdIsNotAllocated(const int32_t vertex_index) const {
  if (InvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: ClusterIdIsNotAllocated(): Invalid arg: vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  const int32_t cluster_id = cluster_mappings_[vertex_index];
  const bool not_allocated = InvalidVertexIndex(cluster_id);
  return not_allocated;
}

// **********************************************************************

}  // namespace ALDS1_12_A_1
