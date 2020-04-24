/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-4. グラフ(Graph)、幅優先探索(Breadth First Search, BFS)。
 * 各頂点について全ての頂点との隣接関係を調べているので、ノード数が|V|の時、計算量はO(|V|^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C12_4_ALDS1_11_C_breadth_first_search.h"
#include <iostream>
#include <string>

namespace ALDS1_11_C {

void CallBreadthFirstSearch(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  BreadthFirstSearch *breadth_first_search = new BreadthFirstSearch();
  try {
    int32_t number_of_vertices;
    input_stream >> number_of_vertices;
    for (int32_t i = 0; i < number_of_vertices; ++i) {
      int32_t vertex_number, out_degree;
      input_stream >> vertex_number >> out_degree;
      breadth_first_search->AddVertex(vertex_number);
      for (int32_t j = 0; j < out_degree; ++j) {
        int32_t tail_vertex;
        input_stream >> tail_vertex;
        breadth_first_search->MapDirection(vertex_number, tail_vertex);
      }
    }
    breadth_first_search->ExploreAllVertices();
    breadth_first_search->Print();
  } catch (...) {
    std::cerr << "ERROR: CallBreadthFirstSearch()" << std::endl;
    throw;
  }
  delete breadth_first_search;
}

// ****************************************************

BreadthFirstSearch::BreadthFirstSearch() noexcept : size_(0) {
  Reset();
}

BreadthFirstSearch::~BreadthFirstSearch() noexcept {}

void BreadthFirstSearch::ExploreAllVertices() {
  try {
    SetStartingVertex(kFirstExploreTargetIndex);
    for (int32_t i = 0; i <= kMaxLoop; ++i) {
      const int32_t vertex_index = PickNextVertex();
      if (DoesNotExist(vertex_index)) {
        break;
      }
      ExploreOneVertex(vertex_index);
    }
  } catch (...) {
    std::cerr << "ERROR: ExploreAllVertices()" << std::endl;
    throw;
  }
}

void BreadthFirstSearch::SetStartingVertex(const int32_t starting_vertex_index) {
  constexpr int32_t kInitialDistance = 0;
  try {
    SetDistance(starting_vertex_index, kInitialDistance);
    PushFutureVertexToExplore(starting_vertex_index);
  } catch (...) {
    std::cerr << "ERROR: SetStartingVertex()" << std::endl;
    throw;
  }
}

int32_t BreadthFirstSearch::PickNextVertex() {
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

void BreadthFirstSearch::ExploreOneVertex(const int32_t vertex_index) {
  if (IsInvalidVertexIndex(vertex_index)) {
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
    const int32_t distance = GetDistance(vertex_index);
    const int32_t neighbour_distance = distance + 1;

    for (int32_t index_tail_vertex = 0; index_tail_vertex < size_; ++index_tail_vertex) {
      if (IsMapped(vertex_index, index_tail_vertex)) {
        if (NotExplored(index_tail_vertex)) {
          PushFutureVertexToExplore(index_tail_vertex);
        }
        if (InvalidDistance(index_tail_vertex) || neighbour_distance < GetDistance(index_tail_vertex)) {
          SetDistance(index_tail_vertex, neighbour_distance);
        }
      }
    }
  } catch (...) {
    std::cerr << "ERROR: ExploreOneVertex()" << std::endl;
    throw;
  }
}

void BreadthFirstSearch::PushFutureVertexToExplore(const int32_t vertex_index) noexcept {
  try {
    if (NotExplored(vertex_index)) {
      todo_.Enqueue(vertex_index);
    }
  } catch (...) {
    std::cerr << "ERROR: PushFutureVertex()" << std::endl;
    throw;
  }
}

bool BreadthFirstSearch::DoesNotExist(const int32_t vertex_index) const {
  bool does_not_exist;
  if (vertex_index == kDoesNotExist) {
    does_not_exist = true;
  } else if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: DoesNotExist(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  } else {
    does_not_exist = false;
  }
  return does_not_exist;
}

bool BreadthFirstSearch::DoesExist(const int32_t vertex_index) const {
  bool does_exist;
  try {
    does_exist = !DoesNotExist(vertex_index);
  } catch (...) {
    std::cerr << "ERROR: DoesExist()" << std::endl;
    throw 1;
  }
  return does_exist;
}

void BreadthFirstSearch::AddVertex(const int32_t vertex_number) {
  if (IsInvalidVertexNumber(vertex_number)) {
    std::cerr << "ERROR: AddVertex(): Invalid arg vertex_number = " << vertex_number << std::endl;
    throw 1;
  }
  size_ = (vertex_number > size_) ? vertex_number : size_;
}

void BreadthFirstSearch::MapDirection(const int32_t vertex_number_from, const int32_t vertex_number_to) {
  if (IsInvalidVertexNumber(vertex_number_from)) {
    std::cerr << "ERROR: MapDirection(): Invalid arg vertex_number_from = " << vertex_number_from << std::endl;
    throw 1;
  } else if (IsInvalidVertexNumber(vertex_number_to)) {
    std::cerr << "ERROR: MapDirection(): Invalid arg vertex_number_to = " << vertex_number_to << std::endl;
    throw 1;
  } else {
    try {
      int32_t index_from = ConvertFromVertexNumberToIndex(vertex_number_from);
      int32_t index_to = ConvertFromVertexNumberToIndex(vertex_number_to);
      adjacency_matrix_[index_from][index_to] = true;
    } catch (...) {
      std::cerr << "ERROR: MapDirection()" << std::endl;
      throw;
    }
  }
}

bool BreadthFirstSearch::IsMapped(const int32_t index_from, const int32_t index_to) const {
  bool is_mapped = false;
  if (IsInvalidVertexIndex(index_from)) {
    std::cerr << "ERROR: IsMapped(): Invalid arg index_from = " << index_from << std::endl;
    throw 1;
  } else if (IsInvalidVertexIndex(index_to)) {
    std::cerr << "ERROR: IsMapped(): Invalid arg index_to = " << index_to << std::endl;
    throw 1;
  } else {
    is_mapped = adjacency_matrix_[index_from][index_to];
  }
  return is_mapped;
}

void BreadthFirstSearch::Print() const {
  try {
    for (int32_t vertex_index = 0; vertex_index < size_; ++vertex_index) {
      std::cout << ConvertFromIndexToVertexNumber(vertex_index) << " " << GetDistance(vertex_index) << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: Print()" << std::endl;
    throw;
  }
}

void BreadthFirstSearch::Reset() noexcept {
  for (auto &row : adjacency_matrix_) {
    for (auto &element : row) {
      element = false;
    }
  }
  for (int32_t &distance : distances_) {
    distance = kNotReached;
  }
  for (bool &cexplored : explored_) {
    cexplored = false;
  }
}

bool BreadthFirstSearch::IsInvalidVertexNumber(const int32_t vertex_number) noexcept {
  return ((vertex_number < 1) || (vertex_number > kMaxVertexNumber));
}

bool BreadthFirstSearch::IsInvalidVertexIndex(const int32_t index) const noexcept {
  return ((index < 0) || (index >= size_));
}

int32_t BreadthFirstSearch::ConvertFromVertexNumberToIndex(const int32_t vertex_number) {
  if (IsInvalidVertexNumber(vertex_number)) {
    std::cerr << "ERROR: ConvertFromVertexNumberToIndex(): Invalid vertex_number=" << vertex_number << std::endl;
    throw 1;
  }
  const int32_t index = vertex_number - 1;
  return index;
}

int32_t BreadthFirstSearch::ConvertFromIndexToVertexNumber(const int32_t index) const {
  if (IsInvalidVertexIndex(index)) {
    std::cerr << "ERROR: ConvertFromIndexToVertexNumber(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  return index + 1;
}

void BreadthFirstSearch::SetDistance(const int32_t index, const int32_t distance) {
  if (IsInvalidVertexIndex(index)) {
    std::cerr << "ERROR: SetDistance(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  } else {
    distances_[index] = distance;
  }
}

int32_t BreadthFirstSearch::GetDistance(const int32_t index) const {
  if (IsInvalidVertexIndex(index)) {
    std::cerr << "ERROR: GetDistance(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  return distances_[index];
}

bool BreadthFirstSearch::NotExplored(const int32_t index) const {
  if (IsInvalidVertexIndex(index)) {
    std::cerr << "ERROR: NotExplored(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  return !explored_[index];
}

bool BreadthFirstSearch::AlreadyExplored(const int32_t index) const {
  if (IsInvalidVertexIndex(index)) {
    std::cerr << "ERROR: AlreadyExplored(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  return explored_[index];
}

void BreadthFirstSearch::MarkAsExplored(const int32_t index) {
  if (IsInvalidVertexIndex(index)) {
    std::cerr << "ERROR: MarkAsExplored(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  explored_[index] = true;
}

bool BreadthFirstSearch::InvalidDistance(const int32_t index) const {
  if (IsInvalidVertexIndex(index)) {
    std::cerr << "ERROR: DoesNotHaveValidDistance(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  const bool invalid_distance = (distances_[index] < 0);
  return invalid_distance;
}

// **********************************************************************

Queue::Queue() noexcept : depth_(0), head_(0), indices_{0} {}

Queue::~Queue() noexcept {}

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

// ******************************

}  // namespace ALDS1_11_C
