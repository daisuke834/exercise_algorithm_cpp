/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part2. 導入問題、Maximum Profit。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "ALDS1_1_D_maximum_profit.h"
namespace ALDS1_1_D {
CurrencyRates::CurrencyRates() noexcept : count_(0), rates_{-1} {}

CurrencyRates::~CurrencyRates() noexcept {}

void CurrencyRates::MaximumProfit(std::istream& input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  try {
    LoadData(input_stream);
    const int32_t result = CalculateMaximumProfit();
    std::cout << result << std::endl;
  } catch (...) {
    std::cerr << "ERROR: MaximumProfit()" << std::endl;
  }
}

void CurrencyRates::LoadData(std::istream& input_stream) {
  input_stream >> count_;
  if (count_ > kMaxCount) {
    std::cout << "kMaxCount is too small for the number of data count." << std::endl;
    throw 1;
  }

  for (int32_t index = 0; index < count_; ++index) {
    input_stream >> rates_[index];
  }
}

int32_t CurrencyRates::CalculateMaximumProfit() noexcept {
  int32_t price_buy = rates_[0];
  int32_t max_profit = -2000000000;
  for (int32_t current_index = 1; current_index < count_; ++current_index) {
    const int32_t current_profit = rates_[current_index] - price_buy;
    max_profit = (current_profit > max_profit) ? current_profit : max_profit;
    price_buy = (rates_[current_index] < price_buy) ? rates_[current_index] : price_buy;
  }
  return max_profit;
}
}  // namespace ALDS1_1_D
