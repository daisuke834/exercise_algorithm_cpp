/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 167-D. Teleporter.
 * graphの周期性を用いた解法。計算量はO(number_of_towns_)
 */

#include "src/D_ABC_167_D_1_teleporter_cycle.h"

namespace ABC_167_D_1 {

void CallTeleporter(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  Teleporter *teleporter = new Teleporter();

  int64_t number_of_towns, number_of_teleportations;
  input_stream >> number_of_towns >> number_of_teleportations;

  teleporter->SetNumberOfTowns(number_of_towns);
  for (int64_t from = 1; from <= number_of_towns; ++from) {
    int32_t to;
    input_stream >> to;
    teleporter->SetMapping(from, to);
  }

  constexpr int64_t kInitialTown = 1;
  const int64_t final_town = teleporter->SearchFinalTown(kInitialTown, number_of_teleportations);
  std::cout << final_town << std::endl;

  delete teleporter;
}

Teleporter::Teleporter() noexcept : number_of_towns_(0) {}

Teleporter::~Teleporter() noexcept {}

void Teleporter::SetNumberOfTowns(const int64_t number_of_towns) noexcept {
  number_of_towns_ = number_of_towns;
  for (int64_t i = 0; i <= number_of_towns; ++i) {
    visited_time_[i] = -1;
  }
}
void Teleporter::SetMapping(const int64_t from, const int64_t to) noexcept {
  ported_to_[from] = to;
}

int64_t Teleporter::SearchFinalTown(const int64_t start_town, const int64_t number_of_teleportations) noexcept {
  int64_t offset = -1;
  int64_t cycle = -1;
  int64_t c_town = start_town;
  visited_time_[start_town] = 0;
  for (int64_t i = 1; i <= number_of_towns_ + 1; ++i) {
    c_town = ported_to_[c_town];
    if (visited_time_[c_town] >= 0) {
      cycle = i - visited_time_[c_town];
      offset = visited_time_[c_town];
      break;
    }
    visited_time_[c_town] = i;
  }
  const int64_t modified_k = (number_of_teleportations > offset)
                                 ? ((number_of_teleportations - offset) % cycle) + offset
                                 : number_of_teleportations;
  c_town = start_town;
  for (int64_t i = 1; i <= modified_k; ++i) {
    c_town = ported_to_[c_town];
  }
  return c_town;
}

}  // namespace ABC_167_D_1
