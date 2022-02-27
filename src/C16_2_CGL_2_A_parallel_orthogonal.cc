/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part16-2. 計算幾何学(Computational Geometry)、直線の直行・平行判定
 */

#include "src/C16_2_CGL_2_A_parallel_orthogonal.h"

#include <iostream>

namespace CGL_2_A {

void CallParallelOrthogonal(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  int32_t number_of_queries;
  input_stream >> number_of_queries;
  for (int32_t i = 0; i < number_of_queries; ++i) {
    int32_t p0_x, p0_y, p1_x, p1_y, p2_x, p2_y, p3_x, p3_y;
    input_stream >> p0_x >> p0_y >> p1_x >> p1_y >> p2_x >> p2_y >> p3_x >> p3_y;
    Line line1(Point2D(p0_x, p0_y), Point2D(p1_x, p1_y));
    Line line2(Point2D(p2_x, p2_y), Point2D(p3_x, p3_y));
    if (line1.IsParallel(line2)) {
      std::cout << 2 << std::endl;
    } else if (line1.IsOrthogonal(line2)) {
      std::cout << 1 << std::endl;
    } else {
      std::cout << 0 << std::endl;
    }
  }
}

// *************************************
Point2D::Point2D(const int32_t x, const int32_t y) noexcept : x_(x), y_(y) {}

Point2D::~Point2D() noexcept {}

Point2D::Point2D(const Point2D& obj) noexcept : x_(obj.x_), y_(obj.y_) {}

Point2D& Point2D::operator=(const Point2D& rhs) noexcept {
  if (this != &rhs) {
    this->x_ = rhs.x_;
    this->y_ = rhs.y_;
  }
  return *this;
}

Point2D::Point2D(Point2D&& obj) noexcept : x_(obj.x_), y_(obj.y_) {}

Point2D& Point2D::operator=(Point2D&& rhs) noexcept {
  if (this != &rhs) {
    this->x_ = rhs.x_;
    this->y_ = rhs.y_;
  }
  return *this;
}

Point2D Point2D::operator+(const Point2D& rhs) const noexcept {
  Point2D point(this->x_ + rhs.x_, this->y_ + rhs.y_);
  return point;
}

Point2D Point2D::operator-(const Point2D& rhs) const noexcept {
  Point2D point(this->x_ - rhs.x_, this->y_ - rhs.y_);
  return point;
}

Point2D Point2D::operator*(const int32_t rhs) const noexcept {
  Point2D point(this->x_ * rhs, this->y_ * rhs);
  return point;
}

int32_t Point2D::X() const noexcept { return x_; }

int32_t Point2D::Y() const noexcept { return y_; }

int32_t Point2D::InnerProduct(const Point2D& rhs) const noexcept { return ((this->x_ * rhs.x_) + (this->y_ * rhs.y_)); }
int32_t Point2D::OuterProduct(const Point2D& rhs) const noexcept { return ((this->x_ * rhs.y_) - (this->y_ * rhs.x_)); }

// ************************************************

Line::Line(const Point2D& p1, const Point2D& p2) noexcept : p1_(p1), p2_(p2) {}

Line::~Line() noexcept {}

bool Line::IsParallel(const Line& rhs) const noexcept {
  const Point2D this_direction = this->p2_ - this->p1_;
  const Point2D rhs_direction = rhs.p2_ - rhs.p1_;
  const int32_t outer_product = this_direction.OuterProduct(rhs_direction);
  const bool is_parallel = (outer_product == 0);
  return is_parallel;
}

bool Line::IsOrthogonal(const Line& rhs) const noexcept {
  const Point2D this_direction = this->p2_ - this->p1_;
  const Point2D rhs_direction = rhs.p2_ - rhs.p1_;
  const int32_t inner_product = this_direction.InnerProduct(rhs_direction);
  const bool is_parallel = (inner_product == 0);
  return is_parallel;
}

bool Line::IsOnLine(const Point2D& point) const noexcept {
  const Line line1(point, p1_);
  const Line line2(point, p2_);
  const bool is_on_line = line1.IsParallel(line2);
  return is_on_line;
}

bool Line::operator==(const Line& rhs) const noexcept { return (IsOnLine(rhs.p1_) && IsOnLine(rhs.p2_)); }

bool Line::operator!=(const Line& rhs) const noexcept { return !(*this == rhs); }

}  // namespace CGL_2_A
