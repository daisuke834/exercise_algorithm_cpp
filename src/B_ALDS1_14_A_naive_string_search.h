/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief ALDS1_14_A. 文字列検索(String Search)、Naive String Search。計算量はO(N*M)。
 */

#ifndef SRC_B_ALDS1_14_A_NAIVE_STRING_SEARCH_H_
#define SRC_B_ALDS1_14_A_NAIVE_STRING_SEARCH_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_14_A {

void CallNaiveStringSearch(std::istream &input_stream);

void NaiveStringSearch(const std::string &text, const std::string &pattern);

}  // namespace ALDS1_14_A

#endif  // SRC_B_ALDS1_14_A_NAIVE_STRING_SEARCH_H_
