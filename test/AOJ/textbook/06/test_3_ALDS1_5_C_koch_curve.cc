/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part6-3. 再帰・分割統治法、コッホ曲線(Koch curve)のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <list>
#include <sstream>

#include "src/AOJ/textbook/06/3_ALDS1_5_C_koch_curve.h"
#include "src/utils/utils.h"

namespace ALDS1_5_C {

constexpr float kEPS = 0.0001;

TEST(Test_ALDS1_5_C, CallKochCurve_0) {
  std::list<Point> answers;
  answers.push_back(CreatePoint(0.0F, 0.0F));
  answers.push_back(CreatePoint(100.00000000F, 0.00000000F));

  std::ostringstream input_stream;
  input_stream << "0" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKochCurve(iss);
  } catch (...) {
    std::cerr << "ERROR: Test_ALDS1_5_C.CallKochCurve_0" << std::endl;
    success = false;
  }
  EXPECT_TRUE(success);

  const std::vector<std::string> result_lines =
      utils::SplitStringToVector(std::string((testing::internal::GetCapturedStdout().c_str())), '\n');
  for (std::string cline : result_lines) {
    const std::vector<float> results = utils::SplitStringToFloatVector(cline, ' ');
    const Point canswer = answers.front();
    ASSERT_NEAR(canswer.x, results[0], kEPS);
    ASSERT_NEAR(canswer.y, results[1], kEPS);
    answers.pop_front();
  }
}

TEST(Test_ALDS1_5_C, CallKochCurve_1) {
  std::list<Point> answers;
  answers.push_back(CreatePoint(0.0F, 0.0F));
  answers.push_back(CreatePoint(33.33333333F, 0.00000000F));
  answers.push_back(CreatePoint(50.00000000F, 28.86751346F));
  answers.push_back(CreatePoint(66.66666667F, 0.00000000F));
  answers.push_back(CreatePoint(100.00000000F, 0.00000000F));

  std::ostringstream input_stream;
  input_stream << "1" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  bool success = true;
  try {
    CallKochCurve(iss);
  } catch (...) {
    std::cerr << "ERROR: Test_ALDS1_5_C.CallKochCurve_1" << std::endl;
    success = false;
  }
  EXPECT_TRUE(success);

  const std::vector<std::string> result_lines =
      utils::SplitStringToVector(std::string((testing::internal::GetCapturedStdout().c_str())), '\n');
  for (std::string cline : result_lines) {
    const std::vector<float> results = utils::SplitStringToFloatVector(cline, ' ');
    const Point canswer = answers.front();
    ASSERT_NEAR(canswer.x, results[0], kEPS);
    ASSERT_NEAR(canswer.y, results[1], kEPS);
    answers.pop_front();
  }
}

TEST(Test_ALDS1_5_C, CreateKochCurve_0) {
  constexpr int32_t kKochDepth = 0;
  std::list<Point> answers;
  answers.push_back(CreatePoint(0.0F, 0.0F));
  answers.push_back(CreatePoint(100.00000000F, 0.00000000F));

  const Point initial_p1 = CreatePoint(0.0F, 0.0F);
  const Point initial_p2 = CreatePoint(100.0F, 0.0F);
  const LineSegment initial_line_segment = CreateLineSegment(initial_p1, initial_p2);
  std::list<LineSegment> segments;
  segments.push_back(initial_line_segment);
  CreateKochCurve(&segments, kKochDepth);
  for (LineSegment csegment : segments) {
    const Point canswer = answers.front();
    ASSERT_NEAR(canswer.x, csegment.first.x, kEPS);
    ASSERT_NEAR(canswer.y, csegment.first.y, kEPS);
    answers.pop_front();
  }
}

TEST(Test_ALDS1_5_C, CreateKochCurve_1) {
  constexpr int32_t kKochDepth = 1;
  std::list<Point> answers;
  answers.push_back(CreatePoint(0.0F, 0.0F));
  answers.push_back(CreatePoint(33.33333333F, 0.00000000F));
  answers.push_back(CreatePoint(50.00000000F, 28.86751346F));
  answers.push_back(CreatePoint(66.66666667F, 0.00000000F));
  answers.push_back(CreatePoint(100.00000000F, 0.00000000F));

  const Point initial_p1 = CreatePoint(0.0F, 0.0F);
  const Point initial_p2 = CreatePoint(100.0F, 0.0F);
  const LineSegment initial_line_segment = CreateLineSegment(initial_p1, initial_p2);
  std::list<LineSegment> segments;
  segments.push_back(initial_line_segment);
  CreateKochCurve(&segments, kKochDepth);
  for (LineSegment csegment : segments) {
    const Point canswer = answers.front();
    ASSERT_NEAR(canswer.x, csegment.first.x, kEPS);
    ASSERT_NEAR(canswer.y, csegment.first.y, kEPS);
    answers.pop_front();
  }
}

}  // namespace ALDS1_5_C
