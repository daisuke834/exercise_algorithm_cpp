/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-6. データ構造の応用、面積計算。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C04_4_ALDS1_3_D_1_CROSS_SECTION_DIAGRAM_H_
#define SRC_C04_4_ALDS1_3_D_1_CROSS_SECTION_DIAGRAM_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace ALDS1_3_D_1 {

constexpr int32_t kMaxNumberOfGridX = 20000;

enum class Slope : int32_t { kFallingToRight = 0, kFlat, kRisingToRight };

struct GridInformation {
  Slope slope;
  int32_t height_left{0};
  int32_t height_right{0};
  int32_t highest_height_leftside{0};
  int32_t highest_height_rightside{0};
  float partial_area{0.0F};
};

class CrossSectionDiagram {
 public:
  CrossSectionDiagram() noexcept;
  ~CrossSectionDiagram() noexcept;
  void Main(std::istream &input_stream);
  void Load(std::istream &input_stream);
  float CalculateAreas();

 private:
  CrossSectionDiagram(const CrossSectionDiagram &obj) = delete;
  CrossSectionDiagram &operator=(const CrossSectionDiagram &rhs) = delete;
  CrossSectionDiagram(CrossSectionDiagram &&obj) = delete;
  CrossSectionDiagram &operator=(CrossSectionDiagram &&rhs) = delete;

  void CalculateHighestHeightLeftSide() noexcept;
  void CalculateHighestHeightRightSide() noexcept;
  float CalculateAreaPerEachGridX(const int32_t index_grid_x);
  bool IsNewPuddle(const int32_t index_grid_x, const std::vector<float> &partial_sum_areas) const noexcept;
  static Slope InterpretSlope(const char c);
  static int32_t GetRelativeHeightOfRightFromLeft(const Slope &current_slope);

 private:
  int32_t number_of_grids_x_;
  GridInformation grids_[kMaxNumberOfGridX];

 private:
  FRIEND_TEST(Test_ALDS1_3_D_1, Load);                             // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_3_D_1, CalculateHighestHeightLeftSide);   // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_3_D_1, CalculateHighestHeightRightSide);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_3_D_1, CalculateAreaPerEachGridX);        // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_3_D_1, CalculateAreas);                   // Should be removed from production code
};

}  // namespace ALDS1_3_D_1

#endif  // SRC_C04_4_ALDS1_3_D_1_CROSS_SECTION_DIAGRAM_H_
