/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-3. 再帰・分割統治法、コッホ曲線(Koch curve)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C06_3_ALDS1_5_C_koch_curve.h"

#include <iostream>
#include <string>

namespace ALDS1_5_C {

void CallKochCurve(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  try {
    int32_t koch_depth;
    input_stream >> koch_depth;

    const Point initial_p1 = CreatePoint(0.0F, 0.0F);
    const Point initial_p2 = CreatePoint(100.0F, 0.0F);
    const LineSegment initial_line_segment = CreateLineSegment(initial_p1, initial_p2);
    std::list<LineSegment> segments;
    segments.push_back(initial_line_segment);
    CreateKochCurve(&segments, koch_depth);
    for (LineSegment csegment : segments) {
      std::cout << csegment.first.x << " " << csegment.first.y << std::endl;
    }
    if (!segments.empty()) {
      std::cout << segments.back().second.x << " " << segments.back().second.y << std::endl;
    }
  } catch (...) {
    std::cerr << "ERROR: CallKochCurve()" << std::endl;
    throw;
  }
}

void CreateKochCurve(std::list<LineSegment>* segments, const int32_t remaining_depth) {
  if (remaining_depth > 0) {
    std::list<LineSegment>::iterator csegment = (*segments).begin();
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      const Point delta = CreateDelta(*csegment);
      const Point point_s = CreatePointS(*csegment, delta);
      const Point point_t = CreatePointT(*csegment, delta);
      const Point point_u = CreatePointU(point_s, delta);
      segments->insert(csegment, CreateLineSegment(csegment->first, point_s));
      segments->insert(csegment, CreateLineSegment(point_s, point_u));
      segments->insert(csegment, CreateLineSegment(point_u, point_t));
      segments->insert(csegment, CreateLineSegment(point_t, csegment->second));
      csegment = segments->erase(csegment);
      if (csegment == (*segments).end()) {
        break;
      }
    }
    const int32_t next_remaining_depth = remaining_depth - 1;
    CreateKochCurve(segments, next_remaining_depth);
  } else {
    // DO NOTHING
  }
}

Point CreatePoint(const float x, const float y) noexcept {
  Point cpoint;
  cpoint.x = x;
  cpoint.y = y;
  return cpoint;
}

LineSegment CreateLineSegment(const Point& first, const Point& second) noexcept {
  LineSegment segment;
  segment.first = first;
  segment.second = second;
  return segment;
}

Point CreateDelta(const LineSegment& segment) noexcept {
  Point delta;
  delta.x = (segment.second.x - segment.first.x) / 3.0F;
  delta.y = (segment.second.y - segment.first.y) / 3.0F;
  return delta;
}

Point CreatePointS(const LineSegment& segment, const Point& delta) noexcept {
  return CreatePoint(segment.first.x + delta.x, segment.first.y + delta.y);
}

Point CreatePointT(const LineSegment& segment, const Point& delta) noexcept {
  return CreatePoint(segment.first.x + 2.0F * delta.x, segment.first.y + 2.0F * delta.y);
}

Point CreatePointU(const Point& point_s, const Point& delta) noexcept {
  const float kRoot3 = 1.7320508075688772;
  const float u_x = point_s.x + delta.x / 2.0F - delta.y * kRoot3 / 2.0F;
  const float u_y = point_s.y + delta.x * kRoot3 / 2.0F + delta.y / 2.0F;
  return CreatePoint(u_x, u_y);
}

}  // namespace ALDS1_5_C
