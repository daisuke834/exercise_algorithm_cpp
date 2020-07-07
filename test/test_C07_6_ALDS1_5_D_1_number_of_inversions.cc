/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-6. 高等的整列、反転数(The Number of Inversions)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C07_6_ALDS1_5_D_1_number_of_inversions.h"

namespace ALDS1_5_D_1 {

class Test_ALDS1_5_D_1 : public ::testing::Test {
 protected:
  NumberOfInversions *number_of_inversions_;
  virtual void SetUp() {
    number_of_inversions_ = new NumberOfInversions();
  }
  virtual void TearDown() {
    delete number_of_inversions_;
  }
};

TEST_F(Test_ALDS1_5_D_1, CallNumberOfInversions) {
  std::ostringstream answer;
  answer << "6" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "3 5 2 1 4" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallNumberOfInversions(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_5_D_1, AddData) {
  ASSERT_EQ(0, number_of_inversions_->size_);

  constexpr int32_t kValue_0 = 3;
  constexpr int32_t kValue_1 = 10;
  number_of_inversions_->AddData(kValue_0);
  number_of_inversions_->AddData(kValue_1);
  ASSERT_EQ(2, number_of_inversions_->size_);
  ASSERT_EQ(kValue_0, number_of_inversions_->values_[0]);
  ASSERT_EQ(kValue_1, number_of_inversions_->values_[1]);
}

TEST_F(Test_ALDS1_5_D_1, CalculateNumberOfInversions_1) {
  number_of_inversions_->AddData(3);
  number_of_inversions_->AddData(5);

  number_of_inversions_->CalculateNumberOfInversions();
  ASSERT_EQ(0, number_of_inversions_->GetNumberOfInversions());
}

TEST_F(Test_ALDS1_5_D_1, CalculateNumberOfInversions_2) {
  number_of_inversions_->AddData(5);
  number_of_inversions_->AddData(3);

  number_of_inversions_->CalculateNumberOfInversions();
  ASSERT_EQ(1, number_of_inversions_->GetNumberOfInversions());
}

TEST_F(Test_ALDS1_5_D_1, CalculateNumberOfInversions_3) {
  number_of_inversions_->AddData(3);
  number_of_inversions_->AddData(4);
  number_of_inversions_->AddData(5);

  number_of_inversions_->CalculateNumberOfInversions();
  ASSERT_EQ(0, number_of_inversions_->GetNumberOfInversions());
}

TEST_F(Test_ALDS1_5_D_1, CalculateNumberOfInversions_4) {
  number_of_inversions_->AddData(3);
  number_of_inversions_->AddData(5);
  number_of_inversions_->AddData(4);

  number_of_inversions_->CalculateNumberOfInversions();
  ASSERT_EQ(1, number_of_inversions_->GetNumberOfInversions());
}

TEST_F(Test_ALDS1_5_D_1, CalculateNumberOfInversions_5) {
  number_of_inversions_->AddData(5);
  number_of_inversions_->AddData(3);
  number_of_inversions_->AddData(4);

  number_of_inversions_->CalculateNumberOfInversions();
  ASSERT_EQ(2, number_of_inversions_->GetNumberOfInversions());
}

TEST_F(Test_ALDS1_5_D_1, CalculateNumberOfInversions_6) {
  number_of_inversions_->AddData(5);
  number_of_inversions_->AddData(4);
  number_of_inversions_->AddData(3);

  number_of_inversions_->CalculateNumberOfInversions();
  ASSERT_EQ(3, number_of_inversions_->GetNumberOfInversions());
}

TEST_F(Test_ALDS1_5_D_1, CalculateNumberOfInversions_7) {
  number_of_inversions_->AddData(3);
  number_of_inversions_->AddData(5);
  number_of_inversions_->AddData(2);
  number_of_inversions_->AddData(1);
  number_of_inversions_->AddData(4);

  number_of_inversions_->CalculateNumberOfInversions();
  ASSERT_EQ(6, number_of_inversions_->GetNumberOfInversions());
}

TEST_F(Test_ALDS1_5_D_1, CalculateNumberOfInversions_8) {
  number_of_inversions_->AddData(5);
  number_of_inversions_->AddData(4);
  number_of_inversions_->AddData(3);
  number_of_inversions_->AddData(2);
  number_of_inversions_->AddData(1);

  number_of_inversions_->CalculateNumberOfInversions();
  ASSERT_EQ(10, number_of_inversions_->GetNumberOfInversions());
}

TEST_F(Test_ALDS1_5_D_1, CalculateNumberOfInversions_9) {
  constexpr int32_t kMaxValue = 100000;
  for (int32_t value = 1; value <= kMaxValue; ++value) {
    number_of_inversions_->AddData(value);
  }
  number_of_inversions_->CalculateNumberOfInversions();
  ASSERT_EQ(0, number_of_inversions_->GetNumberOfInversions());
}

TEST_F(Test_ALDS1_5_D_1, CalculateNumberOfInversions_10) {
  const clock_t tstart = clock();
  constexpr int32_t kMaxValue = 50000;
  int64_t sum = 0;
  for (int32_t value = kMaxValue; value >= 1; --value) {
    number_of_inversions_->AddData(value);
    sum += static_cast<int64_t>(value - 1);
  }
  ASSERT_EQ(kMaxValue, number_of_inversions_->size_);
  number_of_inversions_->CalculateNumberOfInversions();
  const clock_t tend = clock();
  const int64_t duration_in_ms = (tend - tstart) / CLOCKS_PER_SEC * 1000;
  std::cout << duration_in_ms << "msec" << std::endl;
  ASSERT_EQ(sum, number_of_inversions_->GetNumberOfInversions());
  ASSERT_GT(5000, duration_in_ms);
}

}  // namespace ALDS1_5_D_1
