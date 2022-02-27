/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part16-3. 計算幾何学(Computational Geometry)、射影(Projection)。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <list>
#include <sstream>

#include "src/AOJ/textbook/16/3_CGL_1_A_projection.h"
#include "src/utils/utils.h"

namespace CGL_1_A {
namespace {
constexpr double kEPS = 0.00000001;
}  // namespace

class Test_CGL_1_A : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_CGL_1_A, Point2D_Constructors) {
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

TEST_F(Test_CGL_1_A, Point2D_Operators) {
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

TEST_F(Test_CGL_1_A, IsParallel) {
  const Line line1(Point2D(0.0, -1.0), Point2D(2.0, 3.0));
  const Line line2(Point2D(1.0, 2.0), Point2D(2.0, 4.0));
  ASSERT_TRUE(line1.IsParallel(line2));

  const Line line3(Point2D(1.0, 2.0), Point2D(2.0, 7.0));
  ASSERT_FALSE(line1.IsParallel(line3));
}

TEST_F(Test_CGL_1_A, IsOrthogonal) {
  const Line line1(Point2D(1.0, 1.0), Point2D(2.0, 2.0));
  const Line line2(Point2D(0.0, 2.0), Point2D(2.0, 0.0));
  ASSERT_TRUE(line1.IsOrthogonal(line2));

  const Line line3(Point2D(1.0, 2.0), Point2D(2.0, 7.0));
  ASSERT_FALSE(line1.IsOrthogonal(line3));
}

TEST_F(Test_CGL_1_A, IsSame) {
  const Line line1(Point2D(1.0, 2.0), Point2D(2.0, 4.0));
  const Line line2(Point2D(0.0, 0.0), Point2D(3.0, 6.0));
  ASSERT_TRUE(line1 == line2);
  ASSERT_FALSE(line1 != line2);

  const Line line3(Point2D(0.0, 0.0), Point2D(3.0, 5.0));
  ASSERT_FALSE(line1 != line2);
  ASSERT_TRUE(line1 == line2);
}

TEST_F(Test_CGL_1_A, CallProjection_1) {
  std::list<std::pair<double, double>> answers;
  answers.push_back(std::make_pair(3.1200000000, 4.1600000000));

  std::ostringstream input_stream;
  input_stream << "0 0 3 4" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "2 5" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallProjection(iss);
  } catch (...) {
    std::cerr << "ERROR: CallProjection_1" << std::endl;
    success = false;
  }
  EXPECT_TRUE(success);

  const std::vector<std::string> result_lines =
      utils::SplitStringToVector(std::string((testing::internal::GetCapturedStdout().c_str())), '\n');
  for (std::string cline : result_lines) {
    const std::vector<double> results = utils::SplitStringToDoubleVector(cline, ' ');
    const std::pair<double, double> canswer = answers.front();
    ASSERT_NEAR(canswer.first, results[0], kEPS);
    ASSERT_NEAR(canswer.second, results[1], kEPS);
    answers.pop_front();
  }
}

TEST_F(Test_CGL_1_A, CallProjection_2) {
  std::list<std::pair<double, double>> answers;
  answers.push_back(std::make_pair(-1.0000000000, 0.0000000000));
  answers.push_back(std::make_pair(0.0000000000, 0.0000000000));
  answers.push_back(std::make_pair(1.0000000000, 0.0000000000));

  std::ostringstream input_stream;
  input_stream << "0 0 2 0" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "-1 1" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "1 1" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallProjection(iss);
  } catch (...) {
    std::cerr << "ERROR: CallProjection_1" << std::endl;
    success = false;
  }
  EXPECT_TRUE(success);

  const std::vector<std::string> result_lines =
      utils::SplitStringToVector(std::string((testing::internal::GetCapturedStdout().c_str())), '\n');
  for (std::string cline : result_lines) {
    const std::vector<double> results = utils::SplitStringToDoubleVector(cline, ' ');
    const std::pair<double, double> canswer = answers.front();
    ASSERT_NEAR(canswer.first, results[0], kEPS);
    ASSERT_NEAR(canswer.second, results[1], kEPS);
    answers.pop_front();
  }
}

TEST_F(Test_CGL_1_A, CallProjection_3) {
  std::list<std::pair<double, double>> answers;
  answers.push_back(std::make_pair(-0.4411764706, 0.2647058824));
  answers.push_back(std::make_pair(1.4705882353, -0.8823529412));
  answers.push_back(std::make_pair(3.3823529412, -2.0294117647));
  answers.push_back(std::make_pair(5.2941176471, -3.1764705882));
  answers.push_back(std::make_pair(-0.2941176471, 0.1764705882));
  answers.push_back(std::make_pair(1.6176470588, -0.9705882353));
  answers.push_back(std::make_pair(3.5294117647, -2.1176470588));
  answers.push_back(std::make_pair(5.4411764706, -3.2647058824));

  std::ostringstream input_stream;
  input_stream << "0 0 5 -3" << std::endl;
  input_stream << "8" << std::endl;
  input_stream << "0 1" << std::endl;
  input_stream << "2 0" << std::endl;
  input_stream << "4 -1" << std::endl;
  input_stream << "6 -2" << std::endl;
  input_stream << "-1 -1" << std::endl;
  input_stream << "1 -2" << std::endl;
  input_stream << "3 -3" << std::endl;
  input_stream << "5 -4" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallProjection(iss);
  } catch (...) {
    std::cerr << "ERROR: CallProjection_1" << std::endl;
    success = false;
  }
  EXPECT_TRUE(success);

  const std::vector<std::string> result_lines =
      utils::SplitStringToVector(std::string((testing::internal::GetCapturedStdout().c_str())), '\n');
  for (std::string cline : result_lines) {
    const std::vector<double> results = utils::SplitStringToDoubleVector(cline, ' ');
    const std::pair<double, double> canswer = answers.front();
    ASSERT_NEAR(canswer.first, results[0], kEPS);
    ASSERT_NEAR(canswer.second, results[1], kEPS);
    answers.pop_front();
  }
}

}  // namespace CGL_1_A
