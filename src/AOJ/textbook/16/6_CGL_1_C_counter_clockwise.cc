/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part16-6. 計算幾何学(Computational Geometry)、反時計回り(Counter Clockwise)。
 */

#include "6_CGL_1_C_counter_clockwise.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace CGL_1_C {

void CallCounterClockwise(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  double p0_x, p0_y, p1_x, p1_y;
  input_stream >> p0_x >> p0_y >> p1_x >> p1_y;
  const Point2D p0(p0_x, p0_y);
  const Point2D p1(p1_x, p1_y);
  const Point2D p1_from_p0 = p1 - p0;
  int32_t number_of_queries;
  input_stream >> number_of_queries;
  for (int32_t i = 0; i < number_of_queries; ++i) {
    double p2_x, p2_y;
    input_stream >> p2_x >> p2_y;
    const Point2D p2(p2_x, p2_y);
    const OrderOfThreePoints order = JudgeOrderOfThreePoints(p0, p1, p2);
    switch (order) {
      case OrderOfThreePoints::kCounterClockWise:
        std::cout << "COUNTER_CLOCKWISE" << std::endl;
        break;
      case OrderOfThreePoints::kClockWise:
        std::cout << "CLOCKWISE" << std::endl;
        break;
      case OrderOfThreePoints::kOnSegment:
        std::cout << "ON_SEGMENT" << std::endl;
        break;
      case OrderOfThreePoints::kOnlineFront:
        std::cout << "ONLINE_FRONT" << std::endl;
        break;
      case OrderOfThreePoints::kOnlineBack:
        std::cout << "ONLINE_BACK" << std::endl;
        break;
      default:
        std::cerr << "ERROR CallCounterClockwise(): Invalid order" << std::endl;
        throw 1;
        break;
    }
  }
}

// *************************************
Point2D::Point2D() noexcept : x_(0.0), y_(0.0) {}

Point2D::Point2D(const double x, const double y) noexcept : x_(x), y_(y) {}

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

Point2D Point2D::operator*(const double rhs) const noexcept {
  Point2D point(this->x_ * rhs, this->y_ * rhs);
  return point;
}

double Point2D::X() const noexcept { return x_; }

double Point2D::Y() const noexcept { return y_; }

double Point2D::InnerProduct(const Point2D& rhs) const noexcept { return ((this->x_ * rhs.x_) + (this->y_ * rhs.y_)); }
double Point2D::OuterProduct(const Point2D& rhs) const noexcept { return ((this->x_ * rhs.y_) - (this->y_ * rhs.x_)); }

double Point2D::SquareSum() const noexcept { return (x_ * x_ + y_ * y_); }

double Point2D::Norm() const noexcept { return sqrt(SquareSum()); }

