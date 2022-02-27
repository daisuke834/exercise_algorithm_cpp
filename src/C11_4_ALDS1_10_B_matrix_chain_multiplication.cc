/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part11-4. 動的計画法(Dynamic Programming, DP)、連鎖行列積問題(Matrix-Chain Multiplication problem)。
 * (start < i < end)の３つのループ構造になり、計算時間=O(n^3), 追加作業記憶領域=O(n^2).
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C11_4_ALDS1_10_B_matrix_chain_multiplication.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace ALDS1_10_B {

void CallMatrixChainMultiplication(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  MatrixChainMultiplication* matrix_chain_multiplication = new MatrixChainMultiplication();
  try {
    int32_t number_of_matrices;
    input_stream >> number_of_matrices;
    for (int32_t i = 0; i < number_of_matrices; ++i) {
      int32_t number_of_rows, number_of_columns;
      input_stream >> number_of_rows >> number_of_columns;
      matrix_chain_multiplication->AddMatrix(number_of_rows, number_of_columns);
    }
    const int32_t multiply_count = matrix_chain_multiplication->CalculateMinMultiplyCount();
    std::cout << multiply_count << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallMatrixChainMultiplication()" << std::endl;
    throw;
  }
  delete matrix_chain_multiplication;
}

// ****************************************************

MatrixChainMultiplication::MatrixChainMultiplication() noexcept : number_of_matrices_(0) {}

MatrixChainMultiplication::~MatrixChainMultiplication() noexcept {}

void MatrixChainMultiplication::AddMatrix(const int32_t number_of_rows, const int32_t number_of_columns) {
  if (number_of_matrices_ >= kMaxNumberOfMatrices) {
    std::cerr << "ERROR: AddMatrix(): Number of matricis size exceeded a limit = " << kMaxNumberOfMatrices << std::endl;
    throw 1;
  }
  const int32_t store_index = number_of_matrices_;
  ++number_of_matrices_;
  matrices_[store_index] = GenerateMatrix(number_of_rows, number_of_columns);
}

int32_t MatrixChainMultiplication::CalculateMinMultiplyCount() {
  const int32_t count = CalculateMcmRecursively(0, number_of_matrices_ - 1);
  return count;
}

int32_t MatrixChainMultiplication::CalculateMcmRecursively(const int32_t start, const int32_t end) {
  int32_t mcm;
  if (start == end) {
    mcm = 0;
  } else if (IsInvalidArg(start, end)) {
    std::cerr << "ERROR: CalculateMcmRecursively(): Invalid arg start = " << start << ", end = " << end << std::endl;
    throw 1;
  } else {
    try {
      if (IsAlreadyCalculated(start, end)) {
        mcm = GetCalculatedResult(start, end);
      } else {
        mcm = INT32_MAX;
        for (int32_t i = start; i <= end - 1; ++i) {
          const int32_t temp_mcm =
              matrices_[start].number_of_rows * matrices_[i].number_of_columns * matrices_[end].number_of_columns +
              CalculateMcmRecursively(start, i) + CalculateMcmRecursively(i + 1, end);
          mcm = std::min(mcm, temp_mcm);
        }
        StoreCalculatedResult(start, end, mcm);
      }
    } catch (...) {
      std::cerr << "ERROR: CalculateMcmRecursively()" << std::endl;
      throw;
    }
  }
  return mcm;
}

bool MatrixChainMultiplication::IsInvalidIndex(const int32_t index) const noexcept {
  return ((index < 0) || (index > number_of_matrices_));
}

bool MatrixChainMultiplication::IsInvalidArg(const int32_t start, const int32_t end) const noexcept {
  const bool is_invalid_start = IsInvalidIndex(start);
  const bool is_invalid_end = IsInvalidIndex(end);
  const bool is_invalid_order = (start > end);
  return is_invalid_start || is_invalid_end || is_invalid_order;
}

bool MatrixChainMultiplication::IsAlreadyCalculated(const int32_t start, const int32_t end) const {
  if (IsInvalidArg(start, end)) {
    std::cerr << "ERROR: IsAlreadyCalculated(): start = " << start << ", end = " << end << std::endl;
    throw 1;
  }
  return look_up_table_[start][end].calculated;
}

int32_t MatrixChainMultiplication::GetCalculatedResult(const int32_t start, const int32_t end) const {
  if (IsInvalidArg(start, end)) {
    std::cerr << "ERROR: GetCalculatedResult(): start = " << start << ", end = " << end << std::endl;
    throw 1;
  }
  return look_up_table_[start][end].mcm;
}

void MatrixChainMultiplication::StoreCalculatedResult(const int32_t start, const int32_t end, const int32_t mcm) {
  if (IsInvalidArg(start, end)) {
    std::cerr << "ERROR: GetCalculatedResult(): start = " << start << ", end = " << end << std::endl;
    throw 1;
  }
  look_up_table_[start][end].mcm = mcm;
  look_up_table_[start][end].calculated = true;
}

int32_t MatrixChainMultiplication::GetMultiplyCount(const Matrix& a, const Matrix& b) {
  if (a.number_of_columns != b.number_of_rows) {
    std::cerr << "ERROR: GetMultiplyCount(): Invalid a.number_of_columns = " << a.number_of_columns
              << ", b.number_of_rows = " << b.number_of_rows << std::endl;
    throw 1;
  }
  return a.number_of_rows * a.number_of_columns * b.number_of_columns;
}

Matrix MatrixChainMultiplication::GetMultipliedMatrix(const Matrix& a, const Matrix& b) {
  if (a.number_of_columns != b.number_of_rows) {
    std::cerr << "ERROR: GetMultipliedMatrix(): Invalid a.number_of_columns = " << a.number_of_columns
              << ", b.number_of_rows = " << b.number_of_rows << std::endl;
    throw 1;
  }
  const Matrix result = GenerateMatrix(a.number_of_rows, b.number_of_columns);
  return result;
}

Matrix MatrixChainMultiplication::GenerateMatrix(const int32_t number_of_rows, const int32_t number_of_columns) {
  Matrix mat;
  mat.number_of_rows = number_of_rows;
  mat.number_of_columns = number_of_columns;
  return mat;
}

}  // namespace ALDS1_10_B
