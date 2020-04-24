/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part3-5. 初等的整列、安定なソート。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C03_5_ALDS1_2_C_stable_sort.h"
#include <iostream>
namespace ALDS1_2_C {

StableSort::StableSort() noexcept : bubble_sort_{}, selection_sort_{} {}

StableSort::~StableSort() noexcept {}

void StableSort::Main(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  try {
    Load(input_stream);
    Sort();
    Print();
  } catch (...) {
    std::cerr << "ERROR: Main()" << std::endl;
  }
}

void StableSort::Sort() noexcept {
  bubble_sort_.Sort();
  selection_sort_.Sort();
}

void StableSort::Load(std::istream &input_stream) {
  input_stream >> card_group_.count_;
  if (card_group_.count_ > kMaxArraySize) {
    std::cout << "kMaxArraySize is too small for the number of data count." << std::endl;
    throw 1;
  }
  for (int32_t index = 0; index < card_group_.count_; ++index) {
    input_stream >> card_group_.card_[index].suit >> card_group_.card_[index].value;
  }
  bubble_sort_.Load(card_group_);
  selection_sort_.Load(card_group_);
}

void StableSort::Print() const noexcept {
  bubble_sort_.Print();
  if (bubble_sort_.IsStable(card_group_)) {
    std::cout << "Stable" << std::endl;
  } else {
    std::cout << "Not stable" << std::endl;
  }
  selection_sort_.Print();
  if (selection_sort_.IsStable(card_group_)) {
    std::cout << "Stable" << std::endl;
  } else {
    std::cout << "Not stable" << std::endl;
  }
}

BubbleSort::BubbleSort() noexcept : card_group_{} {}

BubbleSort::~BubbleSort() noexcept {}

void BubbleSort::Sort() noexcept {
  bool should_scan = true;
  int32_t index_unsorted_head = 0;
  while (should_scan) {
    should_scan = false;
    for (int32_t index_target = card_group_.count_ - 1; index_target >= index_unsorted_head + 1; --index_target) {
      if (ShouldSwap(index_target)) {
        SwapWithLeftNext(index_target);
        should_scan = true;
      }
    }
    ++index_unsorted_head;
  }
}

bool BubbleSort::ShouldSwap(const int32_t index_target) noexcept {
  return (card_group_.card_[index_target - 1].value > card_group_.card_[index_target].value);
}

void BubbleSort::SwapWithLeftNext(const int32_t index_target) noexcept {
  const Card current_card = card_group_.card_[index_target];
  card_group_.card_[index_target] = card_group_.card_[index_target - 1];
  card_group_.card_[index_target - 1] = current_card;
}

void BubbleSort::Load(const CardGroup &card_group) noexcept {
  card_group_ = card_group;
}

void BubbleSort::Print() const noexcept {
  for (int32_t index = 0; index < card_group_.count_; ++index) {
    if (index != 0) {
      std::cout << " ";
    }
    std::cout << card_group_.card_[index].suit << card_group_.card_[index].value;
  }
  std::cout << std::endl;
}

bool BubbleSort::IsStable(const CardGroup &card_group_compare) const noexcept {
  for (int32_t i = 0; i < card_group_.count_; ++i) {
    for (int32_t j = i + 1; j < card_group_.count_; ++j) {
      for (int32_t a = 0; a < card_group_.count_; ++a) {
        for (int32_t b = a + 1; b < card_group_.count_; ++b) {
          if (IsSameValue(card_group_compare.card_[i], card_group_compare.card_[j])) {
            if (IsSameCard(card_group_compare.card_[i], card_group_.card_[b]) &&
                IsSameCard(card_group_compare.card_[j], card_group_.card_[a])) {
              return false;
            }
          }
        }
      }
    }
  }
  return true;
}

SelectionSort::SelectionSort() noexcept : card_group_{} {}

SelectionSort::~SelectionSort() noexcept {}

void SelectionSort::Sort() noexcept {
  for (int32_t index_unsorted_top = 0; index_unsorted_top < card_group_.count_; ++index_unsorted_top) {
    const int32_t index_minimum = FindMinimumIndex(index_unsorted_top);
    if (index_unsorted_top != index_minimum) {
      Swap(index_unsorted_top, index_minimum);
    }
  }
}

int32_t SelectionSort::FindMinimumIndex(int32_t index_unsorted_top) const noexcept {
  int32_t index_minimum = index_unsorted_top;
  for (int32_t index_scan = index_unsorted_top; index_scan < card_group_.count_; ++index_scan) {
    if (card_group_.card_[index_scan].value < card_group_.card_[index_minimum].value) {
      index_minimum = index_scan;
    }
  }
  return index_minimum;
}

void SelectionSort::Swap(const int32_t index_unsorted_top, const int32_t index_minimum) noexcept {
  const Card card_top = card_group_.card_[index_unsorted_top];
  card_group_.card_[index_unsorted_top] = card_group_.card_[index_minimum];
  card_group_.card_[index_minimum] = card_top;
}

void SelectionSort::Load(const CardGroup &card_group) noexcept {
  card_group_ = card_group;
}

void SelectionSort::Print() const noexcept {
  for (int32_t index = 0; index < card_group_.count_; ++index) {
    if (index != 0) {
      std::cout << " ";
    }
    std::cout << card_group_.card_[index].suit << card_group_.card_[index].value;
  }
  std::cout << std::endl;
}

bool SelectionSort::IsStable(const CardGroup &card_group) const noexcept {
  for (int32_t i = 0; i < card_group_.count_; ++i) {
    for (int32_t j = i + 1; j < card_group_.count_; ++j) {
      for (int32_t a = 0; a < card_group_.count_; ++a) {
        for (int32_t b = a + 1; b < card_group_.count_; ++b) {
          if (IsSameValue(card_group.card_[i], card_group.card_[j])) {
            if (IsSameCard(card_group.card_[i], card_group_.card_[b]) &&
                IsSameCard(card_group.card_[j], card_group_.card_[a])) {
              return false;
            }
          }
        }
      }
    }
  }
  return true;
}

bool IsSameCard(const Card &a, const Card &b) noexcept {
  return (a.suit == b.suit) && (a.value == b.value);
}
bool IsSameValue(const Card &a, const Card &b) noexcept {
  return (a.value == b.value);
}

}  // namespace ALDS1_2_C
