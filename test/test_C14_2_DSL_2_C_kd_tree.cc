/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part14-2. 高度なデータ構造、kD Tree (kd木, k-dimensional tree)
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <ctime>
#include <iostream>
#include <random>
#include <sstream>

#include "src/C14_2_DSL_2_C_kd_tree.h"

namespace DSL_2_C {

class Test_DSL_2_C : public ::testing::Test {
 protected:
  KdTree* kd_tree_;
  virtual void SetUp() { kd_tree_ = new KdTree(); }
  virtual void TearDown() { delete kd_tree_; }
};

TEST_F(Test_DSL_2_C, AddPoint) {
  ASSERT_EQ(0, kd_tree_->number_of_points_);

  constexpr int32_t kX_0 = 1;
  constexpr int32_t kY_0 = 2;
  constexpr int32_t kX_1 = -1;
  constexpr int32_t kY_1 = 5;
  kd_tree_->AddPoint(CreatePoint2D(kX_0, kY_0, 0));
  kd_tree_->AddPoint(CreatePoint2D(kX_1, kY_1, 1));

  ASSERT_EQ(2, kd_tree_->number_of_points_);
  ASSERT_EQ(kX_0, kd_tree_->points_[0].x);
  ASSERT_EQ(kY_0, kd_tree_->points_[0].y);
  ASSERT_EQ(0, kd_tree_->points_[0].key);
  ASSERT_EQ(kX_1, kd_tree_->points_[1].x);
  ASSERT_EQ(kY_1, kd_tree_->points_[1].y);
  ASSERT_EQ(1, kd_tree_->points_[1].key);
}

TEST_F(Test_DSL_2_C, CallKdTree_1) {
  std::ostringstream answer;
  answer << "0" << std::endl;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "4" << std::endl;
  answer << "" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;
  answer << "5" << std::endl;
  answer << "" << std::endl;

  std::ostringstream input_stream;
  input_stream << "6" << std::endl;
  input_stream << "2 1" << std::endl;
  input_stream << "2 2" << std::endl;
  input_stream << "4 2" << std::endl;
  input_stream << "6 2" << std::endl;
  input_stream << "3 3" << std::endl;
  input_stream << "5 4" << std::endl;
  input_stream << "2" << std::endl;
  input_stream << "2 4 0 4" << std::endl;
  input_stream << "4 10 2 5" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKdTree(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_DSL_2_C, CallKdTree_2) {
  std::ostringstream answer;
  answer << "" << std::endl;
  answer << "17" << std::endl;
  answer << "25" << std::endl;
  answer << "" << std::endl;
  answer << "" << std::endl;
  answer << "5" << std::endl;
  answer << "25" << std::endl;
  answer << "" << std::endl;
  answer << "0" << std::endl;
  answer << "3" << std::endl;
  answer << "8" << std::endl;
  answer << "12" << std::endl;
  answer << "14" << std::endl;
  answer << "16" << std::endl;
  answer << "18" << std::endl;
  answer << "26" << std::endl;
  answer << "27" << std::endl;
  answer << "28" << std::endl;
  answer << "31" << std::endl;
  answer << "34" << std::endl;
  answer << "" << std::endl;
  answer << "5" << std::endl;
  answer << "25" << std::endl;
  answer << "" << std::endl;
  answer << "22" << std::endl;
  answer << "27" << std::endl;
  answer << "28" << std::endl;
  answer << "" << std::endl;
  answer << "5" << std::endl;
  answer << "25" << std::endl;
  answer << "33" << std::endl;
  answer << "" << std::endl;
  answer << "5" << std::endl;
  answer << "25" << std::endl;
  answer << "33" << std::endl;
  answer << "" << std::endl;
  answer << "5" << std::endl;
  answer << "25" << std::endl;
  answer << "33" << std::endl;
  answer << "" << std::endl;

  std::ostringstream input_stream;
  input_stream << "35" << std::endl;
  input_stream << "32 56" << std::endl;
  input_stream << "69 64" << std::endl;
  input_stream << "8 0" << std::endl;
  input_stream << "19 56" << std::endl;
  input_stream << "84 62" << std::endl;
  input_stream << "97 29" << std::endl;
  input_stream << "1 63" << std::endl;
  input_stream << "20 35" << std::endl;
  input_stream << "20 49" << std::endl;
  input_stream << "66 30" << std::endl;
  input_stream << "10 44" << std::endl;
  input_stream << "36 10" << std::endl;
  input_stream << "56 52" << std::endl;
  input_stream << "5 43" << std::endl;
  input_stream << "23 80" << std::endl;
  input_stream << "25 34" << std::endl;
  input_stream << "31 76" << std::endl;
  input_stream << "91 75" << std::endl;
  input_stream << "32 69" << std::endl;
  input_stream << "51 11" << std::endl;
  input_stream << "30 29" << std::endl;
  input_stream << "43 33" << std::endl;
  input_stream << "9 90" << std::endl;
  input_stream << "68 72" << std::endl;
  input_stream << "60 4" << std::endl;
  input_stream << "92 49" << std::endl;
  input_stream << "13 72" << std::endl;
  input_stream << "44 90" << std::endl;
  input_stream << "24 90" << std::endl;
  input_stream << "34 43" << std::endl;
  input_stream << "47 17" << std::endl;
  input_stream << "27 51" << std::endl;
  input_stream << "26 27" << std::endl;
  input_stream << "93 8" << std::endl;
  input_stream << "29 62" << std::endl;
  input_stream << "10" << std::endl;
  input_stream << "8 58 93 143" << std::endl;
  input_stream << "88 138 38 88" << std::endl;
  input_stream << "85 135 93 143" << std::endl;
  input_stream << "88 138 20 70" << std::endl;
  input_stream << "11 61 46 96" << std::endl;
  input_stream << "87 137 10 60" << std::endl;
  input_stream << "9 59 87 137" << std::endl;
  input_stream << "68 118 3 53" << std::endl;
  input_stream << "73 123 0 50" << std::endl;
  input_stream << "74 124 5 55" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKdTree(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

/*
TEST_F(Test_DSL_2_C, LargeNumberOfPoints_BuildKdTree) {
  unsigned int seed = 1U;
  for (int32_t i = 0; i < kMaxNumberOfPoints; ++i) {
    Point2D point;
    point.x = rand_r(&seed);
    point.y = rand_r(&seed);
    point.key = i;
    kd_tree_->AddPoint(point);
  }

  kd_tree_->BuildKdTree();
}

TEST_F(Test_DSL_2_C, LargeNumberOfPoints_FindPointsWithinRange) {
  unsigned int seed = 1U;
  for (int32_t i = 0; i < kMaxNumberOfPoints; ++i) {
    Point2D point;
    point.x = rand_r(&seed);
    point.y = rand_r(&seed);
    point.key = i;
    kd_tree_->AddPoint(point);
  }

  kd_tree_->BuildKdTree();
  for (int32_t i = 0; i < kMaxNumberOfQueries; ++i) {
    Range2D range;
    range.x.min = rand_r(&seed) % 100000;
    range.x.max = range.x.min + (rand_r(&seed) % 100000);
    range.y.min = rand_r(&seed);
    range.y.max = range.y.min + (rand_r(&seed) % 100000);
    kd_tree_->FindPointsWithinRange(range);
  }
}
*/

}  // namespace DSL_2_C
