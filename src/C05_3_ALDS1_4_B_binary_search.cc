/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-3. 探索、二分探索。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C05_3_ALDS1_4_B_binary_search.h"
#include <iostream>
#include <string>
namespace ALDS1_4_B {

void CallBinarySearch(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  BinarySearch *binary_search = new BinarySearch();
  try {
    int32_t number_of_sources;
    input_stream >> number_of_sources;
    for (int32_t index_source = 0; index_source < number_of_sources; ++index_source) {
      int32_t source_value;
      input_stream >> source_value;
      binary_search->AddOneSource(source_value);
    }

    int32_t number_of_targets;
    input_stream >> number_of_targets;
    for (int32_t index_target = 0; index_target < number_of_targets; ++index_target) {
      int32_t target_value;
      input_stream >> target_value;
      binary_search->AddOneTarget(target_value);
    }
    const int32_t result = binary_search->SearchTarget();
    std::cout << result << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallBinarySearch()" << std::endl;
  }
  delete binary_search;
}

BinarySearch::BinarySearch() noexcept : sources_{}, targets_{} {
  sources_.size = 0;
  targets_.size = 0;
}
BinarySearch::~BinarySearch() noexcept {}

void BinarySearch::AddOneSource(const int32_t source) {
  if (sources_.size >= kMaxNumberOfSources) {
    std::cerr << "ERROR: sources_ is full." << std::endl;
    throw 1;
  }
  sources_.values[sources_.size] = source;
  ++sources_.size;
}
void BinarySearch::AddOneTarget(const int32_t target) {
  if (targets_.size >= kMaxNumberOfTargets) {
    std::cerr << "ERROR: targets_ is full." << std::endl;
    throw 1;
  }
  targets_.values[targets_.size] = target;
  ++targets_.size;
}

int32_t BinarySearch::SearchTarget() const {
  int32_t count = 0;
  for (int32_t index_target = 0; index_target < targets_.size; ++index_target) {
    if (TargetIsIncludedInSource(index_target)) {
      ++count;
    }
  }
  return count;
}

bool BinarySearch::TargetIsIncludedInSource(const int32_t index_target) const {
  bool is_included = false;
  if (index_target < 0 || index_target >= targets_.size) {
    std::cerr << "ERROR: TargetIsIncludedInSource(): invalid index_target." << std::endl;
    throw 1;
  }
  const int32_t target_value = targets_.values[index_target];
  int32_t start_index = 0;
  int32_t end_index = sources_.size - 1;
  bool loop_end = false;
  for (int32_t i = 0; i < sources_.size; ++i) {  // loop guard
    const int32_t index_center = GetCenterIndex(start_index, end_index);
    const TargetPosition position = GetTargetPosition(target_value, index_center);
    switch (position) {
      case TargetPosition::kCenter:
        is_included = true;
        loop_end = true;
        break;
      case TargetPosition::kLeftSide:
        if (index_center <= 0) {
          loop_end = true;
        } else if (index_center - 1 < start_index) {
          loop_end = true;
        } else {
          end_index = index_center - 1;
        }
        break;
      case TargetPosition::kRightSide:
        if (index_center >= sources_.size - 1) {
          loop_end = true;
        } else if (index_center + 1 > end_index) {
          loop_end = true;
        } else {
          start_index = index_center + 1;
        }
        break;
      default:
        std::cerr << "ERROR: TargetIsIncludedInSource(): enum position." << std::endl;
        break;
    }
    if (loop_end) {
      break;
    }
  }
  return is_included;
}

TargetPosition BinarySearch::GetTargetPosition(const int32_t target_value, const int32_t index_center) const {
  TargetPosition position;
  if (index_center < 0 || index_center >= sources_.size) {
    std::cerr << "ERROR: GetTargetPosition(): invalid index_center." << std::endl;
    throw 1;
  }
  const int32_t center_value = sources_.values[index_center];
  if (target_value == center_value) {
    position = TargetPosition::kCenter;
  } else if (target_value < center_value) {
    position = TargetPosition::kLeftSide;
  } else {
    position = TargetPosition::kRightSide;
  }
  return position;
}

int32_t BinarySearch::GetCenterIndex(const int32_t start, const int32_t end) const {
  const int32_t full_offset = end - start;
  if ((full_offset < 0) || ((start < 0) || (end >= sources_.size))) {
    std::cerr << "ERROR: GetCenterIndex: invalid args. start=" << start << ", end=" << end << std::endl;
    throw 1;
  }
  return start + (full_offset / 2);
}

}  // namespace ALDS1_4_B
