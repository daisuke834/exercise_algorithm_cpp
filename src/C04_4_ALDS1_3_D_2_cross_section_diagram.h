/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-6. データ構造の応用、面積計算。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C04_4_ALDS1_3_D_2_CROSS_SECTION_DIAGRAM_H_
#define SRC_C04_4_ALDS1_3_D_2_CROSS_SECTION_DIAGRAM_H_

#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace ALDS1_3_D_2 {

constexpr int32_t kMaxNumberOfGridX = 20000;

void CallCrossSectionDiagram(std::istream &input_stream) noexcept;

enum class Slope : int32_t { kFallingToRight = 0, kFlat, kRisingToRight };

struct Pond {
  int32_t left_x{0};
  int32_t area{0};
};

class CrossSectionDiagram {
 public:
  CrossSectionDiagram() noexcept;
  ~CrossSectionDiagram() noexcept;
  void LoadOneSlope(const char ch);
  void PrintAreas() noexcept;

 private:
  CrossSectionDiagram(const CrossSectionDiagram &obj) = delete;
  CrossSectionDiagram &operator=(const CrossSectionDiagram &rhs) = delete;
  CrossSectionDiagram(CrossSectionDiagram &&obj) = delete;
  CrossSectionDiagram &operator=(CrossSectionDiagram &&rhs) = delete;

  static Slope InterpretSlope(const char c);

 private:
  int32_t sum_of_areas_;
  int32_t current_x_position_;
  std::stack<int32_t> slopes_;
  std::stack<Pond> ponds_;
};

}  // namespace ALDS1_3_D_2

#endif  // SRC_C04_4_ALDS1_3_D_2_CROSS_SECTION_DIAGRAM_H_
