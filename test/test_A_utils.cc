/**
 * @copyright (c) 2020 Daisuke Hashimoto
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <list>
#include <sstream>
#include "src/utils.h"

namespace utils {
class Test_Utils : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_Utils, SplitStringToVector) {
  std::list<std::string> answers;
  answers.push_back("aa");
  answers.push_back("bb");
  answers.push_back("cc");
  answers.push_back("dd");

  const std::string src_text("aa bb cc dd");
  constexpr char kDelimiter = ' ';
  const std::vector<std::string> result = SplitStringToVector(src_text, kDelimiter);
  for (std::string elem : result) {
    const std::string canswer = answers.front();
    ASSERT_STREQ(canswer.c_str(), elem.c_str());
    answers.pop_front();
  }
}

TEST_F(Test_Utils, SplitStringToFloatVector) {
  std::list<float> answers;
  answers.push_back(1.3F);
  answers.push_back(6.3F);
  answers.push_back(0.0F);
  answers.push_back(-2.0F);

  const std::string src_text("1.3 6.3 0 -2");
  constexpr char kDelimiter = ' ';
  const std::vector<float> result = SplitStringToFloatVector(src_text, kDelimiter);
  for (float elem : result) {
    const float canswer = answers.front();
    ASSERT_EQ(canswer, elem);
    answers.pop_front();
  }
}

TEST_F(Test_Utils, CalculatePower) {
  ASSERT_EQ(0, CalculatePower(0, 1000000000LL));
  ASSERT_EQ(1, CalculatePower(1, 1000000000LL));
  ASSERT_EQ(1024, CalculatePower(2, 10));
  ASSERT_EQ(27, CalculatePower(3, 3));
  ASSERT_EQ(390625, CalculatePower(5, 8));
  ASSERT_EQ(891031477, CalculatePower(31, 8));
}

}  // namespace utils
