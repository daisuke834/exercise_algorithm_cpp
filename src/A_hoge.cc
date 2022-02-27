/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Summary
 */

#include "src/A_hoge.h"

#include <iostream>
namespace hoge {

void CallHoge(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  Hoge* hoge = new Hoge();
  try {
    int32_t value;
    input_stream >> value;
    std::cout << value << std::endl;
  } catch (...) {
    std::cerr << "ERROR: CallHoge()" << std::endl;
    // DO NOT THROW EXCEPTION
  }
  delete hoge;
}

Hoge::Hoge() noexcept {}

Hoge::~Hoge() noexcept {}

int32_t Hoge::MyFunc() noexcept { return 10; }

}  // namespace hoge
