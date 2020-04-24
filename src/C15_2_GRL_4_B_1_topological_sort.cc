/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-2. 高度なグラフアルゴリズム、トポロジカルソート(Topological Sort)。
 * 深さ優先探索(DFS)で、かつ再帰を用いない実装。計算量はO(|V|+|E|)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C15_2_GRL_4_B_1_topological_sort.h"
#include <iostream>
#include <string>

namespace GRL_4_B_1 {

void CallTopologicalSort(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  TopologicalSort *topological_sort = new TopologicalSort();
  try {
    int32_t number_of_vertices, number_of_edges;
    input_stream >> number_of_vertices >> number_of_edges;
    topological_sort->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_edges; ++i) {
      int32_t vertex_index_from, vertex_index_to;
      input_stream >> vertex_index_from >> vertex_index_to;
      topological_sort->MapDirection(vertex_index_from, vertex_index_to);
    }
    topological_sort->GenerateSortedList();
    topological_sort->Print();
  } catch (...) {
    std::cerr << "ERROR: CallTopologicalSort()" << std::endl;
    throw;
  }
  delete topological_sort;
}

// ****************************************************

TopologicalSort::TopologicalSort() noexcept : number_of_vertices_(0) {}

TopologicalSort::~TopologicalSort() noexcept {}

void TopologicalSort::SetNumberOfVertices(const int32_t number_of_vertices) {
  if (number_of_vertices > kMaxNumberOfVertices) {
    std::cerr << "ERROR: SetNumberOfVertices(): Invalid arg: number_of_vertices=" << number_of_vertices << std::endl;
    throw 1;
  }
  number_of_vertices_ = number_of_vertices;
}

void TopologicalSort::GenerateSortedList() {
  try {
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

void TopologicalSort::ExploreOneVertex(const int32_t vertex_index) {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: ExploreOneVertex(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  try {
    const int32_t index_tail_vertex = vertices_[vertex_index].GetNextTailIndex();
    if (DoesNotExist(index_tail_vertex)) {
      CompleteOneVertex(vertex_index);
    } else {
      if (vertices_[index_tail_vertex].GetStatus() == VertexStatus::kInit) {
        DiscoverOneVertex(index_tail_vertex);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: ExploreOneVertex()" << std::endl;
    throw;
  }
}

void TopologicalSort::DiscoverOneVertex(const int32_t vertex_index) {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: DiscoverOneVertex(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  try {
    todo_.push(vertex_index);
    vertices_[vertex_index].Discovered();
  } catch (...) {
    std::cerr << "ERROR: PushInitialVertex()" << std::endl;
    throw;
  }
}

void TopologicalSort::CompleteOneVertex(const int32_t vertex_index) {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: CompleteOneVertex(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  try {
    vertices_[vertex_index].Completed();
    todo_.pop();
    sorted_.push_front(vertex_index);
  } catch (...) {
    std::cerr << "ERROR: CompleteOneVertex()" << std::endl;
    throw;
  }
}

int32_t TopologicalSort::PickNextVertex() {
  int32_t next_vertex_index;
  try {
    if (todo_.empty()) {
      next_vertex_index = kDoesNotExist;
    } else {
      next_vertex_index = todo_.top();
    }
  } catch (...) {
    std::cerr << "ERROR: PickNextVertex()" << std::endl;
    throw;
  }
  return next_vertex_index;
}

bool TopologicalSort::NoMoreUnexploredVertex() const {
  const int32_t unexplored_vertex_index = FindUnexploredVertex();
  const bool no_more = DoesNotExist(unexplored_vertex_index);
  return no_more;
}

int32_t TopologicalSort::FindUnexploredVertex() const {
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

int32_t TopologicalSort::PickUnexploredVertex() {
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

bool TopologicalSort::AllVerticesAreNotCompleted() const {
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

bool TopologicalSort::DoesNotExist(const int32_t vertex_index) const {
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

void TopologicalSort::MapDirection(const int32_t vertex_index_from, const int32_t vertex_index_to) {
  if (IsInvalidVertexIndex(vertex_index_from)) {
    std::cerr << "ERROR: AddVertex(): Invalid arg vertex_index_from = " << vertex_index_from << std::endl;
    throw 1;
  } else if (IsInvalidVertexIndex(vertex_index_to)) {
    std::cerr << "ERROR: AddVertex(): Invalid arg vertex_index_to = " << vertex_index_to << std::endl;
    throw 1;
  } else {
    try {
      vertices_[vertex_index_from].AddTail(vertex_index_to);
    } catch (...) {
      std::cerr << "ERROR: MapDirection()" << std::endl;
      throw;
    }
  }
}

void TopologicalSort::Print() {
  try {
    for (std::list<int32_t>::iterator itr = sorted_.begin(); itr != sorted_.end(); ++itr) {
      std::cout << (*itr) << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: Print()" << std::endl;
    throw;
  }
}

bool TopologicalSort::IsInvalidVertexIndex(const int32_t index) const noexcept {
  return ((index < 0) || (index >= number_of_vertices_));
}

// *************************************
Vertex::Vertex() noexcept : status_(VertexStatus::kInit), next_check_(0) {}

Vertex::~Vertex() noexcept {}

void Vertex::Discovered() {
  if (status_ != VertexStatus::kInit) {
    std::cerr << "ERROR: Vertex::Discovered(): Vertex is not checked yet." << std::endl;
    throw 1;
  }
  status_ = VertexStatus::kDiscovered;
}

void Vertex::Completed() {
  if (status_ != VertexStatus::kDiscovered) {
    std::cerr << "ERROR: Vertex::Completed(): Vertex is not explored yet." << std::endl;
    throw 1;
  }
  status_ = VertexStatus::kCompleted;
}

VertexStatus Vertex::GetStatus() const noexcept {
  return status_;
}

int32_t Vertex::GetNextTailIndex() noexcept {
  int32_t next_tail_index;
  if ((next_check_ < 0) || (next_check_ >= GetNumberOfTails())) {
    next_tail_index = kDoesNotExist;
  } else {
    next_tail_index = tails_[next_check_];
    ++next_check_;
  }
  return next_tail_index;
}

void Vertex::AddTail(const int32_t tail_index) noexcept {
  tails_.push_back(tail_index);
}

int32_t Vertex::GetNumberOfTails() const noexcept {
  return static_cast<int32_t>(tails_.size());
}

}  // namespace GRL_4_B_1
