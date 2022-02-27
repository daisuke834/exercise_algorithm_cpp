/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-189-3. People Whose List of Favorite Companies Is Not a Subset of Another List.
 */

#include "src/B_LC_weekly_189_3_subsequence.h"

namespace LC_weekly_189_3 {

template <class T>
bool IsSubsequence(const std::vector<T>& target, const std::vector<T>& compare) {
  // targetおよびcompareはsort済み前提で、O(N)の計算量。
  bool is_subsequence = true;
  if (compare.size() == 0 || target.size() > compare.size()) {
    is_subsequence = false;
  } else {
    const int32_t target_length = static_cast<int32_t>(target.size());
    const int32_t compare_length = static_cast<int32_t>(compare.size());
    int32_t target_index = 0;
    for (int32_t compare_index = 0; compare_index < compare_length; ++compare_index) {
      if (target[target_index] == compare[compare_index]) {
        ++target_index;
        if (target_index >= target_length) {
          break;
        }
      }
    }
    is_subsequence = (target_index == target_length);
  }
  return is_subsequence;
}

std::vector<int> Solution::peopleIndexes(std::vector<std::vector<std::string>>& favoriteCompanies) {
  for (auto& companies : favoriteCompanies) {
    std::sort(companies.begin(), companies.end());
  }

  std::vector<int> result;
  const int32_t number_of_people = static_cast<int32_t>(favoriteCompanies.size());
  for (int32_t person = 0; person < number_of_people; ++person) {
    bool is_subsequence = false;
    for (int32_t compare = 0; compare < number_of_people; ++compare) {
      if (person != compare) {
        if (IsSubsequence(favoriteCompanies[person], favoriteCompanies[compare])) {
          is_subsequence = true;
          break;
        }
      }
    }
    if (!is_subsequence) {
      result.push_back(person);
    }
  }
  return result;
}

// **********************************************************************

}  // namespace LC_weekly_189_3
