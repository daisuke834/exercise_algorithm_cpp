/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include "src/mint.h"

namespace mint {
class Test_Mint : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_Mint, Cout) {
  Mint x = 2;
  testing::internal::CaptureStdout();
  std::cout << x << std::endl;
  const std::string captured_stdout = testing::internal::GetCapturedStdout();

  std::ostringstream answer;
  answer << "2" << std::endl;

  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_Mint, Init) {
  Mint x_1;
  ASSERT_EQ(0, x_1.value);

  Mint x_2(2);
  ASSERT_EQ(2, x_2.value);

  Mint x_3 = 3;
  ASSERT_EQ(3, x_3.value);

  Mint x_4 = x_2;
  ASSERT_EQ(2, x_4.value);

  Mint x_5 = -1;
  ASSERT_EQ(1000000006LL, x_5.value);
}

TEST_F(Test_Mint, Increment) {
  // 1000000007LL
  Mint x = 1000000005LL;
  ASSERT_EQ(1000000005LL, x.value);
  x += 1;
  ASSERT_EQ(1000000006LL, x.value);
  x += 1;
  ASSERT_EQ(0LL, x.value);
  x += 1;
  ASSERT_EQ(1LL, x.value);

  ASSERT_EQ(5LL, (Mint(2) + Mint(3)).value);
}

TEST_F(Test_Mint, Decrement) {
  // 1000000007LL
  Mint x = 2;
  ASSERT_EQ(2LL, x.value);
  x -= 1;
  ASSERT_EQ(1LL, x.value);
  x -= 1;
  ASSERT_EQ(0LL, x.value);
  x -= 1;
  ASSERT_EQ(1000000006LL, x.value);

  ASSERT_EQ(5LL, (Mint(9) - Mint(4)).value);
}

TEST_F(Test_Mint, Multiply) {
  // 1000000007LL
  Mint x = 220000000;
  ASSERT_EQ(220000000LL, x.value);
  x *= 2;
  ASSERT_EQ(440000000LL, x.value);
  x = 220000000;
  ASSERT_EQ(220000000LL, x.value);
  x *= 10;
  ASSERT_EQ(199999986LL, x.value);

  ASSERT_EQ(36LL, (Mint(9) * Mint(4)).value);
}

TEST_F(Test_Mint, Inv) {
  Mint x = 5;
  Mint y = x.Inv();
  Mint z = x * y;
  ASSERT_EQ(1LL, z.value);
}

TEST_F(Test_Mint, Pow) {
  Mint x = 5;
  ASSERT_EQ(5LL, x.value);
  ASSERT_EQ(1LL, x.Pow(0).value);
  ASSERT_EQ(x.value, x.Pow(1).value);
  ASSERT_EQ(x.value * x.value, x.Pow(2).value);
  ASSERT_EQ(x.value * x.value * x.value, x.Pow(3).value);
  ASSERT_EQ(1LL, (x.Pow(3) * x.Pow(-3)).value);
}

}  // namespace mint
