/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Grand Contest(AGC) 044-B. Joker.
 */

#include "src/D_AGC_044_B_joker.h"

#include <algorithm>

namespace AGC_044_B {

int CallMain(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);

  int32_t N;
  input_stream >> N;
  std::vector<int32_t> P(N * N);
  Solution* solution = new Solution(N);
  for (int32_t i = 0; i < N * N; ++i) {
    input_stream >> P[i];
  }
  const int64_t result = solution->CalculateNumberOfPairs(P);
  std::cout << result << std::endl;
  delete solution;

  return 0;
}

const int32_t neighbours[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

Solution::Solution(const int32_t N) noexcept : N_(N), number_of_dislike_(0) {
  audiences_ = std::vector<std::vector<Audience>>(N, std::vector<Audience>(N));

  for (int32_t row = 0; row < N; ++row) {
    UpdateDistance(Position(row, 0), 0);
    UpdateDistance(Position(row, N - 1), 0);
  }
  for (int32_t column = 0; column < N; ++column) {
    UpdateDistance(Position(0, column), 0);
    UpdateDistance(Position(N - 1, column), 0);
  }

  UpdateAllOfDistances();
}

int32_t Solution::CalculateNumberOfPairs(const std::vector<int32_t>& people_to_exit) noexcept {
  for (const int32_t person_number_to_exit : people_to_exit) {
    const Position position_to_exit = GetPosition(person_number_to_exit);
    ExitOneAudience(position_to_exit);
  }

  return number_of_dislike_;
}

void Solution::ExitOneAudience(const Position& position) noexcept {
  number_of_dislike_ += GetDistance(position);
  audiences_[position.first][position.second].exited = true;
  audiences_[position.first][position.second].distance_to_exit = GetDistanceWhenEmpty(position);
  q_.push(position);
  UpdateAllOfDistances();
}

void Solution::UpdateDistance(const Position& position, const int32_t distance) noexcept {
  if (GetDistance(position) > distance) {
    audiences_[position.first][position.second].distance_to_exit = distance;
    q_.push(position);
  }
}

void Solution::UpdateAllOfDistances() noexcept {
  while (q_.size() > 0) {
    const Position c_position = q_.front();
    const int32_t c_distance = GetDistance(c_position);
    q_.pop();
    for (const auto& next : neighbours) {
      const Position next_position = Position(c_position.first + next[0], c_position.second + next[1]);
      if (IsValidPosition(next_position)) {
        if (IsEmpty(c_position)) {
          UpdateDistance(next_position, c_distance);
        } else {
          UpdateDistance(next_position, c_distance + 1);
        }
      }
    }
  }
}

int32_t Solution::GetDistanceWhenEmpty(const Position& position) const noexcept {
  int32_t minimum_distance = INT32_MAX;
  for (const auto& neighbour : neighbours) {
    const Position neighbour_position = Position(position.first + neighbour[0], position.second + neighbour[1]);
    if (IsValidPosition(neighbour_position)) {
      const int32_t temp_distance =
          IsEmpty(neighbour_position) ? GetDistance(neighbour_position) : GetDistance(neighbour_position) + 1;
      minimum_distance = std::min(temp_distance, minimum_distance);
    } else {
      minimum_distance = 0;
    }
  }
  return minimum_distance;
}

Position Solution::GetPosition(const int32_t audience_number) const noexcept {
  return Position((audience_number - 1) / N_, (audience_number - 1) % N_);
}

bool Solution::IsValidPosition(const Position& position) const noexcept {
  return (position.first >= 0 && position.first < N_ && position.second >= 0 && position.second < N_);
}

bool Solution::IsEmpty(const Position& position) const noexcept {
  return audiences_[position.first][position.second].exited;
}

int32_t Solution::GetDistance(const Position& position) const noexcept {
  return audiences_[position.first][position.second].distance_to_exit;
}

void Solution::PrintDebug() const noexcept {
  for (int32_t row = 0; row < N_; ++row) {
    for (int32_t column = 0; column < N_; ++column) {
      std::cerr << " " << (audiences_[row][column].exited ? "o" : "x");
    }
    std::cerr << "\t";

    for (int32_t column = 0; column < N_; ++column) {
      std::cerr << " " << audiences_[row][column].distance_to_exit;
    }
    std::cerr << std::endl;
  }
  std::cerr << "**************************************" << std::endl;
}

}  // namespace AGC_044_B
