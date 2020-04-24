/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Summary
 */

#include "src/A_hoge.h"
#include <iostream>
namespace hoge {

Hoge::Hoge() noexcept {}

Hoge::~Hoge() noexcept {}

int32_t Hoge::MyFunc() noexcept {
  return 10;
}

int32_t ReadUserInput(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  int32_t value;
  // std::cout << "Enter a number: ";
  input_stream >> value;
  return value;
}
}  // namespace hoge
