/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-6. 探索の応用、最適解の計算。トラックの最大積載量最適化。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C05_6_ALDS1_4_D_allocation.h"

#include <algorithm>
#include <iostream>
#include <string>
namespace ALDS1_4_D {

void CallBaggageAllocation(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  BaggageAllocation* baggage_allocation = new BaggageAllocation();
  try {
    int32_t number_of_baggages;
    int32_t number_of_trucks;
    input_stream >> number_of_baggages >> number_of_trucks;
    for (int32_t index_baggage = 0; index_baggage < number_of_baggages; ++index_baggage) {
      int32_t current_weight;
      input_stream >> current_weight;
      baggage_allocation->AddBaggage(current_weight);
    }
    const int32_t minimum_of_maximum_loading_capacity =
        baggage_allocation->FindMinimumOfMaximumLoadingCapacity(number_of_trucks);
    std::cout << minimum_of_maximum_loading_capacity << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallBaggageAllocation()" << std::endl;
    throw;
  }
  delete baggage_allocation;
}

// ****************************************************
TruckGroup::TruckGroup() noexcept : maximum_loading_capacity_(0), max_number_of_tracks_(0), current_truck_(0) {}
TruckGroup::~TruckGroup() noexcept {}

void TruckGroup::Reset(const int32_t max_number_of_tracks, const int32_t maximum_loading_capacity) {
  max_number_of_tracks_ = max_number_of_tracks;
  maximum_loading_capacity_ = maximum_loading_capacity;
  current_truck_ = 0;
  current_loading_ = 0;
}

bool TruckGroup::LoadOneBaggage(const int32_t weight) {
  if (weight <= 0) {
    std::cerr << "ERROR: LoadOneBaggage(): Invalid weight. " << weight << std::endl;
    throw 1;
  }
  bool loaded_successfully = false;
  if (ExceedingMaxCapacityLimit(weight)) {
    loaded_successfully = false;
  } else if (CanLoadOnCurrentTruck(weight)) {
    current_loading_ += weight;
    loaded_successfully = true;
  } else {
    if (NoAdditionalTruckAvailable()) {
      loaded_successfully = false;
    } else {
      ++current_truck_;
      current_loading_ = weight;
      loaded_successfully = true;
    }
  }
  return loaded_successfully;
}

bool TruckGroup::CanLoadOnCurrentTruck(const int32_t weight) const noexcept {
  return ((current_truck_ < max_number_of_tracks_) && ((current_loading_ + weight) <= maximum_loading_capacity_));
}

bool TruckGroup::NoAdditionalTruckAvailable() const noexcept {
  const int32_t next_index = current_truck_ + 1;
  const int32_t needed_number_of_tracks = next_index + 1;
  return ((needed_number_of_tracks > kMaxNumberOfTrucks) || (needed_number_of_tracks > max_number_of_tracks_));
}

bool TruckGroup::ExceedingMaxCapacityLimit(const int32_t weight) const noexcept {
  return (weight > maximum_loading_capacity_);
}

// ****************************************************

BaggageAllocation::BaggageAllocation() noexcept : truck_group_{}, baggage_group_{} {
  baggage_group_.number_of_baggages = 0;
  baggage_group_.max_weight = 0;
}
BaggageAllocation::~BaggageAllocation() noexcept {}

void BaggageAllocation::AddBaggage(const int32_t current_weight) {
  const int32_t current_index = baggage_group_.number_of_baggages;
  if (current_index >= kMaxNumberOfBaggages) {
    std::cerr << "ERROR: AddBaggage(): Too many baggages " << baggage_group_.number_of_baggages + 1 << std::endl;
    throw 1;
  }
  baggage_group_.weights[current_index] = current_weight;
  baggage_group_.max_weight = std::max(baggage_group_.max_weight, current_weight);
  ++baggage_group_.number_of_baggages;
}

int32_t BaggageAllocation::FindMinimumOfMaximumLoadingCapacity(const int32_t max_number_of_tracks) {
  int32_t minimum_of_maximum_loading_capacity = -1;
  const int32_t initial_maximum_loading_capacity = baggage_group_.max_weight;
  try {
    SearchBound search_bound = CalculateInitialSearchBound(max_number_of_tracks, initial_maximum_loading_capacity);
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      if (SearchFinished(search_bound)) {
        minimum_of_maximum_loading_capacity = GetSearchedValue(search_bound);
        break;
      }
      const int32_t center_value = GetCenterValue(search_bound);
      const bool all_baggages_can_be_carried = SimulateAllBaggagesCanBeCarried(max_number_of_tracks, center_value);
      if (all_baggages_can_be_carried) {
        search_bound.upper_bound = center_value;
      } else {
        search_bound.lower_bound = center_value;
      }
      if (i >= kMaxLoopCount - 1) {
        std::cerr << "ERROR: FindMinimumOfMaximumLoadingCapacity(): Infinite Loop " << std::endl;
        throw 1;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: FindMinimumOfMaximumLoadingCapacity()" << std::endl;
    throw;
  }
  return minimum_of_maximum_loading_capacity;
}

SearchBound BaggageAllocation::CalculateInitialSearchBound(const int32_t max_number_of_tracks,
                                                           const int32_t initial_maximum_loading_capacity) {
  SearchBound search_bound;
  int32_t current_capacity = initial_maximum_loading_capacity;
  for (int32_t i = 0; i < kMaxLoopCount; ++i) {
    const bool all_baggages_can_be_carried = SimulateAllBaggagesCanBeCarried(max_number_of_tracks, current_capacity);
    if (all_baggages_can_be_carried) {
      search_bound.upper_bound = current_capacity;
      search_bound.lower_bound = std::min(current_capacity / 2, 1);
      break;
    } else if (i >= kMaxLoopCount - 1) {
      std::cerr << "ERROR: CalculateInitialSearchBound(): Infinite Loop " << std::endl;
      throw 1;
    } else {
      current_capacity *= 2;
    }
  }
  return search_bound;
}

bool BaggageAllocation::SimulateAllBaggagesCanBeCarried(const int32_t max_number_of_tracks,
                                                        const int32_t maximum_loading_capacity) {
  bool success = false;
  try {
    truck_group_.Reset(max_number_of_tracks, maximum_loading_capacity);
    for (int32_t index_baggage = 0; index_baggage < baggage_group_.number_of_baggages; ++index_baggage) {
      success = truck_group_.LoadOneBaggage(baggage_group_.weights[index_baggage]);
      if (!success) {
        break;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: SimulateAllBaggagesCanBeCarried()" << std::endl;
    throw;
  }
  return success;
}

int32_t BaggageAllocation::GetCenterValue(const SearchBound& search_bound) noexcept {
  const int32_t full_offset = search_bound.upper_bound - search_bound.lower_bound;
  return search_bound.lower_bound + (full_offset / 2);
}

bool BaggageAllocation::SearchFinished(const SearchBound& search_bound) {
  bool search_finished;
  if (search_bound.upper_bound == search_bound.lower_bound + 1) {
    search_finished = true;
  } else if (search_bound.upper_bound <= search_bound.lower_bound) {
    std::cerr << "ERROR: SearchFinished(): Invalid search_bound. upper=" << search_bound.upper_bound
              << ", lower=" << search_bound.lower_bound << std::endl;
    throw 1;
  } else {
    search_finished = false;
  }
  return search_finished;
}

int32_t BaggageAllocation::GetSearchedValue(const SearchBound& search_bound) {
  if (search_bound.upper_bound != search_bound.lower_bound + 1) {
    std::cerr << "ERROR: GetSearchedValue(): Invalid search_bound " << std::endl;
    throw 1;
  }
  return search_bound.upper_bound;
}

}  // namespace ALDS1_4_D
