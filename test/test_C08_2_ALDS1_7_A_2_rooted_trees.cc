/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-2. 木、根付き木の表現(Rooted Trees)。場所固定版＆動的メモリ非使用版。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C08_2_ALDS1_7_A_2_rooted_trees.h"

namespace ALDS1_7_A_2 {

class Test_ALDS1_7_A_2 : public ::testing::Test {
 protected:
  RootedTrees *rooted_trees_;
  virtual void SetUp() {
    rooted_trees_ = new RootedTrees();
  }
  virtual void TearDown() {
    delete rooted_trees_;
  }
};

TEST_F(Test_ALDS1_7_A_2, Node_initial) {
  Node cnode;
  ASSERT_FALSE(cnode.IsValid());
  ASSERT_EQ(kInvalid, cnode.GetParent());
  ASSERT_EQ(kInvalid, cnode.GetChildLeft());
  ASSERT_EQ(kInvalid, cnode.GetChildRight());
  ASSERT_EQ(kInvalid, cnode.GetSiblingRight());
  ASSERT_ANY_THROW(cnode.GetNodeType());
}

TEST_F(Test_ALDS1_7_A_2, Node_Activate) {
  Node cnode;
  ASSERT_FALSE(cnode.IsValid());
  cnode.Activate();
  ASSERT_TRUE(cnode.IsValid());
}

TEST_F(Test_ALDS1_7_A_2, Node_SetParent) {
  const int32_t kId = 123;
  Node cnode;
  cnode.SetParent(kId);
  ASSERT_EQ(kId, cnode.GetParent());
}

TEST_F(Test_ALDS1_7_A_2, Node_SetChildLeft) {
  const int32_t kId = 123;
  Node cnode;
  cnode.SetChildLeft(kId);
  ASSERT_EQ(kId, cnode.GetChildLeft());
  ASSERT_EQ(kId, cnode.GetChildRight());
}

TEST_F(Test_ALDS1_7_A_2, Node_SetChildRight) {
  const int32_t kIdRight = 123;
  Node cnode;
  ASSERT_ANY_THROW(cnode.SetChildRight(kIdRight));

  const int32_t kIdLeft = 256;
  cnode.SetChildLeft(kIdLeft);
  cnode.SetChildRight(kIdRight);
  ASSERT_EQ(kIdRight, cnode.GetChildRight());
}

TEST_F(Test_ALDS1_7_A_2, Node_SetSiblingRight) {
  const int32_t kId = 123;
  Node cnode;
  cnode.SetSiblingRight(kId);
  ASSERT_EQ(kId, cnode.GetSiblingRight());
}

TEST_F(Test_ALDS1_7_A_2, Node_GetNodeType) {
  Node cnode;
  ASSERT_ANY_THROW(cnode.GetNodeType());
  cnode.Activate();
  ASSERT_ANY_THROW(cnode.GetNodeType());
  cnode.SetParent(kTop);
  ASSERT_EQ(NodeType::kRoot, cnode.GetNodeType());
  constexpr int32_t kCurrentId = 123;
  cnode.SetParent(kCurrentId);
  ASSERT_EQ(NodeType::kLeaf, cnode.GetNodeType());
  constexpr int32_t kChildId = 234;
  cnode.SetChildLeft(kChildId);
  ASSERT_EQ(NodeType::kInternal, cnode.GetNodeType());
}

TEST_F(Test_ALDS1_7_A_2, NodeConstructors) {
  Node node_invalid;
  ASSERT_FALSE(node_invalid.IsValid());
  ASSERT_EQ(kInvalid, node_invalid.GetParent());
  ASSERT_EQ(kInvalid, node_invalid.GetChildLeft());
  ASSERT_EQ(kInvalid, node_invalid.GetSiblingRight());
  ASSERT_ANY_THROW(node_invalid.GetNodeType());

  Node node_1;
  node_1.Activate();
  constexpr int32_t kParent = 123;
  node_1.SetParent(kParent);
  constexpr int32_t kChildLeft = 234;
  node_1.SetChildLeft(kChildLeft);
  constexpr int32_t kSiblingRight = 345;
  node_1.SetSiblingRight(kSiblingRight);
  ASSERT_TRUE(node_1.IsValid());
  ASSERT_EQ(kParent, node_1.GetParent());
  ASSERT_EQ(kChildLeft, node_1.GetChildLeft());
  ASSERT_EQ(kSiblingRight, node_1.GetSiblingRight());
  ASSERT_EQ(NodeType::kInternal, node_1.GetNodeType());

  Node node_1_1(node_1);
  ASSERT_TRUE(node_1_1.IsValid());
  ASSERT_EQ(kParent, node_1_1.GetParent());
  ASSERT_EQ(kChildLeft, node_1_1.GetChildLeft());
  ASSERT_EQ(kSiblingRight, node_1_1.GetSiblingRight());
  ASSERT_EQ(NodeType::kInternal, node_1_1.GetNodeType());

  Node node_1_2 = node_1;
  ASSERT_TRUE(node_1_2.IsValid());
  ASSERT_EQ(kParent, node_1_2.GetParent());
  ASSERT_EQ(kChildLeft, node_1_2.GetChildLeft());
  ASSERT_EQ(kSiblingRight, node_1_2.GetSiblingRight());
  ASSERT_EQ(NodeType::kInternal, node_1_2.GetNodeType());

  Node node_1_3 = Node(node_1);
  ASSERT_TRUE(node_1_3.IsValid());
  ASSERT_EQ(kParent, node_1_3.GetParent());
  ASSERT_EQ(kChildLeft, node_1_3.GetChildLeft());
  ASSERT_EQ(kSiblingRight, node_1_3.GetSiblingRight());
  ASSERT_EQ(NodeType::kInternal, node_1_3.GetNodeType());

  Node node_1_4 = std::move(node_1_3);
  ASSERT_TRUE(node_1_4.IsValid());
  ASSERT_EQ(kParent, node_1_4.GetParent());
  ASSERT_EQ(kChildLeft, node_1_4.GetChildLeft());
  ASSERT_EQ(kSiblingRight, node_1_4.GetSiblingRight());
  ASSERT_EQ(NodeType::kInternal, node_1_4.GetNodeType());

  ASSERT_FALSE(node_1_3.IsValid());
  ASSERT_NE(node_1_4.GetParent(), node_1_3.GetParent());
  ASSERT_NE(node_1_4.GetChildLeft(), node_1_3.GetChildLeft());
  ASSERT_NE(node_1_4.GetSiblingRight(), node_1_3.GetSiblingRight());
  ASSERT_ANY_THROW(node_1_3.GetNodeType());
}

TEST_F(Test_ALDS1_7_A_2, CallRootedTrees_1) {
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

TEST_F(Test_ALDS1_7_A_2, CallRootedTrees_2) {
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

TEST_F(Test_ALDS1_7_A_2, CallRootedTrees_3) {
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

}  // namespace ALDS1_7_A_2
