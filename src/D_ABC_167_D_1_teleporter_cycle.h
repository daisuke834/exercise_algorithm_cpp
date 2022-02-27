/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 167-D. Teleporter.
 */

#ifndef SRC_D_ABC_167_D_1_TELEPORTER_CYCLE_H_
#define SRC_D_ABC_167_D_1_TELEPORTER_CYCLE_H_

#include <cstdint>
#include <iostream>
#include <string>

namespace ABC_167_D_1 {

constexpr int64_t kMaxNumberOfTowns = 200000;

void CallTeleporter(std::istream& input_stream) noexcept;

class Teleporter {
 public:
  Teleporter() noexcept;
  ~Teleporter() noexcept;
  void SetNumberOfTowns(const int64_t number_of_towns) noexcept;
  void SetMapping(const int64_t from, const int64_t to) noexcept;
  int64_t SearchFinalTown(const int64_t start_town, const int64_t number_of_teleportations) noexcept;

 private:
  int64_t number_of_towns_;
  int64_t ported_to_[kMaxNumberOfTowns + 1];
  int64_t visited_time_[kMaxNumberOfTowns + 1];
};

}  // namespace ABC_167_D_1

#endif  // SRC_D_ABC_167_D_1_TELEPORTER_CYCLE_H_
