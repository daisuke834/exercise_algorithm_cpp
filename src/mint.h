/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief MOD INT
 */

#ifndef SRC_MINT_H_
#define SRC_MINT_H_

#include <cstdint>
#include <iostream>

namespace mint {

const int64_t kMod = 1000000007LL;
// const int kMod = 998244353LL;
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

}  // namespace mint
#endif  // SRC_MINT_H_
