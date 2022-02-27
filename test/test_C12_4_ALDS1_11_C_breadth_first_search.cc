/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-4. グラフ(Graph)、幅優先探索(Breadth First Search, BFS)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/C12_4_ALDS1_11_C_breadth_first_search.h"

namespace ALDS1_11_C {

class Test_ALDS1_11_C : public ::testing::Test {
 protected:
  BreadthFirstSearch* breadth_first_search_;
  virtual void SetUp() { breadth_first_search_ = new BreadthFirstSearch(); }
  virtual void TearDown() { delete breadth_first_search_; }
};

TEST_F(Test_ALDS1_11_C, CallBreadthFirstSearch_1) {
  std::ostringstream answer;
  answer << "1 0" << std::endl;
  answer << "2 1" << std::endl;
  answer << "3 2" << std::endl;
  answer << "4 1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4" << std::endl;
  input_stream << "1 2 2 4" << std::endl;
  input_stream << "2 1 4" << std::endl;
  input_stream << "3 0" << std::endl;
  input_stream << "4 1 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBreadthFirstSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_11_C, CallBreadthFirstSearch_2) {
  std::ostringstream answer;
  answer << "1 0" << std::endl;
  answer << "2 1" << std::endl;
  answer << "3 1" << std::endl;
  answer << "4 1" << std::endl;
  answer << "5 2" << std::endl;
  answer << "6 3" << std::endl;
  answer << "7 3" << std::endl;
  answer << "8 3" << std::endl;
  answer << "9 3" << std::endl;
  answer << "10 2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10" << std::endl;
  input_stream << "1 3 2 3 4" << std::endl;
  input_stream << "2 0" << std::endl;
  input_stream << "3 1 5" << std::endl;
  input_stream << "4 1 10" << std::endl;
  input_stream << "5 5 6 7 8 9 10" << std::endl;
  input_stream << "6 1 2" << std::endl;
  input_stream << "7 0" << std::endl;
  input_stream << "8 1 7" << std::endl;
  input_stream << "9 1 10" << std::endl;
  input_stream << "10 1 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBreadthFirstSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_11_C, CallBreadthFirstSearch_3) {
  std::ostringstream answer;
  answer << "1 0" << std::endl;
  answer << "2 1" << std::endl;
  answer << "3 1" << std::endl;
  answer << "4 1" << std::endl;
  answer << "5 1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "1 4 2 3 4 5" << std::endl;
  input_stream << "2 4 1 3 4 5" << std::endl;
  input_stream << "3 4 1 2 4 5" << std::endl;
  input_stream << "4 4 1 2 3 5" << std::endl;
  input_stream << "5 4 1 2 3 4" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBreadthFirstSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_11_C
