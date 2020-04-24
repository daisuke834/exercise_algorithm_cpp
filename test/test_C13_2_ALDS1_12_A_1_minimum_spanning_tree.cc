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
#include "src/C13_2_ALDS1_12_A_1_minimum_spanning_tree.h"

namespace ALDS1_12_A_1 {

class Test_ALDS1_12_A_1 : public ::testing::Test {
 protected:
  MinimumSpanningTree *minimum_spanning_tree_;
  virtual void SetUp() {
    minimum_spanning_tree_ = new MinimumSpanningTree();
  }
  virtual void TearDown() {
    delete minimum_spanning_tree_;
  }
};

TEST_F(Test_ALDS1_12_A_1, CanAppendWeightToEdgeArray) {
  constexpr int32_t kValidWeight = 1;
  constexpr int32_t kInvalidWeight = -1;
  ASSERT_TRUE(MinimumSpanningTree::ValidWeight(kValidWeight));
  ASSERT_FALSE(MinimumSpanningTree::ValidWeight(kInvalidWeight));

  ASSERT_FALSE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(0, 0, kValidWeight));
  ASSERT_FALSE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(0, 1, kInvalidWeight));
  ASSERT_TRUE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(0, 1, kValidWeight));
  ASSERT_TRUE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(1, 0, kValidWeight));
  ASSERT_FALSE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(0, 2, kInvalidWeight));
  ASSERT_TRUE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(0, 2, kValidWeight));
  ASSERT_TRUE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(2, 0, kValidWeight));

  minimum_spanning_tree_->adjacency_matrix_[0][1] = kValidWeight;
  minimum_spanning_tree_->adjacency_matrix_[1][0] = kValidWeight;
  ASSERT_FALSE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(0, 0, kValidWeight));
  ASSERT_FALSE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(0, 1, kInvalidWeight));
  ASSERT_FALSE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(0, 1, kValidWeight));
  ASSERT_FALSE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(1, 0, kValidWeight));
  ASSERT_FALSE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(0, 2, kInvalidWeight));
  ASSERT_TRUE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(0, 2, kValidWeight));
  ASSERT_TRUE(minimum_spanning_tree_->CanAppendWeightToEdgeArray(2, 0, kValidWeight));
}

TEST_F(Test_ALDS1_12_A_1, CallMinimumSpanningTree_1) {
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

TEST_F(Test_ALDS1_12_A_1, AddWeight) {
  int32_t kNumberOfVertices = 5;
  minimum_spanning_tree_->SetNumberOfVertices(kNumberOfVertices);
  minimum_spanning_tree_->AddWeight(0, 1, 2);
  minimum_spanning_tree_->AddWeight(0, 2, 3);
  minimum_spanning_tree_->AddWeight(0, 3, 1);
  minimum_spanning_tree_->AddWeight(1, 3, 4);
  minimum_spanning_tree_->AddWeight(2, 3, 1);
  minimum_spanning_tree_->AddWeight(2, 4, 1);
  minimum_spanning_tree_->AddWeight(3, 4, 3);

  ASSERT_EQ(5, minimum_spanning_tree_->number_of_vertices_);

  const int32_t correct_matrix[5][5] = {
      {-1, 2, 3, 1, -1}, {2, -1, -1, 4, -1}, {3, -1, -1, 1, 1}, {1, 4, 1, -1, 3}, {-1, -1, 1, 3, -1}};
  for (int32_t from = 0; from < kNumberOfVertices; ++from) {
    for (int32_t to = 0; to < kNumberOfVertices; ++to) {
      const int32_t correct_answer = correct_matrix[from][to];
      const int32_t result = minimum_spanning_tree_->adjacency_matrix_[from][to];
      ASSERT_EQ(correct_answer, result);
    }
  }

  ASSERT_EQ(7, minimum_spanning_tree_->number_of_edges_);

  int32_t edge_index = 0;
  ASSERT_EQ(0, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(1, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(2, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(0, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(2, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(0, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(1, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(1, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(4, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(2, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(1, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(2, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(4, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(1, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(4, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;
}

TEST_F(Test_ALDS1_12_A_1, ComputeQuickSort) {
  int32_t kNumberOfVertices = 5;
  minimum_spanning_tree_->SetNumberOfVertices(kNumberOfVertices);
  minimum_spanning_tree_->AddWeight(0, 1, 2);
  minimum_spanning_tree_->AddWeight(0, 2, 3);
  minimum_spanning_tree_->AddWeight(0, 3, 1);
  minimum_spanning_tree_->AddWeight(1, 3, 8);
  minimum_spanning_tree_->AddWeight(2, 3, 9);
  minimum_spanning_tree_->AddWeight(2, 4, 4);
  minimum_spanning_tree_->AddWeight(3, 4, 7);
  minimum_spanning_tree_->ComputeQuickSort(0, minimum_spanning_tree_->number_of_edges_ - 1);

  int32_t edge_index = 0;
  ASSERT_EQ(0, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(1, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(0, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(1, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(2, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(0, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(2, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(2, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(4, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(4, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(4, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(7, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(1, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(8, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;

  ASSERT_EQ(2, minimum_spanning_tree_->edges_[edge_index].vertex_1);
  ASSERT_EQ(3, minimum_spanning_tree_->edges_[edge_index].vertex_2);
  ASSERT_EQ(9, minimum_spanning_tree_->edges_[edge_index].weight);
  ++edge_index;
}

}  // namespace ALDS1_12_A_1
