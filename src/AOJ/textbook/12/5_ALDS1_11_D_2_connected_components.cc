/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-5. グラフ(Graph)、連結成分(Connected Components)。隣接メモリリストにvectorを用いる。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "5_ALDS1_11_D_2_connected_components.h"

#include <iostream>
#include <string>

namespace ALDS1_11_D_2 {

void CallConnectedComponents(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  ConnectedComponents* connected_components = new ConnectedComponents();
  try {
    int32_t number_of_vertices, number_of_relations;
    input_stream >> number_of_vertices >> number_of_relations;
    connected_components->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_relations; ++i) {
      int32_t vertex_1, vertex_2;
      input_stream >> vertex_1 >> vertex_2;
      connected_components->AddMapping(vertex_1, vertex_2);
    }

    int32_t number_of_questions;
    input_stream >> number_of_questions;
    for (int32_t i = 0; i < number_of_questions; ++i) {
      int32_t index_from, index_to;
      input_stream >> index_from >> index_to;
      const bool connected = connected_components->ConnectionExistsBetweenStartAndEnd(index_from, index_to);
      if (connected) {
        std::cout << "yes" << std::endl;
      } else {
        std::cout << "no" << std::endl;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CallConnectedComponents()" << std::endl;
    throw;
  }
  delete connected_components;
}

// ****************************************************

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
  int32_t next_vertex_index = kDoesNotExist;
  try {
    for (int32_t i = 0; i < kMaxLoop; ++i) {
      if (todo_.IsEmpty()) {
        next_vertex_index = kDoesNotExist;
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
  if (vertex_index == kDoesNotExist) {
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

void ConnectedComponents::Reset() noexcept {
  for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
    explored_[vertex_index] = false;
    queued_[vertex_index] = false;
  }
  todo_.Clear();
}

void ConnectedComponents::ResetClusterMappings() noexcept {
  for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
    cluster_mappings_[vertex_index] = kDoesNotExist;
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

Queue::Queue() noexcept { Clear(); }

Queue::~Queue() noexcept {}

void Queue::Clear() noexcept {
  depth_ = 0;
  head_ = 0;
}

bool Queue::IsEmpty() const noexcept { return (depth_ <= 0); }

bool Queue::IsFull() const noexcept { return (depth_ >= kMaxQueueSize); }

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

// ****************************************************

}  // namespace ALDS1_11_D_2
