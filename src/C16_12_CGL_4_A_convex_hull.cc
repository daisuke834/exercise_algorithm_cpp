/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part16-12. 計算幾何学(Computational Geometry)、凸包(Convex Hull)。
 */

#include "src/C16_12_CGL_4_A_convex_hull.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

namespace CGL_4_A {

void CallConvexHull(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  ConvexHull *convex_hull = new ConvexHull();
  try {
    int32_t number_of_points;
    input_stream >> number_of_points;
    for (int32_t i = 0; i < number_of_points; ++i) {
      double x, y;
      input_stream >> x >> y;
      convex_hull->AddPoint(Point2D(x, y));
    }
    std::vector<Point2D> vertices = convex_hull->GetVertices();
    const int32_t number_of_vertices = vertices.size();
    std::cout << number_of_vertices << std::endl;
    int32_t start;
    int32_t x_min = INT32_MAX;
    int32_t y_min = INT32_MAX;
    for (int32_t i = number_of_vertices - 1; i >= 0; --i) {
      const Point2D &cpoint = vertices[i];
      if (static_cast<int32_t>(cpoint.Y()) < y_min) {
        start = i;
        x_min = static_cast<int32_t>(cpoint.X());
        y_min = static_cast<int32_t>(cpoint.Y());
      } else if (static_cast<int32_t>(cpoint.Y()) == y_min) {
        if (static_cast<int32_t>(cpoint.X()) < x_min) {
          start = i;
          x_min = static_cast<int32_t>(cpoint.X());
        }
      }
    }
    int32_t cindex = start;
    for (int32_t i = 0; i < number_of_vertices; ++i) {
      std::cout << static_cast<int32_t>(vertices[cindex].X()) << " " << static_cast<int32_t>(vertices[cindex].Y())
                << std::endl;
      cindex = (number_of_vertices + cindex - 1) % number_of_vertices;
    }
  } catch (...) {
    std::cerr << "CallConvexHull()" << std::endl;
    // DO NOT THROW ERROR
  }
  delete convex_hull;
}

// *************************************
Point2D::Point2D() noexcept : x_(0.0), y_(0.0) {}

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

double Point2D::Norm() const noexcept {
  return sqrt(SquareSum());
}

double Point2D::GetHeightOfParallelogram(const Point2D &hypotenuse) const {
  double height;
  try {
    const double area_of_parallelogram = fabs(OuterProduct(hypotenuse));
    const double base_length = Norm();
    constexpr double kEps = 0.00000001;
    if (base_length < kEps) {
      std::cerr << "ERROR: GetHeightOfParallelogram(): Invalid base_length=" << base_length << std::endl;
      throw 1;
    }
    height = area_of_parallelogram / base_length;
  } catch (...) {
    std::cerr << "ERROR: GetHeightOfParallelogram()" << std::endl;
    throw;
  }
  return height;
}

Point2D Point2D::Perpendicular() const noexcept {
  const Point2D perpendicular(Y(), -X());
  return perpendicular;
}

OrderOfThreePoints JudgeOrderOfThreePoints(const Point2D &p0, const Point2D &p1, const Point2D &p2) {
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

bool Line::IsOnSegment(const Point2D &point) const noexcept {
  bool is_on_segment;
  const bool is_on_line = IsOnLine(point);
  if (is_on_line) {
    const Point2D p1_from_point = p1_ - point;
    const Point2D p2_from_point = p2_ - point;
    is_on_segment = (p1_from_point.InnerProduct(p2_from_point) <= 0);
  } else {
    is_on_segment = false;
  }
  return is_on_segment;
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

Point2D Line::ReflectPoint(const Point2D &point) const {
  Point2D reflected_point;
  try {
    const Point2D projected_point = ProjectPoint(point);
    reflected_point = point + ((projected_point - point) * 2.0);
  } catch (...) {
    std::cerr << "ERROR: ReflectPoint()" << std::endl;
  }
  return reflected_point;
}

double Line::GetLineSegmentDistanceFromPoint(const Point2D &point) const {
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

double Line::GetLineSegmentDistance(const Line &line) const {
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

bool Line::PointIsOnSegment(const Point2D &point) const {
  constexpr double kEps = 0.0000001;
  bool point_is_on_segment;
  try {
    point_is_on_segment = (GetLineSegmentDistanceFromPoint(point) < kEps);
  } catch (...) {
    std::cerr << "ERROR: PointIsOnSegment()" << std::endl;
    throw;
  }
  return point_is_on_segment;
}

bool Line::SegmentsAreCrossing(const Line &line) const {
  const Point2D r1 = p2_ - p1_;
  const Point2D diff1_1 = line.p1_ - p1_;
  const Point2D diff1_2 = line.p2_ - p1_;
  const bool temp_1 = ((r1.OuterProduct(diff1_1) * r1.OuterProduct(diff1_2)) < 0.0);

  const Point2D r2 = line.p2_ - line.p1_;
  const Point2D diff2_1 = p1_ - line.p1_;
  const Point2D diff2_2 = p2_ - line.p1_;
  const bool temp_2 = ((r2.OuterProduct(diff2_1) * r2.OuterProduct(diff2_2)) < 0.0);

  const bool any_points_is_on_segment = (PointIsOnSegment(line.p1_) || PointIsOnSegment(line.p2_) ||
                                         line.PointIsOnSegment(p1_) || line.PointIsOnSegment(p2_));

  return (temp_1 && temp_2) || any_points_is_on_segment;
}

Point2D Line::GetCrossPointOfSegments(const Line &line) const {
  Point2D cross_point;
  try {
    const Point2D base_vector = p2_ - p1_;
    const Point2D hypotenuse_vector_1 = line.p1_ - p1_;
    double height_1 = base_vector.GetHeightOfParallelogram(hypotenuse_vector_1);
    const Point2D hypotenuse_vector_2 = line.p2_ - p1_;
    double height_2 = base_vector.GetHeightOfParallelogram(hypotenuse_vector_2);
    constexpr double kEps = 0.0000001;
    const double height_sum = height_1 + height_2;
    if (height_sum < kEps) {
      std::cerr << "ERROR: GetCrossPointOfSegments(): Invalid height_sum=" << height_sum << std::endl;
      throw 1;
    }
    const double ratio = height_1 / height_sum;
    cross_point = line.p1_ + (line.p2_ - line.p1_) * ratio;
  } catch (...) {
    std::cerr << "ERROR: GetCrossPointOfSegments()" << std::endl;
    throw;
  }
  return cross_point;
}

std::pair<Point2D, Point2D> Line::GetBasePoints() const noexcept {
  const std::pair<Point2D, Point2D> pair = std::make_pair(p1_, p2_);
  return pair;
}

bool Line::SegmentCrossesWithRightwardHalflineFromPoint(const Point2D &point) const {
  bool segment_crosses_with_rightward_half_line;
  try {
    Point2D point_y_small = p1_ - point;
    Point2D point_y_large = p2_ - point;
    if (point_y_small.Y() > point_y_large.Y()) {
      const Point2D temp = point_y_small;
      point_y_small = point_y_large;
      point_y_large = temp;
    }
    constexpr double kEps = 0.0000001;
    segment_crosses_with_rightward_half_line = ((point_y_small.Y() < kEps) && (kEps < point_y_large.Y()) &&
                                                (point_y_small.OuterProduct(point_y_large) > kEps));
  } catch (...) {
    std::cerr << "SegmentCrossesWithRightwardHalflineFromPoint::IsContained" << std::endl;
    throw;
  }
  return segment_crosses_with_rightward_half_line;
}

// ************************************************

Circle::Circle(const double center_x, const double center_y, const double radius) noexcept
    : center_(Point2D(center_x, center_y)), radius_(radius) {}

Circle::~Circle() noexcept {}

std::pair<Point2D, Point2D> Circle::GetCrossPointsWithLine(const Line &line) const {
  std::pair<Point2D, Point2D> cross_points;
  try {
    const std::pair<Point2D, Point2D> line_points = line.GetBasePoints();
    const Point2D direction = line_points.second - line_points.first;
    const double temp_x = line_points.first.X() - center_.X();
    const double temp_y = line_points.first.Y() - center_.Y();
    const double a = (direction.X() * direction.X()) + (direction.Y() * direction.Y());
    const double b = 2.0 * ((direction.X() * temp_x) + (direction.Y() * temp_y));
    const double c = temp_x * temp_x + temp_y * temp_y - radius_ * radius_;
    const double temp_sq = sqrt(b * b - 4.0 * a * c);
    constexpr double kEps = 0.0000001;
    if (sqrt(a) < kEps) {
      std::cerr << "ERROR: GetCrossPointsWithLine(): Invalid a=" << a << std::endl;
      throw 1;
    }
    const double t_1 = (-b + temp_sq) / 2.0 / a;
    const double t_2 = (-b - temp_sq) / 2.0 / a;
    const Point2D cross_point_1 = (line_points.first + (direction * t_1));
    const Point2D cross_point_2 = (line_points.first + (direction * t_2));

    if (fabs(cross_point_1.X() - cross_point_2.X()) < kEps) {
      if (cross_point_1.Y() < cross_point_2.Y()) {
        cross_points.first = cross_point_1;
        cross_points.second = cross_point_2;
      } else {
        cross_points.first = cross_point_2;
        cross_points.second = cross_point_1;
      }
    } else if (cross_point_1.X() < cross_point_2.X()) {
      cross_points.first = cross_point_1;
      cross_points.second = cross_point_2;
    } else {
      cross_points.first = cross_point_2;
      cross_points.second = cross_point_1;
    }
  } catch (...) {
    std::cerr << "ERROR: GetCrossPointsWithLine()" << std::endl;
    throw;
  }
  return cross_points;
}

std::pair<Point2D, Point2D> Circle::GetCrossPointsWithCircle(const Circle &circle) const {
  std::pair<Point2D, Point2D> cross_points;
  try {
    const Point2D c1c2 = circle.center_ - center_;
    const double d_squared = c1c2.SquareSum();

    const double t = (radius_ * radius_ - circle.radius_ * circle.radius_ + d_squared) / 2.0 / d_squared;
    const Point2D a = c1c2 * t;

    const Point2D c1c2_perpendicular = c1c2.Perpendicular();
    constexpr double kEps = 0.0000001;
    if (c1c2_perpendicular.Norm() < kEps) {
      std::cerr << "ERROR: GetCrossPointsWithCircle(): Invalid c1c2_perpendicular.Norm()=" << c1c2_perpendicular.Norm()
                << std::endl;
      throw 1;
    }
    const Point2D b = c1c2_perpendicular * (sqrt(radius_ * radius_ - a.SquareSum()) / c1c2_perpendicular.Norm());

    const Point2D cross_point_1 = center_ + a + b;
    const Point2D cross_point_2 = center_ + a - b;

    if (fabs(cross_point_1.X() - cross_point_2.X()) < kEps) {
      if (cross_point_1.Y() < cross_point_2.Y()) {
        cross_points.first = cross_point_1;
        cross_points.second = cross_point_2;
      } else {
        cross_points.first = cross_point_2;
        cross_points.second = cross_point_1;
      }
    } else if (cross_point_1.X() < cross_point_2.X()) {
      cross_points.first = cross_point_1;
      cross_points.second = cross_point_2;
    } else {
      cross_points.first = cross_point_2;
      cross_points.second = cross_point_1;
    }
  } catch (...) {
    std::cerr << "ERROR: GetCrossPointsWithCircle()" << std::endl;
    throw;
  }
  return cross_points;
}

// ************************************************
Polygon::Polygon() noexcept {}
Polygon::~Polygon() noexcept {}

void Polygon::AddVertex(const Point2D &vertex) noexcept {
  vertices_.push_back(vertex);
}

Containment Polygon::AskContainment(const Point2D &point) const noexcept {
  int32_t vertex_count_on_right_size = 0;
  bool loop_completed = true;
  try {
    const int32_t number_of_vertices = static_cast<int32_t>(vertices_.size());
    for (int32_t vertex_index = 0; vertex_index < number_of_vertices; ++vertex_index) {
      const int32_t next_vertex_index = (vertex_index + 1) % number_of_vertices;
      const Point2D &vertex_1 = vertices_[vertex_index];
      const Point2D &vertex_2 = vertices_[next_vertex_index];
      const Line line(vertex_1, vertex_2);
      if (line.IsOnSegment(point)) {
        loop_completed = false;
        break;
      } else {
        const bool segment_crosses_with_rightward_half_line = line.SegmentCrossesWithRightwardHalflineFromPoint(point);
        if (segment_crosses_with_rightward_half_line) {
          ++vertex_count_on_right_size;
        }
      }
    }
  } catch (...) {
    std::cerr << "Polygon::IsContained" << std::endl;
    throw;
  }
  Containment containment;
  if (loop_completed) {
    if (vertex_count_on_right_size % 2 == 0) {
      containment = Containment::kIsNotContained;
    } else {
      containment = Containment::kIsContained;
    }
  } else {
    containment = Containment::kIsOnEdge;
  }
  return containment;
}

// ************************************************
ConvexHull::ConvexHull() noexcept {}

ConvexHull::~ConvexHull() noexcept {}

void ConvexHull::AddPoint(const Point2D &point) noexcept {
  points_.push_back(point);
}

std::vector<Point2D> ConvexHull::GetVertices() {
  std::vector<Point2D> vertices;
  try {
    SortPoints();
    vertices = CreateUpperHalf();
    std::vector<Point2D> lower_half = CreateLowerHalf();
    for (int32_t i = 1; i <= static_cast<int32_t>(lower_half.size()) - 2; ++i) {
      vertices.push_back(lower_half[i]);
    }
  } catch (...) {
    std::cerr << "ERROR: ConvexHull::GetVertices()" << std::endl;
    throw;
  }
  return vertices;
}

std::vector<Point2D> ConvexHull::CreateUpperHalf() noexcept {
  std::vector<Point2D> upper_half;
  try {
    const int32_t number_of_points = static_cast<int32_t>(points_.size());
    for (int32_t index = 0; index < number_of_points; ++index) {
      const Point2D &cpoint = points_[index];
      constexpr int32_t kMaxLoopCount = 2000000;
      for (int32_t i = 0; i < kMaxLoopCount; ++i) {
        const int32_t upper_half_size = static_cast<int32_t>(upper_half.size());
        if (upper_half_size < 2) {
          break;
        } else {
          const OrderOfThreePoints order =
              JudgeOrderOfThreePoints(upper_half[upper_half_size - 2], upper_half[upper_half_size - 1], cpoint);
          if (order == OrderOfThreePoints::kCounterClockWise) {
            upper_half.pop_back();
          } else {
            break;
          }
        }
      }
      upper_half.push_back(cpoint);
    }
  } catch (...) {
    std::cerr << "ERROR: ConvexHull::CreateUpperHalf()" << std::endl;
    throw;
  }
  return upper_half;
}

std::vector<Point2D> ConvexHull::CreateLowerHalf() noexcept {
  std::vector<Point2D> lower_half;
  try {
    const int32_t number_of_points = static_cast<int32_t>(points_.size());
    for (int32_t index = number_of_points - 1; index >= 0; --index) {
      const Point2D &cpoint = points_[index];
      constexpr int32_t kMaxLoopCount = 2000000;
      for (int32_t i = 0; i < kMaxLoopCount; ++i) {
        const int32_t lower_half_size = static_cast<int32_t>(lower_half.size());
        if (lower_half_size < 2) {
          break;
        } else {
          const OrderOfThreePoints order =
              JudgeOrderOfThreePoints(lower_half[lower_half_size - 2], lower_half[lower_half_size - 1], cpoint);
          if (order == OrderOfThreePoints::kCounterClockWise) {
            lower_half.pop_back();
          } else {
            break;
          }
        }
      }
      lower_half.push_back(cpoint);
    }
  } catch (...) {
    std::cerr << "ERROR: ConvexHull::CreateLowerHalf()" << std::endl;
    throw;
  }
  return lower_half;
}

void ConvexHull::SortPoints() {
  try {
    std::sort(points_.begin(), points_.end(), P1xIsLessThanP2x);
  } catch (...) {
    std::cerr << "ERROR: ConvexHull::SortPoints()" << std::endl;
    throw;
  }
}

bool P1xIsLessThanP2x(const Point2D &p1, const Point2D &p2) noexcept {
  bool is_less_than;
  constexpr double kEps = 0.0000001;
  if (p1.X() < p2.X() - kEps) {
    is_less_than = true;
  } else if (p1.X() > p2.X() + kEps) {
    is_less_than = false;
  } else {
    if (p1.Y() < p2.Y() - kEps) {
      is_less_than = true;
    } else {
      is_less_than = false;
    }
  }
  return is_less_than;
}

}  // namespace CGL_4_A
