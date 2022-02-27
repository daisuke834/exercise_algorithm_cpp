/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-2. データ構造、スタック。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C04_2_ALDS1_3_A_stack.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
namespace ALDS1_3_A {

DataType JudgeDataType(const std::string& str) {
  DataType data_type;
  if (std::all_of(str.cbegin(), str.cend(), isdigit)) {
    data_type = DataType::kValue;
  } else if (str == "+") {
    data_type = DataType::kPlus;
  } else if (str == "-") {
    data_type = DataType::kMinus;
  } else if (str == "*") {
    data_type = DataType::kMultiply;
  } else {
    std::cerr << "ERROR: JudgeDataType(): Invalid input data. " << str << std::endl;
    throw 1;
  }
  return data_type;
}

LoadedData LoadOne(std::istream& input_stream) {
  LoadedData data;
  try {
    std::string loaded_str;
    input_stream >> loaded_str;
    if (input_stream.eof()) {
      data.data_type = DataType::kEOF;
      data.value = 0;
    } else {
      data.data_type = JudgeDataType(loaded_str);
      if (data.data_type == DataType::kValue) {
        data.value = stoi(loaded_str);
      } else {
        data.value = 0;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: LoadOne()" << std::endl;
    throw;
  }
  return data;
}

Stack::Stack() noexcept : top_position_(0), values_{0} {}

Stack::~Stack() noexcept {}

void Stack::Main(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  try {
    LoadAndCompute(input_stream);
    PopAndPrint();
  } catch (...) {
    std::cerr << "ERROR: Main()" << std::endl;
  }
}

void Stack::LoadAndCompute(std::istream& input_stream) {
  constexpr int32_t kMaxNumberOfInputs = 200;
  try {
    for (int32_t i = 0; i < kMaxNumberOfInputs; ++i) {
      const LoadedData data = LoadOne(input_stream);
      if (data.data_type == DataType::kEOF) {
        break;
      } else {
        switch (data.data_type) {
          int32_t x;
          int32_t y;
          case DataType::kValue:
            Push(data.value);
            break;
          case DataType::kPlus:
            y = Pop();
            x = Pop();
            Push(x + y);
            break;
          case DataType::kMinus:
            y = Pop();
            x = Pop();
            Push(x - y);
            break;
          case DataType::kMultiply:
            y = Pop();
            x = Pop();
            Push(x * y);
            break;
          default:
            throw 1;
        }
      }
    }
  } catch (...) {
    std::cerr << "ERROR: Load()" << std::endl;
    throw;
  }
}

void Stack::PopAndPrint() noexcept { std::cout << Pop() << std::endl; }

bool Stack::IsEmpty() const noexcept { return (top_position_ <= 0); }

bool Stack::IsFull() const noexcept { return (top_position_ >= kMaxArraySize); }

void Stack::Push(const int32_t x) {
  if (IsFull()) {
    std::cerr << "ERROR: Push(): stack is full." << std::endl;
    throw 1;
  }
  values_[top_position_] = x;
  ++top_position_;
}

int32_t Stack::Pop() {
  if (IsEmpty()) {
    std::cerr << "ERROR: Pop(): stack is empty." << std::endl;
    throw 1;
  }
  --top_position_;
  return values_[top_position_];
}

}  // namespace ALDS1_3_A
