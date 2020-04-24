/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part12-5. グラフ(Graph)、連結成分(Connected Components)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C12_5_ALDS1_11_D_1_connected_components.h"

namespace ALDS1_11_D_1 {

class Test_ALDS1_11_D_1 : public ::testing::Test {
 protected:
  ConnectedComponents *connected_components_;
  virtual void SetUp() {
    connected_components_ = new ConnectedComponents();
  }
  virtual void TearDown() {
    delete connected_components_;
  }
};

TEST_F(Test_ALDS1_11_D_1, CallConnectedComponents_1) {
  std::ostringstream answer;
  answer << "yes" << std::endl;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10 9" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "0 2" << std::endl;
  input_stream << "3 4" << std::endl;
  input_stream << "5 7" << std::endl;
  input_stream << "5 6" << std::endl;
  input_stream << "6 7" << std::endl;
  input_stream << "6 8" << std::endl;
  input_stream << "7 8" << std::endl;
  input_stream << "8 9" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "5 9" << std::endl;
  input_stream << "1 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallConnectedComponents(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_11_D_1, Mapping) {
  connected_components_->SetNumberOfVertices(10);
  connected_components_->AddMapping(0, 1);
  connected_components_->AddMapping(0, 2);
  connected_components_->AddMapping(3, 4);
  connected_components_->AddMapping(5, 7);
  connected_components_->AddMapping(5, 6);
  connected_components_->AddMapping(6, 7);
  connected_components_->AddMapping(6, 8);
  connected_components_->AddMapping(7, 8);
  connected_components_->AddMapping(8, 9);
  connected_components_->BuildGraph();

  ASSERT_EQ(2, connected_components_->GetNumberOfNeighbours(0));
  ASSERT_EQ(1, connected_components_->GetNumberOfNeighbours(1));
  ASSERT_EQ(1, connected_components_->GetNumberOfNeighbours(2));
  ASSERT_EQ(1, connected_components_->GetNumberOfNeighbours(3));
  ASSERT_EQ(1, connected_components_->GetNumberOfNeighbours(4));
  ASSERT_EQ(2, connected_components_->GetNumberOfNeighbours(5));
  ASSERT_EQ(3, connected_components_->GetNumberOfNeighbours(6));
  ASSERT_EQ(3, connected_components_->GetNumberOfNeighbours(7));
  ASSERT_EQ(3, connected_components_->GetNumberOfNeighbours(8));
  ASSERT_EQ(1, connected_components_->GetNumberOfNeighbours(9));

  ASSERT_EQ(1, connected_components_->GetNeighbour(0, 0));
  ASSERT_EQ(2, connected_components_->GetNeighbour(0, 1));
  ASSERT_EQ(0, connected_components_->GetNeighbour(1, 0));
  ASSERT_EQ(0, connected_components_->GetNeighbour(2, 0));
  ASSERT_EQ(4, connected_components_->GetNeighbour(3, 0));
  ASSERT_EQ(3, connected_components_->GetNeighbour(4, 0));
}

TEST_F(Test_ALDS1_11_D_1, BuildGraph_sort) {
  connected_components_->SetNumberOfVertices(10);
  connected_components_->AddMapping(5, 7);
  connected_components_->AddMapping(5, 6);
  connected_components_->AddMapping(6, 7);
  connected_components_->AddMapping(6, 8);
  connected_components_->AddMapping(7, 8);
  connected_components_->AddMapping(8, 9);
  connected_components_->AddMapping(0, 1);
  connected_components_->AddMapping(0, 2);
  connected_components_->AddMapping(3, 4);
  connected_components_->BuildGraph();

  int32_t index_edge = 0;
  ASSERT_EQ(0, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(0, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(1, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(2, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(3, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(4, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(5, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(5, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(6, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(6, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(6, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(7, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(7, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(7, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(8, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(8, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(8, connected_components_->edges_[index_edge++].from);
  ASSERT_EQ(9, connected_components_->edges_[index_edge++].from);

  ASSERT_EQ(1, connected_components_->GetNeighbour(0, 0));
  ASSERT_EQ(2, connected_components_->GetNeighbour(0, 1));
  ASSERT_EQ(0, connected_components_->GetNeighbour(1, 0));
  ASSERT_EQ(0, connected_components_->GetNeighbour(2, 0));
  ASSERT_EQ(4, connected_components_->GetNeighbour(3, 0));
  ASSERT_EQ(3, connected_components_->GetNeighbour(4, 0));
}

TEST_F(Test_ALDS1_11_D_1, BuildGraph_BuildMetaDataOfEdge) {
  connected_components_->SetNumberOfVertices(10);
  connected_components_->AddMapping(5, 7);
  connected_components_->AddMapping(5, 6);
  connected_components_->AddMapping(6, 7);
  connected_components_->AddMapping(6, 8);
  connected_components_->AddMapping(7, 8);
  connected_components_->AddMapping(8, 9);
  connected_components_->AddMapping(0, 1);
  connected_components_->AddMapping(0, 2);
  connected_components_->AddMapping(3, 4);
  connected_components_->BuildGraph();

  int32_t vertex_index;
  int32_t edge_offset;
  int32_t number_of_neighbours;

  vertex_index = 0;
  edge_offset = 0;
  number_of_neighbours = 2;
  ASSERT_EQ(edge_offset, connected_components_->edge_offset_of_each_vertex_[vertex_index]);
  ASSERT_EQ(number_of_neighbours, connected_components_->number_of_neighbours_of_each_vertex_[vertex_index]);

  vertex_index = 1;
  edge_offset += number_of_neighbours;
  number_of_neighbours = 1;
  ASSERT_EQ(edge_offset, connected_components_->edge_offset_of_each_vertex_[vertex_index]);
  ASSERT_EQ(number_of_neighbours, connected_components_->number_of_neighbours_of_each_vertex_[vertex_index]);

  vertex_index = 2;
  edge_offset += number_of_neighbours;
  number_of_neighbours = 1;
  ASSERT_EQ(edge_offset, connected_components_->edge_offset_of_each_vertex_[vertex_index]);
  ASSERT_EQ(number_of_neighbours, connected_components_->number_of_neighbours_of_each_vertex_[vertex_index]);

  vertex_index = 3;
  edge_offset += number_of_neighbours;
  number_of_neighbours = 1;
  ASSERT_EQ(edge_offset, connected_components_->edge_offset_of_each_vertex_[vertex_index]);
  ASSERT_EQ(number_of_neighbours, connected_components_->number_of_neighbours_of_each_vertex_[vertex_index]);

  vertex_index = 4;
  edge_offset += number_of_neighbours;
  number_of_neighbours = 1;
  ASSERT_EQ(edge_offset, connected_components_->edge_offset_of_each_vertex_[vertex_index]);
  ASSERT_EQ(number_of_neighbours, connected_components_->number_of_neighbours_of_each_vertex_[vertex_index]);

  vertex_index = 5;
  edge_offset += number_of_neighbours;
  number_of_neighbours = 2;
  ASSERT_EQ(edge_offset, connected_components_->edge_offset_of_each_vertex_[vertex_index]);
  ASSERT_EQ(number_of_neighbours, connected_components_->number_of_neighbours_of_each_vertex_[vertex_index]);

  vertex_index = 6;
  edge_offset += number_of_neighbours;
  number_of_neighbours = 3;
  ASSERT_EQ(edge_offset, connected_components_->edge_offset_of_each_vertex_[vertex_index]);
  ASSERT_EQ(number_of_neighbours, connected_components_->number_of_neighbours_of_each_vertex_[vertex_index]);

  vertex_index = 7;
  edge_offset += number_of_neighbours;
  number_of_neighbours = 3;
  ASSERT_EQ(edge_offset, connected_components_->edge_offset_of_each_vertex_[vertex_index]);
  ASSERT_EQ(number_of_neighbours, connected_components_->number_of_neighbours_of_each_vertex_[vertex_index]);

  vertex_index = 8;
  edge_offset += number_of_neighbours;
  number_of_neighbours = 3;
  ASSERT_EQ(edge_offset, connected_components_->edge_offset_of_each_vertex_[vertex_index]);
  ASSERT_EQ(number_of_neighbours, connected_components_->number_of_neighbours_of_each_vertex_[vertex_index]);

  vertex_index = 9;
  edge_offset += number_of_neighbours;
  number_of_neighbours = 1;
  ASSERT_EQ(edge_offset, connected_components_->edge_offset_of_each_vertex_[vertex_index]);
  ASSERT_EQ(number_of_neighbours, connected_components_->number_of_neighbours_of_each_vertex_[vertex_index]);
}

TEST_F(Test_ALDS1_11_D_1, ConnectionExistsBetweenStartAndEnd_1) {
  connected_components_->SetNumberOfVertices(10);
  connected_components_->AddMapping(0, 1);
  connected_components_->AddMapping(0, 2);
  connected_components_->AddMapping(3, 4);
  connected_components_->AddMapping(5, 7);
  connected_components_->AddMapping(5, 6);
  connected_components_->AddMapping(6, 7);
  connected_components_->AddMapping(6, 8);
  connected_components_->AddMapping(7, 8);
  connected_components_->AddMapping(8, 9);
  connected_components_->BuildGraph();

  for (int32_t vertex_start = 0; vertex_start <= 2; ++vertex_start) {
    for (int32_t vertex_end = 0; vertex_end <= 2; ++vertex_end) {
      ASSERT_TRUE(connected_components_->ConnectionExistsBetweenStartAndEnd(vertex_start, vertex_end));
    }
    for (int32_t vertex_end = 3; vertex_end <= 9; ++vertex_end) {
      ASSERT_FALSE(connected_components_->ConnectionExistsBetweenStartAndEnd(vertex_start, vertex_end));
    }
  }

  for (int32_t vertex_start = 3; vertex_start <= 4; ++vertex_start) {
    for (int32_t vertex_end = 3; vertex_end <= 4; ++vertex_end) {
      ASSERT_TRUE(connected_components_->ConnectionExistsBetweenStartAndEnd(vertex_start, vertex_end));
    }
    for (int32_t vertex_end = 0; vertex_end <= 9; ++vertex_end) {
      if ((vertex_end != 3) && (vertex_end != 4))
        ASSERT_FALSE(connected_components_->ConnectionExistsBetweenStartAndEnd(vertex_start, vertex_end));
    }
  }

  for (int32_t vertex_start = 5; vertex_start <= 9; ++vertex_start) {
    for (int32_t vertex_end = 5; vertex_end <= 9; ++vertex_end) {
      ASSERT_TRUE(connected_components_->ConnectionExistsBetweenStartAndEnd(vertex_start, vertex_end));
    }
    for (int32_t vertex_end = 0; vertex_end <= 4; ++vertex_end) {
      ASSERT_FALSE(connected_components_->ConnectionExistsBetweenStartAndEnd(vertex_start, vertex_end));
    }
  }
}

TEST_F(Test_ALDS1_11_D_1, ConnectionExistsBetweenStartAndEnd_2) {
  connected_components_->SetNumberOfVertices(10);
  connected_components_->AddMapping(0, 1);
  connected_components_->AddMapping(1, 2);
  connected_components_->AddMapping(2, 9);
  connected_components_->AddMapping(3, 4);
  connected_components_->AddMapping(6, 7);
  connected_components_->BuildGraph();

  ASSERT_TRUE(connected_components_->ConnectionExistsBetweenStartAndEnd(0, 1));
  ASSERT_TRUE(connected_components_->ConnectionExistsBetweenStartAndEnd(0, 2));
  ASSERT_TRUE(connected_components_->ConnectionExistsBetweenStartAndEnd(0, 9));
  ASSERT_TRUE(connected_components_->ConnectionExistsBetweenStartAndEnd(3, 4));
  ASSERT_TRUE(connected_components_->ConnectionExistsBetweenStartAndEnd(6, 7));
  ASSERT_TRUE(connected_components_->ConnectionExistsBetweenStartAndEnd(7, 6));

  ASSERT_FALSE(connected_components_->ConnectionExistsBetweenStartAndEnd(0, 5));
  ASSERT_FALSE(connected_components_->ConnectionExistsBetweenStartAndEnd(0, 6));
  ASSERT_FALSE(connected_components_->ConnectionExistsBetweenStartAndEnd(3, 7));
  ASSERT_FALSE(connected_components_->ConnectionExistsBetweenStartAndEnd(3, 5));
  ASSERT_FALSE(connected_components_->ConnectionExistsBetweenStartAndEnd(5, 8));
  ASSERT_FALSE(connected_components_->ConnectionExistsBetweenStartAndEnd(8, 5));
}

/*
TEST_F(Test_ALDS1_11_D_1, ConnectionExistsBetweenStartAndEnd_3) {
  constexpr int32_t kNumberOfVertices = 100000;
  constexpr int32_t kNumberOfEdges = 80000;
  connected_components_->SetNumberOfVertices(kNumberOfVertices);
  for (int32_t i = 0; i < kNumberOfEdges; ++i) {
    connected_components_->AddMapping(kNumberOfVertices - i - 1, (kNumberOfVertices - i) % kNumberOfVertices);
  }
  connected_components_->BuildGraph();
}
*/

}  // namespace ALDS1_11_D_1
