/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 168-D.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/D_ABC_168_D_1_Dijkstra.h"

namespace ABC_168_D_1 {

class Test_ABC_168_D_1 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_ABC_168_D_1, CallDijkstra_1) {
  std::ostringstream answer;
  answer << "Yes" << std::endl;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 4" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "2 3" << std::endl;
  input_stream << "3 4" << std::endl;
  input_stream << "4 2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDijkstra(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ABC_168_D_1, CallDijkstra_2) {
  std::ostringstream answer;
  answer << "Yes" << std::endl;
  answer << "6" << std::endl;
  answer << "5" << std::endl;
  answer << "5" << std::endl;
  answer << "1" << std::endl;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6 9" << std::endl;
  input_stream << "3 4" << std::endl;
  input_stream << "6 1" << std::endl;
  input_stream << "2 4" << std::endl;
  input_stream << "5 3" << std::endl;
  input_stream << "4 6" << std::endl;
  input_stream << "1 5" << std::endl;
  input_stream << "6 2" << std::endl;
  input_stream << "4 5" << std::endl;
  input_stream << "5 6" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDijkstra(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ABC_168_D_1
