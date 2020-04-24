/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-3. 再帰・分割統治法、コッホ曲線(Koch curve)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C06_3_ALDS1_5_C_KOCH_CURVE_H_
#define SRC_C06_3_ALDS1_5_C_KOCH_CURVE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <list>
#include <string>

namespace ALDS1_5_C {

constexpr int32_t kMaxLoopCount = 1000000000;

void CallKochCurve(std::istream &input_stream);

struct Point {
  float x{0.0F};
  float y{0.0F};
};

struct LineSegment {
  Point first{};
  Point second{};
};

void CreateKochCurve(std::list<LineSegment> *segments, const int32_t remaining_depth);

Point CreatePoint(const float x, const float y) noexcept;

LineSegment CreateLineSegment(const Point &first, const Point &second) noexcept;

Point CreateDelta(const LineSegment &segment) noexcept;

Point CreatePointS(const LineSegment &segment, const Point &delta) noexcept;

Point CreatePointT(const LineSegment &segment, const Point &delta) noexcept;

Point CreatePointU(const Point &point_s, const Point &delta) noexcept;

}  // namespace ALDS1_5_C

#endif  // SRC_C06_3_ALDS1_5_C_KOCH_CURVE_H_
