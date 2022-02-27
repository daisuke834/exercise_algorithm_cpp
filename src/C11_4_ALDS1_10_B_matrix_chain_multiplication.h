/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part11-4. 動的計画法(Dynamic Programming, DP)、連鎖行列積問題(Matrix-Chain Multiplication problem)。
 * (start < i < end)の３つのループ構造になり、計算時間=O(n^3), 追加作業記憶領域=O(n^2).
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C11_4_ALDS1_10_B_MATRIX_CHAIN_MULTIPLICATION_H_
#define SRC_C11_4_ALDS1_10_B_MATRIX_CHAIN_MULTIPLICATION_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_10_B {

constexpr int32_t kMaxNumberOfMatrices = 100;
constexpr int32_t kMaxNumberOfRowsAndCols = 100;

void CallMatrixChainMultiplication(std::istream& input_stream);

struct Matrix {
  int32_t number_of_rows{0};
  int32_t number_of_columns{0};
};

struct LookUp {
  bool calculated{false};
  int32_t mcm{INT32_MAX};
};

class MatrixChainMultiplication {
 public:
  MatrixChainMultiplication() noexcept;
  ~MatrixChainMultiplication() noexcept;

  void AddMatrix(const int32_t number_of_rows, const int32_t number_of_columns);
  int32_t CalculateMinMultiplyCount();

  static int32_t GetMultiplyCount(const Matrix& a, const Matrix& b);
  static Matrix GetMultipliedMatrix(const Matrix& a, const Matrix& b);
  static Matrix GenerateMatrix(const int32_t number_of_rows, const int32_t number_of_columns);

 private:
  int32_t CalculateMcmRecursively(const int32_t start, const int32_t end);
  bool IsInvalidIndex(const int32_t index) const noexcept;
  bool IsInvalidArg(const int32_t start, const int32_t end) const noexcept;
  bool IsAlreadyCalculated(const int32_t start, const int32_t end) const;
  int32_t GetCalculatedResult(const int32_t start, const int32_t end) const;
  void StoreCalculatedResult(const int32_t start, const int32_t end, const int32_t mcm);

  MatrixChainMultiplication(const MatrixChainMultiplication& obj) = delete;
  MatrixChainMultiplication& operator=(const MatrixChainMultiplication& obj) = delete;
  MatrixChainMultiplication(MatrixChainMultiplication&& obj) = delete;
  MatrixChainMultiplication& operator=(MatrixChainMultiplication&& obj) = delete;

 private:
  int32_t number_of_matrices_;
  Matrix matrices_[kMaxNumberOfMatrices];
  LookUp look_up_table_[kMaxNumberOfMatrices][kMaxNumberOfMatrices];

 private:
  FRIEND_TEST(Test_ALDS1_10_B, AddMatrix);                         // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_10_B, MultiplyCount_MultipliedMatrix_2);  // Should be removed from production code
};

}  // namespace ALDS1_10_B

#endif  // SRC_C11_4_ALDS1_10_B_MATRIX_CHAIN_MULTIPLICATION_H_
