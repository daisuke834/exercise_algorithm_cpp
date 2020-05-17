/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest 168-D. Dijkstra.
 */

#ifndef SRC_D_ABC_168_D_1_DIJKSTRA_H_
#define SRC_D_ABC_168_D_1_DIJKSTRA_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <queue>

namespace ABC_168_D_1 {

constexpr int64_t kMaxNumberOfTowns = 200000L;
constexpr int64_t kMaxLog = 60L;  // > log2(K)

void CallDijkstra(std::istream &input_stream) noexcept;

class Doubling {
 public:
  Doubling() noexcept;
  ~Doubling() noexcept;
  void SetNumberOfTowns(const int64_t number_of_towns) noexcept;
  void SetMapping(const int64_t from, const int64_t to) noexcept;
  void CreateTable() noexcept;
  int64_t SearchFinalTown(const int64_t start_town, const int64_t number_of_teleportations) noexcept;

 private:
  int64_t number_of_towns_;
  int64_t ported_to_[kMaxLog][kMaxNumberOfTowns];
};

}  // namespace ABC_168_D_1

#endif  // SRC_D_ABC_168_D_1_DIJKSTRA_H_
