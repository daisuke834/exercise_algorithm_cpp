/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode weekly-189-3. People Whose List of Favorite Companies Is Not a Subset of Another List.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/LeetCode/weekly/189_3_subsequence.h"

namespace LC_weekly_189_3 {

class Test_LC_weekly_189_3 : public ::testing::Test {
 protected:
  std::vector<std::vector<std::string>> inputs_;
  std::vector<int32_t> answers_;
  Solution* solution_;
  std::vector<std::string> temp_vec_;
  virtual void SetUp() {
    inputs_.clear();
    answers_.clear();
    temp_vec_.clear();
    solution_ = new Solution();
  }
  virtual void TearDown() { delete solution_; }
};

TEST_F(Test_LC_weekly_189_3, test_1) {
  temp_vec_.push_back("leetcode");
  temp_vec_.push_back("google");
  temp_vec_.push_back("facebook");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("google");
  temp_vec_.push_back("microsoft");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("google");
  temp_vec_.push_back("facebook");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("google");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("amazon");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  const std::vector<int> my_solution = solution_->peopleIndexes(inputs_);

  answers_.push_back(0);
  answers_.push_back(1);
  answers_.push_back(4);

  EXPECT_EQ(answers_.size(), my_solution.size());
  const int32_t min_length = std::min(static_cast<int32_t>(answers_.size()), static_cast<int32_t>(my_solution.size()));
  for (int32_t i = 0; i < min_length; ++i) {
    ASSERT_EQ(answers_[i], my_solution[i]);
  }
}

TEST_F(Test_LC_weekly_189_3, test_2) {
  // [["leetcode","google","facebook"],["leetcode","amazon"],["facebook","google"]]
  temp_vec_.push_back("leetcode");
  temp_vec_.push_back("google");
  temp_vec_.push_back("facebook");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("leetcode");
  temp_vec_.push_back("amazon");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("facebook");
  temp_vec_.push_back("google");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  const std::vector<int> my_solution = solution_->peopleIndexes(inputs_);

  answers_.push_back(0);
  answers_.push_back(1);

  EXPECT_EQ(answers_.size(), my_solution.size());
  const int32_t min_length = std::min(static_cast<int32_t>(answers_.size()), static_cast<int32_t>(my_solution.size()));
  for (int32_t i = 0; i < min_length; ++i) {
    ASSERT_EQ(answers_[i], my_solution[i]);
  }
}

TEST_F(Test_LC_weekly_189_3, test_3) {
  // [["leetcode"],["google"],["facebook"],["amazon"]]
  temp_vec_.push_back("leetcode");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("google");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("facebook");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("amazon");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  const std::vector<int> my_solution = solution_->peopleIndexes(inputs_);

  answers_.push_back(0);
  answers_.push_back(1);
  answers_.push_back(2);
  answers_.push_back(3);

  EXPECT_EQ(answers_.size(), my_solution.size());
  const int32_t min_length = std::min(static_cast<int32_t>(answers_.size()), static_cast<int32_t>(my_solution.size()));
  for (int32_t i = 0; i < min_length; ++i) {
    ASSERT_EQ(answers_[i], my_solution[i]);
  }
}

TEST_F(Test_LC_weekly_189_3, test_4) {
  temp_vec_.push_back("nxaqhyoprhlhvhyojanr");
  temp_vec_.push_back("ovqdyfqmlpxapbjwtssm");
  temp_vec_.push_back("qmsbphxzmnvflrwyvxlc");
  temp_vec_.push_back("udfuxjdxkxwqnqvgjjsp");
  temp_vec_.push_back("yawoixzhsdkaaauramvg");
  temp_vec_.push_back("zycidpyopumzgdpamnty");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("nxaqhyoprhlhvhyojanr");
  temp_vec_.push_back("ovqdyfqmlpxapbjwtssm");
  temp_vec_.push_back("udfuxjdxkxwqnqvgjjsp");
  temp_vec_.push_back("yawoixzhsdkaaauramvg");
  temp_vec_.push_back("zycidpyopumzgdpamnty");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  temp_vec_.push_back("ovqdyfqmlpxapbjwtssm");
  temp_vec_.push_back("qmsbphxzmnvflrwyvxlc");
  temp_vec_.push_back("udfuxjdxkxwqnqvgjjsp");
  temp_vec_.push_back("yawoixzhsdkaaauramvg");
  temp_vec_.push_back("zycidpyopumzgdpamnty");
  inputs_.push_back(temp_vec_);
  temp_vec_.clear();

  const std::vector<int> my_solution = solution_->peopleIndexes(inputs_);

  answers_.push_back(0);

  EXPECT_EQ(answers_.size(), my_solution.size());
  const int32_t min_length = std::min(static_cast<int32_t>(answers_.size()), static_cast<int32_t>(my_solution.size()));
  for (int32_t i = 0; i < min_length; ++i) {
    ASSERT_EQ(answers_[i], my_solution[i]);
  }
}

}  // namespace LC_weekly_189_3
