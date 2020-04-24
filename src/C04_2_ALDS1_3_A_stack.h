/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-2. データ構造、スタック。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C04_2_ALDS1_3_A_STACK_H_
#define SRC_C04_2_ALDS1_3_A_STACK_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_3_A {

enum class DataType : int32_t { kValue = 0, kPlus, kMinus, kMultiply, kEOF };

struct LoadedData {
  DataType data_type{DataType::kValue};
  int32_t value{0};
};

DataType JudgeDataType(const std::string &str);

LoadedData LoadOne(std::istream &input_stream);

constexpr int32_t kMaxArraySize = 100;

class Stack {
 public:
  Stack() noexcept;
  ~Stack() noexcept;
  void Main(std::istream &input_stream) noexcept;
  void LoadAndCompute(std::istream &input_stream);
  void Push(const int32_t x);
  int32_t Pop();
  bool IsEmpty() const noexcept;
  bool IsFull() const noexcept;

 private:
  void PopAndPrint() noexcept;

 private:
  Stack(const Stack &obj) = delete;
  Stack &operator=(const Stack &rhs) = delete;
  Stack(Stack &&obj) = delete;
  Stack &operator=(Stack &&rhs) = delete;

 private:
  int32_t top_position_;
  int32_t values_[kMaxArraySize];
};

}  // namespace ALDS1_3_A
#endif  // SRC_C04_2_ALDS1_3_A_STACK_H_
