/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part13-3. 重み付きグラフ(Weighted Graph)、単一始点最短経路(Single Source Shortest Path)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C13_3_ALDS1_12_B_2_single_source_shortest_path.h"

namespace ALDS1_12_B_2 {

class Test_ALDS1_12_B_2 : public ::testing::Test {
 protected:
  DijkstraAlgorithm *single_source_shortest_path_;
  virtual void SetUp() {
    single_source_shortest_path_ = new DijkstraAlgorithm();
  }
  virtual void TearDown() {
    delete single_source_shortest_path_;
  }
};

TEST_F(Test_ALDS1_12_B_2, Constructor) {
  for (Vertex &vertex : single_source_shortest_path_->vertices_) {
    ASSERT_EQ(VertexStatus::kUnchecked, vertex.status);
    ASSERT_EQ(INT32_MAX, vertex.distance_from_root);
    ASSERT_EQ(kInvalidVertex, vertex.parent);
  }
}

TEST_F(Test_ALDS1_12_B_2, CallDijkstraAlgorithm_1) {
  std::ostringstream answer;
  answer << "0 0" << std::endl;
  answer << "1 2" << std::endl;
  answer << "2 2" << std::endl;
  answer << "3 1" << std::endl;
  answer << "4 3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "0 3 2 3 3 1 1 2" << std::endl;
  input_stream << "1 2 0 2 3 4" << std::endl;
  input_stream << "2 3 0 3 3 1 4 1" << std::endl;
  input_stream << "3 4 2 1 0 1 1 4 4 3" << std::endl;
  input_stream << "4 2 2 1 3 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallDijkstraAlgorithm(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_12_B_2, AddWeight_1) {
  int32_t kNumberOfVertices = 5;
  single_source_shortest_path_->SetNumberOfVertices(kNumberOfVertices);
  single_source_shortest_path_->AddWeight(0, 1, 2);
  single_source_shortest_path_->AddWeight(0, 2, 3);
  single_source_shortest_path_->AddWeight(0, 3, 1);
  single_source_shortest_path_->AddWeight(1, 0, 2);
  single_source_shortest_path_->AddWeight(1, 3, 4);
  single_source_shortest_path_->AddWeight(2, 0, 3);
  single_source_shortest_path_->AddWeight(2, 3, 1);
  single_source_shortest_path_->AddWeight(2, 4, 1);
  single_source_shortest_path_->AddWeight(3, 0, 1);
  single_source_shortest_path_->AddWeight(3, 1, 4);
  single_source_shortest_path_->AddWeight(3, 2, 1);
  single_source_shortest_path_->AddWeight(3, 4, 3);
  single_source_shortest_path_->AddWeight(4, 2, 1);
  single_source_shortest_path_->AddWeight(4, 3, 3);

  ASSERT_EQ(5, single_source_shortest_path_->number_of_vertices_);

  const int32_t correct_matrix[5][5] = {{kInvalidWeight, 2, 3, 1, kInvalidWeight},
                                        {2, kInvalidWeight, kInvalidWeight, 4, kInvalidWeight},
                                        {3, kInvalidWeight, kInvalidWeight, 1, 1},
                                        {1, 4, 1, kInvalidWeight, 3},
                                        {kInvalidWeight, kInvalidWeight, 1, 3, kInvalidWeight}};
  for (int32_t from = 0; from < kNumberOfVertices; ++from) {
    for (int32_t to = 0; to < kNumberOfVertices; ++to) {
      const int32_t correct_answer = correct_matrix[from][to];
      const int32_t result = single_source_shortest_path_->GetWeight(from, to);
      ASSERT_EQ(correct_answer, result);
    }
  }
}

TEST_F(Test_ALDS1_12_B_2, FindNextVertexToAdd) {
  int32_t kNumberOfVertices = 5;
  single_source_shortest_path_->SetNumberOfVertices(kNumberOfVertices);
  single_source_shortest_path_->AddWeight(0, 1, 2);
  single_source_shortest_path_->AddWeight(0, 2, 3);
  single_source_shortest_path_->AddWeight(0, 3, 1);
  single_source_shortest_path_->AddWeight(1, 0, 2);
  single_source_shortest_path_->AddWeight(1, 3, 4);
  single_source_shortest_path_->AddWeight(2, 0, 3);
  single_source_shortest_path_->AddWeight(2, 3, 1);
  single_source_shortest_path_->AddWeight(2, 4, 1);
  single_source_shortest_path_->AddWeight(3, 0, 1);
  single_source_shortest_path_->AddWeight(3, 1, 4);
  single_source_shortest_path_->AddWeight(3, 2, 1);
  single_source_shortest_path_->AddWeight(3, 4, 3);
  single_source_shortest_path_->AddWeight(4, 2, 1);
  single_source_shortest_path_->AddWeight(4, 3, 3);

  int32_t next_vertex_to_add;
  next_vertex_to_add = kRootVertex;
  single_source_shortest_path_->QueueVertexAsRoot(next_vertex_to_add);
  ASSERT_EQ(next_vertex_to_add, single_source_shortest_path_->FindNextVertexToAdd());
  single_source_shortest_path_->AddVertexToTree(next_vertex_to_add);
  ASSERT_EQ(0, single_source_shortest_path_->vertices_[next_vertex_to_add].distance_from_root);

  next_vertex_to_add = 3;
  ASSERT_EQ(next_vertex_to_add, single_source_shortest_path_->FindNextVertexToAdd());
  single_source_shortest_path_->AddVertexToTree(next_vertex_to_add);
  ASSERT_EQ(1, single_source_shortest_path_->vertices_[next_vertex_to_add].distance_from_root);

  next_vertex_to_add = 2;
  ASSERT_EQ(next_vertex_to_add, single_source_shortest_path_->FindNextVertexToAdd());
  single_source_shortest_path_->AddVertexToTree(next_vertex_to_add);
  ASSERT_EQ(2, single_source_shortest_path_->vertices_[next_vertex_to_add].distance_from_root);

  next_vertex_to_add = 1;
  ASSERT_EQ(next_vertex_to_add, single_source_shortest_path_->FindNextVertexToAdd());
  single_source_shortest_path_->AddVertexToTree(next_vertex_to_add);
  ASSERT_EQ(2, single_source_shortest_path_->vertices_[next_vertex_to_add].distance_from_root);

  next_vertex_to_add = 4;
  ASSERT_EQ(next_vertex_to_add, single_source_shortest_path_->FindNextVertexToAdd());
  single_source_shortest_path_->AddVertexToTree(next_vertex_to_add);
  ASSERT_EQ(3, single_source_shortest_path_->vertices_[next_vertex_to_add].distance_from_root);

  ASSERT_EQ(kInvalidVertex, single_source_shortest_path_->FindNextVertexToAdd());
}

}  // namespace ALDS1_12_B_2
