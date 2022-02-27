/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part2. 導入問題、Maximum Profitのテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>

#include "src/AOJ/textbook/02/ALDS1_1_D_maximum_profit.h"

namespace ALDS1_1_D {
class Test_ALDS1_1_D : public ::testing::Test {
 protected:
  CurrencyRates* currency_rates_;
  virtual void SetUp() { currency_rates_ = new CurrencyRates; }
  virtual void TearDown() { delete currency_rates_; }
};

TEST_F(Test_ALDS1_1_D, LoadData_normal) {
  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "3" << std::endl;
  std::istringstream iss(input_stream.str());
  currency_rates_->LoadData(iss);
  ASSERT_GT(kMaxCount, currency_rates_->count_);
  ASSERT_EQ(6, currency_rates_->count_);
  int32_t index = 0;
  ASSERT_EQ(5, currency_rates_->rates_[index++]);
  ASSERT_EQ(3, currency_rates_->rates_[index++]);
  ASSERT_EQ(1, currency_rates_->rates_[index++]);
  ASSERT_EQ(3, currency_rates_->rates_[index++]);
  ASSERT_EQ(4, currency_rates_->rates_[index++]);
  ASSERT_EQ(3, currency_rates_->rates_[index++]);
}

TEST_F(Test_ALDS1_1_D, LoadData_abnormal) {
  std::ostringstream input_stream;
  input_stream << kMaxCount + 1 << std::endl;
  std::istringstream iss(input_stream.str());
  ASSERT_ANY_THROW(currency_rates_->LoadData(iss));
}

TEST_F(Test_ALDS1_1_D, MaximumProfit_1) {
  const std::string answer("3\n");
  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "3" << std::endl;
  std::istringstream iss(input_stream.str());
  (void)testing::internal::CaptureStdout();
  currency_rates_->MaximumProfit(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_1_D, MaximumProfit_2) {
  const std::string answer("-1\n");
  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "2" << std::endl;
  std::istringstream iss(input_stream.str());
  (void)testing::internal::CaptureStdout();
  currency_rates_->MaximumProfit(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_1_D, MaximumProfit_3) {
  const std::string answer("99\n");
  std::ostringstream input_stream;
  input_stream << "2" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "100" << std::endl;
  std::istringstream iss(input_stream.str());
  (void)testing::internal::CaptureStdout();
  currency_rates_->MaximumProfit(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_1_D, MaximumProfit_4) {
  const std::string answer("-30\n");
  std::ostringstream input_stream;
  input_stream << "2" << std::endl;
  input_stream << "50" << std::endl;
  input_stream << "20" << std::endl;
  std::istringstream iss(input_stream.str());
  (void)testing::internal::CaptureStdout();
  currency_rates_->MaximumProfit(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_1_D, MaximumProfit_5) {
  const std::string answer("0\n");
  std::ostringstream input_stream;
  input_stream << "2" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "5" << std::endl;
  std::istringstream iss(input_stream.str());
  (void)testing::internal::CaptureStdout();
  currency_rates_->MaximumProfit(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_1_D, MaximumProfit_6) {
  const std::string answer("1\n");
  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "6" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "5" << std::endl;
  std::istringstream iss(input_stream.str());
  (void)testing::internal::CaptureStdout();
  currency_rates_->MaximumProfit(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_1_D, MaximumProfit_7) {
  const std::string answer("3\n");
  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "8" << std::endl;
  input_stream << "2" << std::endl;
  std::istringstream iss(input_stream.str());
  (void)testing::internal::CaptureStdout();
  currency_rates_->MaximumProfit(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_1_D, MaximumProfit_8) {
  const std::string answer("4\n");
  std::ostringstream input_stream;
  input_stream << "12" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "8" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "3" << std::endl;
  std::istringstream iss(input_stream.str());
  (void)testing::internal::CaptureStdout();
  currency_rates_->MaximumProfit(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_1_D
