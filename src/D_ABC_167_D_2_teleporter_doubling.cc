/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 167-D. Doubling.
 * ダブリング(doubling)による解法。計算量はO(number_of_towns*log(number_of_teleportations))
 */

#include "src/D_ABC_167_D_2_teleporter_doubling.h"

namespace ABC_167_D_2 {

void CallTeleporter(std::istream &input_stream) noexcept {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  Doubling *teleporter = new Doubling();

  int64_t number_of_towns, number_of_teleportations;
  input_stream >> number_of_towns >> number_of_teleportations;

  teleporter->SetNumberOfTowns(number_of_towns);
  for (int64_t from = 0L; from < number_of_towns; ++from) {
    int64_t to_plus_1;
    input_stream >> to_plus_1;
    teleporter->SetMapping(from, to_plus_1 - 1L);
  }
  teleporter->CreateTable();

  constexpr int64_t kInitialTown = 1L - 1L;
  const int64_t final_town = teleporter->SearchFinalTown(kInitialTown, number_of_teleportations);
  std::cout << final_town + 1L << std::endl;

  delete teleporter;
}

Doubling::Doubling() noexcept : number_of_towns_(0L) {}

Doubling::~Doubling() noexcept {}

void Doubling::SetNumberOfTowns(const int64_t number_of_towns) noexcept {
  number_of_towns_ = number_of_towns;
}
void Doubling::SetMapping(const int64_t from, const int64_t to) noexcept {
  ported_to_[0L][from] = to;
}

void Doubling::CreateTable() noexcept {
  for (int64_t pow = 1LL; pow < kMaxLog; ++pow) {
    for (int64_t from = 0LL; from < kMaxNumberOfTowns; ++from) {
      const int64_t via = ported_to_[pow - 1LL][from];
      const int64_t to = ported_to_[pow - 1LL][via];
      ported_to_[pow][from] = to;
    }
  }
}

int64_t Doubling::SearchFinalTown(const int64_t start_town, const int64_t number_of_teleportations) noexcept {
  int64_t remaining_teleportations = number_of_teleportations;
  int64_t ctown = start_town;
  for (int64_t pow = kMaxLog - 1LL; pow >= 0LL; --pow) {
    int64_t powered = 1LL << pow;
    if (powered <= remaining_teleportations) {
      ctown = ported_to_[pow][ctown];
      remaining_teleportations -= powered;
    }
  }
  return ctown;
}

}  // namespace ABC_167_D_2
