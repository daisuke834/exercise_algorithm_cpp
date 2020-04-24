/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-3. 高等的整列、クイックソート(Quick Sort)。
 * 最悪計算時間=O(N^2), 平均計算時間=O(N*log(N)), 追加作業記憶領域=O(1). Stableでないsort.
 * 最悪計算時間は、pivotの選び方に依存。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C07_3_ALDS1_6_C_quick_sort.h"
#include <iostream>
#include <string>

namespace ALDS1_6_C {

void CallQuickSort(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  static Card original_cards[kMaxArraySize];
  QuickSort *quick_sort = new QuickSort();
  try {
    int32_t count;
    input_stream >> count;
    for (int32_t index = 0; index < count; ++index) {
      std::string card_symbol;
      int32_t card_number;
      input_stream >> card_symbol >> card_number;
      quick_sort->AddCard(card_symbol, card_number);
      Card ccard = ConvertCard(card_symbol, card_number);
      original_cards[index] = ccard;
    }
    quick_sort->Sort();
    const bool is_stable = quick_sort->IsStable(original_cards);
    if (is_stable) {
      std::cout << "Stable" << std::endl;
    } else {
      std::cout << "Not stable" << std::endl;
    }
    quick_sort->Print();
  } catch (...) {
    std::cerr << "ERROR: CallQuickSort()" << std::endl;
    throw;
  }
  delete quick_sort;
}

// ****************************************************

QuickSort::QuickSort() noexcept : size_(0), cards_{} {}
QuickSort::~QuickSort() noexcept {}

void QuickSort::AddCard(const std::string &symbol, const int32_t number) {
  if (size_ >= kMaxArraySize) {
    std::cerr << "ERROR: AddCard(): Data size exceeded a limit = " << kMaxArraySize << std::endl;
    throw 1;
  } else if (symbol.size() != 1) {
    std::cerr << "ERROR: AddCard(): Invalid input symbol. symbol = \"" << symbol << "\"" << std::endl;
    throw 1;
  } else {
    cards_[size_].symbol = symbol.c_str()[0];
    cards_[size_].number = number;
    size_++;
  }
}

void QuickSort::ResetData() noexcept {
  size_ = 0;
}

Card QuickSort::GetCard(const int32_t index) {
  if (IndexOutOfRange(index)) {
    std::cerr << "ERROR: GetCard(): Out of range: index = " << index << std::endl;
    throw 1;
  }
  return cards_[index];
}

void QuickSort::Sort() {
  try {
    ComputeQuickSort(0, size_ - 1);
  } catch (...) {
    std::cerr << "ERROR: Sort()" << std::endl;
    throw;
  }
}

void QuickSort::Print() const noexcept {
  char str[2];
  str[1] = '\0';
  for (int32_t index = 0; index < size_; ++index) {
    const Card card = cards_[index];
    str[0] = card.symbol;
    std::cout << str << " " << card.number << std::endl;
  }
}

void QuickSort::ComputeQuickSort(const int32_t start, const int32_t end) {
  try {
    if (start < end) {
      const int32_t index_pivot = ComputePartition(start, end);
      ComputeQuickSort(start, index_pivot - 1);
      ComputeQuickSort(index_pivot + 1, end);
    }
  } catch (...) {
    std::cerr << "ERROR: ComputeQuickSort()" << std::endl;
    throw;
  }
}

int32_t QuickSort::ComputePartition(const int32_t start, const int32_t end) {
  int32_t index_pivot = -1;
  if (IndexOutOfRange(start)) {
    std::cerr << "ERROR: ComputePartition(): Out of range: start = " << start << std::endl;
    throw 1;
  } else if (IndexOutOfRange(end)) {
    std::cerr << "ERROR: ComputePartition(): Out of range: end = " << end << std::endl;
    throw 1;
  } else {
    try {
      // より汎用性をもたせるには、endを使うのでは無くpivot_indexを外部から指定するようにするべき。
      const int32_t value_pivot = cards_[end].number;
      int32_t index_store = start;
      for (int32_t index_compare = start; index_compare < end; ++index_compare) {
        if (cards_[index_compare].number <= value_pivot) {
          Swap(index_compare, index_store);
          ++index_store;
        }
      }
      Swap(end, index_store);
      index_pivot = index_store;
    } catch (...) {
      std::cerr << "ERROR: ComputePartition()" << std::endl;
      throw;
    }
  }
  return index_pivot;
}

void QuickSort::Swap(const int32_t index_1, const int32_t index_2) {
  if ((IndexOutOfRange(index_1)) || (IndexOutOfRange(index_2))) {
    std::cerr << "ERROR: Swap(): Out of range: index_1=" << index_1 << ", index_2=" << index_2 << std::endl;
    throw 1;
  } else {
    const Card temp = cards_[index_2];
    cards_[index_2] = cards_[index_1];
    cards_[index_1] = temp;
  }
}

bool QuickSort::IndexOutOfRange(const int32_t index) const noexcept {
  return ((index) < 0 || (index >= size_));
}

bool QuickSort::IsStable(const Card cards_compare[kMaxArraySize]) const noexcept {
  for (int32_t index_sorted_1 = 0; index_sorted_1 < size_ - 1; ++index_sorted_1) {
    for (int32_t index_sorted_2 = index_sorted_1 + 1; index_sorted_2 < size_; ++index_sorted_2) {
      if (IsSameValue(cards_[index_sorted_1], cards_[index_sorted_2])) {
        for (int32_t index_original_1 = 0; index_original_1 < size_ - 1; ++index_original_1) {
          if (IsSameCard(cards_compare[index_original_1], cards_[index_sorted_2])) {
            for (int32_t index_original_2 = index_original_1; index_original_2 < size_; ++index_original_2) {
              if (IsSameCard(cards_compare[index_original_2], cards_[index_sorted_1])) {
                return false;
              }
            }
          }
        }
      } else {
        break;
      }
    }
  }
  return true;
}

bool IsSameCard(const Card &a, const Card &b) noexcept {
  return (a.symbol == b.symbol) && (a.number == b.number);
}
bool IsSameValue(const Card &a, const Card &b) noexcept {
  return (a.number == b.number);
}

Card ConvertCard(const std::string &symbol, const int32_t number) {
  if (symbol.size() != 1) {
    std::cerr << "ERROR: ConvertCard(): Invalid input symbol. symbol = \"" << symbol << "\"" << std::endl;
    throw 1;
  }
  Card ccard;
  ccard.symbol = symbol.c_str()[0];
  ccard.number = number;
  return ccard;
}

}  // namespace ALDS1_6_C
