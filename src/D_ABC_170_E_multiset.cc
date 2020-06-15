/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 170-E. Smart Infants.
 */

#include "src/D_ABC_170_E_multiset.h"
#include <set>
#include <vector>

namespace D_ABC_170_E {

int CallMain(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int32_t number_of_children, Q;
  input_stream >> number_of_children >> Q;
  // const int32_t L = static_cast<int32_t>(T.length());
  std::vector<int32_t> rates(number_of_children + 1);
  std::vector<int32_t> current_kindergartens(number_of_children + 1);
  constexpr int32_t kNumberOfKindergartens = 2e5;
  std::vector<std::multiset<int32_t>> rates_of_each_kindergarten(kNumberOfKindergartens + 1);
  std::multiset<int32_t> super_children;

  constexpr int32_t kInvalid = INT32_MIN;

  auto GetMaxRate = [&](const int32_t kinder) -> int32_t {
    return ((rates_of_each_kindergarten[kinder].size() > 0U) ? *rates_of_each_kindergarten[kinder].rbegin() : kInvalid);
  };

  auto AddKindergartenToSupers = [&](const int32_t kinder) -> void {
    const int32_t strongest_rate = GetMaxRate(kinder);
    if (strongest_rate != kInvalid) {
      super_children.insert(strongest_rate);
    }
  };

  auto RemoveKindergartenFromSupers = [&](const int32_t kinder) -> void {
    const int32_t strongest_rate = GetMaxRate(kinder);
    if (strongest_rate != kInvalid) {
      super_children.erase(super_children.find(strongest_rate));
    }
  };

  auto AddChildToKindergarten = [&](const int32_t child, const int32_t kinder) -> void {
    RemoveKindergartenFromSupers(kinder);
    rates_of_each_kindergarten[kinder].insert(rates[child]);
    AddKindergartenToSupers(kinder);
    current_kindergartens[child] = kinder;
  };

  auto RemoveChildFromCurrentKindergarten = [&](const int32_t child) -> void {
    const int32_t kinder = current_kindergartens[child];
    const int32_t rate = rates[child];
    RemoveKindergartenFromSupers(kinder);
    rates_of_each_kindergarten[kinder].erase(rates_of_each_kindergarten[kinder].find(rate));
    AddKindergartenToSupers(kinder);
  };

  for (int32_t i = 1; i <= number_of_children; ++i) {
    int32_t kinder;
    input_stream >> rates[i] >> kinder;
    AddChildToKindergarten(i, kinder);
  }
  for (int32_t j = 0; j < Q; ++j) {
    int32_t child, new_kinder;
    input_stream >> child >> new_kinder;
    RemoveChildFromCurrentKindergarten(child);
    AddChildToKindergarten(child, new_kinder);
    std::cout << *super_children.begin() << std::endl;
  }

  return 0;
}

}  // namespace D_ABC_170_E
