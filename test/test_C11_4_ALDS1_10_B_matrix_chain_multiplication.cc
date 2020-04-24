/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part11-4. 動的計画法(Dynamic Programming, DP)、連鎖行列積問題(Matrix-Chain Multiplication problem)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C11_4_ALDS1_10_B_matrix_chain_multiplication.h"

namespace ALDS1_10_B {

class Test_ALDS1_10_B : public ::testing::Test {
 protected:
  MatrixChainMultiplication *mcm_;
  virtual void SetUp() {
    mcm_ = new MatrixChainMultiplication();
  }
  virtual void TearDown() {
    delete mcm_;
  }
};

TEST_F(Test_ALDS1_10_B, AddMatrix) {
  mcm_->AddMatrix(30, 35);
  mcm_->AddMatrix(2, 3);
  ASSERT_EQ(2, mcm_->number_of_matrices_);
  ASSERT_EQ(30, mcm_->matrices_[0].number_of_rows);
  ASSERT_EQ(35, mcm_->matrices_[0].number_of_columns);
  ASSERT_EQ(2, mcm_->matrices_[1].number_of_rows);
  ASSERT_EQ(3, mcm_->matrices_[1].number_of_columns);
}

TEST_F(Test_ALDS1_10_B, CallMatrixChainMultiplication_1) {
  std::ostringstream answer;
  answer << "15125" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "30 35" << std::endl;
  input_stream << "35 15" << std::endl;
  input_stream << "15 5" << std::endl;
  input_stream << "5 10" << std::endl;
  input_stream << "10 20" << std::endl;
  input_stream << "20 25" << std::endl;

  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMatrixChainMultiplication(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_10_B, MultiplyCount_MultipliedMatrix_1) {
  const Matrix a_1 = MatrixChainMultiplication::GenerateMatrix(2, 2);
  const Matrix b_1 = MatrixChainMultiplication::GenerateMatrix(2, 1);
  ASSERT_EQ(4, MatrixChainMultiplication::GetMultiplyCount(a_1, b_1));
  const Matrix result_1 = MatrixChainMultiplication::GetMultipliedMatrix(a_1, b_1);
  ASSERT_EQ(2, result_1.number_of_rows);
  ASSERT_EQ(1, result_1.number_of_columns);

  const Matrix a_2 = MatrixChainMultiplication::GenerateMatrix(2, 2);
  const Matrix b_2 = MatrixChainMultiplication::GenerateMatrix(2, 2);
  ASSERT_EQ(8, MatrixChainMultiplication::GetMultiplyCount(a_2, b_2));
  const Matrix result_2 = MatrixChainMultiplication::GetMultipliedMatrix(a_2, b_2);
  ASSERT_EQ(2, result_2.number_of_rows);
  ASSERT_EQ(2, result_2.number_of_columns);
}

TEST_F(Test_ALDS1_10_B, MultiplyCount_MultipliedMatrix_2) {
  constexpr int32_t kMinimum = 15125;
  mcm_->AddMatrix(30, 35);
  mcm_->AddMatrix(35, 15);
  mcm_->AddMatrix(15, 5);
  mcm_->AddMatrix(5, 10);
  mcm_->AddMatrix(10, 20);
  mcm_->AddMatrix(20, 25);
  int32_t count = 0;
  Matrix cmat = mcm_->matrices_[0];
  for (int32_t index = 1; index < mcm_->number_of_matrices_; ++index) {
    count += MatrixChainMultiplication::GetMultiplyCount(cmat, mcm_->matrices_[index]);
    cmat = MatrixChainMultiplication::GetMultipliedMatrix(cmat, mcm_->matrices_[index]);
  }
  ASSERT_LT(kMinimum, count);
}

TEST_F(Test_ALDS1_10_B, CalculateMinMultiplyCount_1) {
  constexpr int32_t kAnswer1 = 15125;
  mcm_->AddMatrix(30, 35);
  mcm_->AddMatrix(35, 15);
  mcm_->AddMatrix(15, 5);
  mcm_->AddMatrix(5, 10);
  mcm_->AddMatrix(10, 20);
  mcm_->AddMatrix(20, 25);
  const int32_t result_1 = mcm_->CalculateMinMultiplyCount();
  ASSERT_EQ(kAnswer1, result_1);
}

}  // namespace ALDS1_10_B
