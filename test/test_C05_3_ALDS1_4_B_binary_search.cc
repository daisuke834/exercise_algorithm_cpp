/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-3. 探索、二分探索のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/C05_3_ALDS1_4_B_binary_search.h"

namespace ALDS1_4_B {

class Test_ALDS1_4_B : public ::testing::Test {
 protected:
  BinarySearch *binary_search_;
  virtual void SetUp() {
    binary_search_ = new BinarySearch();
  }
  virtual void TearDown() {
    delete binary_search_;
  }
};

TEST_F(Test_ALDS1_4_B, SearchTarget_1) {
  ASSERT_ANY_THROW(binary_search_->TargetIsIncludedInSource(0));
  ASSERT_EQ(0, binary_search_->SearchTarget());
  ASSERT_ANY_THROW(binary_search_->GetCenterIndex(0, 1));
}

TEST_F(Test_ALDS1_4_B, SearchTarget_2) {
  binary_search_->AddOneTarget(3);
  binary_search_->AddOneTarget(4);
  binary_search_->AddOneTarget(1);

  binary_search_->AddOneSource(1);
  binary_search_->AddOneSource(2);
  binary_search_->AddOneSource(3);
  binary_search_->AddOneSource(4);
  binary_search_->AddOneSource(5);

  ASSERT_EQ(3, binary_search_->SearchTarget());
}

TEST_F(Test_ALDS1_4_B, GetCenterIndex) {
  binary_search_->AddOneSource(1);
  binary_search_->AddOneSource(2);
  binary_search_->AddOneSource(3);
  binary_search_->AddOneSource(4);
  binary_search_->AddOneSource(5);

  ASSERT_EQ(0, binary_search_->GetCenterIndex(0, 0));
  ASSERT_EQ(0, binary_search_->GetCenterIndex(0, 1));
  ASSERT_EQ(1, binary_search_->GetCenterIndex(0, 2));
  ASSERT_ANY_THROW(binary_search_->GetCenterIndex(-1, 2));
  ASSERT_ANY_THROW(binary_search_->GetCenterIndex(2, kMaxNumberOfSources));
}

TEST_F(Test_ALDS1_4_B, GetTargetPosition) {
  binary_search_->AddOneSource(1);
  binary_search_->AddOneSource(2);
  binary_search_->AddOneSource(3);
  binary_search_->AddOneSource(4);
  binary_search_->AddOneSource(5);

  ASSERT_EQ(TargetPosition::kLeftSide, binary_search_->GetTargetPosition(1, 2));
  ASSERT_EQ(TargetPosition::kLeftSide, binary_search_->GetTargetPosition(2, 2));
  ASSERT_EQ(TargetPosition::kCenter, binary_search_->GetTargetPosition(3, 2));
  ASSERT_EQ(TargetPosition::kRightSide, binary_search_->GetTargetPosition(4, 2));
  ASSERT_EQ(TargetPosition::kRightSide, binary_search_->GetTargetPosition(5, 2));
}

TEST_F(Test_ALDS1_4_B, CallBinarySearch_1) {
  std::ostringstream answer;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "1 2 3 4 5" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "3 4 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallBinarySearch(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_4_B, CallBinarySearch_2) {
  std::ostringstream answer;
  answer << "8" << std::endl;

  std::ostringstream input_stream;
  input_stream << "20" << std::endl;
  input_stream << "0 0 0 1 1 2 2 3 3 3 3 5 6 6 6 8 8 9 9 9" << std::endl;
  input_stream << "10" << std::endl;
  input_stream << "9 6 2 4 0 5 1 3 7 8" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallBinarySearch(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_4_B, CallBinarySearch_4) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "4" << std::endl;
  input_stream << "0 1 2 3" << std::endl;
  input_stream << "1" << std::endl;
  input_stream << "2" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallBinarySearch(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_4_B
