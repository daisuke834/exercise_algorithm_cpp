/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-189-3. People Whose List of Favorite Companies Is Not a Subset of Another List.
 */

#ifndef SRC_B_LC_WEEKLY_189_3_SUBSEQUENCE_H_
#define SRC_B_LC_WEEKLY_189_3_SUBSEQUENCE_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace LC_weekly_189_3 {

template <class T>
bool IsSubsequence(const std::vector<T> &target, const std::vector<T> &compare);

class Solution {
 public:
  std::vector<int> peopleIndexes(std::vector<std::vector<std::string>> &favoriteCompanies);
};

}  // namespace LC_weekly_189_3

#endif  // SRC_B_LC_WEEKLY_189_3_SUBSEQUENCE_H_
