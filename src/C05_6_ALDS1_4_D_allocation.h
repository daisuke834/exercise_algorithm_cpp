/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-6. 探索の応用、最適解の計算。トラックの最大積載量最適化。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C05_6_ALDS1_4_D_ALLOCATION_H_
#define SRC_C05_6_ALDS1_4_D_ALLOCATION_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_4_D {

void CallBaggageAllocation(std::istream &input_stream);

constexpr int32_t kMaxNumberOfBaggages = 100000;
constexpr int32_t kMaxNumberOfTrucks = 100000;
constexpr int32_t kMaxNumberOfWeightOfBaggage = 10000;
constexpr int32_t kMaxLoopCount = 10000;

struct BaggageGroup {
  int32_t number_of_baggages{0};
  int32_t weights[kMaxNumberOfBaggages];
  int32_t max_weight;
};

class TruckGroup {
 public:
  TruckGroup() noexcept;
  ~TruckGroup() noexcept;
  void Reset(const int32_t max_number_of_tracks, const int32_t maximum_loading_capacity);
  bool LoadOneBaggage(const int32_t weight);
  bool CanLoadOnCurrentTruck(const int32_t weight) const noexcept;
  bool NoAdditionalTruckAvailable() const noexcept;
  bool ExceedingMaxCapacityLimit(const int32_t weight) const noexcept;

 private:
  TruckGroup(const TruckGroup &obj) = delete;
  TruckGroup &operator=(const TruckGroup &rhs) = delete;
  TruckGroup(TruckGroup &&obj) = delete;
  TruckGroup &operator=(TruckGroup &&rhs) = delete;

 private:
  int32_t maximum_loading_capacity_;
  int32_t max_number_of_tracks_;
  int32_t current_truck_;
  int32_t current_loading_;

 private:
  FRIEND_TEST(Test_ALDS1_4_D, TruckGroup_Reset);                       // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_4_D, TruckGroup_NoAdditionalTruckAvailable);  // Should be removed from production code
};

struct SearchBound {
  int32_t upper_bound{0};
  int32_t lower_bound{0};
};

class BaggageAllocation {
 public:
  BaggageAllocation() noexcept;
  ~BaggageAllocation() noexcept;
  void AddBaggage(const int32_t current_weight);
  int32_t FindMinimumOfMaximumLoadingCapacity(const int32_t max_number_of_tracks);
  bool SimulateAllBaggagesCanBeCarried(const int32_t max_number_of_tracks, const int32_t maximum_loading_capacity);
  SearchBound CalculateInitialSearchBound(const int32_t max_number_of_tracks,
                                          const int32_t initial_maximum_loading_capacity);

 private:
  BaggageAllocation(const BaggageAllocation &obj) = delete;
  BaggageAllocation &operator=(const BaggageAllocation &obj) = delete;
  BaggageAllocation(BaggageAllocation &&obj) = delete;
  BaggageAllocation &operator=(BaggageAllocation &&obj) = delete;

  static int32_t GetCenterValue(const SearchBound &search_bound) noexcept;
  static bool SearchFinished(const SearchBound &search_bound);
  int32_t GetSearchedValue(const SearchBound &search_bound);

 private:
  TruckGroup truck_group_;
  BaggageGroup baggage_group_;

 private:
  FRIEND_TEST(Test_ALDS1_4_D, AddBaggage);  // Should be removed from production code
};

}  // namespace ALDS1_4_D

#endif  // SRC_C05_6_ALDS1_4_D_ALLOCATION_H_
