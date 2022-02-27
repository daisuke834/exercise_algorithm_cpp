/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-3. 高度なグラフアルゴリズム、関節点(Articulation Point)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/C15_3_GRL_3_A_articulation_point.h"

namespace GRL_3_A {

class Test_GRL_3_A : public ::testing::Test {
 protected:
  ArticulationPoint* articulation_point_;
  virtual void SetUp() { articulation_point_ = new ArticulationPoint(); }
  virtual void TearDown() { delete articulation_point_; }
};

TEST_F(Test_GRL_3_A, CallArticulationPoint_1) {
  std::ostringstream answer;
  answer << "2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4 4" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "0 2" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "2 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallArticulationPoint(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_3_A, CallArticulationPoint_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5 4" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "2 3" << std::endl;
  input_stream << "3 4" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallArticulationPoint(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_3_A, CallArticulationPoint_3) {
  std::ostringstream answer;

  std::ostringstream input_stream;
  input_stream << "1 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallArticulationPoint(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_3_A, CallArticulationPoint_4) {
  std::ostringstream answer;
  answer << "2" << std::endl;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "7 10" << std::endl;
  input_stream << "0 2" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "2 3" << std::endl;
  input_stream << "3 4" << std::endl;
  input_stream << "3 6" << std::endl;
  input_stream << "3 5" << std::endl;
  input_stream << "4 5" << std::endl;
  input_stream << "4 6" << std::endl;
  input_stream << "5 6" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallArticulationPoint(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_GRL_3_A, CallArticulationPoint_5) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;
  answer << "4" << std::endl;
  answer << "5" << std::endl;
  answer << "7" << std::endl;

  std::ostringstream input_stream;
  input_stream << "13 14" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "2 3" << std::endl;
  input_stream << "2 4" << std::endl;
  input_stream << "2 5" << std::endl;
  input_stream << "3 6" << std::endl;
  input_stream << "3 7" << std::endl;
  input_stream << "4 8" << std::endl;
  input_stream << "5 9" << std::endl;
  input_stream << "5 10" << std::endl;
  input_stream << "7 11" << std::endl;
  input_stream << "7 12" << std::endl;
  input_stream << "6 1" << std::endl;
  input_stream << "3 12" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallArticulationPoint(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace GRL_3_A
