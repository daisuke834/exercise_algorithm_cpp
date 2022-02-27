/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Educational DP Contest. F. LCS(Longest-common subsequence, 最長共通部分列).
 * https://atcoder.jp/contests/dp/tasks/dp_f
 */

#include "src/D_AtCoder_Educational_DP_F_LCS.h"

#include <algorithm>
#include <string>
#include <vector>

namespace AtCoder_Educational_DP_F {

void CallMain(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  std::string s, t;
  input_stream >> s >> t;
  const int64_t LS = static_cast<int64_t>(s.length());
  const int64_t LT = static_cast<int64_t>(t.length());
  std::vector<std::vector<int64_t>> dp(LS + 1, std::vector<int64_t>(LT + 1, 0));
  for (int64_t i = 1; i <= LS; ++i) {
    for (int64_t j = 1; j <= LT; ++j) {
      if (s.c_str()[i - 1] == t.c_str()[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  std::string result;
  int64_t i = LS;
  int64_t j = LT;
  while (i != 0 && j != 0) {
    if (dp[i - 1][j] == dp[i][j]) {
      --i;
    } else if (dp[i][j - 1] == dp[i][j]) {
      --j;
    } else {
      result += s.substr(i - 1, 1);
      --i;
      --j;
    }
  }
  std::reverse(result.begin(), result.end());
  std::cout << result << std::endl;
}

}  // namespace AtCoder_Educational_DP_F
