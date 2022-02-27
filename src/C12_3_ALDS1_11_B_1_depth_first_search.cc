/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-3. グラフ(Graph)、深さ優先探索(Depth First Search, DFS)。
 * 各頂点について全ての頂点との隣接関係を調べているので、ノード数が|V|の時、計算量はO(|V|^2)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C12_3_ALDS1_11_B_1_depth_first_search.h"

#include <iostream>
#include <string>

namespace ALDS1_11_B_1 {

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

DepthFirstSearch::DepthFirstSearch() noexcept : size_(0) { Reset(); }

DepthFirstSearch::~DepthFirstSearch() noexcept {}

void DepthFirstSearch::ExploreAllVertices() {
  try {
    time_.Set(1);
    PushFutureVertexToExplore(kFirstExploreTargetIndex);
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      int32_t target_vertex_index = PickNextVertex();
      if (DoesNotExist(target_vertex_index)) {
        if (NoMoreUnexploredVertex()) {
          break;
        } else {
          target_vertex_index = GetUnexploredVertex();
        }
      }

      VertexStatus status = GetVertexStatus(target_vertex_index);
      switch (status) {
        case VertexStatus::kNotExplored:
          ExploreOneVertex(target_vertex_index);
          time_.Next();
          break;
        case VertexStatus::kExplored:
          CompleteOneVertex(target_vertex_index);
          time_.Next();
          break;
        default:
          // SKIP LOOP
          break;
      }
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
    std::cerr << "ERROR: ExploreVertex(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  try {
    const int32_t current_time = time_.Get();
    explored_time_[vertex_index].Set(current_time);

    todo_.Push(vertex_index);
    for (int32_t index_tail_vertex = size_ - 1; index_tail_vertex >= 0; --index_tail_vertex) {
      if (IsMapped(vertex_index, index_tail_vertex)) {
        if (NotExplored(index_tail_vertex)) {
          todo_.Push(index_tail_vertex);
        }
      }
    }
  } catch (...) {
    std::cerr << "ERROR: ExploreOneVertex()" << std::endl;
    throw;
  }
}

void DepthFirstSearch::CompleteOneVertex(const int32_t vertex_index) {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: CompleteVertex(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  } else if (explored_time_[vertex_index].IsInvalid()) {
    std::cerr << "ERROR: CompleteVertex(): Selected vertex is not explored yet. vertex_index = " << vertex_index
              << std::endl;
    throw 1;
  } else {
    try {
      const int32_t current_time = time_.Get();
      completion_time_[vertex_index].Set(current_time);
    } catch (...) {
      std::cerr << "ERROR: CompleteOneVertex()" << std::endl;
      throw;
    }
  }
}

VertexStatus DepthFirstSearch::GetVertexStatus(const int32_t vertex_index) const {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: GetVertexStatus(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  VertexStatus status;
  try {
    if (explored_time_[vertex_index].IsInvalid()) {
      status = VertexStatus::kNotExplored;
    } else if (completion_time_[vertex_index].IsInvalid()) {
      status = VertexStatus::kExplored;
    } else {
      status = VertexStatus::kCompleted;
    }
  } catch (...) {
    std::cerr << "ERROR: GetVertexStatus()" << std::endl;
    throw;
  }
  return status;
}

void DepthFirstSearch::PushFutureVertexToExplore(const int32_t vertex_index) noexcept {
  try {
    todo_.Push(vertex_index);
  } catch (...) {
    std::cerr << "ERROR: PushFutureVertex()" << std::endl;
    throw;
  }
}

int32_t DepthFirstSearch::PickNextVertex() noexcept {
  int32_t next_vertex_index;
  try {
    if (todo_.IsEmpty()) {
      next_vertex_index = kDoesNotExist;
    } else {
      next_vertex_index = todo_.Pop();
    }
  } catch (...) {
    std::cerr << "ERROR: PickNextVertex()" << std::endl;
    throw;
  }
  return next_vertex_index;
}

bool DepthFirstSearch::NoMoreUnexploredVertex() const {
  const int32_t unexplored_vertex_index = GetUnexploredVertex();
  const bool no_more = DoesNotExist(unexplored_vertex_index);
  return no_more;
}

int32_t DepthFirstSearch::GetUnexploredVertex() const {
  int32_t unexplored_vertex_index = kDoesNotExist;
  try {
    for (int32_t vertex_index = 0; vertex_index < size_; ++vertex_index) {
      if (NotExplored(vertex_index)) {
        unexplored_vertex_index = vertex_index;
        break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: GetUnexploredVertex()" << std::endl;
    throw;
  }
  return unexplored_vertex_index;
}

bool DepthFirstSearch::AllVerticesAreNotCompleted() const {
  bool not_completed = false;
  try {
    for (int32_t vertex_index = 0; vertex_index < size_; ++vertex_index) {
      if (NotCompleted(vertex_index)) {
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

bool DepthFirstSearch::NotCompleted(const int32_t vertex_index) const {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: Completed(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  const bool not_completed = completion_time_[vertex_index].IsInvalid();
  return not_completed;
}

bool DepthFirstSearch::WasExplored(const int32_t vertex_index) const {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: WasExplored(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  const bool was_explored = explored_time_[vertex_index].IsValid();
  return was_explored;
}

bool DepthFirstSearch::NotExplored(const int32_t vertex_index) const {
  if (IsInvalidVertexIndex(vertex_index)) {
    std::cerr << "ERROR: WasExplored(): Invalid arg vertex_index = " << vertex_index << std::endl;
    throw 1;
  }
  const bool not_explored = explored_time_[vertex_index].IsInvalid();
  return not_explored;
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
  size_ = (vertex_number > size_) ? vertex_number : size_;
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
    for (int32_t vertex_index = 0; vertex_index < size_; ++vertex_index) {
      std::cout << ConvertFromIndexToVertexNumber(vertex_index);
      std::cout << " " << explored_time_[vertex_index].Get();
      std::cout << " " << completion_time_[vertex_index].Get() << std::endl;
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
  for (TimeStamp& explored_time : explored_time_) {
    explored_time.Reset();
  }
  for (TimeStamp& completed_time : completion_time_) {
    completed_time.Reset();
  }
}

bool DepthFirstSearch::IsInvalidVertexNumber(const int32_t vertex_number) noexcept {
  return ((vertex_number < 1) || (vertex_number > kMaxVertexNumber));
}

bool DepthFirstSearch::IsInvalidVertexIndex(const int32_t index) const noexcept {
  return ((index < 0) || (index >= size_));
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

int32_t Stack::Pop() {
  if (IsEmpty()) {
    std::cerr << "ERROR: Pop(): stack is empty." << std::endl;
    throw 1;
  }
  --top_position_;
  return values_[top_position_];
}

TimeStamp::TimeStamp() noexcept : time_(-1) {}
TimeStamp::~TimeStamp() noexcept {}

void TimeStamp::Next() {
  if (IsInvalid()) {
    std::cerr << "ERROR: TimeStamp::Next(): Invalid time." << std::endl;
    throw 1;
  }
  ++time_;
}

int32_t TimeStamp::Get() const {
  if (IsInvalid()) {
    std::cerr << "ERROR: TimeStamp::Get(): Invalid time." << std::endl;
    throw 1;
  }
  return time_;
}

void TimeStamp::Set(const int32_t time) {
  if (IsValid()) {
    std::cerr << "ERROR: TimeStamp::Set(): Time was already set." << std::endl;
    throw 1;
  } else if (time < 0) {
    std::cerr << "ERROR: TimeStamp::Set(): Invalid arg time = " << time << std::endl;
    throw 1;
  } else {
    time_ = time;
  }
}

void TimeStamp::Reset() noexcept { time_ = -1; }

bool TimeStamp::IsInvalid() const noexcept { return (time_ < 0); }

bool TimeStamp::IsValid() const noexcept { return (!IsInvalid()); }

}  // namespace ALDS1_11_B_1
