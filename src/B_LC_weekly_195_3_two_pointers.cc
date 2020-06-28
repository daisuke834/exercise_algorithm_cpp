/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-195-3. 1498. Number of Subsequences That Satisfy the Given Sum Condition.
 * https://leetcode.com/contest/weekly-contest-195/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
 */

#include "src/B_LC_weekly_195_3_two_pointers.h"

namespace LC_weekly_195_3 {

const int64_t kMod = 1000000007LL;
struct Mint {
  int64_t value;
  Mint(int64_t value = 0LL) : value((value % kMod + kMod) % kMod) {}
  Mint operator-() const {
    return Mint(-value);
  }
  Mint &operator+=(const Mint rhs) {
    if ((value += rhs.value) >= kMod) {
      value -= kMod;
    }
    return *this;
  }
  Mint &operator-=(const Mint rhs) {
    if ((value += kMod - rhs.value) >= kMod) {
      value -= kMod;
    }
    return *this;
  }
  Mint &operator*=(const Mint rhs) {
    (value *= rhs.value) %= kMod;
    return *this;
  }
  Mint operator+(const Mint rhs) const {
    return Mint(*this) += rhs;
  }
  Mint operator-(const Mint rhs) const {
    return Mint(*this) -= rhs;
  }
  Mint operator*(const Mint rhs) const {
    return Mint(*this) *= rhs;
  }
  Mint Pow(int64_t p) const {
    if (p == 0LL) {
      return 1LL;
    } else if (p < 0LL) {
      return Pow(-p).Pow(kMod - 2LL);
    }
    Mint temp = Pow(p >> 1LL);
    temp *= temp;
    if (p & 1LL) {
      temp *= (*this);
    }
    return temp;
  }
  Mint Inv() const {
    return Pow(kMod - 2LL);
  }
  Mint &operator/=(const Mint a) {
    return *this *= a.Inv();
  }
  Mint operator/(const Mint a) const {
    return Mint(*this) /= a;
  }
};
std::ostream &operator<<(std::ostream &os, const Mint &a) {
  os << a.value;
  return os;
}

int Solution::numSubseq(std::vector<int> &nums, int target) {
  const int64_t N = static_cast<int64_t>(nums.size());
  sort(nums.begin(), nums.end());
  int64_t ma = N - 1;
  Mint result = 0;
  for (int64_t mi = 0; mi < N; ++mi) {
    while (ma >= mi && static_cast<int64_t>(nums[mi]) + static_cast<int64_t>(nums[ma]) > static_cast<int64_t>(target)) {
      --ma;
    }
    if (ma < mi) {
      break;
    }
    result += Mint(2).Pow(ma - mi);
  }
  return static_cast<int>(result.value);
}

}  // namespace LC_weekly_195_3
