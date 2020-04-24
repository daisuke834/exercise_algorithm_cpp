/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-3. データ構造、キュー。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C04_3_ALDS1_3_B_QUEUE_H_
#define SRC_C04_3_ALDS1_3_B_QUEUE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_3_B {

constexpr int32_t kMaxQueueSize = 100000;
constexpr int32_t kMaxProcessCount = kMaxQueueSize;
constexpr int32_t kMaxLengthProcessName = 10;
constexpr int32_t kMaxTime = 1000000;

void CallRoundRobin(std::istream &input_stream);

class Queue {
 public:
  Queue() noexcept;
  ~Queue() noexcept;
  void Enqueue(const int32_t x);
  int32_t Dequeue();
  bool IsEmpty() const noexcept;
  bool IsFull() const noexcept;

 private:
  Queue(const Queue &obj) = delete;
  Queue &operator=(const Queue &rhs) = delete;
  Queue(Queue &&obj) = delete;
  Queue &operator=(Queue &&rhs) = delete;

  static int32_t GetNextPosition(const int32_t current_position) noexcept;

 private:
  int32_t depth_;
  int32_t head_;
  int32_t indices_[kMaxQueueSize];  //!< DBへの参照インデックス

 private:
  FRIEND_TEST(Test_ALDS1_3_B, Queue_full);  // Should be removed from production code
};

struct Process {
  char name[kMaxLengthProcessName + 1];
  int32_t remaining_time{0};
};

class ProcessGroup {
 public:
  ProcessGroup() noexcept;
  ~ProcessGroup() noexcept;
  int32_t AddAndGetStoredIndex(const std::string &name, const int32_t total_time);
  std::string GetProcessNameFromIndex(const int32_t index) const;
  int32_t ComputeAndReturnComputedTime(const int32_t index, const int32_t compute_time);
  bool AlreadyFinished(const int32_t index) const;

 private:
  ProcessGroup(const ProcessGroup &obj) = delete;
  ProcessGroup &operator=(const ProcessGroup &obj) = delete;
  ProcessGroup(ProcessGroup &&obj) = delete;
  ProcessGroup &operator=(ProcessGroup &&obj) = delete;

 private:
  int32_t number_of_process_;
  Process processes_[kMaxProcessCount];

 private:
  FRIEND_TEST(Test_ALDS1_3_B, ProcessGroup_Add_normal);    // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_3_B, ProcessGroup_Add_abnormal);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_3_B, ProcessGroup_compute);       // Should be removed from production code
};

class RoundRobin {
 public:
  explicit RoundRobin(const int32_t quantum_time) noexcept;
  ~RoundRobin() noexcept;
  void AddProcess(const std::string &name, const int32_t total_time);
  void ComputeOneQuantum();
  void Load(std::istream &input_stream);
  int32_t GetCurrentTime() const noexcept;
  bool AllProcessWasAlreadyFinished() const;

 private:
  RoundRobin() = delete;
  RoundRobin(const RoundRobin &obj) = delete;
  RoundRobin &operator=(const RoundRobin &obj) = delete;
  RoundRobin(RoundRobin &&obj) = delete;
  RoundRobin &operator=(RoundRobin &&obj) = delete;

 private:
  const int32_t quantum_;
  int32_t current_time_;
  Queue process_queue_;
  ProcessGroup processes_;
};

}  // namespace ALDS1_3_B
#endif  // SRC_C04_3_ALDS1_3_B_QUEUE_H_
