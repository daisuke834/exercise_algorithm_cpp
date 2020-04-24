/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part16-3. 計算幾何学(Computational Geometry)、射影(Projection)。
 */

#include "src/C16_3_CGL_1_A_projection.h"
#include <cmath>
#include <iomanip>
#include <iostream>

namespace CGL_1_A {

void CallProjection(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  double p0_x, p0_y, p1_x, p1_y;
  input_stream >> p0_x >> p0_y >> p1_x >> p1_y;
  Line line(Point2D(p0_x, p0_y), Point2D(p1_x, p1_y));

  int32_t number_of_queries;
  input_stream >> number_of_queries;
  for (int32_t i = 0; i < number_of_queries; ++i) {
    double x, y;
    input_stream >> x >> y;
    const Point2D projected_point = line.ProjectPoint(Point2D(x, y));
    std::cout << std::setprecision(20) << projected_point.X() << " " << projected_point.Y() << std::endl;
  }
}

// *************************************
Point2D::Point2D(const double x, const double y) noexcept : x_(x), y_(y) {}

Point2D::~Point2D() noexcept {}

Point2D::Point2D(const Point2D &obj) noexcept : x_(obj.x_), y_(obj.y_) {}

Point2D &Point2D::operator=(const Point2D &rhs) noexcept {
  if (this != &rhs) {
    this->x_ = rhs.x_;
    this->y_ = rhs.y_;
  }
  return *this;
}

Point2D::Point2D(Point2D &&obj) noexcept : x_(obj.x_), y_(obj.y_) {}

Point2D &Point2D::operator=(Point2D &&rhs) noexcept {
  if (this != &rhs) {
    this->x_ = rhs.x_;
    this->y_ = rhs.y_;
  }
  return *this;
}

Point2D Point2D::operator+(const Point2D &rhs) const noexcept {
  Point2D point(this->x_ + rhs.x_, this->y_ + rhs.y_);
  return point;
}

Point2D Point2D::operator-(const Point2D &rhs) const noexcept {
  Point2D point(this->x_ - rhs.x_, this->y_ - rhs.y_);
  return point;
}

Point2D Point2D::operator*(const double rhs) const noexcept {
  Point2D point(this->x_ * rhs, this->y_ * rhs);
  return point;
}

double Point2D::X() const noexcept {
  return x_;
}

double Point2D::Y() const noexcept {
  return y_;
}

double Point2D::InnerProduct(const Point2D &rhs) const noexcept {
  return ((this->x_ * rhs.x_) + (this->y_ * rhs.y_));
}
double Point2D::OuterProduct(const Point2D &rhs) const noexcept {
  return ((this->x_ * rhs.y_) - (this->y_ * rhs.x_));
}

double Point2D::SquareSum() const noexcept {
  return (x_ * x_ + y_ * y_);
}

// ************************************************

Line::Line(const Point2D &p1, const Point2D &p2) noexcept : p1_(p1), p2_(p2) {}

Line::~Line() noexcept {}

bool Line::IsParallel(const Line &rhs) const noexcept {
  const Point2D this_direction = this->p2_ - this->p1_;
  const Point2D rhs_direction = rhs.p2_ - rhs.p1_;
  const double outer_product = this_direction.OuterProduct(rhs_direction);
  constexpr double kEps = 0.0000001;
  const bool is_parallel = (fabs(outer_product) < kEps);
  return is_parallel;
}

bool Line::IsOrthogonal(const Line &rhs) const noexcept {
  const Point2D this_direction = this->p2_ - this->p1_;
  const Point2D rhs_direction = rhs.p2_ - rhs.p1_;
  constexpr double kEps = 0.0000001;
  const double inner_product = this_direction.InnerProduct(rhs_direction);
  const bool is_parallel = (fabs(inner_product) < kEps);
  return is_parallel;
}

bool Line::IsOnLine(const Point2D &point) const noexcept {
  const Line line1(point, p1_);
  const Line line2(point, p2_);
  const bool is_on_line = line1.IsParallel(line2);
  return is_on_line;
}

bool Line::operator==(const Line &rhs) const noexcept {
  return (IsOnLine(rhs.p1_) && IsOnLine(rhs.p2_));
}

bool Line::operator!=(const Line &rhs) const noexcept {
  return !(*this == rhs);
}

Point2D Line::ProjectPoint(const Point2D &point) const {
  const Point2D p2_from_p1 = p2_ - p1_;
  const Point2D point_from_p1 = point - p1_;
  const double square_sum = p2_from_p1.SquareSum();
  constexpr double kEps = 0.0000001;
  if (fabs(square_sum) < kEps) {
    std::cerr << "ERROR: Line::ProjectPoint()" << std::endl;
    throw 1;
  }
  const double coefficient = p2_from_p1.InnerProduct(point_from_p1) / square_sum;
  const Point2D projected_point = p1_ + (p2_from_p1 * coefficient);
  return projected_point;
}

}  // namespace CGL_1_A
