/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-2. 探索、線形探索。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "2_ALDS1_4_A_linear_search.h"

#include <iostream>
#include <string>
namespace ALDS1_4_A {

void CallLinearSearch(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  LinearSearch* linear_search = new LinearSearch();
  try {
    int32_t number_of_sources;
    input_stream >> number_of_sources;
    for (int32_t index_source = 0; index_source < number_of_sources; ++index_source) {
      int32_t source_value;
      input_stream >> source_value;
      linear_search->AddOneSource(source_value);
    }

    int32_t number_of_targets;
    input_stream >> number_of_targets;
    for (int32_t index_target = 0; index_target < number_of_targets; ++index_target) {
      int32_t target_value;
      input_stream >> target_value;
      linear_search->AddOneTarget(target_value);
    }
    const int32_t result = linear_search->SearchTarget();
    std::cout << result << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallLinearSearch()" << std::endl;
  }
  delete linear_search;
}

LinearSearch::LinearSearch() noexcept : sources_{}, targets_{} {}
LinearSearch::~LinearSearch() noexcept {}

void LinearSearch::AddOneSource(const int32_t source) {
  if (sources_.size >= kMaxNumberOfSources) {
    std::cerr << "ERROR: sources_ is full." << std::endl;
    throw 1;
  }
  sources_.values_[sources_.size] = source;
  ++sources_.size;
}
void LinearSearch::AddOneTarget(const int32_t target) {
  if (targets_.size >= kMaxNumberOfTargets) {
    std::cerr << "ERROR: targets_ is full." << std::endl;
    throw 1;
  }
  targets_.values_[targets_.size] = target;
  ++targets_.size;
}

int32_t LinearSearch::SearchTarget() const {
  int32_t count = 0;
  for (int32_t index_target = 0; index_target < targets_.size; ++index_target) {
    if (TargetIsIncludedInSource(index_target)) {
      ++count;
    }
  }
  return count;
}

bool LinearSearch::TargetIsIncludedInSource(const int32_t index_target) const {
  bool is_included = false;
  if (index_target < 0 || index_target >= targets_.size) {
    std::cerr << "ERROR: TargetIsIncludedInSource(): invalid index_target." << std::endl;
    throw 1;
  }
  const int32_t target_value = targets_.values_[index_target];
  for (int32_t index_source = 0; index_source < sources_.size; ++index_source) {
    if (sources_.values_[index_source] == target_value) {
      is_included = true;
      break;
    }
  }
  return is_included;
}

}  // namespace ALDS1_4_A
