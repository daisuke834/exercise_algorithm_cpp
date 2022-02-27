/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part9-3. 二分探索木(Binary Search Tree)、探索(Find)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/C09_3_ALDS1_8_B_binary_search_tree_2.h"

namespace ALDS1_8_B {

class Test_ALDS1_8_B : public ::testing::Test {
 protected:
  BinarySearchTree* binary_search_tree_;
  virtual void SetUp() { binary_search_tree_ = new BinarySearchTree(); }
  virtual void TearDown() { delete binary_search_tree_; }
};

TEST_F(Test_ALDS1_8_B, Node_initial) {
  Node cnode;
  ASSERT_FALSE(cnode.IsValid());
  ASSERT_EQ(kInvalid, cnode.GetParent());
  ASSERT_EQ(kInvalid, cnode.GetChildLeft());
  ASSERT_EQ(kInvalid, cnode.GetChildRight());
  ASSERT_ANY_THROW(cnode.GetNodeType());
  ASSERT_ANY_THROW(cnode.SetKey(0));
  ASSERT_ANY_THROW(cnode.GetKey());
}

TEST_F(Test_ALDS1_8_B, Node_Activate) {
  Node cnode;
  ASSERT_FALSE(cnode.IsValid());
  cnode.Activate();
  ASSERT_TRUE(cnode.IsValid());
}

TEST_F(Test_ALDS1_8_B, Node_SetKey) {
  const int32_t kKey = 1000;
  Node cnode;
  cnode.Activate();
  cnode.SetKey(kKey);
  ASSERT_EQ(kKey, cnode.GetKey());
}

TEST_F(Test_ALDS1_8_B, Node_SetParent) {
  const int32_t kId = 12;
  Node cnode;
  cnode.SetParent(kId);
  ASSERT_EQ(kId, cnode.GetParent());
}

TEST_F(Test_ALDS1_8_B, Node_SetChildLeft) {
  const int32_t kId = 12;
  Node cnode;
  cnode.SetChildLeft(kId);
  ASSERT_EQ(kId, cnode.GetChildLeft());
}

TEST_F(Test_ALDS1_8_B, Node_SetChildRight) {
  const int32_t kIdRight = 12;
  Node cnode;
  cnode.SetChildRight(kIdRight);
  ASSERT_EQ(kIdRight, cnode.GetChildRight());
}

TEST_F(Test_ALDS1_8_B, Node_GetNodeType) {
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

TEST_F(Test_ALDS1_8_B, NodeConstructors) {
  Node node_invalid;
  ASSERT_FALSE(node_invalid.IsValid());
  ASSERT_EQ(kInvalid, node_invalid.GetParent());
  ASSERT_EQ(kInvalid, node_invalid.GetChildLeft());
  ASSERT_ANY_THROW(node_invalid.GetNodeType());
  ASSERT_ANY_THROW(node_invalid.SetKey(0));
  ASSERT_ANY_THROW(node_invalid.GetKey());

  Node node_1;
  node_1.Activate();
  const int32_t kKey = 1000;
  node_1.SetKey(kKey);
  constexpr int32_t kParent = 12;
  node_1.SetParent(kParent);
  constexpr int32_t kChildLeft = 23;
  node_1.SetChildLeft(kChildLeft);
  ASSERT_TRUE(node_1.IsValid());
  ASSERT_EQ(kKey, node_1.GetKey());
  ASSERT_EQ(kParent, node_1.GetParent());
  ASSERT_EQ(kChildLeft, node_1.GetChildLeft());
  ASSERT_EQ(NodeType::kInternal, node_1.GetNodeType());

  Node node_1_1(node_1);
  ASSERT_TRUE(node_1_1.IsValid());
  ASSERT_EQ(kKey, node_1_1.GetKey());
  ASSERT_EQ(kParent, node_1_1.GetParent());
  ASSERT_EQ(kChildLeft, node_1_1.GetChildLeft());
  ASSERT_EQ(NodeType::kInternal, node_1_1.GetNodeType());

  Node node_1_2 = node_1;
  ASSERT_TRUE(node_1_2.IsValid());
  ASSERT_EQ(kKey, node_1_2.GetKey());
  ASSERT_EQ(kParent, node_1_2.GetParent());
  ASSERT_EQ(kChildLeft, node_1_2.GetChildLeft());
  ASSERT_EQ(NodeType::kInternal, node_1_2.GetNodeType());

  Node node_1_3 = Node(node_1);
  ASSERT_TRUE(node_1_3.IsValid());
  ASSERT_EQ(kKey, node_1_3.GetKey());
  ASSERT_EQ(kParent, node_1_3.GetParent());
  ASSERT_EQ(kChildLeft, node_1_3.GetChildLeft());
  ASSERT_EQ(NodeType::kInternal, node_1_3.GetNodeType());

  Node node_1_4 = std::move(node_1_3);
  ASSERT_TRUE(node_1_4.IsValid());
  ASSERT_EQ(kKey, node_1_4.GetKey());
  ASSERT_EQ(kParent, node_1_4.GetParent());
  ASSERT_EQ(kChildLeft, node_1_4.GetChildLeft());
  ASSERT_EQ(NodeType::kInternal, node_1_4.GetNodeType());

  ASSERT_FALSE(node_1_3.IsValid());
  ASSERT_ANY_THROW(node_1_3.GetKey());
  ASSERT_NE(node_1_4.GetParent(), node_1_3.GetParent());
  ASSERT_NE(node_1_4.GetChildLeft(), node_1_3.GetChildLeft());
  ASSERT_ANY_THROW(node_1_3.GetNodeType());
}

TEST_F(Test_ALDS1_8_B, CallBinarySearchTree_1) {
  std::ostringstream answer;
  answer << " 1 12 17 20 25 30 88" << std::endl;
  answer << " 30 12 1 20 17 25 88" << std::endl;

  std::ostringstream input_stream;
  input_stream << "8" << std::endl;
  input_stream << "insert 30" << std::endl;
  input_stream << "insert 88" << std::endl;
  input_stream << "insert 12" << std::endl;
  input_stream << "insert 1" << std::endl;
  input_stream << "insert 20" << std::endl;
  input_stream << "insert 17" << std::endl;
  input_stream << "insert 25" << std::endl;
  input_stream << "print" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBinarySearchTree(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_8_B, CallBinarySearchTree_2) {
  std::ostringstream answer;
  answer << "yes" << std::endl;
  answer << "no" << std::endl;
  answer << " 1 12 17 20 25 30 88" << std::endl;
  answer << " 30 12 1 20 17 25 88" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10" << std::endl;
  input_stream << "insert 30" << std::endl;
  input_stream << "insert 88" << std::endl;
  input_stream << "insert 12" << std::endl;
  input_stream << "insert 1" << std::endl;
  input_stream << "insert 20" << std::endl;
  input_stream << "find 12" << std::endl;
  input_stream << "insert 17" << std::endl;
  input_stream << "insert 25" << std::endl;
  input_stream << "find 16" << std::endl;
  input_stream << "print" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallBinarySearchTree(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_8_B
