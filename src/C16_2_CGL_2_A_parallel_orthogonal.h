/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part16-2. 計算幾何学(Computational Geometry)、直線の直行/平行判定
 */

#ifndef SRC_C16_2_CGL_2_A_PARALLEL_ORTHOGONAL_H_
#define SRC_C16_2_CGL_2_A_PARALLEL_ORTHOGONAL_H_

#include <cstdint>
#include <iostream>

namespace CGL_2_A {

void CallParallelOrthogonal(std::istream &input_stream) noexcept;

class Point2D {
 public:
  Point2D(const int32_t x, const int32_t y) noexcept;
  ~Point2D() noexcept;
  Point2D(const Point2D &obj) noexcept;
  Point2D &operator=(const Point2D &obj) noexcept;
  Point2D(Point2D &&obj) noexcept;
  Point2D &operator=(Point2D &&obj) noexcept;

  Point2D operator+(const Point2D &rhs) const noexcept;
  Point2D operator-(const Point2D &rhs) const noexcept;
  Point2D operator*(const int32_t rhs) const noexcept;
  int32_t InnerProduct(const Point2D &rhs) const noexcept;
  int32_t OuterProduct(const Point2D &rhs) const noexcept;

  int32_t X() const noexcept;
  int32_t Y() const noexcept;

 private:
  Point2D() = delete;

 private:
  int32_t x_;
  int32_t y_;
};

class Line {
 public:
  Line(const Point2D &p1, const Point2D &p2) noexcept;
  ~Line() noexcept;
  bool IsParallel(const Line &rhs) const noexcept;
  bool IsOrthogonal(const Line &rhs) const noexcept;
  bool IsOnLine(const Point2D &point) const noexcept;
  bool operator==(const Line &rhs) const noexcept;
  bool operator!=(const Line &rhs) const noexcept;

 private:
  Line() = delete;
  Line(const Line &obj) = delete;
  Line &operator=(const Line &obj) = delete;
  Line(Line &&obj) = delete;
  Line &operator=(Line &&obj) = delete;

 private:
  Point2D p1_;
  Point2D p2_;
};

}  // namespace CGL_2_A
#endif  // SRC_C16_2_CGL_2_A_PARALLEL_ORTHOGONAL_H_
