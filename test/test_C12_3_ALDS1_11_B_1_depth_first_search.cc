/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-3. グラフ(Graph)、深さ優先探索(Depth First Search, DFS)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/C12_3_ALDS1_11_B_1_depth_first_search.h"

namespace ALDS1_11_B_1 {

class Test_ALDS1_11_B_1 : public ::testing::Test {
 protected:
  DepthFirstSearch* depth_first_search_;
  virtual void SetUp() { depth_first_search_ = new DepthFirstSearch(); }
  virtual void TearDown() { delete depth_first_search_; }
};

TEST_F(Test_ALDS1_11_B_1, CallDepthFirstSearch_1) {
  std::ostringstream answer;
  answer << "1 1 8" << std::endl;
  answer << "2 2 7" << std::endl;
  answer << "3 4 5" << std::endl;
  answer << "4 3 6" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4" << std::endl;
  input_stream << "1 1 2" << std::endl;
  input_stream << "2 1 4" << std::endl;
  input_stream << "3 0" << std::endl;
  input_stream << "4 1 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDepthFirstSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_11_B_1, CallDepthFirstSearch_2) {
  std::ostringstream answer;
  answer << "1 1 12" << std::endl;
  answer << "2 2 11" << std::endl;
  answer << "3 3 8" << std::endl;
  answer << "4 9 10" << std::endl;
  answer << "5 4 7" << std::endl;
  answer << "6 5 6" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "1 2 2 3" << std::endl;
  input_stream << "2 2 3 4" << std::endl;
  input_stream << "3 1 5" << std::endl;
  input_stream << "4 1 6" << std::endl;
  input_stream << "5 1 6" << std::endl;
  input_stream << "6 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDepthFirstSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_11_B_1, CallDepthFirstSearch_3) {
  std::ostringstream answer;
  answer << "1 1 8" << std::endl;
  answer << "2 2 7" << std::endl;
  answer << "3 9 12" << std::endl;
  answer << "4 4 5" << std::endl;
  answer << "5 3 6" << std::endl;
  answer << "6 10 11" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "1 2 2 4" << std::endl;
  input_stream << "2 1 5" << std::endl;
  input_stream << "3 2 5 6" << std::endl;
  input_stream << "4 0" << std::endl;
  input_stream << "5 1 4" << std::endl;
  input_stream << "6 1 6" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDepthFirstSearch(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_11_B_1, ExploreAllVertices_1) {
  depth_first_search_->AddVertex(1);
  depth_first_search_->MapDirection(1, 2);
  depth_first_search_->AddVertex(2);
  depth_first_search_->MapDirection(2, 4);
  depth_first_search_->AddVertex(3);
  depth_first_search_->AddVertex(4);
  depth_first_search_->MapDirection(4, 3);

  depth_first_search_->ExploreAllVertices();

  int32_t vertex_index = 0;
  ASSERT_EQ(1, depth_first_search_->explored_time_[vertex_index++].Get());
  ASSERT_EQ(2, depth_first_search_->explored_time_[vertex_index++].Get());
  ASSERT_EQ(4, depth_first_search_->explored_time_[vertex_index++].Get());
  ASSERT_EQ(3, depth_first_search_->explored_time_[vertex_index++].Get());

  vertex_index = 0;
  ASSERT_EQ(8, depth_first_search_->completion_time_[vertex_index++].Get());
  ASSERT_EQ(7, depth_first_search_->completion_time_[vertex_index++].Get());
  ASSERT_EQ(5, depth_first_search_->completion_time_[vertex_index++].Get());
  ASSERT_EQ(6, depth_first_search_->completion_time_[vertex_index++].Get());
}

TEST_F(Test_ALDS1_11_B_1, ExploreAllVertices_2) {
  depth_first_search_->AddVertex(1);
  depth_first_search_->MapDirection(1, 2);
  depth_first_search_->MapDirection(1, 3);
  depth_first_search_->AddVertex(2);
  depth_first_search_->MapDirection(2, 3);
  depth_first_search_->MapDirection(2, 4);
  depth_first_search_->AddVertex(3);
  depth_first_search_->MapDirection(3, 5);
  depth_first_search_->AddVertex(4);
  depth_first_search_->MapDirection(4, 6);
  depth_first_search_->AddVertex(5);
  depth_first_search_->MapDirection(5, 6);
  depth_first_search_->AddVertex(6);

  depth_first_search_->ExploreAllVertices();

  int32_t vertex_index = 0;
  ASSERT_EQ(1, depth_first_search_->explored_time_[vertex_index++].Get());
  ASSERT_EQ(2, depth_first_search_->explored_time_[vertex_index++].Get());
  ASSERT_EQ(3, depth_first_search_->explored_time_[vertex_index++].Get());
  ASSERT_EQ(9, depth_first_search_->explored_time_[vertex_index++].Get());
  ASSERT_EQ(4, depth_first_search_->explored_time_[vertex_index++].Get());
  ASSERT_EQ(5, depth_first_search_->explored_time_[vertex_index++].Get());

  vertex_index = 0;
  ASSERT_EQ(12, depth_first_search_->completion_time_[vertex_index++].Get());
  ASSERT_EQ(11, depth_first_search_->completion_time_[vertex_index++].Get());
  ASSERT_EQ(8, depth_first_search_->completion_time_[vertex_index++].Get());
  ASSERT_EQ(10, depth_first_search_->completion_time_[vertex_index++].Get());
  ASSERT_EQ(7, depth_first_search_->completion_time_[vertex_index++].Get());
  ASSERT_EQ(6, depth_first_search_->completion_time_[vertex_index++].Get());
}

}  // namespace ALDS1_11_B_1
