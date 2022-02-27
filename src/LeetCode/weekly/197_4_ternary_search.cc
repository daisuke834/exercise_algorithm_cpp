/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-197-4. 1515. Best Position for a Service Centre
 * https://leetcode.com/contest/weekly-contest-197/problems/best-position-for-a-service-centre/
 * 三分探索 (Ternary Search)
 */

#include "197_4_ternary_search.h"

#include <algorithm>
#include <cmath>

namespace LC_weekly_197_4 {

double Solution::getMinDistSum(std::vector<std::vector<int>>& positions) {
  const int64_t N = static_cast<int64_t>(positions.size());

  auto SumDist = [&](const double x, const double y) -> double {
    double sum_d = 0.0;
    for (int64_t i = 0; i < N; ++i) {
      const double dx = (x - positions[i][0]);
      const double dy = (y - positions[i][1]);
      sum_d += std::sqrt(dx * dx + dy * dy);
    }
    return sum_d;
  };

  constexpr int64_t kInf = INT64_MAX / 2L;
  double result = static_cast<double>(kInf);
  double x = 50.0;
  double y = 50.0;
  for (int64_t i = 0; i < 100; ++i) {
    double left_x = 0;
    double right_x = 100.0;
    while (right_x - left_x > 1e-7) {
      double c1_x = (left_x * 2 + right_x) / 3.0;
      double c2_x = (left_x + right_x * 2) / 3.0;
      const double d1 = SumDist(c1_x, y);
      const double d2 = SumDist(c2_x, y);
      if (d1 > d2) {
        left_x = c1_x;
      } else {
        right_x = c2_x;
      }
    }
    x = (left_x + right_x) / 2.0;
    result = std::min(result, SumDist(x, y));

    double left_y = 0;
    double right_y = 100.0;
    while (right_y - left_y > 1e-7) {
      double c1_y = (left_y * 2 + right_y) / 3.0;
      double c2_y = (left_y + right_y * 2) / 3.0;
      const double d1 = SumDist(x, c1_y);
      const double d2 = SumDist(x, c2_y);
      if (d1 > d2) {
        left_y = c1_y;
      } else {
        right_y = c2_y;
      }
    }
    y = (left_y + right_y) / 2.0;
    result = std::min(result, SumDist(x, y));
  }
  return result;
}

}  // namespace LC_weekly_197_4
