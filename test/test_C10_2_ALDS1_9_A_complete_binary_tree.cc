/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part10-2. ヒープ、完全二分木(Complete Binary Tree)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C10_2_ALDS1_9_A_complete_binary_tree.h"

namespace ALDS1_9_A {

class Test_ALDS1_9_A : public ::testing::Test {
 protected:
  CompleteBinaryTree *complete_binary_tree_;
  virtual void SetUp() {
    complete_binary_tree_ = new CompleteBinaryTree();
  }
  virtual void TearDown() {
    delete complete_binary_tree_;
  }
};

TEST_F(Test_ALDS1_9_A, Add) {
  ASSERT_EQ(0, complete_binary_tree_->size_);
  ASSERT_ANY_THROW(complete_binary_tree_->GetKeyByIndex(0));

  const int32_t kKey_0 = 12;
  const int32_t kKey_1 = 26;
  complete_binary_tree_->Add(kKey_0);
  complete_binary_tree_->Add(kKey_1);

  ASSERT_EQ(2, complete_binary_tree_->size_);
  ASSERT_EQ(kKey_0, complete_binary_tree_->nodes_[0].key);
  ASSERT_EQ(kKey_1, complete_binary_tree_->nodes_[1].key);
  ASSERT_EQ(kKey_0, complete_binary_tree_->GetKeyByIndex(0));
  ASSERT_EQ(kKey_1, complete_binary_tree_->GetKeyByIndex(1));
  ASSERT_ANY_THROW(complete_binary_tree_->GetKeyByIndex(2));
}

TEST_F(Test_ALDS1_9_A, CallCompleteBinaryTree_1) {
  std::ostringstream answer;
  answer << "node 1: key = 7, left key = 8, right key = 1, " << std::endl;
  answer << "node 2: key = 8, parent key = 7, left key = 2, right key = 3, " << std::endl;
  answer << "node 3: key = 1, parent key = 7, " << std::endl;
  answer << "node 4: key = 2, parent key = 8, " << std::endl;
  answer << "node 5: key = 3, parent key = 8, " << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "7 8 1 2 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallCompleteBinaryTree(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_9_A
