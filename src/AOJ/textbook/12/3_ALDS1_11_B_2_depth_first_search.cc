/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-3. グラフ(Graph)、深さ優先探索(Depth First Search, DFS)。
 * 隣接行列表現(Adjacency matrices)による管理。
 * 各頂点について全ての頂点との隣接関係を調べているので、ノード数が|V|の時、計算量はO(|V|^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "3_ALDS1_11_B_2_depth_first_search.h"

#include <iostream>
#include <string>

namespace ALDS1_11_B_2 {

void CallDepthFirstSearch(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  DepthFirstSearch* depth_first_search = new DepthFirstSearch();
  try {
    int32_t number_of_vertices;
    input_stream >> number_of_vertices;
    for (int32_t i = 0; i < number_of_vertices; ++i) {
      int32_t vertex_number, out_degree;
      input_stream >> vertex_number >> out_degree;
      depth_first_search->AddVertex(vertex_number);
      for (int32_t j = 0; j < out_degree; ++j) {
        int32_t tail_vertex;
        input_stream >> tail_vertex;
        depth_first_search->MapDirection(vertex_number, tail_vertex);
      }
    }
    depth_first_search->ExploreAllVertices();
    depth_first_search->Print();
  } catch (...) {
    std::cerr << "ERROR: CallDepthFirstSearch()" << std::endl;
    throw;
  }
  delete depth_first_search;
}

// ****************************************************

DepthFirstSearch::DepthFirstSearch() noexcept : time_(kInvalidTime), number_of_vertices_(0) { Reset(); }

DepthFirstSearch::~DepthFirstSearch() noexcept {}

void DepthFirstSearch::ExploreAllVertices() {
  try {
    time_ = 1;
    DiscoverOneVertex(kFirstExploreTargetIndex);
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      int32_t target_vertex_index = PickNextVertex();
      if (DoesNotExist(target_vertex_index)) {
        if (NoMoreUnexploredVertex()) {
          break;
        } else {
          target_vertex_index = PickUnexploredVertex();
        }
      }
      ExploreOneVertex(target_vertex_index);
    }
  } catch (...) {
    std::cerr << "ERROR: ExploreAllVertices()" << std::endl;
    throw;
  }
  if (AllVerticesAreNotCompleted()) {
    std::cerr << "ERROR: ExploreAllVertices(): All vertexes are not completed yet." << std::endl;
    throw 1;
  }
}

void DepthFirstSearch::ExploreOneVertex(const int32_t vertex_index) {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: ExploreOneVertex(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  try {
    bool was_completed = true;
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      const int32_t index_tail_vertex = vertices_[vertex_index].GetNextTailCheck();
      if (index_tail_vertex >= number_of_vertices_) {
        break;
      } else if (IsMapped(vertex_index, index_tail_vertex)) {
        if (vertices_[index_tail_vertex].GetStatus() == VertexStatus::kInit) {
          DiscoverOneVertex(index_tail_vertex);
          was_completed = false;
          break;
        }
      }
    }
    if (was_completed) {
      CompleteOneVertex(vertex_index);
    }
  } catch (...) {
    std::cerr << "ERROR: ExploreOneVertex()" << std::endl;
    throw;
  }
}

void DepthFirstSearch::DiscoverOneVertex(const int32_t vertex_index) {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: DiscoverOneVertex(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  try {
    todo_.Push(vertex_index);
    vertices_[vertex_index].Discovered(time_++);
  } catch (...) {
    std::cerr << "ERROR: PushInitialVertex()" << std::endl;
    throw;
  }
}

void DepthFirstSearch::CompleteOneVertex(const int32_t vertex_index) {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: CompleteOneVertex(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  try {
    vertices_[vertex_index].Completed(time_++);
    todo_.Pop();
  } catch (...) {
    std::cerr << "ERROR: CompleteOneVertex()" << std::endl;
    throw;
  }
}

int32_t DepthFirstSearch::PickNextVertex() {
  int32_t next_vertex_index;
  try {
    if (todo_.IsEmpty()) {
      next_vertex_index = kDoesNotExist;
    } else {
      next_vertex_index = todo_.GetTop();
    }
  } catch (...) {
    std::cerr << "ERROR: PickNextVertex()" << std::endl;
    throw;
  }
  return next_vertex_index;
}

bool DepthFirstSearch::NoMoreUnexploredVertex() const {
  const int32_t unexplored_vertex_index = FindUnexploredVertex();
  const bool no_more = DoesNotExist(unexplored_vertex_index);
  return no_more;
}

int32_t DepthFirstSearch::FindUnexploredVertex() const {
  int32_t unexplored_vertex_index = kDoesNotExist;
  try {
    for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
      if (vertices_[vertex_index].GetStatus() == VertexStatus::kInit) {
        unexplored_vertex_index = vertex_index;
        break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: PickUnexploredVertex()" << std::endl;
    throw;
  }
  return unexplored_vertex_index;
}

int32_t DepthFirstSearch::PickUnexploredVertex() {
  int32_t unexplored_vertex_index;
  try {
    unexplored_vertex_index = FindUnexploredVertex();
    DiscoverOneVertex(unexplored_vertex_index);
  } catch (...) {
    std::cerr << "ERROR: PickUnexploredVertex()" << std::endl;
    throw;
  }
  return unexplored_vertex_index;
}

bool DepthFirstSearch::AllVerticesAreNotCompleted() const {
  bool not_completed = false;
  try {
    for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
      if (vertices_[vertex_index].GetStatus() != VertexStatus::kCompleted) {
        not_completed = true;
        break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: AllVerticesAreNotCompleted()" << std::endl;
    throw;
  }
  return not_completed;
}

bool DepthFirstSearch::DoesNotExist(const int32_t vertex_index) const {
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

void DepthFirstSearch::AddVertex(const int32_t vertex_number) {
  if (IsInvalidVertexNumber(vertex_number)) {
    std::cerr << "ERROR: AddVertex(): Invalid arg vertex_number = " << vertex_number << std::endl;
    throw 1;
  }
  number_of_vertices_ = (vertex_number > number_of_vertices_) ? vertex_number : number_of_vertices_;
}

void DepthFirstSearch::MapDirection(const int32_t vertex_number_from, const int32_t vertex_number_to) {
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
      adjacency_matrix_[index_from][index_to] = true;
    } catch (...) {
      std::cerr << "ERROR: MapDirection()" << std::endl;
      throw;
    }
  }
}

bool DepthFirstSearch::IsMapped(const int32_t index_from, const int32_t index_to) const {
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

void DepthFirstSearch::Print() const {
  try {
    for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
      std::cout << ConvertFromIndexToVertexNumber(vertex_index);
      std::cout << " " << vertices_[vertex_index].GetDiscoveredTime();
      std::cout << " " << vertices_[vertex_index].GetCompletionTime() << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: Print()" << std::endl;
    throw;
  }
}

void DepthFirstSearch::Reset() noexcept {
  for (auto& row : adjacency_matrix_) {
    for (auto& element : row) {
      element = false;
    }
  }
  for (Vertex& vertex : vertices_) {
    vertex.Reset();
  }
}

bool DepthFirstSearch::IsInvalidVertexNumber(const int32_t vertex_number) noexcept {
  return ((vertex_number < 1) || (vertex_number > kMaxVertexNumber));
}

bool DepthFirstSearch::IsInvalidVertexIndex(const int32_t index) const noexcept {
  return ((index < 0) || (index >= number_of_vertices_));
}

int32_t DepthFirstSearch::ConvertFromVertexNumberToIndex(const int32_t vertex_number) {
  if (IsInvalidVertexNumber(vertex_number)) {
    std::cerr << "ERROR: ConvertFromVertexNumberToIndex(): Invalid vertex_number=" << vertex_number << std::endl;
    throw 1;
  }
  const int32_t index = vertex_number - 1;
  return index;
}

int32_t DepthFirstSearch::ConvertFromIndexToVertexNumber(const int32_t index) const {
  if (IsInvalidVertexIndex(index)) {
    std::cerr << "ERROR: ConvertFromIndexToVertexNumber(): Invalid vertex: index = " << index << std::endl;
    throw 1;
  }
  return index + 1;
}

// **********************************************************************

Stack::Stack() noexcept : top_position_(0), values_{0} {}

Stack::~Stack() noexcept {}

bool Stack::IsEmpty() const noexcept { return (top_position_ <= 0); }

bool Stack::IsFull() const noexcept { return (top_position_ >= kMaxStackDepth); }

void Stack::Push(const int32_t x) {
  if (IsFull()) {
    std::cerr << "ERROR: Push(): stack is full." << std::endl;
    throw 1;
  }
  values_[top_position_] = x;
  ++top_position_;
}

void Stack::Pop() {
  if (IsEmpty()) {
    std::cerr << "ERROR: Pop(): stack is empty." << std::endl;
    throw 1;
  }
  --top_position_;
}

int32_t Stack::GetTop() {
  if (IsEmpty()) {
    std::cerr << "ERROR: GetTop(): stack is empty." << std::endl;
    throw 1;
  }
  return values_[top_position_ - 1];
}

// *************************************
Vertex::Vertex() noexcept
    : status_(VertexStatus::kInit), discovered_time_(kInvalidTime), completion_time_(kInvalidTime), next_check_(0) {}

Vertex::~Vertex() noexcept {}

void Vertex::Discovered(const int32_t time) {
  if (status_ != VertexStatus::kInit) {
    std::cerr << "ERROR: Vertex::Discovered(): Vertex is not checked yet." << std::endl;
    throw 1;
  }
  status_ = VertexStatus::kDiscovered;
  discovered_time_ = time;
}

void Vertex::Completed(const int32_t time) {
  if (status_ != VertexStatus::kDiscovered) {
    std::cerr << "ERROR: Vertex::Completed(): Vertex is not explored yet." << std::endl;
    throw 1;
  }
  status_ = VertexStatus::kCompleted;
  completion_time_ = time;
}

VertexStatus Vertex::GetStatus() const noexcept { return status_; }

int32_t Vertex::GetDiscoveredTime() const noexcept { return discovered_time_; }

int32_t Vertex::GetCompletionTime() const noexcept { return completion_time_; }

void Vertex::Reset() noexcept {
  status_ = VertexStatus::kInit;
  discovered_time_ = kInvalidTime;
  completion_time_ = kInvalidTime;
  next_check_ = 0;
}

int32_t Vertex::GetNextTailCheck() noexcept { return next_check_++; }

}  // namespace ALDS1_11_B_2
