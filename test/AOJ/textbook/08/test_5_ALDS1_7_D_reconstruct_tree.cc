/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part8-5. 木、木の復元(Reconstruction of the Tree)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <sstream>

#include "src/AOJ/textbook/08/5_ALDS1_7_D_reconstruct_tree.h"

namespace ALDS1_7_D {

class Test_ALDS1_7_D : public ::testing::Test {
 protected:
  TreeReconstruction* reconstruct_tree_;
  virtual void SetUp() { reconstruct_tree_ = new TreeReconstruction(); }
  virtual void TearDown() { delete reconstruct_tree_; }
};

TEST_F(Test_ALDS1_7_D, Node_initial) {
  Node cnode;
  ASSERT_FALSE(cnode.IsValid());
  ASSERT_EQ(kInvalid, cnode.GetParent());
  ASSERT_EQ(kInvalid, cnode.GetChildLeft());
  ASSERT_EQ(kInvalid, cnode.GetChildRight());
  ASSERT_ANY_THROW(cnode.GetNodeType());
}

TEST_F(Test_ALDS1_7_D, Node_Activate) {
  Node cnode;
  ASSERT_FALSE(cnode.IsValid());
  cnode.Activate();
  ASSERT_TRUE(cnode.IsValid());
}

TEST_F(Test_ALDS1_7_D, Node_SetParent) {
  const int32_t kId = 12;
  Node cnode;
  cnode.SetParent(kId);
  ASSERT_EQ(kId, cnode.GetParent());
}

TEST_F(Test_ALDS1_7_D, Node_SetChildLeft) {
  const int32_t kId = 12;
  Node cnode;
  cnode.SetChildLeft(kId);
  ASSERT_EQ(kId, cnode.GetChildLeft());
}

TEST_F(Test_ALDS1_7_D, Node_SetChildRight) {
  const int32_t kIdRight = 12;
  Node cnode;
  cnode.SetChildRight(kIdRight);
  ASSERT_EQ(kIdRight, cnode.GetChildRight());
}

TEST_F(Test_ALDS1_7_D, Node_GetNodeType) {
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

TEST_F(Test_ALDS1_7_D, NodeConstructors) {
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

TEST_F(Test_ALDS1_7_D, CallTreeReconstruction_0) {
  std::ostringstream answer;
  answer << "3 4 2 5 1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "1 2 3 4 5" << std::endl;
  input_stream << "3 2 4 1 5" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeReconstruction(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_7_D, CallTreeReconstruction_1) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "1" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeReconstruction(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_7_D, CallTreeReconstruction_2) {
  std::ostringstream answer;
  answer << "2 1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "2" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "2 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeReconstruction(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_7_D, CallTreeReconstruction_3) {
  std::ostringstream answer;
  answer << "2 3 1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "1 2 3" << std::endl;
  input_stream << "2 1 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeReconstruction(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_7_D, CallTreeReconstruction_4) {
  std::ostringstream answer;
  answer << "1 3 2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "2 1 3" << std::endl;
  input_stream << "1 2 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeReconstruction(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_7_D, CallTreeReconstruction_5) {
  std::ostringstream answer;
  answer << "2 1 3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "3 2 1" << std::endl;
  input_stream << "2 3 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeReconstruction(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_7_D, CallTreeReconstruction_6) {
  std::ostringstream answer;
  answer << "3 1 2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "2 3 1" << std::endl;
  input_stream << "3 2 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeReconstruction(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_7_D, CallTreeReconstruction_7) {
  std::ostringstream answer;
  answer << "3 2 4 1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4" << std::endl;
  input_stream << "1 2 3 4" << std::endl;
  input_stream << "3 2 1 4" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeReconstruction(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_7_D, CallTreeReconstruction_8) {
  std::ostringstream answer;
  answer << "4 6 7 5 2 8 3 1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "8" << std::endl;
  input_stream << "1 2 4 5 6 7 3 8" << std::endl;
  input_stream << "4 2 6 5 7 1 8 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallTreeReconstruction(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_7_D
