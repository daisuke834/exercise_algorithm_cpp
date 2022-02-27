/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-194-3. 1488. Avoid Flood in The City.
 * https://leetcode.com/contest/weekly-contest-194/problems/avoid-flood-in-the-city/
 */

#include "194_3_binary_search.h"

#include <set>
#include <unordered_map>

namespace LC_weekly_194_3 {

std::vector<int32_t> Solution::avoidFlood(const std::vector<int32_t>& rains) {
  const int32_t L = static_cast<int32_t>(rains.size());
  std::vector<int32_t> ans(L);

  std::unordered_map<int32_t, int32_t> last_rains;
  std::set<int32_t> empty_space;
  for (int32_t i = 0; i < L; ++i) {
    if (rains[i] > 0) {
      ans[i] = -1;
      if (last_rains.find(rains[i]) != last_rains.end()) {
        if (empty_space.empty()) {
          ans.clear();
          return ans;
        }
        auto itr = empty_space.lower_bound(last_rains[rains[i]]);
        if (itr == empty_space.end()) {
          ans.clear();
          return ans;

        } else {
          const int32_t emp_index = *itr;
          empty_space.erase(itr);
          ans[emp_index] = rains[i];
        }
      }
      last_rains[rains[i]] = i;
    } else {
      empty_space.insert(i);
      ans[i] = 1;
    }
  }
  return ans;
}

}  // namespace LC_weekly_194_3
