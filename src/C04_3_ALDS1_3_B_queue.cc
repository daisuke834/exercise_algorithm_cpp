/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-3. データ構造、キュー。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C04_3_ALDS1_3_B_queue.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
namespace ALDS1_3_B {

void CallRoundRobin(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  int32_t number_of_processes;
  int32_t qms;
  input_stream >> number_of_processes >> qms;
  RoundRobin* round_robin = new RoundRobin(qms);
  try {
    for (int32_t process_index = 0; process_index < number_of_processes; ++process_index) {
      std::string process_name;
      int32_t total_processing_time;
      input_stream >> process_name >> total_processing_time;
      round_robin->AddProcess(process_name, total_processing_time);
    }

    while (round_robin->GetCurrentTime() < kMaxTime) {
      round_robin->ComputeOneQuantum();
      if (round_robin->AllProcessWasAlreadyFinished()) {
        break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CallRoundRobin()" << std::endl;
  }
  delete round_robin;
}

Queue::Queue() noexcept : depth_(0), head_(0), indices_{0} {}

Queue::~Queue() noexcept {}

bool Queue::IsEmpty() const noexcept { return (depth_ <= 0); }

bool Queue::IsFull() const noexcept { return (depth_ >= kMaxQueueSize); }

void Queue::Enqueue(const int32_t x) {
  if (IsFull()) {
    std::cerr << "ERROR: Enqueue(): queue is full." << std::endl;
    throw 1;
  }
  const int32_t tail_position = (head_ + depth_) % kMaxQueueSize;
  indices_[tail_position] = x;
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
ProcessGroup::ProcessGroup() noexcept : number_of_process_(0) {}
ProcessGroup::~ProcessGroup() noexcept {}

int32_t ProcessGroup::AddAndGetStoredIndex(const std::string& name, const int32_t total_time) {
  if (number_of_process_ >= kMaxProcessCount) {
    std::cerr << "ERROR: ProcessGroup::AddProcess(): too many processes." << std::endl;
    throw 1;
  }
  const int32_t index_to_store = number_of_process_;
  ++number_of_process_;
  strncpy(processes_[index_to_store].name, name.c_str(), kMaxLengthProcessName);
  processes_[index_to_store].remaining_time = total_time;
  return index_to_store;
}

std::string ProcessGroup::GetProcessNameFromIndex(const int32_t index) const {
  if ((index < 0) && (index >= number_of_process_)) {
    std::cerr << "ERROR: ProcessGroup::GetProcessNameFromIndex(): invalid index." << std::endl;
  }
  return std::string(processes_[index].name);
}

int32_t ProcessGroup::ComputeAndReturnComputedTime(const int32_t index, const int32_t compute_time) {
  int32_t computed_time = 0;
  if ((index < 0) && (index >= number_of_process_)) {
    std::cerr << "ERROR: ProcessGroup::ComputeOneQuantum(): invalid index." << std::endl;
    throw 1;
  } else if (processes_[index].remaining_time == 0) {
    std::cerr << "ERROR: ProcessGroup::ComputeOneQuantum(): already finished." << std::endl;
    throw 1;
  } else {
    const int32_t previous_remaining_time = processes_[index].remaining_time;
    processes_[index].remaining_time = std::max(0, previous_remaining_time - compute_time);
    computed_time = previous_remaining_time - processes_[index].remaining_time;
  }
  return computed_time;
}

bool ProcessGroup::AlreadyFinished(const int32_t index) const {
  if ((index < 0) && (index >= number_of_process_)) {
    std::cerr << "ERROR: ProcessGroup::AlreadyFinished(): invalid index." << std::endl;
  }
  return (processes_[index].remaining_time == 0);
}

// ******************************
RoundRobin::RoundRobin(const int32_t quantum_time) noexcept : quantum_(quantum_time), current_time_(0) {}
RoundRobin::~RoundRobin() noexcept {}

void RoundRobin::AddProcess(const std::string& name, const int32_t total_time) {
  try {
    const int32_t stored_index = processes_.AddAndGetStoredIndex(name, total_time);
    process_queue_.Enqueue(stored_index);
  } catch (...) {
    std::cerr << "ERROR: AddProcess()" << std::endl;
    throw;
  }
}

void RoundRobin::ComputeOneQuantum() {
  try {
    const int32_t process_index = process_queue_.Dequeue();
    const int32_t computed_time = processes_.ComputeAndReturnComputedTime(process_index, quantum_);
    current_time_ += computed_time;
    if (processes_.AlreadyFinished(process_index)) {
      std::cout << processes_.GetProcessNameFromIndex(process_index) << " " << current_time_ << std::endl;
    } else {
      process_queue_.Enqueue(process_index);
    }
  } catch (...) {
    std::cerr << "ERROR: ComputeOneQuantum()" << std::endl;
    throw;
  }
}

int32_t RoundRobin::GetCurrentTime() const noexcept { return current_time_; }

bool RoundRobin::AllProcessWasAlreadyFinished() const { return process_queue_.IsEmpty(); }

}  // namespace ALDS1_3_B
