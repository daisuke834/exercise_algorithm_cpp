/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-6. 探索の応用、最適解の計算。トラックの最大積載量最適化。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C05_6_ALDS1_4_D_allocation.h"

namespace ALDS1_4_D {

class Test_ALDS1_4_D : public ::testing::Test {
 protected:
  BaggageAllocation *baggage_allocation_;
  virtual void SetUp() {
    baggage_allocation_ = new BaggageAllocation();
  }
  virtual void TearDown() {
    delete baggage_allocation_;
  }
};

TEST_F(Test_ALDS1_4_D, CallBaggageAllocation) {
  std::ostringstream answer;
  answer << "10" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5 3" << std::endl;
  input_stream << "8" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "7" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "9" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBaggageAllocation(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_4_D, AddBaggage) {
  baggage_allocation_->AddBaggage(8);
  baggage_allocation_->AddBaggage(1);
  baggage_allocation_->AddBaggage(7);
  baggage_allocation_->AddBaggage(3);
  baggage_allocation_->AddBaggage(9);
  constexpr int32_t kNumberOfBaggages = 5;
  ASSERT_EQ(kNumberOfBaggages, baggage_allocation_->baggage_group_.number_of_baggages);
  ASSERT_EQ(9, baggage_allocation_->baggage_group_.max_weight);
  int32_t index_baggage = 0;
  ASSERT_EQ(8, baggage_allocation_->baggage_group_.weights[index_baggage++]);
  ASSERT_EQ(1, baggage_allocation_->baggage_group_.weights[index_baggage++]);
  ASSERT_EQ(7, baggage_allocation_->baggage_group_.weights[index_baggage++]);
  ASSERT_EQ(3, baggage_allocation_->baggage_group_.weights[index_baggage++]);
  ASSERT_EQ(9, baggage_allocation_->baggage_group_.weights[index_baggage++]);
}

TEST_F(Test_ALDS1_4_D, FindMinimumOfMaximumLoadingCapacity) {
  baggage_allocation_->AddBaggage(8);
  baggage_allocation_->AddBaggage(1);
  baggage_allocation_->AddBaggage(7);
  baggage_allocation_->AddBaggage(3);
  baggage_allocation_->AddBaggage(9);

  constexpr int32_t KNumberOfTrucks = 3;
  const int32_t found_result = baggage_allocation_->FindMinimumOfMaximumLoadingCapacity(KNumberOfTrucks);
  ASSERT_EQ(10, found_result);
}

TEST_F(Test_ALDS1_4_D, SimulateAllBaggagesCanBeCarried) {
  baggage_allocation_->AddBaggage(8);
  baggage_allocation_->AddBaggage(1);
  baggage_allocation_->AddBaggage(7);
  baggage_allocation_->AddBaggage(3);
  baggage_allocation_->AddBaggage(9);

  constexpr int32_t KNumberOfTrucks = 3;
  const bool result_1 = baggage_allocation_->SimulateAllBaggagesCanBeCarried(KNumberOfTrucks, 1);
  ASSERT_FALSE(result_1);

  const bool result_2 = baggage_allocation_->SimulateAllBaggagesCanBeCarried(KNumberOfTrucks, 2);
  ASSERT_FALSE(result_2);

  const bool result_7 = baggage_allocation_->SimulateAllBaggagesCanBeCarried(KNumberOfTrucks, 7);
  ASSERT_FALSE(result_7);

  const bool result_8 = baggage_allocation_->SimulateAllBaggagesCanBeCarried(KNumberOfTrucks, 8);
  ASSERT_FALSE(result_8);

  const bool result_9 = baggage_allocation_->SimulateAllBaggagesCanBeCarried(KNumberOfTrucks, 9);
  ASSERT_FALSE(result_9);

  const bool result_10 = baggage_allocation_->SimulateAllBaggagesCanBeCarried(KNumberOfTrucks, 10);
  ASSERT_TRUE(result_10);

  const bool result_11 = baggage_allocation_->SimulateAllBaggagesCanBeCarried(KNumberOfTrucks, 11);
  ASSERT_TRUE(result_11);
}

TEST_F(Test_ALDS1_4_D, TruckGroup_Reset) {
  TruckGroup truck_group;
  constexpr int32_t kInvalid = 29384;
  truck_group.maximum_loading_capacity_ = kInvalid;
  truck_group.max_number_of_tracks_ = kInvalid;
  truck_group.current_truck_ = kInvalid;
  truck_group.current_loading_ = kInvalid;

  constexpr int32_t KNumberOfTrucks = 3;
  constexpr int32_t kMaxLoadingCapacity = 3;
  truck_group.Reset(KNumberOfTrucks, kMaxLoadingCapacity);

  ASSERT_EQ(kMaxLoadingCapacity, truck_group.maximum_loading_capacity_);
  ASSERT_EQ(KNumberOfTrucks, truck_group.max_number_of_tracks_);
  ASSERT_EQ(0, truck_group.current_truck_);
  ASSERT_EQ(0, truck_group.current_loading_);
}

TEST_F(Test_ALDS1_4_D, TruckGroup_ExceedingMaxCapacityLimit) {
  TruckGroup truck_group;
  constexpr int32_t KNumberOfTrucks = 3;
  constexpr int32_t kMaxLoadingCapacity = 3;
  truck_group.Reset(KNumberOfTrucks, kMaxLoadingCapacity);

  ASSERT_FALSE(truck_group.ExceedingMaxCapacityLimit(kMaxLoadingCapacity));
  ASSERT_TRUE(truck_group.ExceedingMaxCapacityLimit(kMaxLoadingCapacity + 1));
}

TEST_F(Test_ALDS1_4_D, TruckGroup_CanLoadOnCurrentTruck_1) {
  TruckGroup truck_group;
  constexpr int32_t KNumberOfTrucks = 3;
  constexpr int32_t kMaxLoadingCapacity = 3;
  truck_group.Reset(KNumberOfTrucks, kMaxLoadingCapacity);

  ASSERT_TRUE(truck_group.CanLoadOnCurrentTruck(kMaxLoadingCapacity));
  ASSERT_FALSE(truck_group.CanLoadOnCurrentTruck(kMaxLoadingCapacity + 1));
}

TEST_F(Test_ALDS1_4_D, TruckGroup_CanLoadOnCurrentTruck_2) {
  TruckGroup truck_group;
  constexpr int32_t KNumberOfTrucks = 0;
  constexpr int32_t kMaxLoadingCapacity = 3;
  truck_group.Reset(KNumberOfTrucks, kMaxLoadingCapacity);

  ASSERT_FALSE(truck_group.CanLoadOnCurrentTruck(kMaxLoadingCapacity));
  ASSERT_FALSE(truck_group.CanLoadOnCurrentTruck(kMaxLoadingCapacity + 1));
}

TEST_F(Test_ALDS1_4_D, TruckGroup_NoAdditionalTruckAvailable) {
  TruckGroup truck_group;
  constexpr int32_t kMaxLoadingCapacity = 3;

  int32_t number_of_tracks = 0;
  truck_group.Reset(number_of_tracks, kMaxLoadingCapacity);
  ASSERT_TRUE(truck_group.NoAdditionalTruckAvailable());

  number_of_tracks = 3;
  truck_group.Reset(number_of_tracks, kMaxLoadingCapacity);
  ASSERT_FALSE(truck_group.NoAdditionalTruckAvailable());
}

TEST_F(Test_ALDS1_4_D, TruckGroup_LoadOneBaggage_1) {
  TruckGroup truck_group;
  constexpr int32_t KNumberOfTrucks = 3;
  constexpr int32_t kMaxLoadingCapacity = 3;
  truck_group.Reset(KNumberOfTrucks, kMaxLoadingCapacity);

  ASSERT_ANY_THROW(truck_group.LoadOneBaggage(0));
}

TEST_F(Test_ALDS1_4_D, TruckGroup_LoadOneBaggage_2) {
  TruckGroup truck_group;
  constexpr int32_t KNumberOfTrucks = 0;
  constexpr int32_t kMaxLoadingCapacity = 3;
  truck_group.Reset(KNumberOfTrucks, kMaxLoadingCapacity);

  ASSERT_FALSE(truck_group.LoadOneBaggage(3));
}

}  // namespace ALDS1_4_D
