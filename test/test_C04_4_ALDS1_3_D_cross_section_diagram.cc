/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-6. データ構造の応用、面積計算のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C04_4_ALDS1_3_D_cross_section_diagram.h"

namespace ALDS1_3_D {

class Test_ALDS1_3_D : public ::testing::Test {
 protected:
  CrossSectionDiagram *diagram_;
  virtual void SetUp() {
    diagram_ = new CrossSectionDiagram();
  }
  virtual void TearDown() {
    delete diagram_;
  }
};

TEST_F(Test_ALDS1_3_D, Load) {
  std::ostringstream input_stream;
  input_stream << "\\\\__//" << std::endl;
  std::istringstream iss(input_stream.str());
  diagram_->Load(iss);

  ASSERT_EQ(6, diagram_->number_of_grids_x_);

  int32_t index_grid_x = 0;
  ASSERT_EQ(Slope::kFallingToRight, diagram_->grids_[index_grid_x].slope);
  ASSERT_EQ(0, diagram_->grids_[index_grid_x].height_left);
  ASSERT_EQ(-1, diagram_->grids_[index_grid_x].height_right);

  ++index_grid_x;
  ASSERT_EQ(Slope::kFallingToRight, diagram_->grids_[index_grid_x].slope);
  ASSERT_EQ(-1, diagram_->grids_[index_grid_x].height_left);
  ASSERT_EQ(-2, diagram_->grids_[index_grid_x].height_right);

  ++index_grid_x;
  ASSERT_EQ(Slope::kFlat, diagram_->grids_[index_grid_x].slope);
  ASSERT_EQ(-2, diagram_->grids_[index_grid_x].height_left);
  ASSERT_EQ(-2, diagram_->grids_[index_grid_x].height_right);

  ++index_grid_x;
  ASSERT_EQ(Slope::kFlat, diagram_->grids_[index_grid_x].slope);
  ASSERT_EQ(-2, diagram_->grids_[index_grid_x].height_left);
  ASSERT_EQ(-2, diagram_->grids_[index_grid_x].height_right);

  ++index_grid_x;
  ASSERT_EQ(Slope::kRisingToRight, diagram_->grids_[index_grid_x].slope);
  ASSERT_EQ(-2, diagram_->grids_[index_grid_x].height_left);
  ASSERT_EQ(-1, diagram_->grids_[index_grid_x].height_right);

  ++index_grid_x;
  ASSERT_EQ(Slope::kRisingToRight, diagram_->grids_[index_grid_x].slope);
  ASSERT_EQ(-1, diagram_->grids_[index_grid_x].height_left);
  ASSERT_EQ(0, diagram_->grids_[index_grid_x].height_right);
}

TEST_F(Test_ALDS1_3_D, CalculateHighestHeightLeftSide) {
  int32_t index_grid_x = 0;
  diagram_->grids_[index_grid_x].height_left = 0;
  diagram_->grids_[index_grid_x].height_right = -1;
  ++index_grid_x;
  diagram_->grids_[index_grid_x].height_left = -1;
  diagram_->grids_[index_grid_x].height_right = -2;
  ++index_grid_x;
  diagram_->grids_[index_grid_x].height_left = -2;
  diagram_->grids_[index_grid_x].height_right = -2;
  ++index_grid_x;
  diagram_->grids_[index_grid_x].height_left = -2;
  diagram_->grids_[index_grid_x].height_right = -1;
  diagram_->number_of_grids_x_ = index_grid_x + 1;
  ASSERT_EQ(4, diagram_->number_of_grids_x_);

  diagram_->CalculateHighestHeightLeftSide();

  index_grid_x = 0;
  ASSERT_EQ(0, diagram_->grids_[index_grid_x++].highest_height_leftside);
  ASSERT_EQ(0, diagram_->grids_[index_grid_x++].highest_height_leftside);
  ASSERT_EQ(0, diagram_->grids_[index_grid_x++].highest_height_leftside);
  ASSERT_EQ(0, diagram_->grids_[index_grid_x++].highest_height_leftside);
}

TEST_F(Test_ALDS1_3_D, CalculateHighestHeightRightSide) {
  int32_t index_grid_x = 0;
  diagram_->grids_[index_grid_x].height_left = 0;
  diagram_->grids_[index_grid_x].height_right = -1;
  ++index_grid_x;
  diagram_->grids_[index_grid_x].height_left = -1;
  diagram_->grids_[index_grid_x].height_right = -2;
  ++index_grid_x;
  diagram_->grids_[index_grid_x].height_left = -2;
  diagram_->grids_[index_grid_x].height_right = -2;
  ++index_grid_x;
  diagram_->grids_[index_grid_x].height_left = -2;
  diagram_->grids_[index_grid_x].height_right = -1;
  diagram_->number_of_grids_x_ = index_grid_x + 1;
  ASSERT_EQ(4, diagram_->number_of_grids_x_);

  diagram_->CalculateHighestHeightRightSide();

  index_grid_x = diagram_->number_of_grids_x_ - 1;
  ASSERT_EQ(-1, diagram_->grids_[diagram_->number_of_grids_x_ - 1].height_right);
  ASSERT_EQ(-2, diagram_->grids_[diagram_->number_of_grids_x_ - 1].height_left);
  ASSERT_EQ(-1, diagram_->grids_[index_grid_x--].highest_height_rightside);
  ASSERT_EQ(-1, diagram_->grids_[index_grid_x--].highest_height_rightside);
  ASSERT_EQ(-1, diagram_->grids_[index_grid_x--].highest_height_rightside);
  ASSERT_EQ(-1, diagram_->grids_[index_grid_x--].highest_height_rightside);
}

TEST_F(Test_ALDS1_3_D, CalculateAreaPerEachGridX) {
  int32_t index_grid_x = 5;
  GridInformation &cgrid = diagram_->grids_[index_grid_x];

  cgrid.height_left = 0;
  cgrid.height_right = 0;
  cgrid.highest_height_leftside = 0;
  cgrid.highest_height_rightside = 0;
  cgrid.slope = Slope::kFlat;
  ASSERT_FLOAT_EQ(0.0F, diagram_->CalculateAreaPerEachGridX(index_grid_x));

  cgrid.height_left = 0;
  cgrid.height_right = -1;
  cgrid.highest_height_leftside = 0;
  cgrid.highest_height_rightside = 0;
  cgrid.slope = Slope::kFallingToRight;
  ASSERT_FLOAT_EQ(0.5F, diagram_->CalculateAreaPerEachGridX(index_grid_x));

  cgrid.height_left = 0;
  cgrid.height_right = -1;
  cgrid.highest_height_leftside = 0;
  cgrid.highest_height_rightside = -1;
  cgrid.slope = Slope::kFallingToRight;
  ASSERT_FLOAT_EQ(0.0F, diagram_->CalculateAreaPerEachGridX(index_grid_x));

  cgrid.height_left = -1;
  cgrid.height_right = 0;
  cgrid.highest_height_leftside = 0;
  cgrid.highest_height_rightside = 0;
  cgrid.slope = Slope::kRisingToRight;
  ASSERT_FLOAT_EQ(0.5F, diagram_->CalculateAreaPerEachGridX(index_grid_x));

  cgrid.height_left = -1;
  cgrid.height_right = 0;
  cgrid.highest_height_leftside = -1;
  cgrid.highest_height_rightside = 0;
  cgrid.slope = Slope::kRisingToRight;
  ASSERT_FLOAT_EQ(0.0F, diagram_->CalculateAreaPerEachGridX(index_grid_x));

  cgrid.height_left = 0;
  cgrid.height_right = 0;
  cgrid.highest_height_leftside = 10;
  cgrid.highest_height_rightside = 10;
  cgrid.slope = Slope::kFlat;
  ASSERT_FLOAT_EQ(10.0F, diagram_->CalculateAreaPerEachGridX(index_grid_x));

  cgrid.height_left = 0;
  cgrid.height_right = 0;
  cgrid.highest_height_leftside = 10;
  cgrid.highest_height_rightside = 5;
  cgrid.slope = Slope::kFlat;
  ASSERT_FLOAT_EQ(5.0F, diagram_->CalculateAreaPerEachGridX(index_grid_x));

  cgrid.height_left = 0;
  cgrid.height_right = 0;
  cgrid.highest_height_leftside = 10;
  cgrid.highest_height_rightside = 0;
  cgrid.slope = Slope::kFlat;
  ASSERT_FLOAT_EQ(0.0F, diagram_->CalculateAreaPerEachGridX(index_grid_x));

  cgrid.height_left = -1;
  cgrid.height_right = 0;
  cgrid.highest_height_leftside = 10;
  cgrid.highest_height_rightside = 0;
  cgrid.slope = Slope::kRisingToRight;
  ASSERT_FLOAT_EQ(0.5F, diagram_->CalculateAreaPerEachGridX(index_grid_x));

  cgrid.height_left = 0;
  cgrid.height_right = -1;
  cgrid.highest_height_leftside = 10;
  cgrid.highest_height_rightside = -1;
  cgrid.slope = Slope::kFallingToRight;
  ASSERT_FLOAT_EQ(0.0F, diagram_->CalculateAreaPerEachGridX(index_grid_x));
}

TEST_F(Test_ALDS1_3_D, CalculateAreas) {
  int32_t index_grid_x = 0;
  diagram_->grids_[index_grid_x].height_left = 0;
  diagram_->grids_[index_grid_x].height_right = -1;
  diagram_->grids_[index_grid_x].slope = Slope::kFallingToRight;
  ++index_grid_x;
  diagram_->grids_[index_grid_x].height_left = -1;
  diagram_->grids_[index_grid_x].height_right = -2;
  diagram_->grids_[index_grid_x].slope = Slope::kFallingToRight;
  ++index_grid_x;
  diagram_->grids_[index_grid_x].height_left = -2;
  diagram_->grids_[index_grid_x].height_right = -2;
  diagram_->grids_[index_grid_x].slope = Slope::kFlat;
  ++index_grid_x;
  diagram_->grids_[index_grid_x].height_left = -2;
  diagram_->grids_[index_grid_x].height_right = -1;
  diagram_->grids_[index_grid_x].slope = Slope::kRisingToRight;
  diagram_->number_of_grids_x_ = index_grid_x + 1;
  ASSERT_EQ(4, diagram_->number_of_grids_x_);

  const float result = diagram_->CalculateAreas();

  index_grid_x = 0;
  ASSERT_EQ(0, diagram_->grids_[index_grid_x].highest_height_leftside);
  ASSERT_EQ(-1, diagram_->grids_[index_grid_x].highest_height_rightside);
  ASSERT_FLOAT_EQ(0.0F, diagram_->CalculateAreaPerEachGridX(index_grid_x));
  index_grid_x++;
  ASSERT_FLOAT_EQ(0.5F, diagram_->CalculateAreaPerEachGridX(index_grid_x));
  index_grid_x++;
  ASSERT_FLOAT_EQ(1.0F, diagram_->CalculateAreaPerEachGridX(index_grid_x));
  index_grid_x++;
  ASSERT_FLOAT_EQ(0.5F, diagram_->CalculateAreaPerEachGridX(index_grid_x));
  ASSERT_FLOAT_EQ(2.0F, result);
}

TEST_F(Test_ALDS1_3_D, Main_1) {
  std::ostringstream answer;
  answer << "35" << std::endl;
  answer << "5 4 2 1 19 9" << std::endl;

  std::ostringstream input_stream;
  input_stream << "\\\\///\\_/\\/\\\\\\\\/_/\\\\///__\\\\\\_\\\\/_\\/_/\\" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  diagram_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_3_D, Main_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;
  answer << "1 1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "_/\\//" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  diagram_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_3_D, Main_3) {
  std::ostringstream answer;
  answer << "25" << std::endl;
  answer << "4 1 20 1 3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "\\/\\\\\\_/\\\\//__\\/_/\\/\\__/" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  diagram_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_3_D
