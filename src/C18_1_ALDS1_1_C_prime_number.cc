/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_1_C. 素数(Prime Number)の判定。計算量=O(sqrt(N))。
 */

#include "src/C18_1_ALDS1_1_C_prime_number.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

namespace ALDS1_1_C {

void CallPrimeNumber(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  PrimeNumber *prime_number = new PrimeNumber();
  try {
    int32_t count;
    input_stream >> count;
    for (int32_t index = 0; index < count; ++index) {
      int32_t cvalue;
      input_stream >> cvalue;
      prime_number->AddData(cvalue);
    }
    std::cout << prime_number->CalculateNumberOfPrimes() << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallPrimeNumber()" << std::endl;
    throw;
  }
  delete prime_number;
}

// ****************************************************

PrimeNumber::PrimeNumber() noexcept : size_(0), values_{}, number_of_primes_(1), primes_{}, max_search_target_(0) {
  primes_[0] = 2;
}
PrimeNumber::~PrimeNumber() noexcept {}

void PrimeNumber::AddData(const int32_t value) {
  if (size_ >= kMaxValueArraySize) {
    std::cerr << "ERROR: AddData(): Data size exceeded a limit = " << kMaxValueArraySize << std::endl;
    throw 1;
  }
  values_[size_] = value;
  size_++;
}

int32_t PrimeNumber::CalculateNumberOfPrimes() noexcept {
  int32_t count = 0;
  try {
    CalculateMaxSearchTarget();
    CalculatePrimeTable();
    for (int32_t index = 0; index < size_; ++index) {
      if (IsPrime(values_[index])) {
        ++count;
      } else {
        // DO NOTHING
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CalculatePrimeNumber()" << std::endl;
    throw;
  }
  return count;
}

void PrimeNumber::ResetData() noexcept {
  size_ = 0;
  number_of_primes_ = 0;
  max_search_target_ = 0;
}

void PrimeNumber::CalculateMaxSearchTarget() {
  try {
    max_search_target_ = 0;
    for (int32_t index = 0; index < size_; ++index) {
      max_search_target_ = std::max(max_search_target_, values_[index]);
    }
    const float temp = sqrtf(static_cast<float>(max_search_target_));
    max_search_target_ = static_cast<int32_t>(ceilf(temp));
  } catch (...) {
    std::cerr << "ERROR: CalculateMaxSearchTarget()" << std::endl;
    throw;
  }
}

void PrimeNumber::CalculatePrimeTable() {
  try {
    for (int32_t target = 3; target <= max_search_target_; target += 2) {
      if (IsPrime(target)) {
        const int32_t index_to_store = number_of_primes_;
        if (index_to_store >= kMaxPrimeArraySize) {
          std::cerr << "ERROR: CalculatePrimeTable(): The number of primes exceeded a limit: " << size_ << std::endl;
          throw 1;
        } else {
          primes_[index_to_store] = target;
          ++number_of_primes_;
        }
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CalculatePrimeTable()" << std::endl;
    throw;
  }
}

bool PrimeNumber::IsPrime(const int32_t value) const {
  bool is_prime = true;
  if (sqrtf(value) > static_cast<float>(max_search_target_ + 1) || value < 0) {
    std::cerr << "ERROR: IsPrime(): value is out of range: " << value << std::endl;
    throw 1;
  } else if ((value == 0) || (value == 1)) {
    is_prime = false;
  } else {
    for (int32_t index_prime = 0; index_prime < number_of_primes_; ++index_prime) {
      const int32_t cprime = primes_[index_prime];
      if ((value != cprime) && ((value % cprime) == 0)) {
        is_prime = false;
        break;
      }
    }
  }
  return is_prime;
}

}  // namespace ALDS1_1_C
