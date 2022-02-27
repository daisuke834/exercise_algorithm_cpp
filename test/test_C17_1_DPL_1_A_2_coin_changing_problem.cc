/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part17-1. 動的計画法(Dynamic Programming, DP)、コイン問題(Coin Changing Problem)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/C17_1_DPL_1_A_2_coin_changing_problem.h"

namespace DPL_1_A_2 {

class Test_DPL_1_A_2 : public ::testing::Test {
 protected:
  CoinChangingProblem* coin_chainging_problem_;
  virtual void SetUp() { coin_chainging_problem_ = new CoinChangingProblem(); }
  virtual void TearDown() { delete coin_chainging_problem_; }
};

TEST_F(Test_DPL_1_A_2, FindNumberOfMinimumNumberOfCoins_1) {
  coin_chainging_problem_->AddCoinValue(1);
  coin_chainging_problem_->AddCoinValue(2);
  ASSERT_EQ(1, coin_chainging_problem_->FindNumberOfMinimumNumberOfCoins(1));
}

TEST_F(Test_DPL_1_A_2, FindNumberOfMinimumNumberOfCoins_2) {
  coin_chainging_problem_->AddCoinValue(1);
  coin_chainging_problem_->AddCoinValue(2);
  ASSERT_EQ(1, coin_chainging_problem_->FindNumberOfMinimumNumberOfCoins(2));
}

TEST_F(Test_DPL_1_A_2, FindNumberOfMinimumNumberOfCoins_3) {
  coin_chainging_problem_->AddCoinValue(1);
  coin_chainging_problem_->AddCoinValue(2);
  ASSERT_EQ(2, coin_chainging_problem_->FindNumberOfMinimumNumberOfCoins(3));
}

TEST_F(Test_DPL_1_A_2, FindNumberOfMinimumNumberOfCoins_4) {
  coin_chainging_problem_->AddCoinValue(1);
  coin_chainging_problem_->AddCoinValue(2);
  coin_chainging_problem_->AddCoinValue(7);
  coin_chainging_problem_->AddCoinValue(8);
  coin_chainging_problem_->AddCoinValue(12);
  coin_chainging_problem_->AddCoinValue(50);
  ASSERT_EQ(2, coin_chainging_problem_->FindNumberOfMinimumNumberOfCoins(15));
}

TEST_F(Test_DPL_1_A_2, FindNumberOfMinimumNumberOfCoins_5) {
  coin_chainging_problem_->AddCoinValue(1);
  coin_chainging_problem_->AddCoinValue(2);
  coin_chainging_problem_->AddCoinValue(7);
  coin_chainging_problem_->AddCoinValue(8);
  coin_chainging_problem_->AddCoinValue(12);
  coin_chainging_problem_->AddCoinValue(50);
  ASSERT_EQ(3, coin_chainging_problem_->FindNumberOfMinimumNumberOfCoins(65));
}

TEST_F(Test_DPL_1_A_2, CallCoinChangingProblem_1) {
  std::ostringstream answer;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "15 6" << std::endl;
  input_stream << "1 2 7 8 12 50" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallCoinChangingProblem(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace DPL_1_A_2
