/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-195-4. 1499. Max Value of Equation.
 * https://leetcode.com/contest/weekly-contest-195/problems/max-value-of-equation/
 */

#include "src/B_LC_weekly_195_4_two_pointers.h"

#include <set>

namespace LC_weekly_195_4 {

int Solution::findMaxValueOfEquation(std::vector<std::vector<int>>& points, int k) {
  const int64_t N = static_cast<int64_t>(points.size());
  std::vector<int64_t> b(N);
  for (int64_t i = 0; i < N; ++i) {
    b[i] = points[i][1] - points[i][0];
  }
  std::multiset<int64_t> b_candidate;
  int64_t i = 0;
  int64_t result = INT64_MIN;
  for (int64_t j = 0; j < N; ++j) {
    while (i < j && points[j][0] - points[i][0] > k) {
      b_candidate.erase(b_candidate.find(b[i]));
      ++i;
    }
    if (b_candidate.size() > 0) {
      const int64_t b_largest = *(b_candidate.rbegin());
      result = std::max(result, points[j][0] + points[j][1] + b_largest);
    }
    b_candidate.insert(b[j]);
  }
  return static_cast<int>(result);
}

}  // namespace LC_weekly_195_4
