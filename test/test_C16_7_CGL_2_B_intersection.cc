/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part16-7. 計算幾何学(Computational Geometry)、線分の交差判定(Intersection)。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <list>
#include <sstream>
#include "src/C16_7_CGL_2_B_intersection.h"
#include "src/utils.h"

namespace CGL_2_B {
class Test_CGL_2_B : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_CGL_2_B, Point2D_Constructors) {
  constexpr double kX_1 = 1.0;
  constexpr double kY_1 = 2.0;
  const Point2D point_1(kX_1, kY_1);
  ASSERT_FLOAT_EQ(kX_1, point_1.X());
  ASSERT_FLOAT_EQ(kY_1, point_1.Y());

  const Point2D point_1_1 = point_1;
  ASSERT_FLOAT_EQ(point_1_1.X(), point_1.X());
  ASSERT_FLOAT_EQ(point_1_1.Y(), point_1.Y());

  const Point2D point_1_2(point_1);
  ASSERT_FLOAT_EQ(point_1_2.X(), point_1.X());
  ASSERT_FLOAT_EQ(point_1_2.Y(), point_1.Y());

  constexpr double kX_2 = 34.0;
  constexpr double kY_2 = 6543.0;
  Point2D point_1_3(kX_2, kY_2);
  point_1_3 = point_1;
  ASSERT_FLOAT_EQ(point_1_3.X(), point_1.X());
  ASSERT_FLOAT_EQ(point_1_3.Y(), point_1.Y());

  const Point2D point_1_4 = std::move(point_1_3);
  ASSERT_FLOAT_EQ(point_1_4.X(), point_1.X());
  ASSERT_FLOAT_EQ(point_1_4.Y(), point_1.Y());
}

TEST_F(Test_CGL_2_B, Point2D_Operators) {
  const Point2D point_1(1.0, 2.0F);
  const Point2D point_2(3.0, 4.0F);

  const Point2D result_plus = point_1 + point_2;
  ASSERT_FLOAT_EQ(4.0, result_plus.X());
  ASSERT_FLOAT_EQ(6.0, result_plus.Y());

  const Point2D result_minus = point_1 - point_2;
  ASSERT_FLOAT_EQ(-2.0, result_minus.X());
  ASSERT_FLOAT_EQ(-2.0, result_minus.Y());

  const Point2D result_scalar_product = point_1 * 4;
  ASSERT_FLOAT_EQ(4.0, result_scalar_product.X());
  ASSERT_FLOAT_EQ(8.0, result_scalar_product.Y());

  ASSERT_FLOAT_EQ(11.0, point_1.InnerProduct(point_2));
  ASSERT_FLOAT_EQ(-2.0, point_1.OuterProduct(point_2));
}

TEST_F(Test_CGL_2_B, IsParallel) {
  const Line line1(Point2D(0.0, -1.0), Point2D(2.0, 3.0));
  const Line line2(Point2D(1.0, 2.0), Point2D(2.0, 4.0));
  ASSERT_TRUE(line1.IsParallel(line2));

  const Line line3(Point2D(1.0, 2.0), Point2D(2.0, 7.0));
  ASSERT_FALSE(line1.IsParallel(line3));
}

TEST_F(Test_CGL_2_B, IsOrthogonal) {
  const Line line1(Point2D(1.0, 1.0), Point2D(2.0, 2.0));
  const Line line2(Point2D(0.0, 2.0), Point2D(2.0, 0.0));
  ASSERT_TRUE(line1.IsOrthogonal(line2));

  const Line line3(Point2D(1.0, 2.0), Point2D(2.0, 7.0));
  ASSERT_FALSE(line1.IsOrthogonal(line3));
}

TEST_F(Test_CGL_2_B, IsSame) {
  const Line line1(Point2D(1.0, 2.0), Point2D(2.0, 4.0));
  const Line line2(Point2D(0.0, 0.0), Point2D(3.0, 6.0));
  ASSERT_TRUE(line1 == line2);
  ASSERT_FALSE(line1 != line2);

  const Line line3(Point2D(0.0, 0.0), Point2D(3.0, 5.0));
  ASSERT_FALSE(line1 != line2);
  ASSERT_TRUE(line1 == line2);
}

TEST_F(Test_CGL_2_B, CallLineSegmentIntersection_1) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "0 0 3 0 1 1 2 -1" << std::endl;
  input_stream << "0 0 3 0 3 1 3 -1" << std::endl;
  input_stream << "0 0 3 0 3 -2 5 0" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallLineSegmentIntersection(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_CGL_2_B, CallLineSegmentIntersection_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "1" << std::endl;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "0" << std::endl;
  answer << "0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "8" << std::endl;
  input_stream << "0 0 4 0 1 1 1 -1" << std::endl;
  input_stream << "0 0 4 0 2 1 3 -1" << std::endl;
  input_stream << "0 0 4 0 3 1 2 -1" << std::endl;
  input_stream << "0 0 4 0 4 3 2 -3" << std::endl;
  input_stream << "0 0 4 0 5 1 6 -1" << std::endl;
  input_stream << "0 0 4 0 5 0 7 0" << std::endl;
  input_stream << "0 0 4 0 1 2 4 1" << std::endl;
  input_stream << "0 0 4 0 1 -2 1 -4" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallLineSegmentIntersection(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_CGL_2_B, SegmentsAreCrossing_1) {
  Line line1(Point2D(0.0, 0.0), Point2D(3.0, 0.0));
  Line line2(Point2D(1.0, 1.0), Point2D(2.0, -1.0));
  ASSERT_TRUE(line1.SegmentsAreCrossing(line2));
}

TEST_F(Test_CGL_2_B, SegmentsAreCrossing_2) {
  Line line1(Point2D(0.0, 0.0), Point2D(3.0, 0.0));
  Line line2(Point2D(3.0, 1.0), Point2D(3.0, -1.0));
  ASSERT_TRUE(line1.SegmentsAreCrossing(line2));
}

TEST_F(Test_CGL_2_B, SegmentsAreCrossing_3) {
  Line line1(Point2D(0.0, 0.0), Point2D(3.0, 0.0));
  Line line2(Point2D(3.0, -2.0), Point2D(5.0, 0.0));
  ASSERT_FALSE(line1.SegmentsAreCrossing(line2));
}

TEST_F(Test_CGL_2_B, SegmentsAreCrossing_4) {
  Line line1(Point2D(0.0, 0.0), Point2D(4.0, 0.0));
  Line line2(Point2D(5.0, 0.0), Point2D(7.0, 0.0));
  ASSERT_FALSE(line1.SegmentsAreCrossing(line2));
}

}  // namespace CGL_2_B
