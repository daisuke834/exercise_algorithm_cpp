/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part16-2. 計算幾何学(Computational Geometry)、直線の直行・平行判定
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C16_2_CGL_2_A_parallel_orthogonal.h"

namespace CGL_2_A {
class Test_CGL_2_A : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_CGL_2_A, Point2D_Constructors) {
  constexpr int32_t kX_1 = 1;
  constexpr int32_t kY_1 = 2;
  const Point2D point_1(kX_1, kY_1);
  ASSERT_EQ(kX_1, point_1.X());
  ASSERT_EQ(kY_1, point_1.Y());

  const Point2D point_1_1 = point_1;
  ASSERT_EQ(point_1_1.X(), point_1.X());
  ASSERT_EQ(point_1_1.Y(), point_1.Y());

  const Point2D point_1_2(point_1);
  ASSERT_EQ(point_1_2.X(), point_1.X());
  ASSERT_EQ(point_1_2.Y(), point_1.Y());

  constexpr int32_t kX_2 = 34;
  constexpr int32_t kY_2 = 6543;
  Point2D point_1_3(kX_2, kY_2);
  point_1_3 = point_1;
  ASSERT_EQ(point_1_3.X(), point_1.X());
  ASSERT_EQ(point_1_3.Y(), point_1.Y());

  const Point2D point_1_4 = std::move(point_1_3);
  ASSERT_EQ(point_1_4.X(), point_1.X());
  ASSERT_EQ(point_1_4.Y(), point_1.Y());
}

TEST_F(Test_CGL_2_A, Point2D_Operators) {
  const Point2D point_1(1, 2);
  const Point2D point_2(3, 4);

  const Point2D result_plus = point_1 + point_2;
  ASSERT_EQ(4, result_plus.X());
  ASSERT_EQ(6, result_plus.Y());

  const Point2D result_minus = point_1 - point_2;
  ASSERT_EQ(-2, result_minus.X());
  ASSERT_EQ(-2, result_minus.Y());

  const Point2D result_scalar_product = point_1 * 4;
  ASSERT_EQ(4, result_scalar_product.X());
  ASSERT_EQ(8, result_scalar_product.Y());

  ASSERT_EQ(11, point_1.InnerProduct(point_2));
  ASSERT_EQ(-2, point_1.OuterProduct(point_2));
}

TEST_F(Test_CGL_2_A, IsParallel) {
  const Line line1(Point2D(0, -1), Point2D(2, 3));
  const Line line2(Point2D(1, 2), Point2D(2, 4));
  ASSERT_TRUE(line1.IsParallel(line2));

  const Line line3(Point2D(1, 2), Point2D(2, 7));
  ASSERT_FALSE(line1.IsParallel(line3));
}

TEST_F(Test_CGL_2_A, IsOrthogonal) {
  const Line line1(Point2D(1, 1), Point2D(2, 2));
  const Line line2(Point2D(0, 2), Point2D(2, 0));
  ASSERT_TRUE(line1.IsOrthogonal(line2));

  const Line line3(Point2D(1, 2), Point2D(2, 7));
  ASSERT_FALSE(line1.IsOrthogonal(line3));
}

TEST_F(Test_CGL_2_A, IsSame) {
  const Line line1(Point2D(1, 2), Point2D(2, 4));
  const Line line2(Point2D(0, 0), Point2D(3, 6));
  ASSERT_TRUE(line1 == line2);
  ASSERT_FALSE(line1 != line2);

  const Line line3(Point2D(0, 0), Point2D(3, 5));
  ASSERT_FALSE(line1 != line2);
  ASSERT_TRUE(line1 == line2);
}

TEST_F(Test_CGL_2_A, CallParallelOrthogonal) {
  std::ostringstream answer;
  answer << "2" << std::endl;
  answer << "1" << std::endl;
  answer << "0" << std::endl;

  std::ostringstream input_stream;
  input_stream << "3" << std::endl;
  input_stream << "0 0 3 0 0 2 3 2" << std::endl;
  input_stream << "0 0 3 0 1 1 1 4" << std::endl;
  input_stream << "0 0 3 0 1 1 2 2" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  CallParallelOrthogonal(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace CGL_2_A