OrderOfThreePoints JudgeOrderOfThreePoints(const Point2D& p0, const Point2D& p1, const Point2D& p2) {
  OrderOfThreePoints order;
  try {
    constexpr double kEps = 0.00001;
    const Point2D p1_from_p0 = p1 - p0;
    const Point2D p2_from_p0 = p2 - p0;
    if (p1_from_p0.OuterProduct(p2_from_p0) > kEps) {
      order = OrderOfThreePoints::kCounterClockWise;
    } else if (p1_from_p0.OuterProduct(p2_from_p0) < -kEps) {
      order = OrderOfThreePoints::kClockWise;
    } else {
      const Line p0p1(p0, p1);
      const Line p0p2(p0, p2);
      const Point2D from_p0_to_p2;
      if (p0p1.GetLineSegmentDistanceFromPoint(p2) < kEps) {
        order = OrderOfThreePoints::kOnSegment;
      } else if (p0p2.GetLineSegmentDistanceFromPoint(p1) < kEps) {
        order = OrderOfThreePoints::kOnlineFront;
      } else {
        order = OrderOfThreePoints::kOnlineBack;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: JudgeOrderOfThreePoints()" << std::endl;
    throw 1;
  }
  return order;
}

// ************************************************

Line::Line(const Point2D& p1, const Point2D& p2) noexcept : p1_(p1), p2_(p2) {}

Line::~Line() noexcept {}

bool Line::IsParallel(const Line& rhs) const noexcept {
  const Point2D this_direction = this->p2_ - this->p1_;
  const Point2D rhs_direction = rhs.p2_ - rhs.p1_;
  const double outer_product = this_direction.OuterProduct(rhs_direction);
  constexpr double kEps = 0.0000001;
  const bool is_parallel = (fabs(outer_product) < kEps);
  return is_parallel;
}

bool Line::IsOrthogonal(const Line& rhs) const noexcept {
  const Point2D this_direction = this->p2_ - this->p1_;
  const Point2D rhs_direction = rhs.p2_ - rhs.p1_;
  constexpr double kEps = 0.0000001;
  const double inner_product = this_direction.InnerProduct(rhs_direction);
  const bool is_parallel = (fabs(inner_product) < kEps);
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

Point2D Line::ProjectPoint(const Point2D& point) const {
  const Point2D p2_from_p1 = p2_ - p1_;
  const Point2D point_from_p1 = point - p1_;
  const double square_sum = p2_from_p1.SquareSum();
  constexpr double kEps = 0.0000001;
  if (square_sum < kEps) {
    std::cerr << "ERROR: Line::ProjectPoint(): square_sum is too small. square_sum=" << square_sum
              << ",  x=" << p2_from_p1.X() << ", y=" << p2_from_p1.Y() << std::endl;
    throw 1;
  }
  const double coefficient = p2_from_p1.InnerProduct(point_from_p1) / square_sum;
  const Point2D projected_point = p1_ + (p2_from_p1 * coefficient);
  return projected_point;
}

Point2D Line::ReflectPoint(const Point2D& point) const {
  Point2D reflected_point;
  try {
    const Point2D projected_point = ProjectPoint(point);
    reflected_point = point + ((projected_point - point) * 2.0);
  } catch (...) {
    std::cerr << "ERROR: ReflectPoint()" << std::endl;
  }
  return reflected_point;
}

double Line::GetLineSegmentDistanceFromPoint(const Point2D& point) const {
  double distance;
  try {
    const Point2D projected_point_from_point1 = ProjectPoint(point) - p1_;
    const Point2D point2_from_point1 = p2_ - p1_;
    bool projected_point_is_inside = ((projected_point_from_point1.SquareSum() <= point2_from_point1.SquareSum()) &&
                                      (projected_point_from_point1.InnerProduct(point2_from_point1) >= 0.0));
    if (projected_point_is_inside) {
      const Point2D r = ProjectPoint(point) - point;
      distance = r.Norm();
    } else {
      const Point2D diff1 = point - p1_;
      const Point2D diff2 = point - p2_;
      distance = fmin(diff1.Norm(), diff2.Norm());
    }
  } catch (...) {
    std::cerr << "ERROR: GetLineSegmentDistanceFromPoint()" << std::endl;
    throw 1;
  }
  return distance;
}

double Line::GetLineSegmentDistance(const Line& line) const {
  double line_segment_distance;
  try {
    if (SegmentsAreCrossing(line)) {
      line_segment_distance = 0.0;
    } else {
      line_segment_distance =
          fmin(fmin(GetLineSegmentDistanceFromPoint(line.p1_), GetLineSegmentDistanceFromPoint(line.p2_)),
               fmin(line.GetLineSegmentDistanceFromPoint(p1_), line.GetLineSegmentDistanceFromPoint(p2_)));
    }
  } catch (...) {
    std::cerr << "ERROR: GetLineSegmentDistance()" << std::endl;
  }
  return line_segment_distance;
}

bool Line::SegmentsAreCrossing(const Line& line) const {
  const Point2D r1 = p2_ - p1_;
  const Point2D diff1_1 = line.p1_ - p1_;
  const Point2D diff1_2 = line.p2_ - p1_;
  const bool temp_1 = ((r1.OuterProduct(diff1_1) * r1.OuterProduct(diff1_2)) < 0.0);

  const Point2D r2 = line.p2_ - line.p1_;
  const Point2D diff2_1 = p1_ - line.p1_;
  const Point2D diff2_2 = p2_ - line.p1_;
  const bool temp_2 = ((r2.OuterProduct(diff2_1) * r2.OuterProduct(diff2_2)) < 0.0);
  return (temp_1 && temp_2);
}

}  // namespace CGL_1_C
