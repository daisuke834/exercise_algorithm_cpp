/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part16-8. 計算幾何学(Computational Geometry)、線分の交点(Cross Point)。
 */

#ifndef SRC_C16_8_CGL_2_C_CROSS_POINT_H_
#define SRC_C16_8_CGL_2_C_CROSS_POINT_H_

#include <cstdint>
#include <iostream>

namespace CGL_2_C {

void CallLineSegmentCrossPoint(std::istream& input_stream) noexcept;

class Point2D {
 public:
  Point2D() noexcept;
  Point2D(const double x, const double y) noexcept;
  ~Point2D() noexcept;
  Point2D(const Point2D& obj) noexcept;
  Point2D& operator=(const Point2D& obj) noexcept;
  Point2D(Point2D&& obj) noexcept;
  Point2D& operator=(Point2D&& obj) noexcept;

  Point2D operator+(const Point2D& rhs) const noexcept;
  Point2D operator-(const Point2D& rhs) const noexcept;
  Point2D operator*(const double rhs) const noexcept;
  double InnerProduct(const Point2D& rhs) const noexcept;
  double OuterProduct(const Point2D& rhs) const noexcept;
  double SquareSum() const noexcept;
  double Norm() const noexcept;
  double GetHeightOfParallelogram(const Point2D& hypotenuse) const;

  double X() const noexcept;
  double Y() const noexcept;

 private:
  double x_;
  double y_;
};

class Line {
 public:
  Line(const Point2D& p1, const Point2D& p2) noexcept;
  ~Line() noexcept;
  bool IsParallel(const Line& rhs) const noexcept;
  bool IsOrthogonal(const Line& rhs) const noexcept;
  bool IsOnLine(const Point2D& point) const noexcept;
  bool operator==(const Line& rhs) const noexcept;
  bool operator!=(const Line& rhs) const noexcept;
  Point2D ProjectPoint(const Point2D& point) const;
  Point2D ReflectPoint(const Point2D& point) const;

  bool SegmentsAreCrossing(const Line& line) const;
  Point2D GetCrossPointOfSegments(const Line& line) const;
  bool PointIsOnSegment(const Point2D& point) const;
  double GetLineSegmentDistanceFromPoint(const Point2D& point) const;
  double GetLineSegmentDistance(const Line& line) const;

 private:
  Line() = delete;
  Line(const Line& obj) = delete;
  Line& operator=(const Line& obj) = delete;
  Line(Line&& obj) = delete;
  Line& operator=(Line&& obj) = delete;

 private:
  Point2D p1_;
  Point2D p2_;
};

}  // namespace CGL_2_C
#endif  // SRC_C16_8_CGL_2_C_CROSS_POINT_H_
