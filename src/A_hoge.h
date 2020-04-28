/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Summary
 */

#ifndef SRC_A_HOGE_H_
#define SRC_A_HOGE_H_

// #include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>

namespace hoge {

void CallHoge(std::istream &input_stream) noexcept;

class Hoge {
 public:
  Hoge() noexcept;
  ~Hoge() noexcept;
  static int32_t MyFunc() noexcept;

 private:
  Hoge(const Hoge &obj) = delete;
  Hoge &operator=(const Hoge &rhs) = delete;
  Hoge(Hoge &&obj) = delete;
  Hoge &operator=(Hoge &&rhs) = delete;

  //  private:
  //   FRIEND_TEST(HogeTest, Test_1);  // Should be removed from production code
};

}  // namespace hoge
#endif  // SRC_A_HOGE_H_
