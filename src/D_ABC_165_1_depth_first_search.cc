/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest 165. Depth First Search (DFS).
 */

#include "src/D_ABC_165_1_depth_first_search.h"
#include <iostream>

namespace ABC_165_1 {

void CallDepthFirstSearch(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  DepthFirstSearch *depth_first_search = new DepthFirstSearch();
  int32_t array_length, max_value, number_of_conditions;
  input_stream >> array_length >> max_value >> number_of_conditions;
  depth_first_search->ConfigureArray(array_length, max_value);
  for (int32_t index_condition = 0; index_condition < number_of_conditions; ++index_condition) {
    int32_t a, b, c, score;
    input_stream >> a >> b >> c >> score;
    depth_first_search->AddCondition(a - 1, b - 1, c, score);
  }
  std::cout << depth_first_search->SearchMaxScore() << std::endl;
  delete depth_first_search;
}

DepthFirstSearch::DepthFirstSearch() noexcept : max_score_(0) {}

DepthFirstSearch::~DepthFirstSearch() noexcept {}

void DepthFirstSearch::AddCondition(const int32_t a, const int32_t b, const int32_t c, const int32_t score) {
  const int32_t index_stored = condition_.size;
  condition_.a[index_stored] = a;
  condition_.b[index_stored] = b;
  condition_.c[index_stored] = c;
  condition_.score[index_stored] = score;
  ++condition_.size;
}

void DepthFirstSearch::ConfigureArray(const int32_t size, const int32_t max_value) {
  array_.size = size;
  array_.max_value = max_value;
}

int32_t DepthFirstSearch::SearchMaxScore() {
  std::vector<int32_t> array;
  DoDepthFirstSearch(0);
  return max_score_;
}

void DepthFirstSearch::DoDepthFirstSearch(const int32_t target_index) {
  if (target_index >= array_.size) {
    int32_t score_sum = 0;
    for (int32_t index_condition = 0; index_condition < condition_.size; ++index_condition) {
      score_sum += IsOkay(index_condition) ? condition_.score[index_condition] : 0;
    }
    if (score_sum > max_score_) {
      max_score_ = score_sum;
    }
  }
  int32_t &target_value = array_.values[target_index];
  const int32_t start_value = (target_index == 0) ? kMinArrayValue : array_.values[target_index - 1];
  for (target_value = start_value; target_value <= array_.max_value; ++target_value) {
    DoDepthFirstSearch(target_index + 1);
  }
}

bool DepthFirstSearch::IsOkay(const int32_t index_condition) const {
  const int32_t a = condition_.a[index_condition];
  const int32_t b = condition_.b[index_condition];
  const int32_t c = condition_.c[index_condition];
  const bool is_okay = (array_.values[b] - array_.values[a] == c);
  return is_okay;
}

}  // namespace ABC_165_1
