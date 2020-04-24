/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-3. データ構造、キューのテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "src/C04_3_ALDS1_3_B_queue.h"

namespace ALDS1_3_B {
constexpr int32_t kQuantumTime = 100;

class Test_ALDS1_3_B : public ::testing::Test {
 protected:
  Queue *queue_;
  ProcessGroup *process_group_;
  RoundRobin *round_robin_;

  virtual void SetUp() {
    queue_ = new Queue();
    process_group_ = new ProcessGroup();
    round_robin_ = new RoundRobin(kQuantumTime);
  }
  virtual void TearDown() {
    delete queue_;
    delete process_group_;
    delete round_robin_;
  }
};

TEST_F(Test_ALDS1_3_B, Queue_1) {
  ASSERT_TRUE(queue_->IsEmpty());
  ASSERT_FALSE(queue_->IsFull());
  ASSERT_ANY_THROW(queue_->Dequeue());

  constexpr int32_t kInput = 2;
  queue_->Enqueue(kInput);

  ASSERT_FALSE(queue_->IsEmpty());
  ASSERT_FALSE(queue_->IsFull());

  const int32_t result = queue_->Dequeue();
  ASSERT_EQ(kInput, result);
  ASSERT_TRUE(queue_->IsEmpty());
  ASSERT_FALSE(queue_->IsFull());
  ASSERT_ANY_THROW(queue_->Dequeue());
}

TEST_F(Test_ALDS1_3_B, Queue_2) {
  ASSERT_TRUE(queue_->IsEmpty());

  constexpr int32_t kInput_1 = 2;
  queue_->Enqueue(kInput_1);
  constexpr int32_t kInput_2 = 15;
  queue_->Enqueue(kInput_2);

  ASSERT_FALSE(queue_->IsEmpty());
  ASSERT_FALSE(queue_->IsFull());

  const int32_t result_1 = queue_->Dequeue();
  const int32_t result_2 = queue_->Dequeue();
  ASSERT_EQ(kInput_1, result_1);
  ASSERT_EQ(kInput_2, result_2);
  ASSERT_TRUE(queue_->IsEmpty());
}

TEST_F(Test_ALDS1_3_B, Queue_full) {
  ASSERT_TRUE(queue_->IsEmpty());
  ASSERT_FALSE(queue_->IsFull());

  for (int32_t index = 0; index < kMaxQueueSize; ++index) {
    const int32_t input_value = index;
    queue_->Enqueue(input_value);
    const int32_t expected_depth = index + 1;
    ASSERT_EQ(expected_depth, queue_->depth_);
  }

  ASSERT_FALSE(queue_->IsEmpty());
  ASSERT_TRUE(queue_->IsFull());
  ASSERT_ANY_THROW(queue_->Enqueue(0));

  for (int32_t index = 0; index < kMaxQueueSize; ++index) {
    const int32_t answer = index;
    const int32_t result = queue_->Dequeue();
    ASSERT_EQ(answer, result);
  }

  ASSERT_TRUE(queue_->IsEmpty());
}

TEST_F(Test_ALDS1_3_B, ProcessGroup_Add_normal) {
  int32_t count = 0;
  const int32_t expected_index_1 = count;
  const std::string name_1("abcdefg");
  constexpr int32_t kProcessingTime_1 = 120;
  const int32_t stored_index_1 = process_group_->AddAndGetStoredIndex(name_1, kProcessingTime_1);
  ASSERT_EQ(expected_index_1, stored_index_1);
  ++count;
  ASSERT_EQ(count, process_group_->number_of_process_);

  const int32_t expected_index_2 = count;
  const std::string name_2("zzzzzzzzz");
  constexpr int32_t kProcessingTime_2 = 230;
  const int32_t stored_index_2 = process_group_->AddAndGetStoredIndex(name_2, kProcessingTime_2);
  ASSERT_EQ(expected_index_2, stored_index_2);
  ++count;
  ASSERT_EQ(count, process_group_->number_of_process_);

  ASSERT_STREQ(name_1.c_str(), process_group_->GetProcessNameFromIndex(stored_index_1).c_str());
  ASSERT_EQ(kProcessingTime_1, process_group_->processes_[stored_index_1].remaining_time);

  ASSERT_STREQ(name_2.c_str(), process_group_->GetProcessNameFromIndex(stored_index_2).c_str());
  ASSERT_EQ(kProcessingTime_2, process_group_->processes_[stored_index_2].remaining_time);
}

TEST_F(Test_ALDS1_3_B, ProcessGroup_Add_abnormal) {
  const std::string process_name("abcdefg");
  constexpr int32_t kProcessingTime = 120;
  for (int32_t expected_index = 0; expected_index < kMaxProcessCount; ++expected_index) {
    const int32_t stored_index = process_group_->AddAndGetStoredIndex(process_name, kProcessingTime);
    ASSERT_EQ(expected_index, stored_index);
    const int32_t expected_count = expected_index + 1;
    ASSERT_EQ(expected_count, process_group_->number_of_process_);
    ASSERT_STREQ(process_name.c_str(), process_group_->GetProcessNameFromIndex(stored_index).c_str());
    ASSERT_EQ(kProcessingTime, process_group_->processes_[stored_index].remaining_time);
  }
  ASSERT_EQ(kMaxProcessCount, process_group_->number_of_process_);
  ASSERT_ANY_THROW(process_group_->AddAndGetStoredIndex(process_name, kProcessingTime));
}

TEST_F(Test_ALDS1_3_B, ProcessGroup_compute) {
  const std::string name("abcdefg");
  constexpr int32_t kTotalProcessingTime = 520;
  constexpr int32_t kTotalComputeCount = 6;
  const int32_t stored_index = process_group_->AddAndGetStoredIndex(name, kTotalProcessingTime);
  ASSERT_EQ(kTotalProcessingTime, process_group_->processes_[stored_index].remaining_time);

  for (int32_t index_compute = 0; index_compute < kTotalComputeCount; ++index_compute) {
    const int32_t actual_computed_time = process_group_->ComputeAndReturnComputedTime(stored_index, kQuantumTime);
    if (index_compute == kTotalComputeCount - 1) {
      ASSERT_EQ(20, actual_computed_time);
      ASSERT_TRUE(process_group_->AlreadyFinished(stored_index));
    } else {
      ASSERT_EQ(kQuantumTime, actual_computed_time);
      ASSERT_FALSE(process_group_->AlreadyFinished(stored_index));
    }
  }
  ASSERT_TRUE(process_group_->AlreadyFinished(stored_index));

  ASSERT_ANY_THROW(process_group_->ComputeAndReturnComputedTime(stored_index, kQuantumTime));
}
// ***************************
TEST_F(Test_ALDS1_3_B, RoundRobin_Add_normal) {
  const std::string name_1("abcdefg");
  constexpr int32_t kProcessingTime_1 = 520;
  constexpr int32_t kTotalComputeCount = 6;
  round_robin_->AddProcess(name_1, kProcessingTime_1);

  testing::internal::CaptureStdout();
  for (int32_t index_compute = 0; index_compute < kTotalComputeCount; ++index_compute) {
    round_robin_->ComputeOneQuantum();
    int32_t expected_current_time;
    if (index_compute == kTotalComputeCount - 1) {
      expected_current_time = kProcessingTime_1;
    } else {
      expected_current_time = (index_compute + 1) * kQuantumTime;
    }
    ASSERT_EQ(expected_current_time, round_robin_->GetCurrentTime());
  }
  std::ostringstream answer;
  answer << name_1 << " " << kProcessingTime_1 << std::endl;
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(round_robin_->AllProcessWasAlreadyFinished());
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

/*
TEST_F(Test_ALDS1_3_B, RoundRobin_Add_max) {
  bool finished_correctly = false;
  std::string name_pre("p");
  for (int32_t process_index = 0; process_index < kMaxProcessCount; ++process_index) {
    constexpr int32_t kProcessingTime = 1;
    round_robin_->AddProcess(name_pre + std::to_string(process_index), kProcessingTime);
  }

  while (round_robin_->GetCurrentTime() < kMaxTime) {
    round_robin_->ComputeOneQuantum();
    if (round_robin_->AllProcessWasAlreadyFinished()) {
      finished_correctly = true;
      break;
    }
  }
  ASSERT_TRUE(finished_correctly);
}
*/

TEST_F(Test_ALDS1_3_B, CallRoundRobin) {
  std::ostringstream answer;
  answer << "p2 180" << std::endl;
  answer << "p5 400" << std::endl;
  answer << "p1 450" << std::endl;
  answer << "p3 550" << std::endl;
  answer << "p4 800" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5 100" << std::endl;
  input_stream << "p1 150" << std::endl;
  input_stream << "p2 80" << std::endl;
  input_stream << "p3 200" << std::endl;
  input_stream << "p4 350" << std::endl;
  input_stream << "p5 20" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallRoundRobin(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_3_B
