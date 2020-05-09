/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-4. 木の直径(Diameter of a Tree)。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C15_4_GRL_5_A_diameter_of_tree.h"

namespace GRL_5_A {

class Test_GRL_5_A : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_GRL_5_A, CallTreeDiameter_1) {
  std::ostringstream answer;
  answer << "5" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4" << std::endl;
  input_stream << "0 1 2" << std::endl;
  input_stream << "1 2 1" << std::endl;
  input_stream << "1 3 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeDiameter(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_5_A, CallTreeDiameter_2) {
  std::ostringstream answer;
  answer << "7" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4" << std::endl;
  input_stream << "0 1 1" << std::endl;
  input_stream << "1 2 2" << std::endl;
  input_stream << "2 3 4" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeDiameter(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace GRL_5_A
