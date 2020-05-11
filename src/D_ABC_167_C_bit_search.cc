/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest 165-B. ビット全探索(bit全探索).
 */

#include "src/D_ABC_167_C_bit_search.h"

namespace ABC_167_C {

void CallBitSearch(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  BitSearch *bit_search = new BitSearch();

  std::ios::sync_with_stdio(false);
  int32_t number_of_books, number_of_areas, threshold;
  input_stream >> number_of_books >> number_of_areas >> threshold;
  bit_search->SetParameters(number_of_books, number_of_areas, threshold);

  for (int32_t book = 0; book < number_of_books; ++book) {
    int32_t cost;
    input_stream >> cost;
    bit_search->SetCostOfBook(book, cost);
    for (int32_t area = 0; area < number_of_areas; ++area) {
      int32_t knowledge;
      input_stream >> knowledge;
      bit_search->SetKnowledgeOfBook(book, area, knowledge);
    }
  }
  std::cout << bit_search->SearchMinimumCost() << std::endl;
  delete bit_search;
}

BitSearch::BitSearch() noexcept : number_of_books_(0), number_of_areas_(0), threshold_(0) {}

BitSearch::~BitSearch() noexcept {}

void BitSearch::SetParameters(const int32_t number_of_books, const int32_t number_of_areas,
                              const int32_t threshold) noexcept {
  number_of_books_ = number_of_books;
  number_of_areas_ = number_of_areas;
  threshold_ = threshold;
}

void BitSearch::SetCostOfBook(const int32_t index_book, const int32_t cost) noexcept {
  cost_[index_book] = cost;
}

void BitSearch::SetKnowledgeOfBook(const int32_t index_book, const int32_t area, const int32_t knowledge) noexcept {
  knowledge_[index_book][area] = knowledge;
}

int32_t BitSearch::SearchMinimumCost() noexcept {
  int32_t minimum_cost = INT32_MAX;
  for (int32_t s = 0; s < (1 << number_of_books_); ++s) {
    int32_t cost = 0;
    std::vector<int32_t> understandings(number_of_areas_);
    for (int32_t book = 0; book < number_of_books_; ++book) {
      if ((s >> book) & 1) {
        cost += cost_[book];
        for (int32_t area = 0; area < number_of_areas_; ++area) {
          understandings[area] += knowledge_[book][area];
        }
      }
    }
    bool ok = true;
    for (int32_t area = 0; area < number_of_areas_; ++area) {
      if (understandings[area] < threshold_) {
        ok = false;
        break;
      }
    }
    if (ok) {
      minimum_cost = std::min(minimum_cost, cost);
    }
  }
  if (minimum_cost == INT32_MAX) {
    minimum_cost = -1;
  }
  return minimum_cost;
}

}  // namespace ABC_167_C
