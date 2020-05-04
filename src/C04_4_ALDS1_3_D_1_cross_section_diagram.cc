/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-6. データ構造の応用、面積計算。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C04_4_ALDS1_3_D_1_cross_section_diagram.h"
#include <algorithm>
#include <iostream>
#include <string>
namespace ALDS1_3_D_1 {
constexpr float kAreaHalfGrid = 0.5F;
const float kEps = 0.00001F;

CrossSectionDiagram::CrossSectionDiagram() noexcept : number_of_grids_x_(0), grids_{} {}
CrossSectionDiagram::~CrossSectionDiagram() noexcept {}

void CrossSectionDiagram::Main(std::istream &input_stream) {
  try {
    Load(input_stream);
    const int32_t result = static_cast<int32_t>(CalculateAreas());
    std::cout << result << std::endl;

    std::vector<float> partial_sum_areas;
    for (int32_t index_grid_x = 0; index_grid_x < number_of_grids_x_; ++index_grid_x) {
      const float &c_area = grids_[index_grid_x].partial_area;
      if (IsNewPuddle(index_grid_x, partial_sum_areas)) {
        partial_sum_areas.push_back(c_area);
      } else {
        if (c_area > kEps) {
          partial_sum_areas[partial_sum_areas.size() - 1] += c_area;
        }
      }
    }
    std::cout << partial_sum_areas.size();
    for (int32_t index = 0; index < static_cast<int32_t>(partial_sum_areas.size()); ++index) {
      const int32_t result = static_cast<int32_t>(partial_sum_areas[index]);
      std::cout << " " << result;
    }
    std::cout << std::endl;
  } catch (...) {
    std::cerr << "ERROR: Main()" << std::endl;
    throw;
  }
}

void CrossSectionDiagram::Load(std::istream &input_stream) {
  try {
    int32_t current_height_left = 0;
    for (int32_t index_grid_x = 0; index_grid_x < kMaxNumberOfGridX; ++index_grid_x) {
      if (input_stream.eof()) {
        break;
      }
      char c;
      input_stream.get(c);
      if (c == '\n') {
        break;
      }
      ++number_of_grids_x_;
      GridInformation &cgrid = grids_[index_grid_x];
      cgrid.slope = InterpretSlope(c);
      cgrid.height_left = current_height_left;
      cgrid.height_right = cgrid.height_left + GetRelativeHeightOfRightFromLeft(cgrid.slope);
      current_height_left = cgrid.height_right;
    }
  } catch (...) {
    std::cerr << "ERROR: Load()" << std::endl;
    throw;
  }
}

static bool FloatEq(const float a, const float b) {
  return ((a < b + kEps) && (a > b - kEps));
}

bool CrossSectionDiagram::IsNewPuddle(const int32_t index_grid_x, const std::vector<float> &partial_sum_areas) const
    noexcept {
  bool is_new_puddle = false;
  if (partial_sum_areas.size() == 0 && grids_[index_grid_x].partial_area > kEps) {
    is_new_puddle = true;
  } else if (index_grid_x > 0) {
    if (FloatEq(0.0F, grids_[index_grid_x - 1].partial_area) && (!FloatEq(0.0F, grids_[index_grid_x].partial_area))) {
      is_new_puddle = true;
    } else if ((grids_[index_grid_x - 1].slope == Slope::kRisingToRight) &&
               (FloatEq(kAreaHalfGrid, grids_[index_grid_x - 1].partial_area)) &&
               (FloatEq(kAreaHalfGrid, grids_[index_grid_x].partial_area))) {
      is_new_puddle = true;
    }
  } else {
    is_new_puddle = false;
  }
  return is_new_puddle;
}

float CrossSectionDiagram::CalculateAreas() {
  float sum_area = 0.0F;
  try {
    CalculateHighestHeightLeftSide();
    CalculateHighestHeightRightSide();

    for (int32_t index_grid_x = 0; index_grid_x < number_of_grids_x_; ++index_grid_x) {
      sum_area += CalculateAreaPerEachGridX(index_grid_x);
    }
  } catch (...) {
    std::cerr << "ERROR: CalculateAreas()" << std::endl;
    throw;
  }
  return sum_area;
}

float CrossSectionDiagram::CalculateAreaPerEachGridX(const int32_t index_grid_x) {
  GridInformation &cgrid = grids_[index_grid_x];
  float &area = cgrid.partial_area;
  const int32_t lower_highest_height_each_side =
      std::min(cgrid.highest_height_leftside, cgrid.highest_height_rightside);
  switch (grids_[index_grid_x].slope) {
    case Slope::kFallingToRight:
      area = static_cast<float>(std::max(0, lower_highest_height_each_side - grids_[index_grid_x].height_left));
      if (cgrid.height_right < cgrid.highest_height_rightside) {
        area += kAreaHalfGrid;
      }
      break;
    case Slope::kRisingToRight:
      area = static_cast<float>(std::max(0, lower_highest_height_each_side - grids_[index_grid_x].height_right));
      if (cgrid.height_left < cgrid.highest_height_leftside) {
        area += kAreaHalfGrid;
      }
      break;
    case Slope::kFlat:
      area = static_cast<float>(std::max(0, lower_highest_height_each_side - grids_[index_grid_x].height_left));
      break;
    default:
      std::cerr << "ERROR: CalculateAreaPerEachGridX(): invalid current_slope." << std::endl;
      break;
  }
  return area;
}

void CrossSectionDiagram::CalculateHighestHeightLeftSide() noexcept {
  int32_t highest_height = grids_[0].height_left;
  for (int32_t index_grid = 0; index_grid < number_of_grids_x_; ++index_grid) {
    highest_height = std::max(highest_height, grids_[index_grid].height_left);
    grids_[index_grid].highest_height_leftside = highest_height;
  }
}

void CrossSectionDiagram::CalculateHighestHeightRightSide() noexcept {
  int32_t highest_height = grids_[number_of_grids_x_ - 1].height_right;
  for (int32_t index_grid = number_of_grids_x_ - 1; index_grid >= 0; --index_grid) {
    highest_height = std::max(highest_height, grids_[index_grid].height_right);
    grids_[index_grid].highest_height_rightside = highest_height;
  }
}

Slope CrossSectionDiagram::InterpretSlope(const char c) {
  Slope current_slope;
  switch (c) {
    case '\\':
      current_slope = Slope::kFallingToRight;
      break;
    case '/':
      current_slope = Slope::kRisingToRight;
      break;
    case '_':
      current_slope = Slope::kFlat;
      break;
    default:
      std::cerr << "ERROR: InterpretSlope(): invalid char." << std::endl;
      throw 1;
  }
  return current_slope;
}

int32_t CrossSectionDiagram::GetRelativeHeightOfRightFromLeft(const Slope &current_slope) {
  int32_t relative_height;
  switch (current_slope) {
    case Slope::kFallingToRight:
      relative_height = -1;
      break;
    case Slope::kRisingToRight:
      relative_height = 1;
      break;
    case Slope::kFlat:
      relative_height = 0;
      break;
    default:
      std::cerr << "ERROR: GetRelativeHeightOfRightFromLeft(): invalid current_slope." << std::endl;
      break;
  }
  return relative_height;
}

}  // namespace ALDS1_3_D_1
