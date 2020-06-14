/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-193-3. 5455. Minimum Number of Days to Make m Bouquets.
 */

#include "src/B_LC_weekly_193_3_binary_search.h"

namespace LC_weekly_193_3 {

int Solution::minDays(std::vector<int> &bloomDay, int m, int k) {
  int N = static_cast<int32_t>(bloomDay.size());
  if (m * k > N) {
    return -1;
  }
  int max_day = *max_element(bloomDay.begin(), bloomDay.end());
  int min_day = *min_element(bloomDay.begin(), bloomDay.end());
  if (max_day == min_day) {
    return min_day;
  }

  int result = -1;
  while (min_day != max_day) {
    if (min_day + 1 == max_day) {
      if (IsOkay(bloomDay, m, k, min_day)) {
        result = min_day;
        break;
      } else if (IsOkay(bloomDay, m, k, max_day)) {
        result = max_day;
        break;
      } else {
        result = -1;
        break;
      }
    }
    int half = (min_day + max_day) / 2;
    if (IsOkay(bloomDay, m, k, half)) {
      result = half;
      max_day = half;
    } else {
      min_day = half;
    }
  }
  return result;
}

bool Solution::IsOkay(const std::vector<int> &bloomDay, const int m, const int k, const int day) {
  int number_of_bour = 0;
  int conse = 0;
  for (const int d : bloomDay) {
    if (d <= day) {
      ++conse;
    } else {
      conse = 0;
    }
    if (conse >= k) {
      ++number_of_bour;
      conse = 0;
      if (number_of_bour >= m) {
        return true;
      }
    }
  }
  return false;
}

}  // namespace LC_weekly_193_3
