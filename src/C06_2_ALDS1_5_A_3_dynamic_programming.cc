/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-2. ALDS1_5_A_3を動的計画法(Dynamic Programming, DP)を用いて再実装。
 * 計算時間=O(num_of_values * num_of_sources), 追加作業記憶領域=O(num_of_targets * num_of_sources).
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C06_2_ALDS1_5_A_3_dynamic_programming.h"
#include <iostream>
#include <string>

namespace ALDS1_5_A_3 {

void CallDynamicProgramming(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  DynamicProgramming *exhaustive_search = new DynamicProgramming();
  try {
    int32_t number_of_sources;
    input_stream >> number_of_sources;
    for (int32_t index_source = 0; index_source < number_of_sources; ++index_source) {
      int32_t source_value;
      input_stream >> source_value;
      exhaustive_search->AddOneSource(source_value);
    }

    int32_t number_of_targets;
    input_stream >> number_of_targets;
    for (int32_t index_target = 0; index_target < number_of_targets; ++index_target) {
      int32_t target_value;
      input_stream >> target_value;
      exhaustive_search->AddOneTarget(target_value);
    }

    exhaustive_search->Check();
  } catch (...) {
    std::cerr << "ERROR: CallDynamicProgramming()" << std::endl;
    throw;
  }
  delete exhaustive_search;
}

// ****************************************************

DynamicProgramming::DynamicProgramming() noexcept {
  sources_.size = 0;
  targets_.size = 0;
}
DynamicProgramming::~DynamicProgramming() noexcept {}

void DynamicProgramming::AddOneSource(const int32_t source) {
  if (sources_.size >= kMaxNumberOfSources) {
    std::cerr << "ERROR: AddOneSource(): sources_ is full." << std::endl;
    throw 1;
  }
  sources_.values[sources_.size] = source;
  ++sources_.size;
}

void DynamicProgramming::AddOneTarget(const int32_t target) {
  if (targets_.size >= kMaxNumberOfTargets) {
    std::cerr << "ERROR: AddOneTarget(): targets_ is full." << std::endl;
    throw 1;
  }
  targets_.values[targets_.size] = target;
  ++targets_.size;
}

void DynamicProgramming::Check() {
  try {
    for (int32_t index_target = 0; index_target < targets_.size; ++index_target) {
      const int32_t target = targets_.values[index_target];
      bool can_be_created = CanBeCreated(target, 0);
      if (can_be_created) {
        std::cout << "yes" << std::endl;
      } else {
        std::cout << "no" << std::endl;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: Check()" << std::endl;
    throw;
  }
}

bool DynamicProgramming::CanBeCreated(const int32_t target, const int32_t start_index_of_source) {
  if (IsInvalidSourceIndex(start_index_of_source)) {
    std::cerr << "ERROR: CanBeCreated(): Invalid start_index_of_source = " << start_index_of_source << std::endl;
    throw 1;
  }
  if (AlreadyCalculated(target, start_index_of_source)) {
    // DO NOTHING
  } else {
    const int32_t residual_target = target - sources_.values[start_index_of_source];
    if (residual_target == 0) {
      SetResult(target, start_index_of_source, true);
    } else if (IsValidSourceIndex(start_index_of_source + 1)) {
      bool can_be_created = false;
      if (residual_target > 0) {
        can_be_created = CanBeCreated(residual_target, start_index_of_source + 1);
      }
      if (!can_be_created) {
        can_be_created = CanBeCreated(target, start_index_of_source + 1);
      }
      SetResult(target, start_index_of_source, can_be_created);
    } else {
      SetResult(target, start_index_of_source, false);
    }
  }
  return LoadCanBeCreated(target, start_index_of_source);
}

bool DynamicProgramming::LoadCanBeCreated(const int32_t target, const int32_t start_index_of_source) const {
  if (IsInvalidValue(target)) {
    std::cerr << "ERROR: CanBeCreated(): Invalid target = " << target << std::endl;
    throw 1;
  } else if (IsInvalidSourceIndex(start_index_of_source)) {
    std::cerr << "ERROR: CanBeCreated(): Invalid start_index_of_source = " << start_index_of_source << std::endl;
    throw 1;
  } else {
    // DO NOTHING
  }
  const bool can_be_created = look_up_table_[target][start_index_of_source].can_be_created;
  return can_be_created;
}

bool DynamicProgramming::AlreadyCalculated(const int32_t target, const int32_t start_index_of_source) const {
  if (IsInvalidValue(target)) {
    std::cerr << "ERROR: AlreadyCalculated(): Invalid target = " << target << std::endl;
    throw 1;
  } else if ((start_index_of_source < 0) || (start_index_of_source >= kMaxNumberOfSources)) {
    std::cerr << "ERROR: AlreadyCalculated(): Invalid start_index_of_source = " << start_index_of_source << std::endl;
    throw 1;
  } else {
    // DO NOTHING
  }
  const bool calculated = look_up_table_[target][start_index_of_source].calculated;
  return calculated;
}

void DynamicProgramming::SetResult(const int32_t target, const int32_t start_index_of_source,
                                   const bool can_be_created) {
  if (IsInvalidValue(target)) {
    std::cerr << "ERROR: SetResult(): Invalid target = " << target << std::endl;
    throw 1;
  } else if ((start_index_of_source < 0) || (start_index_of_source >= kMaxNumberOfSources)) {
    std::cerr << "ERROR: SetResult(): Invalid start_index_of_source = " << start_index_of_source << std::endl;
    throw 1;
  } else {
    look_up_table_[target][start_index_of_source].can_be_created = can_be_created;
    look_up_table_[target][start_index_of_source].calculated = true;
  }
}

bool DynamicProgramming::IsInvalidSourceIndex(const int32_t index) const noexcept {
  return ((index < 0) || (index >= sources_.size));
}

bool DynamicProgramming::IsValidSourceIndex(const int32_t index) const noexcept {
  return !IsInvalidSourceIndex(index);
}

bool DynamicProgramming::IsInvalidValue(const int32_t value) const noexcept {
  return ((value < kMinValue) || (value > kMaxValue));
}

}  // namespace ALDS1_5_A_3
