/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 165-B. ビット全探索(bit全探索).
 */

#ifndef SRC_D_ABC_167_C_BIT_SEARCH_H_
#define SRC_D_ABC_167_C_BIT_SEARCH_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace ABC_167_C {

constexpr int32_t kMaxNumberOfBooks = 12;
constexpr int32_t kMaxNumberOfAreas = 12;

void CallBitSearch(std::istream& input_stream) noexcept;

class BitSearch {
 public:
  BitSearch() noexcept;
  ~BitSearch() noexcept;
  void SetParameters(const int32_t number_of_books, const int32_t number_of_areas, const int32_t threshold) noexcept;
  void SetCostOfBook(const int32_t index_book, const int32_t cost) noexcept;
  void SetKnowledgeOfBook(const int32_t index_book, const int32_t area, const int32_t knowledge) noexcept;
  int32_t SearchMinimumCost() noexcept;

 private:
  int32_t number_of_books_;
  int32_t number_of_areas_;
  int32_t threshold_;
  int32_t cost_[kMaxNumberOfBooks];
  int32_t knowledge_[kMaxNumberOfBooks][kMaxNumberOfAreas];
};

}  // namespace ABC_167_C

#endif  // SRC_D_ABC_167_C_BIT_SEARCH_H_
