/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part16-12. 計算幾何学(Computational Geometry)、凸包(Convex Hull)。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <list>
#include <sstream>

#include "src/AOJ/textbook/16/12_CGL_4_A_convex_hull.h"
#include "src/utils/utils.h"

namespace CGL_4_A {
namespace {
constexpr double kEPS = 0.00000001;
}  // namespace

class Test_CGL_4_A : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_CGL_4_A, Point2D_Constructors) {
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

TEST_F(Test_CGL_4_A, Point2D_Operators) {
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

TEST_F(Test_CGL_4_A, Point2D_Perpendicular) {
  const Point2D vector_1(0, 1);
  const Point2D perp_1 = vector_1.Perpendicular();
  ASSERT_FLOAT_EQ(0, vector_1.InnerProduct(perp_1));

  const Point2D vector_2(1, 0);
  const Point2D perp_2 = vector_2.Perpendicular();
  ASSERT_FLOAT_EQ(0, vector_2.InnerProduct(perp_2));

  const Point2D vector_3(1, 1);
  const Point2D perp_3 = vector_3.Perpendicular();
  ASSERT_FLOAT_EQ(0, vector_3.InnerProduct(perp_3));
}

TEST_F(Test_CGL_4_A, IsParallel) {
  const Line line1(Point2D(0.0, -1.0), Point2D(2.0, 3.0));
  const Line line2(Point2D(1.0, 2.0), Point2D(2.0, 4.0));
  ASSERT_TRUE(line1.IsParallel(line2));

  const Line line3(Point2D(1.0, 2.0), Point2D(2.0, 7.0));
  ASSERT_FALSE(line1.IsParallel(line3));
}

TEST_F(Test_CGL_4_A, IsOrthogonal) {
  const Line line1(Point2D(1.0, 1.0), Point2D(2.0, 2.0));
  const Line line2(Point2D(0.0, 2.0), Point2D(2.0, 0.0));
  ASSERT_TRUE(line1.IsOrthogonal(line2));

  const Line line3(Point2D(1.0, 2.0), Point2D(2.0, 7.0));
  ASSERT_FALSE(line1.IsOrthogonal(line3));
}

TEST_F(Test_CGL_4_A, IsSame) {
  const Line line1(Point2D(1.0, 2.0), Point2D(2.0, 4.0));
  const Line line2(Point2D(0.0, 0.0), Point2D(3.0, 6.0));
  ASSERT_TRUE(line1 == line2);
  ASSERT_FALSE(line1 != line2);

  const Line line3(Point2D(0.0, 0.0), Point2D(3.0, 5.0));
  ASSERT_FALSE(line1 != line2);
  ASSERT_TRUE(line1 == line2);
}

TEST_F(Test_CGL_4_A, SegmentsAreCrossing_1) {
  Line line1(Point2D(0.0, 0.0), Point2D(3.0, 0.0));
  Line line2(Point2D(1.0, 1.0), Point2D(2.0, -1.0));
  ASSERT_TRUE(line1.SegmentsAreCrossing(line2));
}

TEST_F(Test_CGL_4_A, SegmentsAreCrossing_2) {
  Line line1(Point2D(0.0, 0.0), Point2D(3.0, 0.0));
  Line line2(Point2D(3.0, 1.0), Point2D(3.0, -1.0));
  ASSERT_TRUE(line1.SegmentsAreCrossing(line2));
}

TEST_F(Test_CGL_4_A, SegmentsAreCrossing_3) {
  Line line1(Point2D(0.0, 0.0), Point2D(3.0, 0.0));
  Line line2(Point2D(3.0, -2.0), Point2D(5.0, 0.0));
  ASSERT_FALSE(line1.SegmentsAreCrossing(line2));
}

TEST_F(Test_CGL_4_A, SegmentsAreCrossing_4) {
  Line line1(Point2D(0.0, 0.0), Point2D(4.0, 0.0));
  Line line2(Point2D(5.0, 0.0), Point2D(7.0, 0.0));
  ASSERT_FALSE(line1.SegmentsAreCrossing(line2));
}

TEST_F(Test_CGL_4_A, GetHeightOfParallelogram) {
  const Point2D base_vector_1(1.0, 0.0);
  const Point2D hypotenuse_vector_1(0.0, 1.0);
  ASSERT_NEAR(1.0, base_vector_1.GetHeightOfParallelogram(hypotenuse_vector_1), 0.00001);

  const Point2D hypotenuse_vector_2(1.0, 1.0);
  ASSERT_NEAR(1.0, base_vector_1.GetHeightOfParallelogram(hypotenuse_vector_2), 0.00001);

  const Point2D base_vector_3(1.4142135623730951, 1.4142135623730951);
  const Point2D hypotenuse_vector_3(0.0, 1.0);
  ASSERT_NEAR(0.7071067811865476, base_vector_3.GetHeightOfParallelogram(hypotenuse_vector_3), 0.00001);
}

TEST_F(Test_CGL_4_A, GetCrossPointsWithLine_1) {
  const Circle circle(2.0, 1.0, 1.0);

  const Line line_1(Point2D(0.0, 1.0), Point2D(4.0, 1.0));
  std::pair<Point2D, Point2D> cross_points_1 = circle.GetCrossPointsWithLine(line_1);
  ASSERT_NEAR(1.0, cross_points_1.first.X(), kEPS);
  ASSERT_NEAR(1.0, cross_points_1.first.Y(), kEPS);
  ASSERT_NEAR(3.0, cross_points_1.second.X(), kEPS);
  ASSERT_NEAR(1.0, cross_points_1.second.Y(), kEPS);

  const Line line_2(Point2D(3.0, 0.0), Point2D(3.0, 3.0));
  std::pair<Point2D, Point2D> cross_points_2 = circle.GetCrossPointsWithLine(line_2);
  ASSERT_NEAR(3.0, cross_points_2.first.X(), kEPS);
  ASSERT_NEAR(1.0, cross_points_2.first.Y(), kEPS);
  ASSERT_NEAR(3.0, cross_points_2.second.X(), kEPS);
  ASSERT_NEAR(1.0, cross_points_2.second.Y(), kEPS);
}

TEST_F(Test_CGL_4_A, GetCrossPointsWithLine_2) {
  constexpr int32_t kNumberOfLines = 8;
  const double answers[kNumberOfLines][4] = {
      {-0.43468860, -0.90058083, 0.95192997, -0.30631573}, {-0.77700043, 0.62950007, 0.93916259, 0.34347290},
      {-0.84991694, -0.52691669, 0.92050517, -0.39073037}, {-0.94804172, 0.31814603, -0.63686394, -0.77097621},
      {-0.24253563, 0.97014250, 0.24253563, -0.97014250},  {-0.31622777, -0.94868330, 0.31622777, 0.94868330},
      {-0.32432432, -0.94594595, 0.00000000, -1.00000000}, {0.26322452, -0.96473460, 0.83266589, 0.55377570}};

  const Circle circle(0.0, 0.0, 1.0);
  const float segments[kNumberOfLines][4] = {{-3.0, -2.0, 4.0, 1.0}, {-3.0, 1.0, 3.0, 0.0}, {-7.0, -1.0, 6.0, 0.0},
                                             {-2.0, 4.0, 0.0, -3.0}, {-1.0, 4.0, 0.0, 0.0}, {1.0, 3.0, -1.0, -3.0},
                                             {-6.0, 0.0, 6.0, -2.0}, {1.0, 1.0, -2.0, -7.0}};

  for (int32_t i = 0; i < kNumberOfLines; ++i) {
    const Line line(Point2D(segments[i][0], segments[i][1]), Point2D(segments[i][2], segments[i][3]));
    std::pair<Point2D, Point2D> cross_points = circle.GetCrossPointsWithLine(line);
    ASSERT_NEAR(answers[i][0], cross_points.first.X(), kEPS);
    ASSERT_NEAR(answers[i][1], cross_points.first.Y(), kEPS);
    ASSERT_NEAR(answers[i][2], cross_points.second.X(), kEPS);
    ASSERT_NEAR(answers[i][3], cross_points.second.Y(), kEPS);
  }
}

TEST_F(Test_CGL_4_A, GetCrossPointsWithCircle_1) {
  const double answers[4] = {1.00000000, -1.73205080, 1.00000000, 1.73205080};

  std::ostringstream input_stream;
  const Circle circle_1(0, 0, 2);
  const Circle circle_2(2, 0, 2);
  const std::pair<Point2D, Point2D> cross_points = circle_1.GetCrossPointsWithCircle(circle_2);
  ASSERT_NEAR(answers[0], cross_points.first.X(), kEPS);
  ASSERT_NEAR(answers[1], cross_points.first.Y(), kEPS);
  ASSERT_NEAR(answers[2], cross_points.second.X(), kEPS);
  ASSERT_NEAR(answers[3], cross_points.second.Y(), kEPS);
}

TEST_F(Test_CGL_4_A, GetCrossPointsWithCircle_2) {
  const double answers[4] = {0.00000000, 2.00000000, 0.00000000, 2.00000000};

  std::ostringstream input_stream;
  const Circle circle_1(0, 0, 2);
  const Circle circle_2(0, 3, 1);
  const std::pair<Point2D, Point2D> cross_points = circle_1.GetCrossPointsWithCircle(circle_2);
  ASSERT_NEAR(answers[0], cross_points.first.X(), kEPS);
  ASSERT_NEAR(answers[1], cross_points.first.Y(), kEPS);
  ASSERT_NEAR(answers[2], cross_points.second.X(), kEPS);
  ASSERT_NEAR(answers[3], cross_points.second.Y(), kEPS);
}

TEST_F(Test_CGL_4_A, GetCrossPointsWithCircle_3) {
  const double answers[4] = {38.04051291, 2.73817308, 64.95948709, 5.26182692};

  std::ostringstream input_stream;
  const Circle circle_1(50, 20, 21);
  const Circle circle_2(53, -12, 21);
  const std::pair<Point2D, Point2D> cross_points = circle_1.GetCrossPointsWithCircle(circle_2);
  EXPECT_NEAR(answers[0], cross_points.first.X(), kEPS);
  EXPECT_NEAR(answers[1], cross_points.first.Y(), kEPS);
  EXPECT_NEAR(answers[2], cross_points.second.X(), kEPS);
  EXPECT_NEAR(answers[3], cross_points.second.Y(), kEPS);
}

TEST_F(Test_CGL_4_A, GetCrossPointsWithCircle_4) {
  const double answers[4] = {43.31475034, 39.90747189, 69.90747189, 13.31475034};

  std::ostringstream input_stream;
  const Circle circle_1(50, 20, 21);
  const Circle circle_2(41, 11, 29);
  const std::pair<Point2D, Point2D> cross_points = circle_1.GetCrossPointsWithCircle(circle_2);
  EXPECT_NEAR(answers[0], cross_points.first.X(), kEPS);
  EXPECT_NEAR(answers[1], cross_points.first.Y(), kEPS);
  EXPECT_NEAR(answers[2], cross_points.second.X(), kEPS);
  EXPECT_NEAR(answers[3], cross_points.second.Y(), kEPS);
}

TEST_F(Test_CGL_4_A, IsOnSegment) {
  const Line line(Point2D(0.0, 0.0), Point2D(1.0, 1.0));
  ASSERT_TRUE(line.IsOnSegment(Point2D(0.0, 0.0)));
  ASSERT_TRUE(line.IsOnSegment(Point2D(0.1, 0.1)));
  ASSERT_TRUE(line.IsOnSegment(Point2D(0.5, 0.5)));
  ASSERT_TRUE(line.IsOnSegment(Point2D(1.0, 1.0)));

  ASSERT_FALSE(line.IsOnSegment(Point2D(0.1, 0.0)));
  ASSERT_FALSE(line.IsOnSegment(Point2D(0.0, 0.1)));
  ASSERT_FALSE(line.IsOnSegment(Point2D(-1.0, -1.0)));
  ASSERT_FALSE(line.IsOnSegment(Point2D(2.0, 2.0)));
}

TEST_F(Test_CGL_4_A, SegmentCrossesWithRightwardHalflineFromPoint) {
  const Line line(Point2D(3.0, 1.0), Point2D(2.0, 3.0));
  ASSERT_TRUE(line.SegmentCrossesWithRightwardHalflineFromPoint(Point2D(2.0, 2.0)));
  ASSERT_FALSE(line.SegmentCrossesWithRightwardHalflineFromPoint(Point2D(3.0, 2.0)));
  ASSERT_TRUE(line.SegmentCrossesWithRightwardHalflineFromPoint(Point2D(2.0, 1.0)));
  ASSERT_FALSE(line.SegmentCrossesWithRightwardHalflineFromPoint(Point2D(0.0, 3.0)));
}

TEST_F(Test_CGL_4_A, AskContainment_1) {
  Polygon polygon;
  polygon.AddVertex(Point2D(0.0, 0.0));
  polygon.AddVertex(Point2D(3.0, 1.0));
  polygon.AddVertex(Point2D(2.0, 3.0));
  polygon.AddVertex(Point2D(0.0, 3.0));

  ASSERT_EQ(Containment::kIsNotContained, polygon.AskContainment(Point2D(4.0, 2.0)));
  ASSERT_EQ(Containment::kIsNotContained, polygon.AskContainment(Point2D(-1.0, 2.0)));
  ASSERT_EQ(Containment::kIsOnEdge, polygon.AskContainment(Point2D(0.0, 1.0)));
  ASSERT_EQ(Containment::kIsOnEdge, polygon.AskContainment(Point2D(3.0, 1.0)));
  ASSERT_EQ(Containment::kIsContained, polygon.AskContainment(Point2D(2.0, 2.0)));
  ASSERT_EQ(Containment::kIsContained, polygon.AskContainment(Point2D(2.0, 1.0)));
}
TEST_F(Test_CGL_4_A, AskContainment_2) {
  Polygon polygon;
  polygon.AddVertex(Point2D(0.0, 0.0));
  polygon.AddVertex(Point2D(3.0, 1.0));
  polygon.AddVertex(Point2D(3.0, 3.0));
  polygon.AddVertex(Point2D(0.0, 3.0));

  ASSERT_EQ(Containment::kIsNotContained, polygon.AskContainment(Point2D(2.0, 0.0)));
  ASSERT_EQ(Containment::kIsNotContained, polygon.AskContainment(Point2D(4.0, 1.0)));
}

TEST_F(Test_CGL_4_A, CallConvexHull_1) {
  std::ostringstream answer;
  answer << "5" << std::endl;
  answer << "0 0" << std::endl;
  answer << "2 1" << std::endl;
  answer << "4 2" << std::endl;
  answer << "3 3" << std::endl;
  answer << "1 3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "7" << std::endl;
  input_stream << "2 1" << std::endl;
  input_stream << "0 0" << std::endl;
  input_stream << "1 2" << std::endl;
  input_stream << "2 2" << std::endl;
  input_stream << "4 2" << std::endl;
  input_stream << "1 3" << std::endl;
  input_stream << "3 3" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallConvexHull(iss);
  } catch (...) {
    success = false;
  }
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(success);
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace CGL_4_A
