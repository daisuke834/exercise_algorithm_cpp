/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Grand Contest(AGC) 044-B. Joker.
 */

#ifndef SRC_D_AGC_044_B_JOKER_H_
#define SRC_D_AGC_044_B_JOKER_H_

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace AGC_044_B {

int CallMain(std::istream& input_stream);

using Position = std::pair<int32_t, int32_t>;  // row, column

struct Audience {
  bool exited{false};
  int32_t distance_to_exit{INT32_MAX};
};

class Solution {
 public:
  Solution() = delete;
  explicit Solution(const int32_t N) noexcept;
  int32_t CalculateNumberOfPairs(const std::vector<int32_t>& people_to_exit) noexcept;

 private:
  void ExitOneAudience(const Position& position) noexcept;
  Position GetPosition(const int32_t audience_number) const noexcept;
  void UpdateDistance(const Position& position, const int32_t distance) noexcept;
  void UpdateAllOfDistances() noexcept;
  int32_t GetDistanceWhenEmpty(const Position& position) const noexcept;
  bool IsValidPosition(const Position& position) const noexcept;
  bool IsEmpty(const Position& position) const noexcept;
  int32_t GetDistance(const Position& position) const noexcept;
  void PrintDebug() const noexcept;

 private:
  int32_t N_;
  int32_t number_of_dislike_;
  std::vector<std::vector<Audience>> audiences_;
  std::queue<Position> q_;
};

}  // namespace AGC_044_B

#endif  // SRC_D_AGC_044_B_JOKER_H_
