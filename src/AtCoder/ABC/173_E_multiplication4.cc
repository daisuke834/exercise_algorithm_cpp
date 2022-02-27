/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 173-E. Multiplication 4.
 */

#include "173_E_multiplication4.h"

#include <algorithm>
#include <queue>
#include <set>
#include <vector>

namespace {
const int64_t kMod = 1000000007LL;
// const int64_t kMod = 998244353LL;
struct Mint {
  int64_t value;
  Mint(int64_t value = 0LL) : value((value % kMod + kMod) % kMod) {}
  Mint operator-() const { return Mint(-value); }
  Mint& operator+=(const Mint rhs) {
    if ((value += rhs.value) >= kMod) {
      value -= kMod;
    }
    return *this;
  }
  Mint& operator-=(const Mint rhs) {
    if ((value += kMod - rhs.value) >= kMod) {
      value -= kMod;
    }
    return *this;
  }
  Mint& operator*=(const Mint rhs) {
    (value *= rhs.value) %= kMod;
    return *this;
  }
  Mint operator+(const Mint rhs) const { return Mint(*this) += rhs; }
  Mint operator-(const Mint rhs) const { return Mint(*this) -= rhs; }
  Mint operator*(const Mint rhs) const { return Mint(*this) *= rhs; }
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
  Mint Inv() const { return Pow(kMod - 2LL); }
  Mint& operator/=(const Mint a) { return *this *= a.Inv(); }
  Mint operator/(const Mint a) const { return Mint(*this) /= a; }
};
}  // namespace

namespace D_ABC_173_E {

int CallMain(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int64_t N, K;
  input_stream >> N >> K;
  std::vector<int64_t> A(N);
  int64_t num_of_plus = 0;
  int64_t num_of_minus = 0;
  std::vector<int64_t> pluses;
  std::vector<int64_t> minuses;
  for (int64_t i = 0; i < N; ++i) {
    input_stream >> A[i];
    if (A[i] >= 0) {
      pluses.emplace_back(A[i]);
      ++num_of_plus;
    } else if (A[i] < 0) {
      minuses.emplace_back(A[i]);
      --num_of_minus;
    }
  }

  auto GreaterThan = [](const int64_t a, const int64_t b) -> bool { return (std::abs(a) > std::abs(b)); };
  std::sort(A.begin(), A.end(), GreaterThan);

  bool can_be_plus = false;
  if (num_of_plus > 0) {
    if (N == K) {
      can_be_plus = (num_of_minus % 2 == 0);
    } else {
      can_be_plus = true;
    }
  } else if (num_of_plus == 0) {
    can_be_plus = (K % 2 == 0);
  }

  Mint result = 1;
  if (can_be_plus) {
    result = 1;
    std::sort(pluses.begin(), pluses.end());
    std::sort(minuses.rbegin(), minuses.rend());
    if (K % 2 == 1) {
      result *= pluses.back();
      pluses.pop_back();
      --K;
    }
    std::priority_queue<int64_t> q;
    while (static_cast<int64_t>(pluses.size()) >= 2) {
      int64_t tmp = pluses.back();
      pluses.pop_back();
      tmp *= pluses.back();
      pluses.pop_back();
      q.emplace(tmp);
    }
    while (static_cast<int64_t>(minuses.size()) >= 2) {
      int64_t tmp = minuses.back();
      minuses.pop_back();
      tmp *= minuses.back();
      minuses.pop_back();
      q.emplace(tmp);
    }
    while (K > 0) {
      result *= q.top();
      q.pop();
      K -= 2;
    }
  } else {
    result = 1;
    for (int64_t i = N - 1; i >= N - K; --i) {
      result *= A[i];
    }
  }
  std::cout << result.value << std::endl;

  return 0;
}

}  // namespace D_ABC_173_E
