/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_1_C. 素数(Prime Number)の判定。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C18_1_ALDS1_1_C_prime_number.h"

namespace ALDS1_1_C {

class Test_ALDS1_1_C : public ::testing::Test {
 protected:
  PrimeNumber *prime_number_;
  virtual void SetUp() {
    prime_number_ = new PrimeNumber();
  }
  virtual void TearDown() {
    delete prime_number_;
  }
};

TEST_F(Test_ALDS1_1_C, CallPrimeNumber) {
  std::ostringstream answer;
  answer << "4" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "6" << std::endl;
  input_stream << "7" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallPrimeNumber(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_1_C, AddData) {
  ASSERT_EQ(0, prime_number_->size_);

  constexpr int32_t kValue_0 = 3;
  constexpr int32_t kValue_1 = 10;
  prime_number_->AddData(kValue_0);
  prime_number_->AddData(kValue_1);
  ASSERT_EQ(2, prime_number_->size_);
  ASSERT_EQ(kValue_0, prime_number_->values_[0]);
  ASSERT_EQ(kValue_1, prime_number_->values_[1]);
}

TEST_F(Test_ALDS1_1_C, CalculateNumberOfPrimes_1) {
  prime_number_->AddData(2);
  prime_number_->AddData(3);
  prime_number_->AddData(4);
  prime_number_->AddData(5);
  prime_number_->AddData(6);
  prime_number_->AddData(7);
  const int32_t result = prime_number_->CalculateNumberOfPrimes();
  ASSERT_EQ(4, result);
}

TEST_F(Test_ALDS1_1_C, CalculateNumberOfPrimes_2) {
  prime_number_->AddData(3);
  prime_number_->AddData(7);
  prime_number_->AddData(29);
  prime_number_->AddData(4);
  prime_number_->AddData(5);
  prime_number_->AddData(6);
  prime_number_->AddData(2);
  const int32_t result = prime_number_->CalculateNumberOfPrimes();
  ASSERT_EQ(5, result);
}

TEST_F(Test_ALDS1_1_C, CalculatePrimeTable) {
  prime_number_->max_search_target_ = 20;

  prime_number_->CalculatePrimeTable();
  int32_t index_prime = 0;
  ASSERT_EQ(2, prime_number_->primes_[index_prime++]);
  ASSERT_EQ(3, prime_number_->primes_[index_prime++]);
  ASSERT_EQ(5, prime_number_->primes_[index_prime++]);
  ASSERT_EQ(7, prime_number_->primes_[index_prime++]);
  ASSERT_EQ(11, prime_number_->primes_[index_prime++]);
  ASSERT_EQ(13, prime_number_->primes_[index_prime++]);
  ASSERT_EQ(17, prime_number_->primes_[index_prime++]);
  ASSERT_EQ(19, prime_number_->primes_[index_prime++]);

  ASSERT_FALSE(prime_number_->IsPrime(0));
  ASSERT_FALSE(prime_number_->IsPrime(1));
  ASSERT_TRUE(prime_number_->IsPrime(2));
  ASSERT_TRUE(prime_number_->IsPrime(3));
  ASSERT_FALSE(prime_number_->IsPrime(4));
  ASSERT_TRUE(prime_number_->IsPrime(5));
  ASSERT_FALSE(prime_number_->IsPrime(6));
  ASSERT_TRUE(prime_number_->IsPrime(7));
  ASSERT_FALSE(prime_number_->IsPrime(8));
  ASSERT_FALSE(prime_number_->IsPrime(9));
  ASSERT_FALSE(prime_number_->IsPrime(10));
  ASSERT_TRUE(prime_number_->IsPrime(11));
  ASSERT_FALSE(prime_number_->IsPrime(12));
  ASSERT_TRUE(prime_number_->IsPrime(13));
  ASSERT_FALSE(prime_number_->IsPrime(14));
  ASSERT_FALSE(prime_number_->IsPrime(15));
  ASSERT_FALSE(prime_number_->IsPrime(16));
  ASSERT_TRUE(prime_number_->IsPrime(17));
  ASSERT_FALSE(prime_number_->IsPrime(18));
  ASSERT_TRUE(prime_number_->IsPrime(19));
  ASSERT_FALSE(prime_number_->IsPrime(20));
}

}  // namespace ALDS1_1_C
