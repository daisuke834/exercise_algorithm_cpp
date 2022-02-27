/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 176-D. Wizard in Maze.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/AtCoder/ABC/176_D_2_grid_Dijkstra.h"

namespace D_ABC_176_D_2 {

class Test_D_ABC_176_D_2 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_D_ABC_176_D_2, test_1) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 4" << std::endl;
  input_stream << "1 1" << std::endl;
  input_stream << "4 4" << std::endl;
  input_stream << "..#." << std::endl;
  input_stream << "..#." << std::endl;
  input_stream << ".#.." << std::endl;
  input_stream << ".#.." << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_D_ABC_176_D_2, test_2) {
  std::ostringstream answer;
  answer << "-1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 4" << std::endl;
  input_stream << "1 4" << std::endl;
  input_stream << "4 1" << std::endl;
  input_stream << ".##." << std::endl;
  input_stream << "####" << std::endl;
  input_stream << "####" << std::endl;
  input_stream << ".##." << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_D_ABC_176_D_2, test_3) {
  std::ostringstream answer;
  answer << "0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 4" << std::endl;
  input_stream << "2 2" << std::endl;
  input_stream << "3 3" << std::endl;
  input_stream << "...." << std::endl;
  input_stream << "...." << std::endl;
  input_stream << "...." << std::endl;
  input_stream << "...." << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_D_ABC_176_D_2, test_4) {
  std::ostringstream answer;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 5" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "2 5" << std::endl;
  input_stream << "#.###" << std::endl;
  input_stream << "####." << std::endl;
  input_stream << "#..##" << std::endl;
  input_stream << "#..##" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMain(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace D_ABC_176_D_2
