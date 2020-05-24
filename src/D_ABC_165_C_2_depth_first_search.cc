/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 165-C. Depth First Search (DFS).
 * StackによるDFSの実装。
 */

#include "src/D_ABC_165_C_2_depth_first_search.h"
#include <iostream>
#include <stack>

namespace ABC_165_2 {

void CallDepthFirstSearch(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  DepthFirstSearch *depth_first_search = new DepthFirstSearch();
  int32_t array_length, max_value, number_of_conditions;
  input_stream >> array_length >> max_value >> number_of_conditions;
  depth_first_search->ConfigureArray(array_length, max_value);
  for (int32_t index_condition = 0; index_condition < number_of_conditions; ++index_condition) {
    int32_t a, b, c;
    int64_t score;
    input_stream >> a >> b >> c >> score;
    depth_first_search->AddCondition(a - 1, b - 1, c, score);
  }
  std::cout << depth_first_search->SearchMaxScore() << std::endl;
  delete depth_first_search;
}

DepthFirstSearch::DepthFirstSearch() noexcept {
  condition_.size = 0;
}

DepthFirstSearch::~DepthFirstSearch() noexcept {}

void DepthFirstSearch::ConfigureArray(const int32_t size, const int32_t max_value) {
  if (size <= 1 || size > kMaxArraySize) {
    std::cerr << "ERROR: ConfigureArray(): Invalid arg size=" << size << std::endl;
    throw 1;
  } else if ((max_value < kMinArrayValue) || (max_value > kMaxArrayValue)) {
    std::cerr << "ERROR: ConfigureArray(): Invalid arg max_value=" << max_value << std::endl;
    throw 1;
  } else {
    array_.size = size;
    array_.max_value = max_value;
  }
}

void DepthFirstSearch::AddCondition(const int32_t a, const int32_t b, const int32_t c, const int64_t score) {
  if (condition_.size >= kMaxNumberOfConditions) {
    std::cerr << "ERROR: AddCondition(): Full." << std::endl;
    throw 1;
  } else if ((a < 0) || (a >= array_.size)) {
    std::cerr << "ERROR: Invalid arg a=" << a << std::endl;
  } else if ((b < 0) || (b >= array_.size)) {
    std::cerr << "ERROR: Invalid arg b=" << b << std::endl;
  } else {
    const int32_t index_stored = condition_.size;
    condition_.a[index_stored] = a;
    condition_.b[index_stored] = b;
    condition_.c[index_stored] = c;
    condition_.score[index_stored] = score;
    ++condition_.size;
  }
}

int64_t DepthFirstSearch::SearchMaxScore() {
  int64_t max_score = 0;
  try {
    std::stack<int32_t> stack;
    constexpr int32_t kStartIndex = 0;
    array_.values[kStartIndex] = kMinArrayValue;
    stack.push(kStartIndex);
    constexpr int32_t kMaxLoopCount = 2000000;
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      if (static_cast<int32_t>(stack.size()) < array_.size) {
        const int32_t index_top = stack.top();
        const int32_t index_next = index_top + 1;
        array_.values[index_next] = array_.values[index_top];
        stack.push(index_next);
      } else {
        const int64_t score = CalculateScore();
        if (score > max_score) {
          max_score = score;
        }

        while (!stack.empty()) {
          int32_t &value_top = array_.values[stack.top()];
          if (value_top < array_.max_value) {
            ++value_top;
            break;
          } else {
            stack.pop();
          }
        }
        if (stack.empty()) {
          break;
        }
      }
    }
  } catch (...) {
    std::cerr << "ERROR: ConfigureArray()" << std::endl;
    throw;
  }
  return max_score;
}

int64_t DepthFirstSearch::CalculateScore() const {
  int64_t score_sum = 0;
  try {
    for (int32_t index_condition = 0; index_condition < condition_.size; ++index_condition) {
      score_sum += IsOkay(index_condition) ? condition_.score[index_condition] : 0;
    }
  } catch (...) {
    std::cerr << "ERROR: CalculateScore()" << std::endl;
    throw;
  }
  return score_sum;
}

bool DepthFirstSearch::IsOkay(const int32_t index_condition) const {
  if ((index_condition) < 0 || (index_condition >= condition_.size)) {
    std::cerr << "ERROR: IsOkay(): Invalid arg index_condition=" << index_condition << std::endl;
    throw 1;
  }
  const int32_t a = condition_.a[index_condition];
  const int32_t b = condition_.b[index_condition];
  const int32_t c = condition_.c[index_condition];
  const bool is_okay = (array_.values[b] - array_.values[a] == c);
  return is_okay;
}

}  // namespace ABC_165_2
