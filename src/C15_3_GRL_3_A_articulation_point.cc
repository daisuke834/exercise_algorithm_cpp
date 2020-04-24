/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-3. 高度なグラフアルゴリズム、関節点(Articulation Point)。
 * 深さ優先探索(DFS)で、かつ再帰を用いない実装。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C15_3_GRL_3_A_articulation_point.h"
#include <iostream>
#include <string>

namespace GRL_3_A {

void CallArticulationPoint(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  ArticulationPoint *articulation_point = new ArticulationPoint();
  try {
    int32_t number_of_vertices, number_of_edges;
    input_stream >> number_of_vertices >> number_of_edges;
    articulation_point->SetNumberOfVertices(number_of_vertices);
    for (int32_t i = 0; i < number_of_edges; ++i) {
      int32_t vertex_index_from, vertex_index_to;
      input_stream >> vertex_index_from >> vertex_index_to;
      articulation_point->MapDirection(vertex_index_from, vertex_index_to);
    }
    articulation_point->ExploreAllVertices();
    articulation_point->PrintArticulationPoints();
  } catch (...) {
    std::cerr << "ERROR: CallArticulationPoint()" << std::endl;
    throw;
  }
  delete articulation_point;
}

// ****************************************************

ArticulationPoint::ArticulationPoint() noexcept : number_of_vertices_(0), preorder_number_(1) {}

ArticulationPoint::~ArticulationPoint() noexcept {}

void ArticulationPoint::SetNumberOfVertices(const int32_t number_of_vertices) {
  if (number_of_vertices > kMaxNumberOfVertices) {
    std::cerr << "ERROR: SetNumberOfVertices(): Invalid arg: number_of_vertices=" << number_of_vertices << std::endl;
    throw 1;
  }
  number_of_vertices_ = number_of_vertices;
}

void ArticulationPoint::ExploreAllVertices() {
  try {
    DiscoverOneVertex(kFirstExploreTargetIndex, kRoot);
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      int32_t target_vertex_index = PickNextVertex();
      if (DoesNotExist(target_vertex_index)) {
        if (NoMoreUnexploredVertex()) {
          break;
        } else {
          std::cerr << "ERROR: ExploreAllVertices(): More than 1 root vertices." << std::endl;
          throw 1;
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

void ArticulationPoint::ExploreOneVertex(const int32_t vertex_index) {
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
        DiscoverOneVertex(index_tail_vertex, vertex_index);
      } else {
        if (index_tail_vertex != vertices_[vertex_index].GetParentIndex()) {
          // Back Edgeの場合
          vertices_[vertex_index].UpdateLowestScore(vertices_[index_tail_vertex].GetPreorderNumber());
        }
      }
    }
  } catch (...) {
    std::cerr << "ERROR: ExploreOneVertex()" << std::endl;
    throw;
  }
}

void ArticulationPoint::DiscoverOneVertex(const int32_t discovered_index, const int32_t parent_index) {
  if (IsInvalidVertexIndex(discovered_index)) {
    std::cerr << "ERROR: DiscoverOneVertex(): Invalid arg discovered_index = " << discovered_index << std::endl;
    throw 1;
  }
  try {
    todo_.push(discovered_index);
    vertices_[discovered_index].Discovered(preorder_number_, parent_index);
    if (!IsInvalidVertexIndex(parent_index)) {
      vertices_[parent_index].AddChild(discovered_index);
    }
    ++preorder_number_;
  } catch (...) {
    std::cerr << "ERROR: PushInitialVertex()" << std::endl;
    throw;
  }
}

void ArticulationPoint::CompleteOneVertex(const int32_t vertex_index) {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: CompleteOneVertex(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  try {
    const int32_t parent_index = vertices_[vertex_index].GetParentIndex();
    const int32_t lowest_score = vertices_[vertex_index].GetLowestScore();
    if (!IsInvalidVertexIndex(parent_index)) {
      vertices_[parent_index].UpdateLowestScore(lowest_score);
    }
    vertices_[vertex_index].Completed();
    todo_.pop();
  } catch (...) {
    std::cerr << "ERROR: CompleteOneVertex()" << std::endl;
    throw;
  }
}

int32_t ArticulationPoint::PickNextVertex() {
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

bool ArticulationPoint::NoMoreUnexploredVertex() const {
  const int32_t unexplored_vertex_index = FindUnexploredVertex();
  const bool no_more = DoesNotExist(unexplored_vertex_index);
  return no_more;
}

int32_t ArticulationPoint::FindUnexploredVertex() const {
  int32_t unexplored_vertex_index = kDoesNotExist;
  try {
    for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
      if (vertices_[vertex_index].GetStatus() == VertexStatus::kInit) {
        unexplored_vertex_index = vertex_index;
        break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: FindUnexploredVertex()" << std::endl;
    throw;
  }
  return unexplored_vertex_index;
}

bool ArticulationPoint::AllVerticesAreNotCompleted() const {
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

bool ArticulationPoint::DoesNotExist(const int32_t vertex_index) const {
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

void ArticulationPoint::MapDirection(const int32_t vertex_index_from, const int32_t vertex_index_to) {
  if (IsInvalidVertexIndex(vertex_index_from)) {
    std::cerr << "ERROR: AddVertex(): Invalid arg vertex_index_from = " << vertex_index_from << std::endl;
    throw 1;
  } else if (IsInvalidVertexIndex(vertex_index_to)) {
    std::cerr << "ERROR: AddVertex(): Invalid arg vertex_index_to = " << vertex_index_to << std::endl;
    throw 1;
  } else {
    try {
      vertices_[vertex_index_from].AddTail(vertex_index_to);
      vertices_[vertex_index_to].AddTail(vertex_index_from);
    } catch (...) {
      std::cerr << "ERROR: MapDirection()" << std::endl;
      throw;
    }
  }
}

void ArticulationPoint::PrintArticulationPoints() {
  try {
    for (int32_t vertex_index = 0; vertex_index < number_of_vertices_; ++vertex_index) {
      if (IsArticulationPoint(vertex_index)) {
        std::cout << vertex_index << std::endl;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: PrintArticulationPoints()" << std::endl;
    throw;
  }
}

bool ArticulationPoint::IsArticulationPoint(const int32_t vertex_index) const {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: IsArticulationPoint(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  bool is_articulation_point;
  const std::vector<int32_t> children = vertices_[vertex_index].GetChildren();
  if (vertices_[vertex_index].GetParentIndex() == kRoot) {
    is_articulation_point = (children.size() >= 2);
  } else {
    is_articulation_point = false;
    for (const int32_t child : children) {
      if (vertices_[vertex_index].GetPreorderNumber() <= vertices_[child].GetLowestScore()) {
        is_articulation_point = true;
        break;
      }
    }
  }
  return is_articulation_point;
}

bool ArticulationPoint::IsInvalidVertexIndex(const int32_t index) const noexcept {
  return ((index < 0) || (index >= number_of_vertices_));
}

// *************************************
Vertex::Vertex() noexcept
    : status_(VertexStatus::kInit),
      parent_index_(kDoesNotExist),
      preorder_number_(kDoesNotExist),
      lowest_score_(INT32_MAX),
      next_check_(0) {}

Vertex::~Vertex() noexcept {}

void Vertex::Discovered(const int32_t preorder_number, const int32_t parent_index) {
  if (status_ != VertexStatus::kInit) {
    std::cerr << "ERROR: Vertex::Discovered(): Vertex is not checked yet." << std::endl;
    throw 1;
  } else if (preorder_number < 1 || preorder_number > kMaxNumberOfVertices) {
    std::cerr << "ERROR: Vertex::Discovered(): Invalid arg preorder_number=" << preorder_number << std::endl;
    throw 1;
  } else if (parent_index != kRoot && (parent_index < 0 || parent_index >= kMaxNumberOfVertices)) {
    std::cerr << "ERROR: Vertex::Discovered(): Invalid arg parent_index=" << parent_index << std::endl;
    throw 1;
  } else {
    status_ = VertexStatus::kDiscovered;
    preorder_number_ = preorder_number;
    UpdateLowestScore(preorder_number);
    parent_index_ = parent_index;
  }
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

int32_t Vertex::GetParentIndex() const noexcept {
  return parent_index_;
}

int32_t Vertex::GetPreorderNumber() const noexcept {
  return preorder_number_;
}

void Vertex::UpdateLowestScore(const int32_t lowest_score) noexcept {
  if (lowest_score < lowest_score_) {
    lowest_score_ = lowest_score;
  }
}

int32_t Vertex::GetLowestScore() const noexcept {
  return lowest_score_;
}

void Vertex::AddChild(const int32_t child_index) {
  children_.push_back(child_index);
}

std::vector<int32_t> Vertex::GetChildren() const noexcept {
  return children_;
}

}  // namespace GRL_3_A
