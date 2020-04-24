/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_1_C. 素数(Prime Number)の判定。計算量=O(sqrt(N))。
 */

#ifndef SRC_C18_1_ALDS1_1_C_PRIME_NUMBER_H_
#define SRC_C18_1_ALDS1_1_C_PRIME_NUMBER_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_1_C {

constexpr int32_t kMaxValueArraySize = 200000;
constexpr int32_t kMaxPrimeArraySize = 50000;

void CallPrimeNumber(std::istream &input_stream);

class PrimeNumber {
 public:
  PrimeNumber() noexcept;
  ~PrimeNumber() noexcept;
  void AddData(const int32_t value);
  void ResetData() noexcept;
  int32_t CalculateNumberOfPrimes() noexcept;
  void CalculateMaxSearchTarget();
  void CalculatePrimeTable();
  bool IsPrime(const int32_t value) const;

 private:
  PrimeNumber(const PrimeNumber &obj) = delete;
  PrimeNumber &operator=(const PrimeNumber &rhs) = delete;
  PrimeNumber(PrimeNumber &&obj) = delete;
  PrimeNumber &operator=(PrimeNumber &&rhs) = delete;

 private:
  int32_t size_;
  int32_t values_[kMaxValueArraySize];
  int32_t number_of_primes_;
  int32_t primes_[kMaxPrimeArraySize];
  int32_t max_search_target_;

 private:
  FRIEND_TEST(Test_ALDS1_1_C, AddData);              // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_1_C, CalculatePrimeTable);  // Should be removed from production code
};

}  // namespace ALDS1_1_C

#endif  // SRC_C18_1_ALDS1_1_C_PRIME_NUMBER_H_
