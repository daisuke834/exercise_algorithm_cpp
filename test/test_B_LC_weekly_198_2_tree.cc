/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-198-2. 1519. Number of Nodes in the Sub-Tree With the Same Label
 * https://leetcode.com/contest/weekly-contest-198/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_LC_weekly_198_2_tree.h"

namespace LC_weekly_198_2 {

class Test_LC_weekly_198_2 : public ::testing::Test {
 protected:
  Solution *solution_;
  virtual void SetUp() {
    solution_ = new Solution();
  }
  virtual void TearDown() {
    delete solution_;
  }
};

TEST_F(Test_LC_weekly_198_2, test_1) {
  int64_t n = 7;
  std::vector<std::vector<int>> edges = {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}};
  std::string labels = "abaedcd";
  std::vector<int> answer = {2, 1, 1, 1, 1, 1, 1};
  ASSERT_EQ(answer, solution_->countSubTrees(n, edges, labels));
}

TEST_F(Test_LC_weekly_198_2, test_2) {
  int64_t n = 4;
  std::vector<std::vector<int>> edges = {{0, 1}, {1, 2}, {0, 3}};
  std::string labels = "bbbb";
  std::vector<int> answer = {4, 2, 1, 1};
  ASSERT_EQ(answer, solution_->countSubTrees(n, edges, labels));
}

TEST_F(Test_LC_weekly_198_2, test_3) {
  int64_t n = 5;
  std::vector<std::vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {0, 4}};
  std::string labels = "aabab";
  std::vector<int> answer = {3, 2, 1, 1, 1};
  ASSERT_EQ(answer, solution_->countSubTrees(n, edges, labels));
}

TEST_F(Test_LC_weekly_198_2, test_4) {
  int64_t n = 6;
  std::vector<std::vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {3, 4}, {4, 5}};
  std::string labels = "cbabaa";
  std::vector<int> answer = {1, 2, 1, 1, 2, 1};
  ASSERT_EQ(answer, solution_->countSubTrees(n, edges, labels));
}

TEST_F(Test_LC_weekly_198_2, test_5) {
  int64_t n = 7;
  std::vector<std::vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};
  std::string labels = "aaabaaa";
  std::vector<int> answer = {6, 5, 4, 1, 3, 2, 1};
  ASSERT_EQ(answer, solution_->countSubTrees(n, edges, labels));
}

}  // namespace LC_weekly_198_2
