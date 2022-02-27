/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-4. 木、木の巡回(Tree Walk)。
 * Preorder Tree Walk(先行順巡回)/Inorder Tree Walk(中間順巡回)/Postorder Tree Walk(後行順巡回)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/C08_4_ALDS1_7_C_tree_walk.h"

namespace ALDS1_7_C {

class Test_ALDS1_7_C : public ::testing::Test {
 protected:
  TreeWalk* tree_walk_;
  virtual void SetUp() { tree_walk_ = new TreeWalk(); }
  virtual void TearDown() { delete tree_walk_; }
};

TEST_F(Test_ALDS1_7_C, Node_initial) {
  Node cnode;
  ASSERT_FALSE(cnode.IsValid());
  ASSERT_EQ(kInvalid, cnode.GetParent());
  ASSERT_EQ(kInvalid, cnode.GetChildLeft());
  ASSERT_EQ(kInvalid, cnode.GetChildRight());
  ASSERT_ANY_THROW(cnode.GetNodeType());
}

TEST_F(Test_ALDS1_7_C, Node_Activate) {
  Node cnode;
  ASSERT_FALSE(cnode.IsValid());
  cnode.Activate();
  ASSERT_TRUE(cnode.IsValid());
}

TEST_F(Test_ALDS1_7_C, Node_SetParent) {
  const int32_t kId = 12;
  Node cnode;
  cnode.SetParent(kId);
  ASSERT_EQ(kId, cnode.GetParent());
}

TEST_F(Test_ALDS1_7_C, Node_SetChildLeft) {
  const int32_t kId = 12;
  Node cnode;
  cnode.SetChildLeft(kId);
  ASSERT_EQ(kId, cnode.GetChildLeft());
}

TEST_F(Test_ALDS1_7_C, Node_SetChildRight) {
  const int32_t kIdRight = 12;
  Node cnode;
  cnode.SetChildRight(kIdRight);
  ASSERT_EQ(kIdRight, cnode.GetChildRight());
}

TEST_F(Test_ALDS1_7_C, Node_GetNodeType) {
  Node cnode;
  ASSERT_ANY_THROW(cnode.GetNodeType());
  cnode.Activate();
  ASSERT_ANY_THROW(cnode.GetNodeType());
  cnode.SetParent(kTop);
  ASSERT_EQ(NodeType::kRoot, cnode.GetNodeType());
  constexpr int32_t kCurrentId = 12;
  cnode.SetParent(kCurrentId);
  ASSERT_EQ(NodeType::kLeaf, cnode.GetNodeType());
  constexpr int32_t kChildId = 23;
  cnode.SetChildLeft(kChildId);
  ASSERT_EQ(NodeType::kInternal, cnode.GetNodeType());
}

TEST_F(Test_ALDS1_7_C, NodeConstructors) {
  Node node_invalid;
  ASSERT_FALSE(node_invalid.IsValid());
  ASSERT_EQ(kInvalid, node_invalid.GetParent());
  ASSERT_EQ(kInvalid, node_invalid.GetChildLeft());
  ASSERT_ANY_THROW(node_invalid.GetNodeType());

  Node node_1;
  node_1.Activate();
  constexpr int32_t kParent = 12;
  node_1.SetParent(kParent);
  constexpr int32_t kChildLeft = 23;
  node_1.SetChildLeft(kChildLeft);
  ASSERT_TRUE(node_1.IsValid());
  ASSERT_EQ(kParent, node_1.GetParent());
  ASSERT_EQ(kChildLeft, node_1.GetChildLeft());
  ASSERT_EQ(NodeType::kInternal, node_1.GetNodeType());

  Node node_1_1(node_1);
  ASSERT_TRUE(node_1_1.IsValid());
  ASSERT_EQ(kParent, node_1_1.GetParent());
  ASSERT_EQ(kChildLeft, node_1_1.GetChildLeft());
  ASSERT_EQ(NodeType::kInternal, node_1_1.GetNodeType());

  Node node_1_2 = node_1;
  ASSERT_TRUE(node_1_2.IsValid());
  ASSERT_EQ(kParent, node_1_2.GetParent());
  ASSERT_EQ(kChildLeft, node_1_2.GetChildLeft());
  ASSERT_EQ(NodeType::kInternal, node_1_2.GetNodeType());

  Node node_1_3 = Node(node_1);
  ASSERT_TRUE(node_1_3.IsValid());
  ASSERT_EQ(kParent, node_1_3.GetParent());
  ASSERT_EQ(kChildLeft, node_1_3.GetChildLeft());
  ASSERT_EQ(NodeType::kInternal, node_1_3.GetNodeType());

  Node node_1_4 = std::move(node_1_3);
  ASSERT_TRUE(node_1_4.IsValid());
  ASSERT_EQ(kParent, node_1_4.GetParent());
  ASSERT_EQ(kChildLeft, node_1_4.GetChildLeft());
  ASSERT_EQ(NodeType::kInternal, node_1_4.GetNodeType());

  ASSERT_FALSE(node_1_3.IsValid());
  ASSERT_NE(node_1_4.GetParent(), node_1_3.GetParent());
  ASSERT_NE(node_1_4.GetChildLeft(), node_1_3.GetChildLeft());
  ASSERT_ANY_THROW(node_1_3.GetNodeType());
}

TEST_F(Test_ALDS1_7_C, CallTreeWalk_1) {
  std::ostringstream answer;
  answer << "Preorder" << std::endl;
  answer << " 0 1 2 3 4 5 6 7 8" << std::endl;
  answer << "Inorder" << std::endl;
  answer << " 2 1 3 0 6 5 7 4 8" << std::endl;
  answer << "Postorder" << std::endl;
  answer << " 2 3 1 6 7 5 8 4 0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "9" << std::endl;
  input_stream << "0 1 4" << std::endl;
  input_stream << "1 2 3" << std::endl;
  input_stream << "2 -1 -1" << std::endl;
  input_stream << "3 -1 -1" << std::endl;
  input_stream << "4 5 8" << std::endl;
  input_stream << "5 6 7" << std::endl;
  input_stream << "6 -1 -1" << std::endl;
  input_stream << "7 -1 -1" << std::endl;
  input_stream << "8 -1 -1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeWalk(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_7_C
