/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part14-1. 高度なデータ構造、Union Find Tree
 * (素集合データ構造, Union Find木, 互いに素な集合, Disjoint Sets Forest)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "src/C14_1_DSL_1_A_union_find_tree.h"

namespace DSL_1_A {

class Test_DSL_1_A : public ::testing::Test {
 protected:
  UnionFindTree *union_find_tree_;
  virtual void SetUp() {
    union_find_tree_ = new UnionFindTree();
  }
  virtual void TearDown() {
    delete union_find_tree_;
  }
};

TEST_F(Test_DSL_1_A, CallUnionFindTree_1) {
  std::ostringstream answer;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "0" << std::endl;
  answer << "1" << std::endl;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5 12" << std::endl;
  input_stream << "0 1 4" << std::endl;
  input_stream << "0 2 3" << std::endl;
  input_stream << "1 1 2" << std::endl;
  input_stream << "1 3 4" << std::endl;
  input_stream << "1 1 4" << std::endl;
  input_stream << "1 3 2" << std::endl;
  input_stream << "0 1 3" << std::endl;
  input_stream << "1 2 4" << std::endl;
  input_stream << "1 3 0" << std::endl;
  input_stream << "0 0 4" << std::endl;
  input_stream << "1 0 2" << std::endl;
  input_stream << "1 3 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallUnionFindTree(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DSL_1_A, Initialized) {
  constexpr int32_t kNumberOfElements = 10;
  ASSERT_EQ(0, union_find_tree_->number_of_elements_);

  union_find_tree_->Initialize(kNumberOfElements);
  ASSERT_EQ(kNumberOfElements, union_find_tree_->number_of_elements_);
  for (int32_t index = 0; index < kNumberOfElements; ++index) {
    ASSERT_EQ(index, union_find_tree_->GetRoot(index));
    ASSERT_TRUE(union_find_tree_->IsRoot(index));
  }

  ASSERT_EQ(1, union_find_tree_->GetRoot(1));
  ASSERT_EQ(2, union_find_tree_->GetRoot(2));
  ASSERT_FALSE(union_find_tree_->IsSameSet(0, 1));
  ASSERT_FALSE(union_find_tree_->IsSameSet(1, 2));
  for (int32_t i = 0; i < kNumberOfElements; ++i) {
    for (int32_t j = 0; j < kNumberOfElements; ++j) {
      if (i == j) {
        ASSERT_TRUE(union_find_tree_->IsSameSet(i, j));
      } else {
        ASSERT_FALSE(union_find_tree_->IsSameSet(i, j));
      }
    }
  }
}

TEST_F(Test_DSL_1_A, UniteSets_1) {
  constexpr int32_t kNumberOfElements = 10;
  union_find_tree_->Initialize(kNumberOfElements);
  union_find_tree_->UniteSets(0, 1);
  ASSERT_TRUE(union_find_tree_->IsSameSet(0, 1));
  ASSERT_FALSE(union_find_tree_->IsSameSet(0, 2));
  ASSERT_FALSE(union_find_tree_->IsSameSet(1, 2));
  ASSERT_FALSE(union_find_tree_->IsSameSet(2, 3));
  ASSERT_FALSE(union_find_tree_->IsSameSet(4, 5));

  union_find_tree_->UniteSets(0, 4);
  ASSERT_TRUE(union_find_tree_->IsSameSet(0, 1));
  ASSERT_TRUE(union_find_tree_->IsSameSet(0, 4));
  ASSERT_TRUE(union_find_tree_->IsSameSet(1, 4));
  ASSERT_FALSE(union_find_tree_->IsSameSet(0, 2));
  ASSERT_FALSE(union_find_tree_->IsSameSet(1, 2));
  ASSERT_FALSE(union_find_tree_->IsSameSet(4, 2));
  ASSERT_FALSE(union_find_tree_->IsSameSet(2, 3));
  ASSERT_FALSE(union_find_tree_->IsSameSet(4, 5));
}

TEST_F(Test_DSL_1_A, UniteSets_2) {
  constexpr int32_t kNumberOfElements = 5;
  union_find_tree_->Initialize(kNumberOfElements);

  union_find_tree_->UniteSets(1, 4);
  union_find_tree_->UniteSets(2, 3);
  ASSERT_FALSE(union_find_tree_->IsSameSet(1, 2));
  ASSERT_FALSE(union_find_tree_->IsSameSet(3, 4));
  ASSERT_TRUE(union_find_tree_->IsSameSet(1, 4));
  ASSERT_TRUE(union_find_tree_->IsSameSet(3, 2));

  union_find_tree_->UniteSets(1, 3);
  ASSERT_TRUE(union_find_tree_->IsSameSet(2, 4));
  ASSERT_FALSE(union_find_tree_->IsSameSet(3, 0));

  union_find_tree_->UniteSets(0, 4);
  ASSERT_TRUE(union_find_tree_->IsSameSet(0, 2));
  ASSERT_TRUE(union_find_tree_->IsSameSet(3, 0));
}

TEST_F(Test_DSL_1_A, CallUnionFindTree_2) {
  std::ostringstream answer;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "10 30" << std::endl;
  input_stream << "1 3 2" << std::endl;
  input_stream << "1 0 8" << std::endl;
  input_stream << "0 6 9" << std::endl;
  input_stream << "1 1 3" << std::endl;
  input_stream << "1 8 3" << std::endl;
  input_stream << "0 6 9" << std::endl;
  input_stream << "0 7 2" << std::endl;
  input_stream << "0 0 3" << std::endl;
  input_stream << "1 2 4" << std::endl;
  input_stream << "1 1 7" << std::endl;
  input_stream << "0 4 5" << std::endl;
  input_stream << "0 4 0" << std::endl;
  input_stream << "0 4 3" << std::endl;
  input_stream << "1 0 6" << std::endl;
  input_stream << "0 1 9" << std::endl;
  input_stream << "1 5 1" << std::endl;
  input_stream << "0 4 5" << std::endl;
  input_stream << "1 0 7" << std::endl;
  input_stream << "0 3 4" << std::endl;
  input_stream << "0 0 9" << std::endl;
  input_stream << "0 6 2" << std::endl;
  input_stream << "0 3 0" << std::endl;
  input_stream << "1 9 5" << std::endl;
  input_stream << "1 9 7" << std::endl;
  input_stream << "1 7 4" << std::endl;
  input_stream << "0 9 6" << std::endl;
  input_stream << "0 3 5" << std::endl;
  input_stream << "1 6 9" << std::endl;
  input_stream << "0 2 5" << std::endl;
  input_stream << "1 8 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallUnionFindTree(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DSL_1_A, UniteSets_3) {
  constexpr int32_t kNumberOfElements = 10;
  union_find_tree_->Initialize(kNumberOfElements);

  union_find_tree_->UniteSets(6, 9);
  union_find_tree_->UniteSets(6, 9);
  union_find_tree_->UniteSets(7, 2);
  union_find_tree_->UniteSets(0, 3);
  union_find_tree_->UniteSets(4, 5);

  ASSERT_FALSE(union_find_tree_->IsSameSet(0, 5));
  union_find_tree_->UniteSets(4, 0);
  ASSERT_TRUE(union_find_tree_->IsSameSet(0, 5));

  union_find_tree_->UniteSets(4, 3);

  ASSERT_FALSE(union_find_tree_->IsSameSet(1, 6));
  union_find_tree_->UniteSets(1, 9);
  ASSERT_TRUE(union_find_tree_->IsSameSet(1, 6));

  union_find_tree_->UniteSets(4, 5);
  union_find_tree_->UniteSets(3, 4);

  ASSERT_FALSE(union_find_tree_->IsSameSet(4, 6));
  union_find_tree_->UniteSets(0, 9);
  ASSERT_TRUE(union_find_tree_->IsSameSet(4, 6));

  ASSERT_FALSE(union_find_tree_->IsSameSet(7, 3));
  union_find_tree_->UniteSets(6, 2);
  ASSERT_TRUE(union_find_tree_->IsSameSet(7, 3));
  ASSERT_TRUE(union_find_tree_->IsSameSet(9, 5));

  union_find_tree_->UniteSets(3, 0);
  ASSERT_TRUE(union_find_tree_->IsSameSet(9, 5));
}

TEST_F(Test_DSL_1_A, UniteSets_4) {
  constexpr int32_t kNumberOfElements = 4;
  union_find_tree_->Initialize(kNumberOfElements);

  union_find_tree_->UniteSets(0, 1);
  union_find_tree_->UniteSets(2, 3);
  ASSERT_TRUE(union_find_tree_->IsSameSet(0, 1));
  ASSERT_TRUE(union_find_tree_->IsSameSet(2, 3));
  ASSERT_FALSE(union_find_tree_->IsSameSet(0, 2));
  ASSERT_FALSE(union_find_tree_->IsSameSet(0, 3));

  union_find_tree_->UniteSets(1, 3);
  ASSERT_TRUE(union_find_tree_->IsSameSet(0, 1));
  ASSERT_TRUE(union_find_tree_->IsSameSet(2, 3));
  ASSERT_TRUE(union_find_tree_->IsSameSet(0, 2));
  ASSERT_TRUE(union_find_tree_->IsSameSet(0, 3));
}

TEST_F(Test_DSL_1_A, UniteSets_5) {
  constexpr int32_t kNumberOfElements = 3;
  union_find_tree_->Initialize(kNumberOfElements);
  union_find_tree_->UniteSets(1, 2);
  union_find_tree_->UniteSets(0, 1);
  union_find_tree_->UniteSets(1, 2);
  ASSERT_TRUE(union_find_tree_->IsSameSet(0, 2));
}

}  // namespace DSL_1_A
