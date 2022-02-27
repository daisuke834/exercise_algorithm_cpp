/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-2. 再帰・分割統治法、全探索(Exhaustive Search)。最上位以外動的メモリを使わないバージョン。
 * 計算時間=O(2^num_of_sources).
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C06_2_ALDS1_5_A_2_exhaustive_search.h"

#include <iostream>
#include <string>

namespace ALDS1_5_A_2 {

void CallExhaustiveSearch(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  ExhaustiveSearch* exhaustive_search = new ExhaustiveSearch();
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
    std::cerr << "ERROR: CallExhaustiveSearch()" << std::endl;
    throw;
  }
  delete exhaustive_search;
}

// ****************************************************

ExhaustiveSearch::ExhaustiveSearch() noexcept {
  sources_.size = 0;
  targets_.size = 0;
}
ExhaustiveSearch::~ExhaustiveSearch() noexcept {}

void ExhaustiveSearch::AddOneSource(const int32_t source) {
  if (sources_.size >= kMaxNumberOfSources) {
    std::cerr << "ERROR: AddOneSource(): sources_ is full." << std::endl;
    throw 1;
  }
  sources_.values[sources_.size] = source;
  ++sources_.size;
}

void ExhaustiveSearch::AddOneTarget(const int32_t target) {
  if (targets_.size >= kMaxNumberOfTargets) {
    std::cerr << "ERROR: AddOneTarget(): targets_ is full." << std::endl;
    throw 1;
  }
  targets_.values[targets_.size] = target;
  ++targets_.size;
}

void ExhaustiveSearch::Check() {
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

bool ExhaustiveSearch::CanBeCreated(const int32_t target, const int32_t start_index_of_source) const {
  bool can_be_created = false;
  if (IsInvalidSourceIndex(start_index_of_source)) {
    std::cerr << "ERROR: CanBeCreated(): Invalid start_index_of_source = " << start_index_of_source << std::endl;
    throw 1;
  }
  const int32_t residual_target = target - sources_.values[start_index_of_source];
  if (residual_target == 0) {
    can_be_created = true;
  } else if (IsValidSourceIndex(start_index_of_source + 1)) {
    if (residual_target > 0) {
      can_be_created = CanBeCreated(residual_target, start_index_of_source + 1);
    }
    if (!can_be_created) {
      can_be_created = CanBeCreated(target, start_index_of_source + 1);
    }
  } else {
    can_be_created = false;
  }

  return can_be_created;
}

bool ExhaustiveSearch::IsInvalidSourceIndex(const int32_t index) const noexcept {
  return ((index < 0) || (index >= sources_.size));
}

bool ExhaustiveSearch::IsValidSourceIndex(const int32_t index) const noexcept { return !IsInvalidSourceIndex(index); }

}  // namespace ALDS1_5_A_2
