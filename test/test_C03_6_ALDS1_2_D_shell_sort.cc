/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-6. 初等的整列、シェルソートのテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C03_6_ALDS1_2_D_shell_sort.h"

namespace ALDS1_2_D {
class Test_ALDS1_2_D : public ::testing::Test {
 protected:
  ShellSort *shell_sort_;
  virtual void SetUp() {
    shell_sort_ = new ShellSort();
  }
  virtual void TearDown() {
    delete shell_sort_;
  }
};

TEST_F(Test_ALDS1_2_D, LoadData_abnormal) {
  std::ostringstream input_stream;
  input_stream << kMaxArraySize + 1 << std::endl;
  std::istringstream iss(input_stream.str());
  ASSERT_ANY_THROW(shell_sort_->Load(iss));
}

TEST_F(Test_ALDS1_2_D, InsertionSort_gap_1) {
  constexpr int32_t kGap = 1;
  shell_sort_->count_ = 5;
  ASSERT_GT(kMaxArraySize, shell_sort_->count_);
  int32_t index = 0;
  shell_sort_->values_[index++] = 5;
  shell_sort_->values_[index++] = 1;
  shell_sort_->values_[index++] = 4;
  shell_sort_->values_[index++] = 3;
  shell_sort_->values_[index++] = 2;
  shell_sort_->InsertionSort(kGap);

  index = 0;
  ASSERT_EQ(1, shell_sort_->values_[index++]);
  ASSERT_EQ(2, shell_sort_->values_[index++]);
  ASSERT_EQ(3, shell_sort_->values_[index++]);
  ASSERT_EQ(4, shell_sort_->values_[index++]);
  ASSERT_EQ(5, shell_sort_->values_[index++]);
}

TEST_F(Test_ALDS1_2_D, InsertionSort_gap_2a) {
  constexpr int32_t kGap = 2;
  shell_sort_->count_ = 3;
  ASSERT_GT(kMaxArraySize, shell_sort_->count_);
  int32_t index = 0;
  shell_sort_->values_[index++] = 3;
  shell_sort_->values_[index++] = 2;
  shell_sort_->values_[index++] = 1;
  shell_sort_->InsertionSort(kGap);

  index = 0;
  EXPECT_EQ(1, shell_sort_->values_[index++]);
  EXPECT_EQ(2, shell_sort_->values_[index++]);
  EXPECT_EQ(3, shell_sort_->values_[index++]);
}

TEST_F(Test_ALDS1_2_D, InsertionSort_gap_2b) {
  constexpr int32_t kGap = 2;
  shell_sort_->count_ = 4;
  ASSERT_GT(kMaxArraySize, shell_sort_->count_);
  int32_t index = 0;
  shell_sort_->values_[index++] = 4;
  shell_sort_->values_[index++] = 3;
  shell_sort_->values_[index++] = 2;
  shell_sort_->values_[index++] = 1;
  shell_sort_->InsertionSort(kGap);

  index = 0;
  EXPECT_EQ(2, shell_sort_->values_[index++]);
  EXPECT_EQ(1, shell_sort_->values_[index++]);
  EXPECT_EQ(4, shell_sort_->values_[index++]);
  EXPECT_EQ(3, shell_sort_->values_[index++]);
}

TEST_F(Test_ALDS1_2_D, InsertionSort_gap_2c) {
  constexpr int32_t kGap = 2;
  shell_sort_->count_ = 5;
  ASSERT_GT(kMaxArraySize, shell_sort_->count_);
  int32_t index = 0;
  shell_sort_->values_[index++] = 5;
  shell_sort_->values_[index++] = 4;
  shell_sort_->values_[index++] = 3;
  shell_sort_->values_[index++] = 2;
  shell_sort_->values_[index++] = 1;
  shell_sort_->InsertionSort(kGap);

  index = 0;
  EXPECT_EQ(1, shell_sort_->values_[index++]);
  EXPECT_EQ(2, shell_sort_->values_[index++]);
  EXPECT_EQ(3, shell_sort_->values_[index++]);
  EXPECT_EQ(4, shell_sort_->values_[index++]);
  EXPECT_EQ(5, shell_sort_->values_[index++]);
}

TEST_F(Test_ALDS1_2_D, InsertionSort_gap_2d) {
  constexpr int32_t kGap = 2;
  shell_sort_->count_ = 5;
  ASSERT_GT(kMaxArraySize, shell_sort_->count_);
  int32_t index = 0;
  shell_sort_->values_[index++] = 2;
  shell_sort_->values_[index++] = 1;
  shell_sort_->values_[index++] = 4;
  shell_sort_->values_[index++] = 3;
  shell_sort_->values_[index++] = 5;
  shell_sort_->InsertionSort(kGap);

  index = 0;
  EXPECT_EQ(2, shell_sort_->values_[index++]);
  EXPECT_EQ(1, shell_sort_->values_[index++]);
  EXPECT_EQ(4, shell_sort_->values_[index++]);
  EXPECT_EQ(3, shell_sort_->values_[index++]);
  EXPECT_EQ(5, shell_sort_->values_[index++]);
}

TEST_F(Test_ALDS1_2_D, InsertionSort_gap_4a) {
  constexpr int32_t kGap = 4;
  shell_sort_->count_ = 5;
  ASSERT_GT(kMaxArraySize, shell_sort_->count_);
  int32_t index = 0;
  shell_sort_->values_[index++] = 5;
  shell_sort_->values_[index++] = 1;
  shell_sort_->values_[index++] = 4;
  shell_sort_->values_[index++] = 3;
  shell_sort_->values_[index++] = 2;
  shell_sort_->InsertionSort(kGap);

  index = 0;
  ASSERT_EQ(2, shell_sort_->values_[index++]);
  ASSERT_EQ(1, shell_sort_->values_[index++]);
  ASSERT_EQ(4, shell_sort_->values_[index++]);
  ASSERT_EQ(3, shell_sort_->values_[index++]);
  ASSERT_EQ(5, shell_sort_->values_[index++]);
}

TEST_F(Test_ALDS1_2_D, InsertionSort_gap_4b) {
  constexpr int32_t kGap = 4;
  shell_sort_->count_ = 4;
  ASSERT_GT(kMaxArraySize, shell_sort_->count_);
  int32_t index = 0;
  shell_sort_->values_[index++] = 5;
  shell_sort_->values_[index++] = 1;
  shell_sort_->values_[index++] = 4;
  shell_sort_->values_[index++] = 3;
  shell_sort_->InsertionSort(kGap);

  index = 0;
  ASSERT_EQ(5, shell_sort_->values_[index++]);
  ASSERT_EQ(1, shell_sort_->values_[index++]);
  ASSERT_EQ(4, shell_sort_->values_[index++]);
  ASSERT_EQ(3, shell_sort_->values_[index++]);
}

TEST_F(Test_ALDS1_2_D, SwapAndInsert) {
  constexpr int32_t kGap = 2;
  shell_sort_->count_ = 5;
  ASSERT_GT(kMaxArraySize, shell_sort_->count_);
  int32_t index = 0;
  shell_sort_->values_[index++] = 2;
  shell_sort_->values_[index++] = 1;
  shell_sort_->values_[index++] = 4;
  shell_sort_->values_[index++] = 3;
  shell_sort_->values_[index++] = 5;
  shell_sort_->SwapAndInsert(3, kGap);

  index = 0;
  EXPECT_EQ(2, shell_sort_->values_[index++]);
  EXPECT_EQ(1, shell_sort_->values_[index++]);
  EXPECT_EQ(4, shell_sort_->values_[index++]);
  EXPECT_EQ(3, shell_sort_->values_[index++]);
  EXPECT_EQ(5, shell_sort_->values_[index++]);
}

TEST_F(Test_ALDS1_2_D, MAIN_1) {
  std::ostringstream answer;
  answer << "2" << std::endl;
  answer << "4 1" << std::endl;
  answer << "3" << std::endl;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;
  answer << "4" << std::endl;
  answer << "5" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  shell_sort_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_2_D, MAIN_2) {
  std::ostringstream answer;
  answer << "2" << std::endl;
  answer << "4 1" << std::endl;
  answer << "3" << std::endl;
  answer << "1" << std::endl;
  answer << "2" << std::endl;
  answer << "3" << std::endl;
  answer << "4" << std::endl;
  answer << "5" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "5" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "4" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  shell_sort_->Main(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_2_D, CalculateGaps) {
  shell_sort_->count_ = 125;
  ASSERT_GT(kMaxArraySize, shell_sort_->count_);

  shell_sort_->CalculateGaps();

  EXPECT_EQ(125, shell_sort_->count_);
  EXPECT_EQ(5, shell_sort_->number_of_gaps_);
  EXPECT_EQ(1, shell_sort_->gaps_[0]);
  EXPECT_EQ(4, shell_sort_->gaps_[1]);
  EXPECT_EQ(13, shell_sort_->gaps_[2]);
  EXPECT_EQ(40, shell_sort_->gaps_[3]);
  EXPECT_EQ(121, shell_sort_->gaps_[4]);
  EXPECT_EQ(121, shell_sort_->gaps_[shell_sort_->number_of_gaps_ - 1]);
}

TEST_F(Test_ALDS1_2_D, ShellSort) {
  shell_sort_->count_ = 125;
  ASSERT_GT(kMaxArraySize, shell_sort_->count_);
  int32_t index = 0;
  shell_sort_->values_[index++] = 19381;
  shell_sort_->values_[index++] = 57930;
  shell_sort_->values_[index++] = 7480;
  shell_sort_->values_[index++] = 26604;
  shell_sort_->values_[index++] = 53386;
  shell_sort_->values_[index++] = 61359;
  shell_sort_->values_[index++] = 76207;
  shell_sort_->values_[index++] = 41954;
  shell_sort_->values_[index++] = 56079;
  shell_sort_->values_[index++] = 73702;
  shell_sort_->values_[index++] = 21365;
  shell_sort_->values_[index++] = 74453;
  shell_sort_->values_[index++] = 3732;
  shell_sort_->values_[index++] = 39836;
  shell_sort_->values_[index++] = 68432;
  shell_sort_->values_[index++] = 94563;
  shell_sort_->values_[index++] = 23017;
  shell_sort_->values_[index++] = 35107;
  shell_sort_->values_[index++] = 83583;
  shell_sort_->values_[index++] = 14910;
  shell_sort_->values_[index++] = 8467;
  shell_sort_->values_[index++] = 48116;
  shell_sort_->values_[index++] = 71546;
  shell_sort_->values_[index++] = 51719;
  shell_sort_->values_[index++] = 25528;
  shell_sort_->values_[index++] = 48071;
  shell_sort_->values_[index++] = 80107;
  shell_sort_->values_[index++] = 78256;
  shell_sort_->values_[index++] = 58520;
  shell_sort_->values_[index++] = 22353;
  shell_sort_->values_[index++] = 76528;
  shell_sort_->values_[index++] = 88154;
  shell_sort_->values_[index++] = 56430;
  shell_sort_->values_[index++] = 73477;
  shell_sort_->values_[index++] = 95048;
  shell_sort_->values_[index++] = 46520;
  shell_sort_->values_[index++] = 31204;
  shell_sort_->values_[index++] = 83414;
  shell_sort_->values_[index++] = 80810;
  shell_sort_->values_[index++] = 35719;
  shell_sort_->values_[index++] = 47925;
  shell_sort_->values_[index++] = 58298;
  shell_sort_->values_[index++] = 32131;
  shell_sort_->values_[index++] = 11701;
  shell_sort_->values_[index++] = 26709;
  shell_sort_->values_[index++] = 30751;
  shell_sort_->values_[index++] = 5022;
  shell_sort_->values_[index++] = 12817;
  shell_sort_->values_[index++] = 48652;
  shell_sort_->values_[index++] = 73924;
  shell_sort_->values_[index++] = 34695;
  shell_sort_->values_[index++] = 60471;
  shell_sort_->values_[index++] = 61153;
  shell_sort_->values_[index++] = 4625;
  shell_sort_->values_[index++] = 30978;
  shell_sort_->values_[index++] = 55616;
  shell_sort_->values_[index++] = 1142;
  shell_sort_->values_[index++] = 46597;
  shell_sort_->values_[index++] = 57088;
  shell_sort_->values_[index++] = 41732;
  shell_sort_->values_[index++] = 31917;
  shell_sort_->values_[index++] = 44404;
  shell_sort_->values_[index++] = 92743;
  shell_sort_->values_[index++] = 80395;
  shell_sort_->values_[index++] = 42749;
  shell_sort_->values_[index++] = 54407;
  shell_sort_->values_[index++] = 55936;
  shell_sort_->values_[index++] = 74302;
  shell_sort_->values_[index++] = 83767;
  shell_sort_->values_[index++] = 66045;
  shell_sort_->values_[index++] = 51563;
  shell_sort_->values_[index++] = 30340;
  shell_sort_->values_[index++] = 33398;
  shell_sort_->values_[index++] = 44896;
  shell_sort_->values_[index++] = 13051;
  shell_sort_->values_[index++] = 87807;
  shell_sort_->values_[index++] = 51767;
  shell_sort_->values_[index++] = 4997;
  shell_sort_->values_[index++] = 78978;
  shell_sort_->values_[index++] = 80650;
  shell_sort_->values_[index++] = 27809;
  shell_sort_->values_[index++] = 62330;
  shell_sort_->values_[index++] = 92360;
  shell_sort_->values_[index++] = 30716;
  shell_sort_->values_[index++] = 65161;
  shell_sort_->values_[index++] = 52293;
  shell_sort_->values_[index++] = 63209;
  shell_sort_->values_[index++] = 23753;
  shell_sort_->values_[index++] = 46098;
  shell_sort_->values_[index++] = 65130;
  shell_sort_->values_[index++] = 79634;
  shell_sort_->values_[index++] = 34543;
  shell_sort_->values_[index++] = 71889;
  shell_sort_->values_[index++] = 74088;
  shell_sort_->values_[index++] = 79031;
  shell_sort_->values_[index++] = 692;
  shell_sort_->values_[index++] = 20401;
  shell_sort_->values_[index++] = 68674;
  shell_sort_->values_[index++] = 72294;
  shell_sort_->values_[index++] = 15693;
  shell_sort_->values_[index++] = 91165;
  shell_sort_->values_[index++] = 71949;
  shell_sort_->values_[index++] = 38765;
  shell_sort_->values_[index++] = 57737;
  shell_sort_->values_[index++] = 82458;
  shell_sort_->values_[index++] = 841;
  shell_sort_->values_[index++] = 17048;
  shell_sort_->values_[index++] = 65943;
  shell_sort_->values_[index++] = 36229;
  shell_sort_->values_[index++] = 90215;
  shell_sort_->values_[index++] = 67389;
  shell_sort_->values_[index++] = 7209;
  shell_sort_->values_[index++] = 10388;
  shell_sort_->values_[index++] = 59754;
  shell_sort_->values_[index++] = 80243;
  shell_sort_->values_[index++] = 13501;
  shell_sort_->values_[index++] = 62271;
  shell_sort_->values_[index++] = 76516;
  shell_sort_->values_[index++] = 77564;
  shell_sort_->values_[index++] = 50277;
  shell_sort_->values_[index++] = 86912;
  shell_sort_->values_[index++] = 10005;
  shell_sort_->values_[index++] = 20611;
  shell_sort_->values_[index++] = 67212;
  shell_sort_->values_[index++] = 72782;

  shell_sort_->Sort();

  ASSERT_EQ(5, shell_sort_->number_of_gaps_);
  ASSERT_EQ(125, shell_sort_->count_);
  ASSERT_EQ(548, shell_sort_->swap_count_);
  ASSERT_EQ(1, shell_sort_->gaps_[0]);
  ASSERT_EQ(4, shell_sort_->gaps_[1]);
  ASSERT_EQ(13, shell_sort_->gaps_[2]);
  ASSERT_EQ(40, shell_sort_->gaps_[3]);
  ASSERT_EQ(121, shell_sort_->gaps_[4]);
  ASSERT_EQ(121, shell_sort_->gaps_[shell_sort_->number_of_gaps_ - 1]);
  index = 0;
  ASSERT_EQ(692, shell_sort_->values_[index++]);
  ASSERT_EQ(841, shell_sort_->values_[index++]);
  ASSERT_EQ(1142, shell_sort_->values_[index++]);
}

}  // namespace ALDS1_2_D
