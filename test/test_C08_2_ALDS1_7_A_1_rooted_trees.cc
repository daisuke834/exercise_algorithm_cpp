/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-2. 木、根付き木の表現(Rooted Trees)。可変長配列＆場所不定版。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/C08_2_ALDS1_7_A_1_rooted_trees.h"

namespace ALDS1_7_A_1 {

class Test_ALDS1_7_A_1 : public ::testing::Test {
 protected:
  RootedTrees* rooted_trees_;
  virtual void SetUp() { rooted_trees_ = new RootedTrees(); }
  virtual void TearDown() { delete rooted_trees_; }
};

TEST_F(Test_ALDS1_7_A_1, NodeId) {
  NodeId node_id_invalid;
  ASSERT_TRUE(node_id_invalid.IsInvalid());
  ASSERT_FALSE(node_id_invalid.IsValid());

  NodeId node_id_1(234);
  ASSERT_TRUE(node_id_1.Equals(node_id_1));
  ASSERT_TRUE(node_id_1 == node_id_1);
  ASSERT_FALSE(node_id_1 != node_id_1);
  ASSERT_FALSE(node_id_1.Equals(node_id_invalid));
  ASSERT_FALSE(node_id_1 == node_id_invalid);
  ASSERT_TRUE(node_id_1 != node_id_invalid);

  NodeId node_id_2(1);
  ASSERT_FALSE(node_id_1.Equals(node_id_2));
  ASSERT_FALSE(node_id_1 == node_id_2);
  ASSERT_TRUE(node_id_1 != node_id_2);

  NodeId node_id_1_1 = node_id_1;
  ASSERT_TRUE(node_id_1.Equals(node_id_1_1));
  ASSERT_TRUE(node_id_1 == node_id_1_1);
  ASSERT_FALSE(node_id_1 != node_id_1_1);
  ASSERT_FALSE(node_id_2.Equals(node_id_1_1));
  ASSERT_FALSE(node_id_2 == node_id_1_1);
  ASSERT_TRUE(node_id_2 != node_id_1_1);

  NodeId node_id_1_2 = NodeId(234);
  ASSERT_TRUE(node_id_1.Equals(node_id_1_2));
  ASSERT_TRUE(node_id_1 == node_id_1_2);
  ASSERT_FALSE(node_id_1 != node_id_1_2);
  ASSERT_FALSE(node_id_2.Equals(node_id_1_2));
  ASSERT_FALSE(node_id_2 == node_id_1_2);
  ASSERT_TRUE(node_id_2 != node_id_1_2);

  NodeId node_id_1_3(node_id_1);
  ASSERT_TRUE(node_id_1.Equals(node_id_1_3));
  ASSERT_TRUE(node_id_1 == node_id_1_3);
  ASSERT_FALSE(node_id_1 != node_id_1_3);
  ASSERT_FALSE(node_id_2.Equals(node_id_1_3));
  ASSERT_FALSE(node_id_2 == node_id_1_3);
  ASSERT_TRUE(node_id_2 != node_id_1_3);

  NodeId node_id_1_4 = NodeId(node_id_1);
  ASSERT_TRUE(node_id_1.Equals(node_id_1_4));
  ASSERT_TRUE(node_id_1 == node_id_1_4);
  ASSERT_FALSE(node_id_1 != node_id_1_4);
  ASSERT_FALSE(node_id_2.Equals(node_id_1_4));
  ASSERT_FALSE(node_id_2 == node_id_1_4);
  ASSERT_TRUE(node_id_2 != node_id_1_4);

  NodeId node_id_1_5 = std::move(node_id_1_4);
  ASSERT_TRUE(node_id_1.Equals(node_id_1_5));
  ASSERT_TRUE(node_id_1 == node_id_1_5);
  ASSERT_FALSE(node_id_1 != node_id_1_5);
  ASSERT_FALSE(node_id_1_5.Equals(node_id_1_4));
  ASSERT_FALSE(node_id_1_5 == node_id_1_4);
  ASSERT_TRUE(node_id_1_5 != node_id_1_4);
  ASSERT_FALSE(node_id_2.Equals(node_id_1_5));
  ASSERT_FALSE(node_id_2 == node_id_1_5);
  ASSERT_TRUE(node_id_2 != node_id_1_5);
}

TEST_F(Test_ALDS1_7_A_1, Node) {
  Node node_invalid;
  ASSERT_TRUE(node_invalid.GetNodeId().IsInvalid());
  ASSERT_TRUE(node_invalid.GetParentId().IsInvalid());
  ASSERT_EQ(0, node_invalid.GetNumberOfChilds());

  NodeId node_id_1(234);
  Node node_1(node_id_1);
  ASSERT_TRUE(node_id_1 == node_1.GetNodeId());
  ASSERT_TRUE(node_1.GetParentId().IsInvalid());
  ASSERT_EQ(0, node_1.GetNumberOfChilds());

  NodeId node_id_2(1);
  Node node_2(node_id_2);
  ASSERT_TRUE(node_1.GetNodeId() != node_2.GetNodeId());

  Node node_1_1 = node_1;
  ASSERT_TRUE(node_1.GetNodeId() == node_1_1.GetNodeId());
  ASSERT_TRUE(node_1.GetParentId() != node_1_1.GetParentId());
  ASSERT_TRUE(node_2.GetNodeId() != node_1_1.GetNodeId());

  NodeId node_parent_id(888);
  node_1.SetParentId(node_parent_id);
  const int32_t child_ids[] = {1001, 2043, 1932};
  for (int32_t child_id : child_ids) {
    node_1.AddChildId(NodeId(child_id));
  }
  ASSERT_LT(0, node_1.GetNumberOfChilds());
  ASSERT_EQ(static_cast<int32_t>(sizeof(child_ids) / sizeof(int32_t)), node_1.GetNumberOfChilds());

  node_1_1 = node_1;
  ASSERT_TRUE(node_1.GetNodeId() == node_1_1.GetNodeId());
  ASSERT_TRUE(node_1.GetParentId() == node_1_1.GetParentId());
  ASSERT_EQ(node_1.GetNumberOfChilds(), node_1_1.GetNumberOfChilds());
  ASSERT_TRUE(node_2.GetNodeId() != node_1_1.GetNodeId());

  Node node_1_2(node_1);
  ASSERT_TRUE(node_1.GetNodeId() == node_1_2.GetNodeId());
  ASSERT_TRUE(node_1.GetParentId() == node_1_2.GetParentId());
  ASSERT_EQ(node_1.GetNumberOfChilds(), node_1_2.GetNumberOfChilds());
  ASSERT_TRUE(node_2.GetNodeId() != node_1_2.GetNodeId());

  Node node_1_3 = Node(node_1);
  ASSERT_TRUE(node_1.GetNodeId() == node_1_3.GetNodeId());
  ASSERT_TRUE(node_1.GetParentId() == node_1_3.GetParentId());
  ASSERT_EQ(node_1.GetNumberOfChilds(), node_1_3.GetNumberOfChilds());
  ASSERT_TRUE(node_2.GetNodeId() != node_1_3.GetNodeId());

  Node node_1_4 = std::move(node_1_3);
  ASSERT_TRUE(node_1.GetNodeId() == node_1_4.GetNodeId());
  ASSERT_TRUE(node_1.GetParentId() == node_1_4.GetParentId());
  ASSERT_EQ(node_1.GetNumberOfChilds(), node_1_4.GetNumberOfChilds());
  ASSERT_TRUE(node_1_4.GetNodeId() != node_1_3.GetNodeId());
  ASSERT_NE(node_1_4.GetNumberOfChilds(), node_1_3.GetNumberOfChilds());
  ASSERT_TRUE(node_1_4.GetParentId() != node_1_3.GetParentId());
  ASSERT_TRUE(node_2.GetNodeId() != node_1_4.GetNodeId());
}

TEST_F(Test_ALDS1_7_A_1, Node_initial) {
  Node cnode;
  ASSERT_FALSE(cnode.GetParentId().IsValid());
  ASSERT_EQ(0, cnode.GetNumberOfChilds());
  ASSERT_ANY_THROW(cnode.GetChildId(-1));
  ASSERT_ANY_THROW(cnode.GetChildId(0));
  ASSERT_ANY_THROW(cnode.GetChildId(1));
}

TEST_F(Test_ALDS1_7_A_1, Node_SetParentId_GetParentId) {
  Node cnode;
  const NodeId parent_id(123);
  cnode.SetParentId(parent_id);
  ASSERT_TRUE(parent_id == cnode.GetParentId());
}

TEST_F(Test_ALDS1_7_A_1, Node_AddChildId_GetChildId) {
  Node cnode;
  const NodeId child_id_0(12);
  const NodeId child_id_1(632);
  constexpr int32_t kNumberOfChilds = 2;
  cnode.AddChildId(child_id_0);
  cnode.AddChildId(child_id_1);
  ASSERT_EQ(kNumberOfChilds, cnode.GetNumberOfChilds());
  ASSERT_TRUE(child_id_0 == cnode.GetChildId(0));
  ASSERT_TRUE(child_id_1 == cnode.GetChildId(1));
  ASSERT_ANY_THROW(cnode.GetChildId(-1));
  ASSERT_ANY_THROW(cnode.GetChildId(kNumberOfChilds));
}

TEST_F(Test_ALDS1_7_A_1, Node_AddChildId_copy_constructor) {
  Node* node_source = new Node();
  const NodeId child_id_0(12);
  const NodeId child_id_1(632);
  constexpr int32_t kNumberOfChilds = 2;
  node_source->AddChildId(child_id_0);
  node_source->AddChildId(child_id_1);

  Node node_destination;
  node_destination = (*node_source);
  delete node_source;

  ASSERT_EQ(kNumberOfChilds, node_destination.GetNumberOfChilds());
  ASSERT_TRUE(child_id_0 == node_destination.GetChildId(0));
  ASSERT_TRUE(child_id_1 == node_destination.GetChildId(1));
  ASSERT_ANY_THROW(node_destination.GetChildId(-1));
  ASSERT_ANY_THROW(node_destination.GetChildId(kNumberOfChilds));
}

TEST_F(Test_ALDS1_7_A_1, RootedTrees_AddNode) {
  ASSERT_EQ(0, rooted_trees_->size_);

  const NodeId node_id_0(3);
  const NodeId node_id_1(10);
  rooted_trees_->AddNode(Node(node_id_0));
  rooted_trees_->AddNode(Node(node_id_1));
  ASSERT_EQ(2, rooted_trees_->size_);
  ASSERT_TRUE(rooted_trees_->nodes_[0].GetNodeId().IsValid());
  ASSERT_TRUE(rooted_trees_->nodes_[1].GetNodeId().IsValid());
  ASSERT_TRUE(rooted_trees_->nodes_[2].GetNodeId().IsInvalid());
  ASSERT_TRUE(node_id_0 == rooted_trees_->nodes_[0].GetNodeId());
  ASSERT_TRUE(node_id_1 == rooted_trees_->nodes_[1].GetNodeId());
}

TEST_F(Test_ALDS1_7_A_1, CallRootedTrees_1) {
  std::ostringstream answer;
  answer << "node 0: parent = -1, depth = 0, root, []" << std::endl;

  std::ostringstream input_stream;
  input_stream << "1" << std::endl;
  input_stream << "0 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallRootedTrees(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_7_A_1, CallRootedTrees_2) {
  std::ostringstream answer;
  answer << "node 0: parent = -1, depth = 0, root, [1, 4, 10]" << std::endl;
  answer << "node 1: parent = 0, depth = 1, internal node, [2, 3]" << std::endl;
  answer << "node 2: parent = 1, depth = 2, leaf, []" << std::endl;
  answer << "node 3: parent = 1, depth = 2, leaf, []" << std::endl;
  answer << "node 4: parent = 0, depth = 1, internal node, [5, 6, 7]" << std::endl;
  answer << "node 5: parent = 4, depth = 2, leaf, []" << std::endl;
  answer << "node 6: parent = 4, depth = 2, leaf, []" << std::endl;
  answer << "node 7: parent = 4, depth = 2, internal node, [8, 9]" << std::endl;
  answer << "node 8: parent = 7, depth = 3, leaf, []" << std::endl;
  answer << "node 9: parent = 7, depth = 3, leaf, []" << std::endl;
  answer << "node 10: parent = 0, depth = 1, internal node, [11, 12]" << std::endl;
  answer << "node 11: parent = 10, depth = 2, leaf, []" << std::endl;
  answer << "node 12: parent = 10, depth = 2, leaf, []" << std::endl;

  std::ostringstream input_stream;
  input_stream << "13" << std::endl;
  input_stream << "0 3 1 4 10" << std::endl;
  input_stream << "1 2 2 3" << std::endl;
  input_stream << "2 0" << std::endl;
  input_stream << "3 0" << std::endl;
  input_stream << "4 3 5 6 7" << std::endl;
  input_stream << "5 0" << std::endl;
  input_stream << "6 0" << std::endl;
  input_stream << "7 2 8 9" << std::endl;
  input_stream << "8 0" << std::endl;
  input_stream << "9 0" << std::endl;
  input_stream << "10 2 11 12" << std::endl;
  input_stream << "11 0" << std::endl;
  input_stream << "12 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallRootedTrees(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_7_A_1, CallRootedTrees_3) {
  std::ostringstream answer;
  answer << "node 0: parent = -1, depth = 0, root, [6, 1]" << std::endl;
  answer << "node 1: parent = 0, depth = 1, internal node, [2]" << std::endl;
  answer << "node 2: parent = 1, depth = 2, internal node, [3]" << std::endl;
  answer << "node 3: parent = 2, depth = 3, internal node, [4]" << std::endl;
  answer << "node 4: parent = 3, depth = 4, internal node, [5]" << std::endl;
  answer << "node 5: parent = 4, depth = 5, leaf, []" << std::endl;
  answer << "node 6: parent = 0, depth = 1, internal node, [7, 8, 9, 10]" << std::endl;
  answer << "node 7: parent = 6, depth = 2, leaf, []" << std::endl;
  answer << "node 8: parent = 6, depth = 2, leaf, []" << std::endl;
  answer << "node 9: parent = 6, depth = 2, leaf, []" << std::endl;
  answer << "node 10: parent = 6, depth = 2, leaf, []" << std::endl;

  std::ostringstream input_stream;
  input_stream << "11" << std::endl;
  input_stream << "6 4 7 8 9 10" << std::endl;
  input_stream << "0 2 6 1" << std::endl;
  input_stream << "1 1 2" << std::endl;
  input_stream << "2 1 3" << std::endl;
  input_stream << "3 1 4" << std::endl;
  input_stream << "4 1 5" << std::endl;
  input_stream << "5 0" << std::endl;
  input_stream << "7 0" << std::endl;
  input_stream << "8 0" << std::endl;
  input_stream << "9 0" << std::endl;
  input_stream << "10 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallRootedTrees(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_7_A_1
