/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part2. 導入問題、Maximum Profit。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C02_ALDS1_1_D_MAXIMUM_PROFIT_H_
#define SRC_C02_ALDS1_1_D_MAXIMUM_PROFIT_H_

#include <gtest/gtest_prod.h>

#include <cstdint>
#include <iostream>
namespace ALDS1_1_D {

constexpr int32_t kMaxCount = 200000;

class CurrencyRates {
 public:
  CurrencyRates() noexcept;
  ~CurrencyRates() noexcept;
  void MaximumProfit(std::istream& input_stream) noexcept;

 private:
  void LoadData(std::istream& input_stream);
  int32_t CalculateMaximumProfit() noexcept;
  int32_t CalculateIndexBuy() noexcept;
  int32_t CalculateIndexSell(const int32_t index_buy) noexcept;

 private:
  CurrencyRates(const CurrencyRates& obj) = delete;
  CurrencyRates& operator=(const CurrencyRates& rhs) = delete;
  CurrencyRates(CurrencyRates&& obj) = delete;
  CurrencyRates& operator=(CurrencyRates&& rhs) = delete;

 private:
  int32_t count_;
  int32_t rates_[kMaxCount];

 private:
  FRIEND_TEST(Test_ALDS1_1_D, LoadData_normal);    // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_1_D, LoadData_abnormal);  // Should be removed from production code
};
}  // namespace ALDS1_1_D
#endif  // SRC_C02_ALDS1_1_D_MAXIMUM_PROFIT_H_
