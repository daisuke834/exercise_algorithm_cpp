/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-2. 重み付きグラフ(Weighted Graph)、最小全域木(Minimum Spanning Tree, MST)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C13_2_ALDS1_12_A_2_minimum_spanning_tree.h"

namespace ALDS1_12_A_2 {

class Test_ALDS1_12_A_2 : public ::testing::Test {
 protected:
  MinimumSpanningTree *minimum_spanning_tree_;
  virtual void SetUp() {
    minimum_spanning_tree_ = new MinimumSpanningTree();
  }
  virtual void TearDown() {
    delete minimum_spanning_tree_;
  }
};

TEST_F(Test_ALDS1_12_A_2, Constructor) {
  for (Vertex &vertex : minimum_spanning_tree_->vertices_) {
    ASSERT_EQ(VertexStatus::kUnchecked, vertex.status);
    ASSERT_EQ(INT32_MAX, vertex.minimum_distance_to_this);
    ASSERT_EQ(kInvalidVertex, vertex.parent);
  }
}

TEST_F(Test_ALDS1_12_A_2, CallMinimumSpanningTree_1) {
  std::ostringstream answer;
  answer << "5" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "-1 2 3 1 -1" << std::endl;
  input_stream << "2 -1 -1 4 -1" << std::endl;
  input_stream << "3 -1 -1 1 1" << std::endl;
  input_stream << "1 4 1 -1 3" << std::endl;
  input_stream << "-1 -1 1 3 -1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallMinimumSpanningTree(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_12_A_2, AddWeight) {
  int32_t kNumberOfVertices = 5;
  minimum_spanning_tree_->SetNumberOfVertices(kNumberOfVertices);
  minimum_spanning_tree_->AddWeight(0, 1, 2);
  minimum_spanning_tree_->AddWeight(0, 2, 3);
  minimum_spanning_tree_->AddWeight(0, 3, 1);
  minimum_spanning_tree_->AddWeight(1, 0, 2);
  minimum_spanning_tree_->AddWeight(1, 3, 4);
  minimum_spanning_tree_->AddWeight(2, 0, 3);
  minimum_spanning_tree_->AddWeight(2, 3, 1);
  minimum_spanning_tree_->AddWeight(2, 4, 1);
  minimum_spanning_tree_->AddWeight(3, 0, 1);
  minimum_spanning_tree_->AddWeight(3, 1, 4);
  minimum_spanning_tree_->AddWeight(3, 2, 1);
  minimum_spanning_tree_->AddWeight(3, 4, 3);
  minimum_spanning_tree_->AddWeight(4, 2, 1);
  minimum_spanning_tree_->AddWeight(4, 3, 3);

  ASSERT_EQ(5, minimum_spanning_tree_->number_of_vertices_);

  const int32_t correct_matrix[5][5] = {{kInvalidWeight, 2, 3, 1, kInvalidWeight},
                                        {2, kInvalidWeight, kInvalidWeight, 4, kInvalidWeight},
                                        {3, kInvalidWeight, kInvalidWeight, 1, 1},
                                        {1, 4, 1, kInvalidWeight, 3},
                                        {kInvalidWeight, kInvalidWeight, 1, 3, kInvalidWeight}};
  for (int32_t from = 0; from < kNumberOfVertices; ++from) {
    for (int32_t to = 0; to < kNumberOfVertices; ++to) {
      const int32_t correct_answer = correct_matrix[from][to];
      const int32_t result = minimum_spanning_tree_->adjacency_matrix_[from][to];
      ASSERT_EQ(correct_answer, result);
    }
  }
}

TEST_F(Test_ALDS1_12_A_2, FindNextVertexToAdd) {
  int32_t kNumberOfVertices = 5;
  minimum_spanning_tree_->SetNumberOfVertices(kNumberOfVertices);
  minimum_spanning_tree_->AddWeight(0, 1, 2);
  minimum_spanning_tree_->AddWeight(0, 2, 3);
  minimum_spanning_tree_->AddWeight(0, 3, 1);
  minimum_spanning_tree_->AddWeight(1, 0, 2);
  minimum_spanning_tree_->AddWeight(1, 3, 4);
  minimum_spanning_tree_->AddWeight(2, 0, 3);
  minimum_spanning_tree_->AddWeight(2, 3, 1);
  minimum_spanning_tree_->AddWeight(2, 4, 1);
  minimum_spanning_tree_->AddWeight(3, 0, 1);
  minimum_spanning_tree_->AddWeight(3, 1, 4);
  minimum_spanning_tree_->AddWeight(3, 2, 1);
  minimum_spanning_tree_->AddWeight(3, 4, 3);
  minimum_spanning_tree_->AddWeight(4, 2, 1);
  minimum_spanning_tree_->AddWeight(4, 3, 3);

  int32_t next_vertex_to_add;
  next_vertex_to_add = kRootVertex;
  minimum_spanning_tree_->QueueVertexAsRoot(next_vertex_to_add);
  ASSERT_EQ(next_vertex_to_add, minimum_spanning_tree_->FindNextVertexToAdd());
  minimum_spanning_tree_->AddVertexToTree(next_vertex_to_add);
  ASSERT_EQ(0, minimum_spanning_tree_->GetSumOfWeights());

  next_vertex_to_add = 3;
  ASSERT_EQ(next_vertex_to_add, minimum_spanning_tree_->FindNextVertexToAdd());
  minimum_spanning_tree_->AddVertexToTree(next_vertex_to_add);
  ASSERT_EQ(1, minimum_spanning_tree_->GetSumOfWeights());

  next_vertex_to_add = 2;
  ASSERT_EQ(next_vertex_to_add, minimum_spanning_tree_->FindNextVertexToAdd());
  minimum_spanning_tree_->AddVertexToTree(next_vertex_to_add);

  next_vertex_to_add = 4;
  ASSERT_EQ(next_vertex_to_add, minimum_spanning_tree_->FindNextVertexToAdd());
  minimum_spanning_tree_->AddVertexToTree(next_vertex_to_add);

  next_vertex_to_add = 1;
  ASSERT_EQ(next_vertex_to_add, minimum_spanning_tree_->FindNextVertexToAdd());
  minimum_spanning_tree_->AddVertexToTree(next_vertex_to_add);

  ASSERT_EQ(kInvalidVertex, minimum_spanning_tree_->FindNextVertexToAdd());
}

}  // namespace ALDS1_12_A_2
