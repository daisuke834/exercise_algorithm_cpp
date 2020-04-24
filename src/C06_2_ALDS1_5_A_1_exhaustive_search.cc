/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-2. 再帰・分割統治法、全探索(Exhaustive Search)。動的メモリを使ったバージョン。
 * 計算時間=O(2^num_of_sources).
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C06_2_ALDS1_5_A_1_exhaustive_search.h"
#include <iostream>
#include <string>

namespace ALDS1_5_A_1 {

void CallExhaustiveSearch(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  ExhaustiveSearch *exhaustive_search = new ExhaustiveSearch();
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

ExhaustiveSearch::ExhaustiveSearch() noexcept : sources_{}, targets_{} {
  sources_.clear();
  targets_.size = 0;
}
ExhaustiveSearch::~ExhaustiveSearch() noexcept {}

void ExhaustiveSearch::AddOneSource(const int32_t source) {
  if (sources_.size() >= kMaxNumberOfSources) {
    std::cerr << "ERROR: AddOneSource(): sources_ is full." << std::endl;
    throw 1;
  }
  sources_.push_back(source);
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
  for (int32_t index_target = 0; index_target < targets_.size; ++index_target) {
    const int32_t target = targets_.values[index_target];
    bool can_be_created = CanBeCreated(target, sources_);
    if (can_be_created) {
      std::cout << "yes" << std::endl;
    } else {
      std::cout << "no" << std::endl;
    }
  }
}

bool ExhaustiveSearch::CanBeCreated(const int32_t target, const std::list<int32_t> &sources) {
  bool can_be_created = false;
  if (sources.size() <= 0) {
    can_be_created = false;
  } else {
    std::list<int32_t> next_sources(sources);
    for (int32_t i = 0; i < static_cast<int32_t>(sources.size()); ++i) {
      const int32_t source = next_sources.front();
      next_sources.pop_front();
      const int32_t next_target = target - source;
      if (next_target == 0) {
        can_be_created = true;
        break;
      } else if (next_target > 0) {
        can_be_created = CanBeCreated(next_target, next_sources);
        if (can_be_created) {
          break;
        }
      } else {
        // next_sources.push_back(source); // 重複計算になるので、いらない
      }
    }
  }
  return can_be_created;
}

}  // namespace ALDS1_5_A_1
